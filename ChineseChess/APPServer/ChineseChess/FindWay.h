#pragma once
//#include "ChooseChess.h"
//#include "MoveChess.h"
#include "Player1.h"
#include "Player2.h"
//#include "ChessGame.h"
#include "Vector2.h"
#include "Chess.h"
class CChessGame;
//struct Moves;
struct Moves{	
public:
	Vector2 vec2;
	Vector2 vec;	
	CChess *chess;	
	Moves(){};
	Moves(Vector2 *vec1,CChess *chess2){
		vec=*vec1;chess=chess2;vec2=*chess2->GetPosition();
	}	
};
class CFindWay
{
private:
	//CChooseChess *mPCChooseChess;
	//CMoveChess *mMCoveChess;
	
	//int mCurAccessLen;
	//Vector2 *mPVChooseChess;
	//Vector2 *mPVMoveChess;
	//static const char cucvlPiecePos[7][256];
	int iMove;
	int iUndoMove;
	
public:
	CChessGame *mChessGame;
	CPlayer1 *mPlayer1;
	CPlayer2 *mPlayer2;	
	//Moves* pMoves;
	//int iindex;
public:
	//CFindWay(CPlayer1*,CPlayer2*,CChessGame*);
	CFindWay(CChessGame*);
	~CFindWay(void);
	Moves FindWay();
	Vector2* GetChooseChess();
	Vector2* GetMoveChess();
	int GetCurAccessLen();
	int GenerateMoves(Moves*,char*);
	int FRed(Moves*,int&,char*);
	int FBlack(Moves*,int&,char*);
	int GetMovesLen();
	CChess* MovePiece(Moves*);
	void UndoMovePiece(Moves*,CChess*);
	bool MakeMove(Moves*,int&);
	void UndoMakeMove(Moves*,int&);
	void AddPiece(Vector2*,CChess*);
	void DelPiece(Vector2*,CChess*);
	int Evaluate() const;
	int SearchFull(int,int,int,char*);
	static int CompareHistory(const void*, const void*);
	int MOVE(Moves*);	
	void SearchMain();
	bool MoveChess(int,int,int,int);
	bool MoveChess(Moves*);
	bool GetBlackDead();
	bool GetRedDead();
	void UndoMoveChess(int,int,int,int,CChess*);
	void UndoMoveChess(Moves*,CChess*);
};

