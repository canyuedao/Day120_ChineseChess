// chess.cpp : �������̨Ӧ�ó������ڵ㡣
//
//�췽�����ӣ�1,9��ʾ��;2��8��ʾ��;3,7��ʾ��;4,6��ʾʿ;5��ʾ˧;10,11��ʾ��;12��13��14��15��16��ʾ��;
//�ڷ������ӣ�17,25��ʾ��;18��24��ʾ��;19,23��ʾ��;20,22��ʾʿ;21��ʾ��;26��27��ʾ��;28��29��30��31��32��ʾ��;
#include "StdAfx.h"
//#include "FKComposition.h"
//#include<winsock2.h>
#include "FKIDtoSocketMap.h"
//#include <Windows.h>
//#include <vector>
#include "iostream"
using namespace std;
//#pragma comment(lib,"ws2_32.lib") // Socket������õĶ�̬���ӿ� 
#pragma comment(lib,"Kernel32.lib")// IOCP��Ҫ�õ��Ķ�̬���ӿ�  
#define DEFUALT_PORT 600
#define MAX_TABEL_NUMBER 1024
using namespace std;
struct sDataBag
{

	int x1;
	int y1;
	int x2;
	int y2;
	int iClientOperate1;
	int iClientOperate2;
	//int ChessBoardLock;
	int iJuge;//�ƶ�����״ֵ̬���ж��ܷ��ƶ�����
	int win_lose;
	int iJudgeRedOrBlack;
	int StartKey;//��ʼ
	int PeaceKey;//���
	int GiveUp;  //����
	int Regret;  //����
	int exit;    //�˳�
	int yeskey;  //ͬ��
	int nokey;   //��ͬ��
	int iTable;
	int iGameType;
	int ID;
	int iCheck;
	//int iJuge1;
};
/** 
 * �ṹ�����ƣ�PER_IO_DATA 
 * �ṹ�幦�ܣ��ص�I/O��Ҫ�õ��Ľṹ�壬��ʱ��¼IO���� 
 **/  
struct sPerIO_OperationData
{
	OVERLAPPED oOverlapped;
	WSABUF dataBuff;
	char pBuffer[1024];
	int iBufferLength;
	int operationType;
};

/** 
 * �ṹ�����ƣ�PER_HANDLE_DATA 
 * �ṹ��洢����¼�����׽��ֵ����ݣ��������׽��ֵı������׽��ֵĶ�Ӧ�Ŀͻ��˵ĵ�ַ�� 
 * �ṹ�����ã��������������Ͽͻ���ʱ����Ϣ�洢���ýṹ���У�֪���ͻ��˵ĵ�ַ�Ա��ڻطá� 
 **/  
struct sPerHandleData{
	SOCKET sockSocket;
	SOCKADDR_IN ClientAddr;
	//sDataBag *pDataBag;
};

//struct sSocket
//{
//	SOCKET sockServerRed;
//	SOCKET sockServerBlack;
//};
//sPerHandleData *pLAP_PerHandleData;
//sPerIO_OperationData *pPerIO_OperationData[2];
//sPerIO_OperationData Per_IO_DATA;
//vector<sPerHandleData *>vClientGroup;
FKIDtoSocketMap *pIDtoSocketMap=new FKIDtoSocketMap;
//vector<sDa *>vDataBag;
sDataBag *pDataBag=new sDataBag[MAX_TABEL_NUMBER];
int iDataBagNumbers=0;
//int ID_Number=0;
//sSocket *pSocket;
HANDLE hMutex=CreateMutex(NULL,FALSE,NULL);
DWORD WINAPI ServerWorkThread(LPVOID CompletionPortID);
DWORD WINAPI ServerSendThread(LPVOID pthread);


