#pragma once
#include "Chess.h"
class CBlackHorse:public CChess
{
public:
	CBlackHorse(char*,int,CChessBoard*);
	~CBlackHorse(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

