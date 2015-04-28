#pragma once


#include "Vector2.h" 
#include "ChessBoard.h"

class CChess{	
public:	
	char* mColor;
	CChessBoard *mChessBoard;
	Vector2* mPosition;

	Vector2 *mAllAccess;
	Vector2 *mCurAccess;
	int mCurAccessLen;
	int mAllAccessLen;
	int ID;
	int bDead;
public:	
	void SetPosition(int,int);
	Vector2*  GetPosition();

	virtual void FindCurAccess(char*){};
	virtual void FindAllAccess(char*){};
	Vector2* GetCurAccess();
	Vector2* GetAllAccess();
	int GetCurAccessLen();
	int GetAllAccessLen();
};