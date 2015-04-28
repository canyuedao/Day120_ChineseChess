#pragma once
#include "Chess.h"

class CBlackBachelor:public CChess
{
public:
	CBlackBachelor(char*,int,CChessBoard*);
	~CBlackBachelor(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);	
};

