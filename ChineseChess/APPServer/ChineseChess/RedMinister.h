#pragma once
#include "Chess.h"
class CRedMinister:public CChess
{
public:
	CRedMinister(char*,int,CChessBoard*);
	~CRedMinister(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

