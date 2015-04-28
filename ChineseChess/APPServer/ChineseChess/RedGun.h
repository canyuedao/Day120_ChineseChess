#pragma once
#include "Chess.h"
class CRedGun:public CChess
{
public:
	CRedGun(char*,int,CChessBoard*);
	~CRedGun(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

