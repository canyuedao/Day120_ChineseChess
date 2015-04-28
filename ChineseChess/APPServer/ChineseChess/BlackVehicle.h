#pragma once
#include "Chess.h"
class CBlackVehicle:public CChess
{
public:
	CBlackVehicle(char*,int,CChessBoard*);
	~CBlackVehicle(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

