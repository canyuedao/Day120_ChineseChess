// chess.cpp : �������̨Ӧ�ó������ڵ㡣
//
//�췽�����ӣ�1,9��ʾ��;2��8��ʾ��;3,7��ʾ��;4,6��ʾʿ;5��ʾ˧;10,11��ʾ��;12��13��14��15��16��ʾ��;
//�ڷ������ӣ�17,25��ʾ��;18��24��ʾ��;19,23��ʾ��;20,22��ʾʿ;21��ʾ��;26��27��ʾ��;28��29��30��31��32��ʾ��;
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
	
	int x1;//��ʼ�ĺ�����
	int y1;//��ʼ��������
	int x2;//����ĺ�����
	int y2;//�����������
	int iClientOperate1;//���ܣ��ͻ����Լ��õ�
	int iClientOperate2;//���ܣ��ͻ����Լ��õ�
	int ChessBoardLock;//�����̣�����һ��ѡ���ƶ���ʱ����һ�����ܶ�����
	int iJuge;//�ƶ�����״ֵ̬���ж��ܷ��ƶ�����
	int win_lose;//�ж���Ӯ����ʱû�õ�
	int iJudgeRedOrBlack;//�жϺ췽���Ǻڷ�����Ҫ�ǿͻ��������ж������ĸ���¡����
	//int iJuge1;
};
struct sSocket
{
	SOCKET sockServerRed;//�췽socket
	SOCKET sockServerBlack;//�ڷ�socket
};
//FKComposition *pComposition=new FKComposition;//���������
CChessGame *pChessGame=new CChessGame();
//CPlayer1 *pPlayer1=new CPlayer1("Red");
//CPlayer2 *pPlayer2=new CPlayer2("Black");
//CFindWay *pFindWay=new CFindWay(pPlayer1,pPlayer2,pChessGame);
char *pReceiveBuffer=new char[sizeof(sDataBag)];//���յĻ�����
DWORD WINAPI RedWorkThread(LPVOID pthread1);//�췽�̣߳���ʱ��������߳�
DWORD WINAPI BlackWorkThread(LPVOID pthread2);//��ʱû�õ�����߳�
bool bPlayer1Move=true;//������������жϸ��ĸ�����ƶ��ͽ����ĸ���ҵ����ݰ�
//bool bPlayer2Move=false;
int tmain()
{
	//printf("%d",pComposition->pChessBoard->iaChessMan[9][2]);
	//printf(" %d",pComposition->pChessBoard->iaChessMan[7][4]);
	//if(pComposition->Composition(4,0,4,1))
	//	printf("�ƶ�֮��%d\n",pComposition->pChessBoard->iaChessMan[1][4]);
	//if(pComposition->Composition(2,9,4,7))
	//	printf("�ƶ�֮��%d\n",pComposition->pChessBoard->iaChessMan[7][4]);
	//if(pComposition->Composition(4,4,5,4))
	//	printf("�ƶ�֮��%d\n",pComposition->pChessBoard->iaChessMan[4][5]);
	//if(pComposition->Composition(1,9,2,7))
	//	printf("�ƶ�֮��%d\n",pComposition->pChessBoard->iaChessMan[7][2]);
	//if(pComposition->Composition(4,2,2,0))
	//	printf("�ƶ�֮��%d\n",pComposition->pChessBoard->iaChessMan[0][2]);
	//printf("��Ч����: %d\n",pComposition->pChessBoard->iStepNumber);

	//��ʼ��socket    begin
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

	//��ʼ��socekt  end
	//�췽socket���ӽ���
	pSocket->sockServerRed=accept(sockListen,(SOCKADDR*)&gotoroom2,&len);
	printf("�ƶ�֮ǰ,�췽���ӽ�����\n"); 
	//�췽�Ĵ���

	
	//�ڷ�socekt���ӽ���
	pSocket->sockServerBlack=accept(sockListen,(SOCKADDR*)&gotoroom2,&len);
	printf("�ƶ�֮ǰ,�ڷ����ӽ�����\n"); 
	//�ڷ��Ĵ���

	HANDLE handle[2];
	//��ʱֻ��һ���̣߳����ø�
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
	//��������0
	memset(pReceiveBuffer,0,sizeof(sDataBag));
	//����¡�ж������ĳ���Ӧ��ֵ�����ͻ��ˡ�ע��������ƶ�֮ǰ�ͷ�
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
		
		int iCloseStatus;//����������жϿͻ��˶Ͽ����ӵ�
		//�ֵ����պ췽�����ݰ�
		if(bPlayer1Move)
		{
		iCloseStatus=recv((SOCKET)((sSocket *)pthread1)->sockServerRed,pReceiveBuffer,sizeof(sDataBag),0);
		}
		//�ֵ����պڷ������ݰ�������Ҫ����Ӧ������
		else
		{
		iCloseStatus=recv((SOCKET)((sSocket *)pthread1)->sockServerBlack,pReceiveBuffer,sizeof(sDataBag),0);
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1))=8-*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1))=9-*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2))=8-*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2))=9-*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2));
		}
		if(iCloseStatus==-1)//�Ƿ����
		{
			if(pChessGame)//���տռ�
			{
			
			delete pChessGame;
			pChessGame=NULL;
			delete []pReceiveBuffer;
			}
			return 0;//��������ѭ��
		}
		printf("��������\n");
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)));
		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge)));
		*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge))=0;//����0����ʾ�����ƶ�
		CChess *pchess=pChessGame->mChessBoard->GetPosition((int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)),*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)))->mPChess;
		Vector2 *pvec2=pChessGame->mChessBoard->GetPosition((int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)),(int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)));
		//Moves *pmoves=new Moves(pvec2,pchess);
		//if(pFindWay->MoveChess((int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)) ,*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)), (int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)),(int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)),"Red"))
		if(pChessGame->mFindWay->MoveChess(0,0,0,0))
		{
			printf("\n��׼��");
			*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge))=1;//�ƶ��ɹ�������1
			bPlayer1Move=!bPlayer1Move;//�ı�����״̬
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
		if(pChessGame->iStepNumber%2==1)//�������Ч�ز���
			*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=0;
		else
			*(pReceiveBuffer+(int)&(((sDataBag *)0)->ChessBoardLock))=1;//������Ϊ1��ʾ���ƶ�
		send((SOCKET)((sSocket *)pthread1)->sockServerRed,pReceiveBuffer,sizeof(sDataBag),0);
		printf("�췽�յ���Ϣ��\n");

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
		printf("�ڷ��յ���Ϣ��\n");
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
//		printf("��������\n");
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)));
//		printf("%d ",*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge)));
//		*(pReceiveBuffer+(int)&(((sDataBag *)0)->iJuge))=0;
//		if(pComposition->Composition((int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y1)) ,*(pReceiveBuffer+(int)&(((sDataBag *)0)->x1)), (int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->y2)),(int)*(pReceiveBuffer+(int)&(((sDataBag *)0)->x2))))
//		{
//			printf("\n��׼��");
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
