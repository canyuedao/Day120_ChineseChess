// chess.cpp : 定义控制台应用程序的入口点。
//
//红方的棋子：1,9表示车;2，8表示马;3,7表示象;4,6表示士;5表示帅;10,11表示炮;12，13，14，15，16表示兵;
//黑方的棋子：17,25表示车;18，24表示马;19,23表示象;20,22表示士;21表示将;26，27表示炮;28，29，30，31，32表示卒;
//#include "StdAfx.h"
//#include "FKComposition.h"
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <stdio.h>
#include "ChessGame.h"
#include "Player1.h"
#include "Player2.h"
#include "FindWay.h"
#define MAX_TABEL_NUMBER 2


struct sDataBag
{
	
	int x1;//起始的横坐标
	int y1;//起始的纵坐标
	int x2;//落棋的横坐标
	int y2;//落棋的纵坐标
	int iClientOperate1;//不管，客户端自己用的
	int iClientOperate2;//不管，客户端自己用的
	int ChessBoardLock;//锁棋盘，就是一方选棋移动的时候，另一方不能动棋盘
	int iJuge;//移动棋子状态值，判断能否移动棋子
	int win_lose;//判断输赢，暂时没用到
	int iJudgeRedOrBlack;//判断红方还是黑方，主要是客户端用来判定调用哪个克隆函数
	//int iJuge1;
};
struct sSocket
{
	SOCKET sockServerRed;//红方socket
	SOCKET sockServerBlack;//黑方socket
};
//FKComposition *pComposition=new FKComposition;//虚拟的棋子
CChessGame *pChessGame=new CChessGame();
//CPlayer1 *pPlayer1=new CPlayer1("Red");
//CPlayer2 *pPlayer2=new CPlayer2("Black");
//CFindWay *pFindWay=new CFindWay(pPlayer1,pPlayer2,pChessGame);
char *pReceiveBuffer=new char[sizeof(sDataBag)];//接收的缓冲区
DWORD WINAPI RedWorkThread(LPVOID pthread1);//红方线程，暂时就用这个线程
DWORD WINAPI BlackWorkThread(LPVOID pthread2);//暂时没用到这个线程
bool bPlayer1Move=true;//玩家锁，就是判断该哪个玩家移动就接收哪个玩家的数据包
//bool bPlayer2Move=false;
int tmain()
{
	//printf("%d",pComposition->pChessBoard->iaChessMan[9][2]);
	//printf(" %d",pComposition->pChessBoard->iaChessMan[7][4]);
	//if(pComposition->Composition(4,0,4,1))
	//	printf("移动之后：%d\n",pComposition->pChessBoard->iaChessMan[1][4]);
	//if(pComposition->Composition(2,9,4,7))
	//	printf("移动之后：%d\n",pComposition->pChessBoard->iaChessMan[7][4]);
	//if(pComposition->Composition(4,4,5,4))
	//	printf("移动之后：%d\n",pComposition->pChessBoard->iaChessMan[4][5]);
	//if(pComposition->Composition(1,9,2,7))
	//	printf("移动之后：%d\n",pComposition->pChessBoard->iaChessMan[7][2]);
	//if(pComposition->Composition(4,2,2,0))
	//	printf("移动之后：%d\n",pComposition->pChessBoard->iaChessMan[0][2]);
	//printf("有效步数: %d\n",pComposition->pChessBoard->iStepNumber);

	//初始化socket    begin
	WSADATA wsadata1;
	SOCKET sockListen;
	sSocket *pSocket=new sSocket;
	SOCKADDR_IN gotoroom2;
	WSAStartup(MAKEWORD(2,2),&wsadata1);
	sockListen=socket(AF_INET,SOCK_STREAM,0);

	SOCKADDR_IN gotoroom1;
	gotoroom1.sin_family=AF_INET;
	gotoroom1.sin_addr.s_addr=htonl(INADDR_ANY);
	gotoroom1.sin_port=htons(600);

	bind(sockListen,(SOCKADDR*)&gotoroom1,sizeof(gotoroom1));
	listen(sockListen,100);
	int len=sizeof(SOCKADDR);

	//初始化socekt  end
	//红方socket连接进来
	pSocket->sockServerRed=accept(sockListen,(SOCKADDR*)&gotoroom2,&len);
	printf("移动之前,红方连接进来了\n"); 
	//红方的代码

	
	//黑方socekt连接进来
	pSocket->sockServerBlack=accept(sockListen,(SOCKADDR*)&gotoroom2,&len);
	printf("移动之前,黑方连接进来了\n"); 
	//黑方的代码

	HANDLE handle[2];
	//暂时只用一个线程，懒得改
	handle[0]=CreateThread(NULL,0,RedWorkThread,(void *)pSocket,0,NULL);
	//handle[1]=CreateThread(NULL,0,BlackWorkThread,(void *)sockServerBlack,0,NULL);
	WaitForMultipleObjects(2,handle,TRUE,INFINITE);
	//closesocket(pSocket->sockServerBlack);
	//closesocket(pSocket->sockServerRed);
	//delete pSocket;
	//CloseHandle(handle[0]);
	//CloseHandle(handle[1]);
	while(1);
	return 0;
}
DWORD WINAPI RedWorkThread(LPVOID pthread1)
{
	//sDataBag *pDataBag=new sDataBag;
	//缓冲区清0
	memset(pReceiveBuffer,0,sizeof(sDataBag));
	//将克隆判定变量改成相应的值发给客户端。注：这个在移动之前就发
	*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJudgeRedOrBlack))=1;
	*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=1;
	//pDataBag->iJudgeRedOrBlack=1;
	send((SOCKET)((sSocket *)pthread1)->sockServerRed,pReceiveBuffer,sizeof(sDataBag),0);


	*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJudgeRedOrBlack))=2;
	*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=0;
	//pDataBag->iJudgeRedOrBlack=-1;
	//pReceiveBuffer=(char *)pDataBag;
	send((SOCKET)((sSocket *)pthread1)->sockServerBlack,pReceiveBuffer,sizeof(sDataBag),0);
	while(1)
	{
		
		int iCloseStatus;//这个是用来判断客户端断开链接的
		//轮到接收红方的数据包
		if(bPlayer1Move)
		{
		iCloseStatus=recv((SOCKET)((sSocket *)pthread1)->sockServerRed,pReceiveBuffer,sizeof(sDataBag),0);
		}
		//轮到接收黑方的数据包，这里要改相应的坐标
		else
		{
		iCloseStatus=recv((SOCKET)((sSocket *)pthread1)->sockServerBlack,pReceiveBuffer,sizeof(sDataBag),0);
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1))=8-*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1))=9-*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2))=8-*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2))=9-*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2));
		}
		if(iCloseStatus==-1)//是否掉线
		{
			if(pChessGame)//回收空间
			{
			
			delete pChessGame;
			pChessGame=NULL;
			delete []pReceiveBuffer;
			}
			return 0;//跳出无限循环
		}
		printf("棋子坐标\n");
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge)));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge))=0;//返回0，表示不能移动
		CChess *pchess=pChessGame->mChessBoard->GetPosition((int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)),*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)))->mPChess;
		Vector2 *pvec2=pChessGame->mChessBoard->GetPosition((int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)),(int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)));
		//Moves *pmoves=new Moves(pvec2,pchess);
		//if(pFindWay->MoveChess((int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)) ,*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)), (int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)),(int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)),"Red"))
		if(pChessGame->mFindWay->MoveChess(0,0,0,0))
		{
			printf("\n朕准了");
			*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge))=1;//移动成功，返回1
			bPlayer1Move=!bPlayer1Move;//改变锁的状态
			pChessGame->mFindWay->mPlayer1->SetIsChoosingChess(bPlayer1Move);
			pChessGame->mFindWay->mPlayer2->SetIsChoosingChess(!bPlayer1Move);
			//*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))^=1;
			//if(*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))==1)
			//	*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=0;
			//else
			//	*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=1;
		}
		printf("\n%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)));
		printf("%d\n",*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge)));
		//*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))^=1;
		//if(*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))==1)
		//	*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=0;
		//else
		//	*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=1;
		if(pChessGame->iStepNumber%2==1)//这个是有效地步数
			*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=0;
		else
			*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=1;//棋盘锁为1表示能移动
		send((SOCKET)((sSocket *)pthread1)->sockServerRed,pReceiveBuffer,sizeof(sDataBag),0);
		printf("红方收到消息了\n");

		*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1))=8-*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1))=9-*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2))=8-*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2))=9-*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2));
		//*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))^=1;
		//if(*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))==1)
		//	*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=0;
		//else
		//	*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=1;
		if(pChessGame->iStepNumber%2==1)
			*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=1;
		else
			*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=0;
		send((SOCKET)((sSocket *)pthread1)->sockServerBlack,pReceiveBuffer,sizeof(sDataBag),0);
		printf("黑方收到消息了\n");
	}
	return 0;
}
//DWORD WINAPI BlackWorkThread(LPVOID pthread2)
//{
//	while(1)
//	{
//		if(1){
//		int iCloseStatus;
//		iCloseStatus=recv((SOCKET)pthread2,pReceiveBuffer,sizeof(sDataBag),0);
//		if(iCloseStatus==-1)
//		{
//			if(pComposition)
//			{
//			delete pComposition;
//			pComposition=NULL;
//			delete []pReceiveBuffer;
//			}
//			return 0;
//		}
//		printf("棋子坐标\n");
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge)));
//		*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge))=0;
//		if(pComposition->Composition((int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)) ,*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)), (int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)),(int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2))))
//		{
//			printf("\n朕准了");
//			*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge))=1;
//		}
//		printf("\n%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge)));
//		bPlayer1Move=false;
//		}
//		send((SOCKET)pthread2,pReceiveBuffer,sizeof(sDataBag),0);
//		//bPlayer2Move=true;
//	}
//	return 0;
//}
