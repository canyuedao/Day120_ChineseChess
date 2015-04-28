#pragma once
//#include "Player1.h"
//#include "Player2.h"
//#include "Black.h"
//#include "Red.h"
#include "Chess.h"
#include "Vector2.h"
class CChooseChess
{
public:
	CChooseChess(CChessBoard*);
	~CChooseChess(void);
	bool GetPlayer1Suc();
	bool GetPlayer2Suc();
	void SetPlayer1Suc(bool);
	void SetPlayer2Suc(bool);
	CChess *GetChess(int,int);
	//CChess *GetPlayer2Chess(Vector2 v2);
public:
	//CPlayer1 *mPlayer1; 
	//CPlayer2 *mPlayer2;
	//CRed *mRed;
	//CBlack *mBlack;
private:
	
	CChess *mChess;
	CChessBoard *mPChessBoard;
	bool mPlayer1Success;
	bool mPlayer2Success;
};

