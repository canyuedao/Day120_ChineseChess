// ��ɶ˿ڲ��Կͻ���.cpp : �������̨Ӧ�ó������ڵ㡣
//
// socket��ϰ.cpp : �������̨Ӧ�ó������ڵ㡣
//
//#include"StdAfx.h"
#include<winsock2.h>
#include<stdio.h>
#include "ChessGame.h"
//#include "FKComposition.h"
#define TABLE_MAX 100
#define MAX_NUMBER_OF_PROCESSING_BAG 1024
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

	int x1;//��ʼ�ĺ�����
	int y1;//��ʼ��������
	int x2;//����ĺ�����
	int y2;//�����������
	int iClientOperate1;//���ܣ��ͻ����Լ��õ�
	int iClientOperate2;//���ܣ��ͻ����Լ��õ�
	//int ChessBoardLock;//�����̣�����һ��ѡ���ƶ���ʱ����һ�����ܶ�����
	int iJuge;//�ƶ�����״ֵ̬���ж��ܷ��ƶ�����
	int win_lose;//�ж���Ӯ����ʱû�õ�
	int iJudgeRedOrBlack;//�жϺ췽���Ǻڷ�����Ҫ�ǿͻ��������ж������ĸ���¡����
	int StartKey;//��ʼ
	int PeaceKey;//���
	int GiveUp;  //����
	int Regret;  //����
	int exit;    //�˳�
	int yeskey;  //ͬ��
	int nokey;   //��ͬ��
	int iTable;  //����
	int iGameType;//��Ϸ���͸�ֵΪ1
	int ID;      //���ID
	int iCheck;
	//int iJuge1;
};
//int iPersonID[2]={0};
int iaTable[TABLE_MAX]={0};
int iHead=0;
int iRump=0;
sDataBag *pTransferDataBag=new sDataBag[MAX_NUMBER_OF_PROCESSING_BAG];
//FKComposition *pComposition=new FKComposition[TABLE_MAX];//���������
CChessGame *pChessGame=new CChessGame[TABLE_MAX];
DWORD WINAPI WokerSeverThread(LPVOID pthread1){
	//WaitForSingleObject(handle[0],INFINITE);
	sDataBag *pDataBag=new sDataBag;
	//printf("%d \n",pDataBag->exit);
	while(1)
	{
	recv((SOCKET)pthread1,(char *)(pDataBag),sizeof(sDataBag),0);
	printf("��%d����\n",iHead);
	iHead++;
	//*(pTransferDataBag+iHead)=*pDataBag;
	pDataBag->iGameType=0;
	//printf("%d \n",pDataBag->iJudgeRedOrBlack);
	int i;
	for(i=0;i<TableNumber;i++)
	{
		if(iaTable[i]==pDataBag->iTable)
		{
			if((pChessGame+i)->iPersonID[0]==0)
				(pChessGame+i)->iPersonID[0]=pDataBag->ID;
			else if((pChessGame+i)->iPersonID[1]==0)
				(pChessGame+i)->iPersonID[1]=pDataBag->ID;
			if((pChessGame+i)->iPersonID[1]!=0)
			{

				if(pDataBag->iJudgeRedOrBlack==0)
				{
					pDataBag->ID=(pChessGame+i)->iPersonID[0];
//					pDataBag->ChessBoardLock=1;
					pDataBag->iJudgeRedOrBlack=1;
					send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
					printf("���췽������Ϣ: ");
//					printf("%d \n",pDataBag->ChessBoardLock);
					pDataBag->ID=(pChessGame+i)->iPersonID[1];
//					pDataBag->ChessBoardLock=0;
					pDataBag->iJudgeRedOrBlack=2;
					send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
					printf("���ڷ�������Ϣ: ");
//					printf("%d \n",pDataBag->ChessBoardLock);
				}
				else
				{
					pDataBag->iJuge=0;
					pDataBag->iCheck=0;
					pDataBag->win_lose=0;
					//if((pComposition+j)->pChessBoard->iStepNumber==8)
					//break;
					if(pDataBag->ID==(pChessGame+i)->iPersonID[0])
					{
						//pDataBag->ID=4;
						if((pChessGame+i)->mFindWay->MoveChess(pDataBag->y1,pDataBag->x1,pDataBag->y2,pDataBag->x2))
						{
							printf("��׼��\n");

							pDataBag->iJuge=1;
							
							if((pChessGame+i)->GetRedChecked()){
								pDataBag->iCheck=1;
							}
							if((pChessGame+i)->mFindWay->GetRedDead())
							{
								pDataBag->win_lose=1;
								pDataBag->iJuge=0;
							}
						}
// 						if((pComposition+i)->pChessBoard->iStepNumber%2==1)
// 							pDataBag->ChessBoardLock=0;
// 						else
// 							pDataBag->ChessBoardLock=1;
						pDataBag->iJudgeRedOrBlack=1;
						send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
						printf("���췽������Ϣ: ");
						printf("��������\n");
						printf("%d ",pDataBag->x1);
						printf("%d ",pDataBag->y1);
						printf("%d ",pDataBag->x2);
						printf("%d ",pDataBag->y2);
						printf("%d ",pDataBag->iGameType);
						printf("%d ",pDataBag->iJuge);
						printf("%d \n",pDataBag->ID);
						pDataBag->ID=(pChessGame+i)->iPersonID[1];
						pDataBag->x1=9-pDataBag->x1;
						pDataBag->y1=8-pDataBag->y1;
						pDataBag->x2=9-pDataBag->x2;
						pDataBag->y2=8-pDataBag->y2;
						pDataBag->iJudgeRedOrBlack=2;
// 						if((pComposition+i)->pChessBoard->iStepNumber%2==1)
// //							pDataBag->ChessBoardLock=1;  
// 						else
// //							pDataBag->ChessBoardLock=0;
						send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
						printf("���ڷ�������Ϣ: ");
						printf("��������\n");
						printf("%d ",pDataBag->x1);
						printf("%d ",pDataBag->y1);
						printf("%d ",pDataBag->x2);
						printf("%d ",pDataBag->y2);
						printf("%d ",pDataBag->iGameType);
						printf("%d ",pDataBag->iJuge);
						printf("%d \n",pDataBag->ID);
					}
					else if(pDataBag->ID==(pChessGame+i)->iPersonID[1])
					{
						pDataBag->x1=9-pDataBag->x1;
						pDataBag->y1=8-pDataBag->y1;
						pDataBag->x2=9-pDataBag->x2; 
						pDataBag->y2=8-pDataBag->y2; 
						if((pChessGame+i)->mFindWay->MoveChess(pDataBag->y1,pDataBag->x1,pDataBag->y2,pDataBag->x2))
						{
							printf("��׼��\n");
							pDataBag->iJuge=1;
							pDataBag->win_lose=1;
							if((pChessGame+i)->GetRedChecked()){
								pDataBag->iCheck=1;
							}
							if((pChessGame+i)->mFindWay->GetBlackDead())
							{
								pDataBag->win_lose=1;
								pDataBag->iJuge=0;
							}
						}
						pDataBag->iJudgeRedOrBlack=2;
// 						if((pComposition+i)->pChessBoard->iStepNumber%2==1)
// //							pDataBag->ChessBoardLock=1;
// 						else
// //							pDataBag->ChessBoardLock=0;
						pDataBag->x1=9-pDataBag->x1;
						pDataBag->y1=8-pDataBag->y1;
						pDataBag->x2=9-pDataBag->x2; 
						pDataBag->y2=8-pDataBag->y2;
						send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
						printf("���ڷ�������Ϣ: ");
						printf("��������\n");
						printf("%d ",pDataBag->x1);
						printf("%d ",pDataBag->y1);
						printf("%d ",pDataBag->x2);
						printf("%d ",pDataBag->y2);
						printf("%d ",pDataBag->iGameType);
						printf("%d ",pDataBag->iJuge);
						printf("%d \n",pDataBag->ID);
						pDataBag->ID=(pChessGame+i)->iPersonID[0];
						pDataBag->x1=9-pDataBag->x1;
						pDataBag->y1=8-pDataBag->y1;
						pDataBag->x2=9-pDataBag->x2; 
						pDataBag->y2=8-pDataBag->y2;
// 						if((pComposition+i)->pChessBoard->iStepNumber%2==1)
// 							pDataBag->ChessBoardLock=0;
// 						else
// 							pDataBag->ChessBoardLock=1;
						pDataBag->iJudgeRedOrBlack=1;
						send((SOCKET)pthread1,(char *)pDataBag,sizeof(sDataBag),0);
						printf("���췽������Ϣ: ");
						printf("��������\n");
						printf("%d ",pDataBag->x1);
						printf("%d ",pDataBag->y1);
						printf("%d ",pDataBag->x2);
						printf("%d ",pDataBag->y2);
						printf("%d ",pDataBag->iGameType);
						printf("%d ",pDataBag->iJuge);
						printf("%d \n",pDataBag->ID);
					}
					if((pDataBag)->exit==1||pDataBag->win_lose)
					{
						printf("�Է��Ǹ���������\n");
						(pChessGame+i)->Reset();
						iaTable[i]=0;
					}
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
	}
	}
	//pComposition->pChessBoard->FKChessBoard();
	delete pDataBag;
	//delete pComposition;
	return 0;
}
DWORD WINAPI SendDataBagThread(LPVOID pthread2){
	return 0;
}
int main()
{
	WSADATA wsaData;
	SOCKET sockClient;//�����ͻ����׽��֡�
	SOCKADDR_IN addrServer;//����˵�ַ
	WSAStartup(MAKEWORD(2,2),&wsaData);
	//�½��ͻ���socket
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	//����Ҫ���ӵķ���˵�ַ
	addrServer.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//Ŀ��IP(127.0.0.1�ǻ��͵�ַ)
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(600);//���Ӷ˿�6000
	//���ӵ������
	connect(sockClient,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));
	//��������
	
	sDataBag *pDataBag=new sDataBag;
	pDataBag->ID=0;
	pDataBag->iGameType=0;
	send(sockClient,(char *)pDataBag,sizeof(sDataBag),0);
	/*while(1)*///{
		printf("%d\n",pDataBag->ID);
	HANDLE handle[2];
	//handle[1]=CreateThread(NULL,0,fun2send,(LPVOID)sockClient,0,NULL);
	//
	handle[0]=CreateThread(NULL,0,WokerSeverThread,(LPVOID)sockClient,0,NULL);
	handle[1]=CreateThread(NULL,0,SendDataBagThread,(LPVOID)sockClient,0,NULL);
	//WaitForSingleObject(handle[0],INFINITE);
	// 	timeSetEvent(3000,1,LPTIMECALLBACKFUN2,10,1);
	// 	timeSetEvent(2000,1,LPTIMECALLBACKFUN,10,1);
	WaitForMultipleObjects(2,handle,TRUE,INFINITE);
	//send(sockClient,sendBuf,strlen(sendBuf)+1,0);
	//�ر�socketr
	closesocket(sockClient);
	WSACleanup();
	Sleep(10000);
	return 0;
}