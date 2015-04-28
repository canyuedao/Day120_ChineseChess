#pragma once
//#include "Player1.h"
//#include "Player2.h"
//#include "Black.h"
//#include "Red.h"
#include "Vector2.h"
#include "ChooseChess.h"
#include "ChessGame.h"
#include "FindWay.h"
class CMoveChess
{
public:
	CMoveChess(CChessGame*,CChooseChess*);
	~CMoveChess(void);
	bool Player1MoveChess(Vector2*);
	bool MoveChess(int,int,int,int);
	bool Player2MoveChess(Vector2*);
	bool GetPlayer1MoveChessState();
	bool GetPlayer2MoveChessState();
	void SetPlayer1Suc(bool);
	void SetPlayer2Suc(bool);
public:
	//CPlayer1 *mPlayer1;
	//CPlayer2 *mPlayer2;
	//CRed *mRed;
	//CBlack *mBlack;
	CChessGame *mPChessGame;
private:
	
	CChooseChess *mPChooseChess;
	CFindWay *mFindWay;
	bool mPlayer1Success;
	bool mPlayer2Success;
};

