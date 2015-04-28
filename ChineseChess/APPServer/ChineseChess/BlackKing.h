#pragma once
#include "Chess.h"

class CBlackKing:public CChess{
public:
	CBlackKing(char*,CChessBoard*);
	~CBlackKing(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);	
};