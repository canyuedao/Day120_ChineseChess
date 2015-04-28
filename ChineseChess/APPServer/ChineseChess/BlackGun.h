#pragma once
#include "Chess.h"
class CBlackGun:public CChess
{
public:
	CBlackGun(char*,int,CChessBoard*);
	~CBlackGun(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