//FKComposition *pComposition=new FKComposition;//���������
//char *pReceiveBuffer=new char[sizeof(sDataBag)];
//DWORD WINAPI RedWorkThread(LPVOID pthread1);
//DWORD WINAPI BlackWorkThread(LPVOID pthread2);
//bool bPlayer1Move=true;
//bool bPlayer2Move=false;
int _tmain(int argc, _TCHAR* argv[])
{

	WORD wVersionRequested=MAKEWORD(2,2);//����socket2��2�汾�Ŀ⺯��
	WSADATA wsaSocketData; //����windows socket�ṹ��Ϣ

	DWORD dError=WSAStartup(wVersionRequested,&wsaSocketData);
	if(0!=dError){//����׽��ֿ��Ƿ�����ɹ�
		cerr<<"Request Windows Socket Library Error!!\n"<<endl;
		system("puase");
		return -1;
	}
	if(2!=LOBYTE(wsaSocketData.wVersion)||2!=HIBYTE(wsaSocketData.wVersion))
	{//����ǲ���2.2�汾
		WSACleanup();
		cerr<<"Request Windows Socket Version 2.2 Error!\n";
		system("puase");
		return -1;
	}

	HANDLE hCompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0);
	if(hCompletionPort==NULL)//����IO�ں˶���ʧ��
	{
     cerr<<"Creat CompletionPort Error:"<<GetLastError()<<endl;
	 system("puase");
	 return -1;
	}

	SYSTEM_INFO mySysInfo;
	GetSystemInfo(&mySysInfo);//��ȡcpu����
	for(unsigned int i=0;i<mySysInfo.dwNumberOfProcessors*2;i++)
	{
		HANDLE hThread=CreateThread(NULL,0,ServerWorkThread,hCompletionPort,0,NULL);
		if(hThread==NULL)
		{
			cerr<<"Creat Thread Error:"<<GetLastError()<<endl;
			system("puase");
			return -1;
		}
		CloseHandle(hThread);
	}
	SOCKET sockListen;
	//sSocket *pSocket=new sSocket;
	SOCKADDR_IN sockAddr;
	sockListen=socket(AF_INET,SOCK_STREAM,0);
	//SOCKADDR_IN sockAddr;
	sockAddr.sin_family=AF_INET;
	sockAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	sockAddr.sin_port=htons(DEFUALT_PORT);

	int iBindResult=bind(sockListen,(SOCKADDR*)&sockAddr,sizeof(SOCKADDR));
	if(iBindResult==SOCKET_ERROR)
	{
		cerr << "Bind failed. Error:" << GetLastError() << endl;  
		system("pause");  
		return -1;  
	}
	int iListenResult=listen(sockListen,SOMAXCONN);
	if(iListenResult==SOCKET_ERROR)
	{
		cerr<<"Listen Failed Error:"<<GetLastError()<<endl;
		system("puase");
		return -1;
	}
	// ��ʼ����IO����  
	printf("����������׼����ϣ����ڵȴ��ͻ������ӽ�����������\n");

	//�������ڷ��͵��߳�
	HANDLE hSendThread=CreateThread(NULL,0,ServerSendThread,0,NULL,0);
	while(true)
	{
		sPerHandleData *pPerHandleData=NULL;
		SOCKADDR_IN sockaddrRemote;
		int RemoteLen=sizeof(sockaddrRemote);
		SOCKET AcceptSocket;
		// �������ӣ���������ɶˣ����������AcceptEx()
		AcceptSocket=accept(sockListen,(SOCKADDR*)&sockaddrRemote,&RemoteLen);
		//pPerHandleData->ClientAddr=sockaddrRemote;
		//printf("%d\n",sockaddrRemote); 
		//pSocket->sockServerBlack=accept(sockListen,(SOCKADDR*)&sockaddrRemote,&RemoteLen);
		//printf("�ƶ�֮ǰ,�ڷ����ӽ�����\n");
		if(AcceptSocket==SOCKET_ERROR/*||pSocket->sockServerRed==SOCKET_ERROR*/)
		{
			cerr << "Accept Socket Error: " << GetLastError() << endl;  
			system("pause");  
			return -1;  
		}
		
		recv(AcceptSocket,(char *)pDataBag,sizeof(sDataBag),0);
		// �����������׽��ֹ����ĵ����������Ϣ�ṹ

		pPerHandleData=(sPerHandleData *)GlobalAlloc(GPTR,sizeof(sPerHandleData)); // �ڶ���Ϊ���PerHandleData����ָ����С���ڴ� 
		pPerHandleData->sockSocket=AcceptSocket;
		//pPerHandleData->sockSocket=pSocket->sockServerBlack;
		//vClientGroup.push_back(pPerHandleData);
		pIDtoSocketMap->ModifyMapFun(pDataBag->ID,pPerHandleData->sockSocket);
		printf("%d \n",pDataBag->ID);
		switch((pDataBag)->iGameType)
		{
		case 0:
			//��ͻ��˷�������
			//send(pIDtoSocketMap->IdToSocket((pDataBag+iDataBagNumbers)->ID), (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // ������Ϣ
			//send(vClientGroup[0]->sockSocket, (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // ������Ϣ
			break;
		case 1:
			//����
			//pDataBag->x1=122;
			//(pDataBag+iDataBagNumbers)->iGameType=0;
			send(pIDtoSocketMap->IdToSocket(0), (char *)(pDataBag), sizeof(sDataBag), 0);  // ������Ϣ
			break;
		case 2:
			//(pDataBag+iDataBagNumbers)->iGameType=0;
			break;
			//3��ɱ
		case 3:
			//̨��
			//(pDataBag+iDataBagNumbers)->iGameType=0;
			break;
		case 4:
			//����
			//(pDataBag+iDataBagNumbers)->iGameType=0;
			break;
		default:
			break;
			//send(vClientGroup[1]->sockSocket,(char *)pDataBag,sizeof(sDataBag),0);
		}
		//ID_Number++;
		//for(int i=0;i<vClientGroup.size();i++)
		//{
		//printf("\n�ͻ���IP ��%d\n",vClientGroup[i]->ClientAddr);
		//}
		//vClientGroup.push_back()
		CreateIoCompletionPort((HANDLE)pPerHandleData->sockSocket,hCompletionPort,(DWORD)pPerHandleData,0);

		// ��ʼ�ڽ����׽����ϴ���I/Oʹ���ص�I/O����  
		// ���½����׽�����Ͷ��һ�������첽  
		// WSARecv��WSASend������ЩI/O������ɺ󣬹������̻߳�ΪI/O�����ṩ����      
		// ��I/O��������(I/O�ص�)  
		sPerIO_OperationData *pPerIO_Data=NULL;
		pPerIO_Data=(sPerIO_OperationData *)GlobalAlloc(GPTR,sizeof(sPerIO_OperationData));
		ZeroMemory(&(pPerIO_Data->oOverlapped),sizeof(OVERLAPPED));
		pPerIO_Data->dataBuff.len=sizeof(sDataBag);
		pPerIO_Data->dataBuff.buf=pPerIO_Data->pBuffer;
		pPerIO_Data->operationType=0;// read 
		DWORD RecvBytes;
		DWORD Flags=0;
		WSARecv(pPerHandleData->sockSocket,&(pPerIO_Data->dataBuff),1,&RecvBytes,&Flags,&(pPerIO_Data->oOverlapped),NULL);
	}


	//HANDLE handle[2];
	//handle[0]=CreateThread(NULL,0,RedWorkThread,(void *)pSocket,0,NULL);
	////handle[1]=CreateThread(NULL,0,BlackWorkThread,(void *)sockServerBlack,0,NULL);
	//WaitForMultipleObjects(2,handle,TRUE,INFINITE);
	//closesocket(pSocket->sockServerBlack);
	//closesocket(pSocket->sockServerRed);
	//delete pSocket;
	//CloseHandle(handle[0]);
	//CloseHandle(handle[1]);
	while(1);
	return 0;
}
DWORD WINAPI ServerWorkThread(LPVOID pThread1)
{
	
	HANDLE hCompletionPort=(HANDLE)pThread1;
	DWORD BytesThransferred;
	LPOVERLAPPED lpOverLapped;
	sPerHandleData *pPerHandleData=NULL;
	sPerIO_OperationData *pPerIO_OperationData=NULL;
	DWORD RecvBytes;
	DWORD Flags=0;
	bool bRet=false;
	//int i=0;
	
	while(true)
	{
		
     bRet=GetQueuedCompletionStatus(hCompletionPort,&BytesThransferred,(PULONG_PTR)&pPerHandleData,(LPOVERLAPPED *)&lpOverLapped,INFINITE);
	 if(bRet==0)
	 {
		 cerr << "GetQueuedCompletionStatus Error: " << GetLastError() << endl;  //cerr�������壬������cout������𡣣���������á�
		 return -1;  
	 }
	 pPerIO_OperationData=(sPerIO_OperationData *)CONTAINING_RECORD(lpOverLapped,sPerIO_OperationData,oOverlapped);

	   // ������׽������Ƿ��д�����  
	 if(0==BytesThransferred)
	 {
		 closesocket(pPerHandleData->sockSocket);
		 GlobalFree(pPerHandleData);
		 GlobalFree(pPerIO_OperationData);
		 //delete pDataBag;
		 continue;
	 } 

	 // ��ʼ���ݴ����������Կͻ��˵�����  
	 
	 WaitForSingleObject(hMutex,INFINITE);
	 
	 *(pDataBag+iDataBagNumbers)=*(sDataBag *)(pPerIO_OperationData->dataBuff.buf);
	 //cout << "A Client says: " << pPerIO_OperationData->dataBuff.buf << endl;
	 //vDataBag.push_back(pDataBag);
	 printf("\n���ط������յ��� %d ",(pDataBag+iDataBagNumbers)->x1);
	 printf("%d ",(pDataBag+iDataBagNumbers)->y1);
	 printf("%d ",(pDataBag+iDataBagNumbers)->x2);
	 printf("%d ",(pDataBag+iDataBagNumbers)->y2);
	 // printf("%d ",(pDataBag+iDataBagNumbers)->ChessBoardLock);
	  printf("%d ",(pDataBag+iDataBagNumbers)->iGameType);
	  printf("%d ",(pDataBag+iDataBagNumbers)->ID);
	  printf("%d ",(pDataBag+iDataBagNumbers)->iJudgeRedOrBlack);
	 printf("%d \n",(pDataBag+iDataBagNumbers)->iJuge);

	 switch((pDataBag+iDataBagNumbers)->iGameType)
	 {
	 case 0:
		 //��ͻ��˷�������
		 send(pIDtoSocketMap->IdToSocket((pDataBag+iDataBagNumbers)->ID), (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // ������Ϣ
		 //send(vClientGroup[0]->sockSocket, (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // ������Ϣ
		 break;
	 case 1:
		 //����
		 //pDataBag->x1=122;
		 (pDataBag+iDataBagNumbers)->iGameType=0;
		 send(pIDtoSocketMap->IdToSocket(0), (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // ������Ϣ
		 break;
	 case 2:
		 (pDataBag+iDataBagNumbers)->iGameType=0;
		 break;
		 //3��ɱ
	 case 3:
		 //̨��
		 (pDataBag+iDataBagNumbers)->iGameType=0;
		 break;
	 case 4:
		 //����
		 (pDataBag+iDataBagNumbers)->iGameType=0;
		 break;
	 default:
		 break;
		 //send(vClientGroup[1]->sockSocket,(char *)pDataBag,sizeof(sDataBag),0);
	 }
	 //printf("%d \n",(pDataBag+iDataBagNumbers)->ID);
	 //send(pIDtoSocketMap->IdToSocket((pDataBag+iDataBagNumbers)->ID), (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // ������Ϣ
	 
	 iDataBagNumbers++;
	 if(iDataBagNumbers==MAX_TABEL_NUMBER+1)
		 iDataBagNumbers=0;
	 ReleaseMutex(hMutex);  
	 
	 // Ϊ��һ���ص����ý�����I/O�������� 
	 ZeroMemory(&(pPerIO_OperationData->oOverlapped),sizeof(OVERLAPPED)); // ����ڴ� 
	 pPerIO_OperationData->dataBuff.len=sizeof(sDataBag);
	 pPerIO_OperationData->dataBuff.buf=pPerIO_OperationData->pBuffer;
	 pPerIO_OperationData->operationType=0;
	 WSARecv(pPerHandleData->sockSocket,&(pPerIO_OperationData->dataBuff),1,&RecvBytes,&Flags,&(pPerIO_OperationData->oOverlapped),NULL);
	}
//	delete pDataBag;
	return 0;
}

// ������Ϣ���߳�ִ�к��� 
DWORD WINAPI ServerSendThread(LPVOID pThread2)
{
	//sPerHandleData *pPerHandleData=NULL;
	//sPerIO_OperationData *pPerIO_OperationData=NULL;
	//sDataBag *pDataBag=new sDataBag(); 
	while(1){  
		 
		//gets(talk);  
		//int len;  
		//for (len = 0; talk[len] != '\0'; ++len){  
			// �ҳ�����ַ���ĳ���  
		//}  
		//talk[len] = '\n';  
		//talk[++len] = '\0';  
		//printf("I Say:");  
		//cout << talk;

		WaitForSingleObject(hMutex,INFINITE);

		{ 
			//send(pIDtoSocketMap->IdToSocket((pDataBag)->ID),(char *)(pDataBag),sizeof(sDataBag),0);
			//*pDataBag=*(pDataBag+1);
			//send(pIDtoSocketMap->IdToSocket((pDataBag+3)->ID),(char *)(pDataBag+3),sizeof(sDataBag),0);
		}  
		ReleaseMutex(hMutex);   
	} 
	//delete pDataBag;
	return 0;  
}


