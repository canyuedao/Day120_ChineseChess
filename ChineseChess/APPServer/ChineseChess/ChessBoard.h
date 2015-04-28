#pragma once
#include "Vector2.h"
class CChessBoard
{
public:
	CChessBoard(void);
	~CChessBoard(void);
	Vector2* GetPosition(int i,int j);
private:
	Vector2* mAllBoardPosition[9][10];
};

