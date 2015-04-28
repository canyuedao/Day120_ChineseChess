// 完成端口测试客户端.cpp : 定义控制台应用程序的入口点。
//
// socket练习.cpp : 定义控制台应用程序的入口点。
//
//#include"StdAfx.h"
#include<winsock2.h>
#include<stdio.h>
//#include "FKComposition.h"
#include "ChessGame.h"
#define TABLE_MAX 100
#pragma comment(lib,"ws2_32.lib")
//#pragma comment(lib,"winmm.lib")

// void CALLBACK LPTIMECALLBACKFUN2(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2){
// 	scanf("%s",sendBuf);
// 	send(sockClient,sendBuf,strlen(sendBuf)+1,0);
// };
// void CALLBACK LPTIMECALLBACKFUN(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2){
// 	recv(sockClient,recvBuf,100,0);
// 	printf("%s\n",recvBuf);
// };
int TableNumber=0;
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
	int StartKey;//开始
	int PeaceKey;//求和
	int GiveUp;  //认输
	int Regret;  //悔棋
	int exit;    //退出
	int yeskey;  //同意
	int nokey;   //不同意
	int iTable;  //桌号
	int iGameType;//游戏类型赋值为1
	int ID;      //玩家ID

	//int iJuge1;
};
//int iPersonID[2]={0};
int iaTable[TABLE_MAX]={0};
CChessGame *pChessGame=new CChessGame[TABLE_MAX];//虚拟的棋子
DWORD WINAPI WokerSever(LPVOID pthread1){
	//WaitForSingleObject(handle[0],INFINITE);
	sDataBag *pDataBag=new sDataBag;
	//printf("%d \n",pDataBag->exit);
	while(1)
	{
		recv((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
		pDataBag->iGameType=0;
		//printf("%d \n",pDataBag->iJudgeRedOrBlack);
		int i;
		for(i=0;i<TableNumber;i++)
		{
			if(iaTable[i]==pDataBag->iTable)
			{
				//if((pComposition+i)->pChessBoard->iPersonID[0]==0)
				//	(pComposition+i)->pChessBoard->iPersonID[0]=pDataBag->ID;
				//else if((pComposition+i)->pChessBoard->iPersonID[1]==0)
				//	(pComposition+i)->pChessBoard->iPersonID[1]=pDataBag->ID;
				//if((pComposition+i)->pChessBoard->iPersonID[0]!=0)
				{

					//else
					{
						pDataBag->iJuge=0;
						//if((pComposition+j)->pChessBoard->iStepNumber==8)
						//break;
						if(pDataBag->ID==(pChessGame+i)->iPersonID[0])
						{
							//pDataBag->ID=4;
							if((pChessGame+i)->mFindWay->MoveChess(pDataBag->y1,pDataBag->x1,pDataBag->y2,pDataBag->x2))
							{
								printf("朕准了\n");

								pDataBag->iJuge=1;
							}
							if((pChessGame+i)->iStepNumber%2==1)
								pDataBag->ChessBoardLock=0;
							else
								pDataBag->ChessBoardLock=1;
							//pDataBag->iJudgeRedOrBlack=1;
							send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
							printf("给红方发送消息: ");
							printf("棋子坐标\n");
							printf("%d ",pDataBag->y1);
							printf("%d ",pDataBag->x1);
							printf("%d ",pDataBag->y2);
							printf("%d ",pDataBag->x2);
							printf("%d ",pDataBag->iGameType);
							printf("%d ",pDataBag->iJuge);
							printf("%d \n",pDataBag->ID);
							/*************
							坐标带进去给电脑计算移动
							************/
							//pDataBag->ID=(pComposition+i)->pChessBoard->iPersonID[1];
							//pDataBag->x1=9-pDataBag->x1;
							//pDataBag->y1=8-pDataBag->y1;
							//pDataBag->x2=9-pDataBag->x2;
							//pDataBag->y2=8-pDataBag->y2;
							//pDataBag->iJudgeRedOrBlack=2;
							//if((pComposition+i)->pChessBoard->iStepNumber%2==1)
								//pDataBag->ChessBoardLock=1;  
							//else
								//pDataBag->ChessBoardLock=0;
							//send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
							//printf("给黑方发送消息: ");
							//printf("棋子坐标\n");
							//printf("%d ",pDataBag->x1);
							//printf("%d ",pDataBag->y1);
							//printf("%d ",pDataBag->x2);
							//printf("%d ",pDataBag->y2);
							//printf("%d ",pDataBag->iGameType);
							//printf("%d ",pDataBag->iJuge);
							//printf("%d \n",pDataBag->ID);
						}
						//条件改为如果轮到电脑移动棋子。
						if(pChessGame->iStepNumber%2==1)
						{
							//pDataBag->x1=9-pDataBag->x1;
							//pDataBag->y1=8-pDataBag->y1;
							//pDataBag->x2=9-pDataBag->x2; 
							//pDataBag->y2=8-pDataBag->y2; 
							//if((pComposition+i)->Composition(pDataBag->y1,pDataBag->x1,pDataBag->y2,pDataBag->x2))
							//{
								//printf("朕准了\n");
								//pDataBag->iJuge=1;
							//}
							//pDataBag->iJudgeRedOrBlack=2;
							//if((pComposition+i)->pChessBoard->iStepNumber%2==1)
							//	pDataBag->ChessBoardLock=1;
							//else
								//pDataBag->ChessBoardLock=0;
							//pDataBag->x1=9-pDataBag->x1;
							//pDataBag->y1=8-pDataBag->y1;
							//pDataBag->x2=9-pDataBag->x2; 
							//pDataBag->y2=8-pDataBag->y2;
							//send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
							//printf("给黑方发送消息: ");
							//printf("棋子坐标\n");
							//printf("%d ",pDataBag->x1);
							//printf("%d ",pDataBag->y1);
							//printf("%d ",pDataBag->x2);
							//printf("%d ",pDataBag->y2);
							//printf("%d ",pDataBag->iGameType);
							//printf("%d ",pDataBag->iJuge);
							//printf("%d \n",pDataBag->ID);
						    
							pDataBag->ID=(pChessGame+i)->iPersonID[0];
							pDataBag->iJuge=1;
							//pDataBag->iClientOperate1++;
		                    /*************
							坐标带进去给电脑计算移动，电脑走的棋子坐标写在。。。。。
							************/
							Moves *pmoves=&pChessGame->mFindWay->FindWay();
							pChessGame->mFindWay->MoveChess(pmoves);
							pDataBag->x1=pmoves->vec2.y;
							pDataBag->y1=pmoves->vec2.x;
							pDataBag->x2=pmoves->vec.y; 
							pDataBag->y2=pmoves->vec.x;
							//if((pComposition+i)->pChessBoard->iStepNumber%2==1)
								//pDataBag->ChessBoardLock=0;
							//else
								pDataBag->ChessBoardLock=1;
							//pDataBag->iJudgeRedOrBlack=1;
							send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
							printf("给红方发送消息: ");
							printf("棋子坐标\n");
							printf("%d ",pDataBag->y1);
							printf("%d ",pDataBag->x1);
							printf("%d ",pDataBag->y2);
							printf("%d ",pDataBag->x2);
							printf("%d ",pDataBag->iGameType);
							printf("%d ",pDataBag->iJuge);
							printf("%d \n",pDataBag->ID);
						}
						//if((pComposition+i)->pChessBoard->iStepNumber==8)
						//{
						//	(pComposition+i)->pChessBoard->ResetThisChessBoard();
						//	iaTable[i]=0;
						//}
					}
				}
				break;     
			}
		}
		if(i==TableNumber)
		{ 
			iaTable[TableNumber]=pDataBag->iTable;
			(pChessGame+TableNumber)->iPersonID[0]=pDataBag->ID;
			TableNumber++;
			//if(pDataBag->iJudgeRedOrBlack==0)
			{
				pDataBag->ID=(pChessGame+i)->iPersonID[0];
				pDataBag->ChessBoardLock=1;
				pDataBag->iJudgeRedOrBlack=1;
				send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
				printf("给红方发送消息: ");
				printf("%d \n",pDataBag->ChessBoardLock);
				//pDataBag->ID=(pComposition+i)->pChessBoard->iPersonID[1];
				//pDataBag->ChessBoardLock=0;
				//pDataBag->iJudgeRedOrBlack=2;
				//send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
				//printf("给黑方发送消息: ");
				//printf("%d \n",pDataBag->ChessBoardLock);
			}
		}
	}
	//pComposition->pChessBoard->FKChessBoard();
	delete pDataBag;
	//delete pComposition;
	return 0;
}
DWORD WINAPI fun2send(LPVOID pthread2){
	return 0;
}
void ttmain()
{
	WSADATA wsaData;
	SOCKET sockClient;//创建客户端套接字。
	SOCKADDR_IN addrServer;//服务端地址
	WSAStartup(MAKEWORD(2,2),&wsaData);
	//新建客户端socket
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	//定义要连接的服务端地址
	addrServer.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//目标IP(127.0.0.1是回送地址)
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(600);//连接端口6000
	//连接到服务端
	connect(sockClient,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));
	//发送数据

	sDataBag *pDataBag=new sDataBag;
	pDataBag->ID=3;
	pDataBag->iGameType=0;
	send(sockClient,(char *)pDataBag,sizeof(sDataBag),0);
	/*while(1)*///{
	printf("asdasd\n");
	HANDLE handle[2];
	//handle[1]=CreateThread(NULL,0,fun2send,(LPVOID)sockClient,0,NULL);
	//
	handle[0]=CreateThread(NULL,0,WokerSever,(LPVOID)sockClient,0,NULL);
	WaitForSingleObject(handle[0],INFINITE);
	// 	timeSetEvent(3000,1,LPTIMECALLBACKFUN2,10,1);
	// 	timeSetEvent(2000,1,LPTIMECALLBACKFUN,10,1);
	WaitForMultipleObjects(2,handle,TRUE,INFINITE);
	//send(sockClient,sendBuf,strlen(sendBuf)+1,0);
	//关闭socketr
	closesocket(sockClient);
	WSACleanup();
	Sleep(10000);
}





