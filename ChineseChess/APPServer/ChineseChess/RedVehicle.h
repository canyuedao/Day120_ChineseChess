#pragma once
#include "Chess.h"
class CRedVehicle:public CChess
{
public:
	CRedVehicle(char*,int,CChessBoard*);
	~CRedVehicle(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

