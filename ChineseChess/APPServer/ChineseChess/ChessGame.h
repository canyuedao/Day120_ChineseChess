#pragma once
#include "ChessBoard.h"
#include "Black.h"
#include "Red.h"
#include "FindWay.h"
//class CFindWay;
class CChessGame
{
	
public:

	//CChessGame(bool,char*);
	CChessGame(void);
	~CChessGame(void);
	bool GetManVStComputer();
	bool GetBlackChecked();
	bool GetRedChecked();
	bool GetBlackBlocked();
	bool GetRedBlocked();
	//bool GetBlackDead();
	//bool GetRedDead();
	int GetBlackResult();
	int GetRedResult();	
	void Reset();
public:
	CBlack *mBlack;
	CRed *mRed;
	CChessBoard *mChessBoard;
	bool mIsManVSComputer;
	char *mColor;
	int vlWhite, vlBlack,nDistance;
	int iStepNumber;
	CFindWay *mFindWay;
	int iPersonID[2];
};

