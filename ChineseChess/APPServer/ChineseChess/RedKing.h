#pragma once
#include "Chess.h"
class CRedKing:public CChess
{
public:
	CRedKing(char*,CChessBoard*);
	~CRedKing(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

