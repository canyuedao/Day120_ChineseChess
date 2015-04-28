#pragma once
#include "Chess.h"
class CBlackMinister:public CChess
{
public:
	CBlackMinister(char*,int,CChessBoard*);
	~CBlackMinister(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

