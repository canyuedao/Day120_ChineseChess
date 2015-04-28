#pragma once
#include <map>
#include "iostream"
#include <winsock2.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

//如果查到有这个id,那么就返回对应的socket，否则返回-1;
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

