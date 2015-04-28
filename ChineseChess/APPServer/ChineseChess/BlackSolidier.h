#pragma once
#include "Chess.h"
class CBlackSolidier:public CChess
{
public:
	CBlackSolidier(char*,int,CChessBoard*);
	~CBlackSolidier(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

