#pragma once
#include <map>
#include "iostream"
#include <winsock2.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

//����鵽�����id,��ô�ͷ��ض�Ӧ��socket�����򷵻�-1;
class FKIDtoSocketMap
{
private:
	typedef map<int ,SOCKET> UDT_MAP_INT_CSOCKET;
	UDT_MAP_INT_CSOCKET enumMap;
public:
	FKIDtoSocketMap(void);
	~FKIDtoSocketMap(void);
	SOCKET IdToSocket(int id);
	void insertFun(int id,SOCKET s);
	void ReMoveIDFun(int id);
	void ModifyMapFun(int id,SOCKET s);
	//int ID_Number;
};

