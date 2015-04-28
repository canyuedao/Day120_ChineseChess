#pragma once
#include "Chess.h"
class CRedHorse:public CChess
{
public:
	CRedHorse(char*,int,CChessBoard*);
	~CRedHorse(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

