#pragma once
#include "Chess.h"
class CRedSolidier:public CChess
{
public:
	CRedSolidier(char*,int,CChessBoard*);
	~CRedSolidier(void);
	void FindCurAccess(char*);
	void FindAllAccess(char*);
};

