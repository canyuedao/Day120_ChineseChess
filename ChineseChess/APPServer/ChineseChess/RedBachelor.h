#pragma once
#include "Chess.h"
class CRedBachelor:public CChess
{
public:
	CRedBachelor(char*,int,CChessBoard*);
	~CRedBachelor(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);	
};

