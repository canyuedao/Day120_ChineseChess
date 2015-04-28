// chess.cpp : 定义控制台应用程序的入口点。
//
//红方的棋子：1,9表示车;2，8表示马;3,7表示象;4,6表示士;5表示帅;10,11表示炮;12，13，14，15，16表示兵;
//黑方的棋子：17,25表示车;18，24表示马;19,23表示象;20,22表示士;21表示将;26，27表示炮;28，29，30，31，32表示卒;
#include "StdAfx.h"
//#include "FKComposition.h"
//#include<winsock2.h>
#include "FKIDtoSocketMap.h"
//#include <Windows.h>
//#include <vector>
#include "iostream"
using namespace std;
//#pragma comment(lib,"ws2_32.lib") // Socket编程需用的动态链接库 
#pragma comment(lib,"Kernel32.lib")// IOCP需要用到的动态链接库  
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
	int iJuge;//移动棋子状态值，判断能否移动棋子
	int win_lose;
	int iJudgeRedOrBlack;
	int StartKey;//开始
	int PeaceKey;//求和
	int GiveUp;  //认输
	int Regret;  //悔棋
	int exit;    //退出
	int yeskey;  //同意
	int nokey;   //不同意
	int iTable;
	int iGameType;
	int ID;
	int iCheck;
	//int iJuge1;
};
/** 
 * 结构体名称：PER_IO_DATA 
 * 结构体功能：重叠I/O需要用到的结构体，临时记录IO数据 
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
 * 结构体名称：PER_HANDLE_DATA 
 * 结构体存储：记录单个套接字的数据，包括了套接字的变量及套接字的对应的客户端的地址。 
 * 结构体作用：当服务器连接上客户端时，信息存储到该结构体中，知道客户端的地址以便于回访。 
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


//FKComposition *pComposition=new FKComposition;//虚拟的棋子
//char *pReceiveBuffer=new char[sizeof(sDataBag)];
//DWORD WINAPI RedWorkThread(LPVOID pthread1);
//DWORD WINAPI BlackWorkThread(LPVOID pthread2);
//bool bPlayer1Move=true;
//bool bPlayer2Move=false;
int _tmain(int argc, _TCHAR* argv[])
{

	WORD wVersionRequested=MAKEWORD(2,2);//请求socket2，2版本的库函数
	WSADATA wsaSocketData; //接收windows socket结构信息

	DWORD dError=WSAStartup(wVersionRequested,&wsaSocketData);
	if(0!=dError){//检查套接字库是否申请成功
		cerr<<"Request Windows Socket Library Error!!\n"<<endl;
		system("puase");
		return -1;
	}
	if(2!=LOBYTE(wsaSocketData.wVersion)||2!=HIBYTE(wsaSocketData.wVersion))
	{//检查是不是2.2版本
		WSACleanup();
		cerr<<"Request Windows Socket Version 2.2 Error!\n";
		system("puase");
		return -1;
	}

	HANDLE hCompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0);
	if(hCompletionPort==NULL)//创建IO内核对象失败
	{
     cerr<<"Creat CompletionPort Error:"<<GetLastError()<<endl;
	 system("puase");
	 return -1;
	}

	SYSTEM_INFO mySysInfo;
	GetSystemInfo(&mySysInfo);//获取cpu个数
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
	// 开始处理IO数据  
	printf("本服务器已准备完毕，正在等待客户端连接进来。。。。\n");

	//创建用于发送的线程
	HANDLE hSendThread=CreateThread(NULL,0,ServerSendThread,0,NULL,0);
	while(true)
	{
		sPerHandleData *pPerHandleData=NULL;
		SOCKADDR_IN sockaddrRemote;
		int RemoteLen=sizeof(sockaddrRemote);
		SOCKET AcceptSocket;
		// 接收连接，并分配完成端，这儿可以用AcceptEx()
		AcceptSocket=accept(sockListen,(SOCKADDR*)&sockaddrRemote,&RemoteLen);
		//pPerHandleData->ClientAddr=sockaddrRemote;
		//printf("%d\n",sockaddrRemote); 
		//pSocket->sockServerBlack=accept(sockListen,(SOCKADDR*)&sockaddrRemote,&RemoteLen);
		//printf("移动之前,黑方连接进来了\n");
		if(AcceptSocket==SOCKET_ERROR/*||pSocket->sockServerRed==SOCKET_ERROR*/)
		{
			cerr << "Accept Socket Error: " << GetLastError() << endl;  
			system("pause");  
			return -1;  
		}
		
		recv(AcceptSocket,(char *)pDataBag,sizeof(sDataBag),0);
		// 创建用来和套接字关联的单句柄数据信息结构

		pPerHandleData=(sPerHandleData *)GlobalAlloc(GPTR,sizeof(sPerHandleData)); // 在堆中为这个PerHandleData申请指定大小的内存 
		pPerHandleData->sockSocket=AcceptSocket;
		//pPerHandleData->sockSocket=pSocket->sockServerBlack;
		//vClientGroup.push_back(pPerHandleData);
		pIDtoSocketMap->ModifyMapFun(pDataBag->ID,pPerHandleData->sockSocket);
		printf("%d \n",pDataBag->ID);
		switch((pDataBag)->iGameType)
		{
		case 0:
			//向客户端发送数据
			//send(pIDtoSocketMap->IdToSocket((pDataBag+iDataBagNumbers)->ID), (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // 发送信息
			//send(vClientGroup[0]->sockSocket, (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // 发送信息
			break;
		case 1:
			//象棋
			//pDataBag->x1=122;
			//(pDataBag+iDataBagNumbers)->iGameType=0;
			send(pIDtoSocketMap->IdToSocket(0), (char *)(pDataBag), sizeof(sDataBag), 0);  // 发送信息
			break;
		case 2:
			//(pDataBag+iDataBagNumbers)->iGameType=0;
			break;
			//3国杀
		case 3:
			//台球
			//(pDataBag+iDataBagNumbers)->iGameType=0;
			break;
		case 4:
			//大厅
			//(pDataBag+iDataBagNumbers)->iGameType=0;
			break;
		default:
			break;
			//send(vClientGroup[1]->sockSocket,(char *)pDataBag,sizeof(sDataBag),0);
		}
		//ID_Number++;
		//for(int i=0;i<vClientGroup.size();i++)
		//{
		//printf("\n客户端IP ：%d\n",vClientGroup[i]->ClientAddr);
		//}
		//vClientGroup.push_back()
		CreateIoCompletionPort((HANDLE)pPerHandleData->sockSocket,hCompletionPort,(DWORD)pPerHandleData,0);

		// 开始在接受套接字上处理I/O使用重叠I/O机制  
		// 在新建的套接字上投递一个或多个异步  
		// WSARecv或WSASend请求，这些I/O请求完成后，工作者线程会为I/O请求提供服务      
		// 单I/O操作数据(I/O重叠)  
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
		 cerr << "GetQueuedCompletionStatus Error: " << GetLastError() << endl;  //cerr不被缓冲，这是与cout最大区别。，紧急情况用。
		 return -1;  
	 }
	 pPerIO_OperationData=(sPerIO_OperationData *)CONTAINING_RECORD(lpOverLapped,sPerIO_OperationData,oOverlapped);

	   // 检查在套接字上是否有错误发生  
	 if(0==BytesThransferred)
	 {
		 closesocket(pPerHandleData->sockSocket);
		 GlobalFree(pPerHandleData);
		 GlobalFree(pPerIO_OperationData);
		 //delete pDataBag;
		 continue;
	 } 

	 // 开始数据处理，接收来自客户端的数据  
	 
	 WaitForSingleObject(hMutex,INFINITE);
	 
	 *(pDataBag+iDataBagNumbers)=*(sDataBag *)(pPerIO_OperationData->dataBuff.buf);
	 //cout << "A Client says: " << pPerIO_OperationData->dataBuff.buf << endl;
	 //vDataBag.push_back(pDataBag);
	 printf("\n网关服务器收到的 %d ",(pDataBag+iDataBagNumbers)->x1);
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
		 //向客户端发送数据
		 send(pIDtoSocketMap->IdToSocket((pDataBag+iDataBagNumbers)->ID), (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // 发送信息
		 //send(vClientGroup[0]->sockSocket, (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // 发送信息
		 break;
	 case 1:
		 //象棋
		 //pDataBag->x1=122;
		 (pDataBag+iDataBagNumbers)->iGameType=0;
		 send(pIDtoSocketMap->IdToSocket(0), (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // 发送信息
		 break;
	 case 2:
		 (pDataBag+iDataBagNumbers)->iGameType=0;
		 break;
		 //3国杀
	 case 3:
		 //台球
		 (pDataBag+iDataBagNumbers)->iGameType=0;
		 break;
	 case 4:
		 //大厅
		 (pDataBag+iDataBagNumbers)->iGameType=0;
		 break;
	 default:
		 break;
		 //send(vClientGroup[1]->sockSocket,(char *)pDataBag,sizeof(sDataBag),0);
	 }
	 //printf("%d \n",(pDataBag+iDataBagNumbers)->ID);
	 //send(pIDtoSocketMap->IdToSocket((pDataBag+iDataBagNumbers)->ID), (char *)(pDataBag+iDataBagNumbers), sizeof(sDataBag), 0);  // 发送信息
	 
	 iDataBagNumbers++;
	 if(iDataBagNumbers==MAX_TABEL_NUMBER+1)
		 iDataBagNumbers=0;
	 ReleaseMutex(hMutex);  
	 
	 // 为下一个重叠调用建立单I/O操作数据 
	 ZeroMemory(&(pPerIO_OperationData->oOverlapped),sizeof(OVERLAPPED)); // 清空内存 
	 pPerIO_OperationData->dataBuff.len=sizeof(sDataBag);
	 pPerIO_OperationData->dataBuff.buf=pPerIO_OperationData->pBuffer;
	 pPerIO_OperationData->operationType=0;
	 WSARecv(pPerHandleData->sockSocket,&(pPerIO_OperationData->dataBuff),1,&RecvBytes,&Flags,&(pPerIO_OperationData->oOverlapped),NULL);
	}
//	delete pDataBag;
	return 0;
}

// 发送信息的线程执行函数 
DWORD WINAPI ServerSendThread(LPVOID pThread2)
{
	//sPerHandleData *pPerHandleData=NULL;
	//sPerIO_OperationData *pPerIO_OperationData=NULL;
	//sDataBag *pDataBag=new sDataBag(); 
	while(1){  
		 
		//gets(talk);  
		//int len;  
		//for (len = 0; talk[len] != '\0'; ++len){  
			// 找出这个字符组的长度  
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


