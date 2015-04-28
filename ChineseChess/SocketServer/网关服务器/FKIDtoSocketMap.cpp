#include "StdAfx.h"
#include "FKIDtoSocketMap.h"


FKIDtoSocketMap::FKIDtoSocketMap(void)
{
	//ID_Number=0;
}


FKIDtoSocketMap::~FKIDtoSocketMap(void)
{
}

SOCKET FKIDtoSocketMap::IdToSocket( int id )
{
	UDT_MAP_INT_CSOCKET::iterator itr=enumMap.find(id);
	if(itr!=enumMap.end())
		return itr->second;
	else
		return -1;
}

void FKIDtoSocketMap::insertFun( int id,SOCKET s )
{
	enumMap.insert(map<int,SOCKET>::value_type(id,s));
	//ID_Number++;
}

void FKIDtoSocketMap::ReMoveIDFun( int id )
{
	UDT_MAP_INT_CSOCKET::iterator iter=enumMap.find(id);
	if(iter!=enumMap.end())
	{
		enumMap.erase(id);
	}
}

void FKIDtoSocketMap::ModifyMapFun( int id,SOCKET s )
{
	UDT_MAP_INT_CSOCKET::iterator iter=enumMap.find(id);
	if(iter==enumMap.end())
	{
		insertFun(id,s);
	}
	else
	{
		iter->second=s;
	}
}
