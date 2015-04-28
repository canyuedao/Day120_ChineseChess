#include "FindWay.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "ChessGame.h"

const int DEL_VALUE=-100;
const int MATE_VALUE=10000;
const int MAX_GEN_MOVES=128;
const int LIMIT_DEPTH=5;
const int WIN_VALUE = MATE_VALUE - 100;
const int ADVANCED_VALUE=3;


static struct {
	Moves mvResult;             // 电脑走的棋
	int nHistoryTable[65536]; // 历史表
} Search;
static const char cucvlPiecePos[7][256] = {
	{ // 帅(将)
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  2,  2,  2,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 11, 15, 11,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	}, { // 仕(士)
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 20,  0, 20,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0, 23,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 20,  0, 20,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	}, { // 相(象)
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0, 20,  0,  0,  0, 20,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0, 18,  0,  0,  0, 23,  0,  0,  0, 18,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0, 20,  0,  0,  0, 20,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		}, { // 马
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0, 90, 90, 90, 96, 90, 96, 90, 90, 90,  0,  0,  0,  0,
				0,  0,  0, 90, 96,103, 97, 94, 97,103, 96, 90,  0,  0,  0,  0,
				0,  0,  0, 92, 98, 99,103, 99,103, 99, 98, 92,  0,  0,  0,  0,
				0,  0,  0, 93,108,100,107,100,107,100,108, 93,  0,  0,  0,  0,
				0,  0,  0, 90,100, 99,103,104,103, 99,100, 90,  0,  0,  0,  0,
				0,  0,  0, 90, 98,101,102,103,102,101, 98, 90,  0,  0,  0,  0,
				0,  0,  0, 92, 94, 98, 95, 98, 95, 98, 94, 92,  0,  0,  0,  0,
				0,  0,  0, 93, 92, 94, 95, 92, 95, 94, 92, 93,  0,  0,  0,  0,
				0,  0,  0, 85, 90, 92, 93, 78, 93, 92, 90, 85,  0,  0,  0,  0,
				0,  0,  0, 88, 85, 90, 88, 90, 88, 90, 85, 88,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		}, { // 车
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,206,208,207,213,214,213,207,208,206,  0,  0,  0,  0,
				0,  0,  0,206,212,209,216,233,216,209,212,206,  0,  0,  0,  0,
				0,  0,  0,206,208,207,214,216,214,207,208,206,  0,  0,  0,  0,
				0,  0,  0,206,213,213,216,216,216,213,213,206,  0,  0,  0,  0,
				0,  0,  0,208,211,211,214,215,214,211,211,208,  0,  0,  0,  0,
				0,  0,  0,208,212,212,214,215,214,212,212,208,  0,  0,  0,  0,
				0,  0,  0,204,209,204,212,214,212,204,209,204,  0,  0,  0,  0,
				0,  0,  0,198,208,204,212,212,212,204,208,198,  0,  0,  0,  0,
				0,  0,  0,200,208,206,212,200,212,206,208,200,  0,  0,  0,  0,
				0,  0,  0,194,206,204,212,200,212,204,206,194,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		}, { // 炮
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,100,100, 96, 91, 90, 91, 96,100,100,  0,  0,  0,  0,
				0,  0,  0, 98, 98, 96, 92, 89, 92, 96, 98, 98,  0,  0,  0,  0,
				0,  0,  0, 97, 97, 96, 91, 92, 91, 96, 97, 97,  0,  0,  0,  0,
				0,  0,  0, 96, 99, 99, 98,100, 98, 99, 99, 96,  0,  0,  0,  0,
				0,  0,  0, 96, 96, 96, 96,100, 96, 96, 96, 96,  0,  0,  0,  0,
				0,  0,  0, 95, 96, 99, 96,100, 96, 99, 96, 95,  0,  0,  0,  0,
				0,  0,  0, 96, 96, 96, 96, 96, 96, 96, 96, 96,  0,  0,  0,  0,
				0,  0,  0, 97, 96,100, 99,101, 99,100, 96, 97,  0,  0,  0,  0,
				0,  0,  0, 96, 97, 98, 98, 98, 98, 98, 97, 96,  0,  0,  0,  0,
				0,  0,  0, 96, 96, 97, 99, 99, 99, 97, 96, 96,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
			}, { // 兵(卒)
				0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
					0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
					0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
					0,  0,  0,  9,  9,  9, 11, 13, 11,  9,  9,  9,  0,  0,  0,  0,
					0,  0,  0, 19, 24, 34, 42, 44, 42, 34, 24, 19,  0,  0,  0,  0,
					0,  0,  0, 19, 24, 32, 37, 37, 37, 32, 24, 19,  0,  0,  0,  0,
					0,  0,  0, 19, 23, 27, 29, 30, 29, 27, 23, 19,  0,  0,  0,  0,
					0,  0,  0, 14, 18, 20, 27, 29, 27, 20, 18, 14,  0,  0,  0,  0,
					0,  0,  0,  7,  0, 13,  0, 16,  0, 13,  0,  7,  0,  0,  0,  0,
					0,  0,  0,  7,  0,  7,  0, 15,  0,  7,  0,  7,  0,  0,  0,  0,
					0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
					0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
					0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
					0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
					0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
					0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
			}
};

//CFindWay::CFindWay(CPlayer1 *pPlayer1,CPlayer2 *pPlayer2,CChessGame *pChessGame)
CFindWay::CFindWay(CChessGame *pChessGame)
{
	
	//mPlayer1=pPlayer1;
	//mPlayer2=pPlayer2;
	mPlayer1=new CPlayer1("Red");
	mPlayer2=new CPlayer2("Black");
	mChessGame=pChessGame;
	iMove=iUndoMove=0;
	//mPlayer2=new CPlayer2();
}


CFindWay::~CFindWay(void)
{
	//delete pMoves;
}
int CFindWay::FRed(Moves *pmoves,int &iindex,char *cColor){
	for(int k=0;k<90;k++){
		int x=k%9;
		int y=9-k/9;
		CChess *pchess=mChessGame->mChessBoard->GetPosition(x,y)->mPChess;
		if(pchess){
			if(pchess->mColor=="Red"){
				pchess->FindCurAccess(cColor);			
				for(int i=0;i<pchess->GetCurAccessLen();i++){
					Moves *tmpMove=new Moves((Vector2*)((int)(pchess->GetCurAccess())+i*sizeof(Vector2)),pchess);
					pmoves[iindex]=*tmpMove;
					delete tmpMove;
					iindex++;
				}
			}

		}
	}
	/*if(!mChessGame->mRed->mRedKing->bDead){
		mChessGame->mRed->mRedKing->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedKing->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedKing->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedKing);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedBachelor[0]->bDead){
		mChessGame->mRed->mRedBachelor[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedBachelor[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedBachelor[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedBachelor[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedBachelor[1]->bDead){
		mChessGame->mRed->mRedBachelor[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedBachelor[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedBachelor[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedBachelor[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedMinister[0]->bDead){
		mChessGame->mRed->mRedMinister[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedMinister[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedMinister[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedMinister[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedMinister[1]->bDead){
		mChessGame->mRed->mRedMinister[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedMinister[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedMinister[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedMinister[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}	
	if(!mChessGame->mRed->mRedHorse[0]->bDead){
		mChessGame->mRed->mRedHorse[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedHorse[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedHorse[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedHorse[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedHorse[1]->bDead){
		mChessGame->mRed->mRedHorse[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedHorse[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedHorse[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedHorse[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedVehicle[0]->bDead){
		mChessGame->mRed->mRedVehicle[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedVehicle[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedVehicle[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedVehicle[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedVehicle[1]->bDead){
		mChessGame->mRed->mRedVehicle[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedVehicle[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedVehicle[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedVehicle[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedGun[0]->bDead){
		mChessGame->mRed->mRedGun[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedGun[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedGun[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedGun[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mRed->mRedGun[1]->bDead){
		mChessGame->mRed->mRedGun[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mRed->mRedGun[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedGun[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedGun[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	for(int j=0;j<5;j++){
		if(!mChessGame->mRed->mRedSolidier[j]->bDead){
			mChessGame->mRed->mRedSolidier[j]->FindCurAccess(cColor);
			for(int i=0;i<mChessGame->mRed->mRedSolidier[j]->GetCurAccessLen();i++){
				Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mRed->mRedSolidier[j]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mRed->mRedSolidier[j]);
				pmoves[iindex]=*tmpMove;
				delete tmpMove;
				iindex++;
			}
		}
	}*/
	return iindex;
}

int CFindWay::FBlack(Moves *pmoves,int &iindex,char *cColor){
	for(int k=0;k<90;k++){
		int x=k%9;
		int y=9-k/9;
		CChess *pchess=mChessGame->mChessBoard->GetPosition(x,y)->mPChess;
		if(pchess){
			if(pchess->mColor=="Black"){
				pchess->FindCurAccess(cColor);			
				for(int i=0;i<pchess->GetCurAccessLen();i++){
					Moves *tmpMove=new Moves((Vector2*)((int)(pchess->GetCurAccess())+i*sizeof(Vector2)),pchess);
					pmoves[iindex]=*tmpMove;
					delete tmpMove;
					iindex++;
				}
			}

		}
	}
	/*if(!mChessGame->mBlack->mBlackVehicle[0]->bDead){
		mChessGame->mBlack->mBlackVehicle[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackVehicle[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackVehicle[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackVehicle[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mBlack->mBlackHorse[0]->bDead){
		mChessGame->mBlack->mBlackHorse[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackHorse[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackHorse[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackHorse[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mBlack->mBlackMinister[0]->bDead){
		mChessGame->mBlack->mBlackMinister[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackMinister[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackMinister[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackMinister[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mBlack->mBlackBachelor[0]->bDead){
		mChessGame->mBlack->mBlackBachelor[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackBachelor[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackBachelor[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackBachelor[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mBlack->mBlackKing->bDead){
		mChessGame->mBlack->mBlackKing->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackKing->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackKing->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackKing);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	
	if(!mChessGame->mBlack->mBlackBachelor[1]->bDead){
		mChessGame->mBlack->mBlackBachelor[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackBachelor[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackBachelor[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackBachelor[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	
	if(!mChessGame->mBlack->mBlackMinister[1]->bDead){
		mChessGame->mBlack->mBlackMinister[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackMinister[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackMinister[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackMinister[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}	
	
	if(!mChessGame->mBlack->mBlackHorse[1]->bDead){
		mChessGame->mBlack->mBlackHorse[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackHorse[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackHorse[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackHorse[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	
	if(!mChessGame->mBlack->mBlackVehicle[1]->bDead){
		mChessGame->mBlack->mBlackVehicle[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackVehicle[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackVehicle[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackVehicle[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mBlack->mBlackGun[0]->bDead){
		mChessGame->mBlack->mBlackGun[0]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackGun[0]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackGun[0]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackGun[0]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	if(!mChessGame->mBlack->mBlackGun[1]->bDead){
		mChessGame->mBlack->mBlackGun[1]->FindCurAccess(cColor);
		for(int i=0;i<mChessGame->mBlack->mBlackGun[1]->GetCurAccessLen();i++){
			Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackGun[1]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackGun[1]);
			pmoves[iindex]=*tmpMove;
			delete tmpMove;
			iindex++;
		}
	}
	for(int j=0;j<5;j++){
		if(!mChessGame->mBlack->mBlackSolidier[j]->bDead){
			mChessGame->mBlack->mBlackSolidier[j]->FindCurAccess(cColor);
			for(int i=0;i<mChessGame->mBlack->mBlackSolidier[j]->GetCurAccessLen();i++){
				Moves *tmpMove=new Moves((Vector2*)((int)(mChessGame->mBlack->mBlackSolidier[j]->GetCurAccess())+i*sizeof(Vector2)),mChessGame->mBlack->mBlackSolidier[j]);
				pmoves[iindex]=*tmpMove;
				delete tmpMove;
				iindex++;
			}
		}
	}*/
	return iindex;
}
int CFindWay::GenerateMoves(Moves *pmoves,char *cColor){
	
	int iTmp=0;
	if(mPlayer1->GetIsChoosingChess()){
		if(mPlayer1->GetColor()=="Black"){
			iTmp=FBlack(pmoves,iTmp,cColor);
		}	
		if(mPlayer1->GetColor()=="Red"){
			iTmp=FRed(pmoves,iTmp,cColor);
		}	
	}
	if(mPlayer2->GetIsChoosingChess()){
		if(mPlayer2->GetColor()=="Black"){
			iTmp=FBlack(pmoves,iTmp,cColor);
		}
		if(mPlayer2->GetColor()=="Red"){
			iTmp=FRed(pmoves,iTmp,cColor);
		}
	}

	return iTmp;
	
}

bool CFindWay::GetBlackDead(){
	//int i, nGenMoveNum, pcCaptured;
	char *cColor="Red";
	Moves mvs[MAX_GEN_MOVES];

	int nGenMoveNum = GenerateMoves(mvs,cColor);
	for (int i = 0; i < nGenMoveNum; i ++) {
		CChess *pChess = MovePiece(&mvs[i]);
		if (!mChessGame->GetBlackChecked()) {
			UndoMovePiece(&mvs[i], pChess);
			return false;
		}
		else {
			UndoMovePiece(&mvs[i], pChess);
		}
	}
	return true;
}

bool CFindWay::GetRedDead(){
	//int i, nGenMoveNum, pcCaptured;
	char *cColor="Red";
	Moves mvs[MAX_GEN_MOVES];

	int nGenMoveNum = GenerateMoves(mvs,cColor);
	for (int i = 0; i < nGenMoveNum; i ++) {
		CChess *pChess = MovePiece(&mvs[i]);
		if (!mChessGame->GetRedChecked()) {
			UndoMovePiece(&mvs[i], pChess);
			return false;
		} 
		else {
			UndoMovePiece(&mvs[i], pChess);
		}
	}
	return true;
}

//int CFindWay::GetMovesLen(){
//	//return iindex;
//}

void CFindWay::AddPiece(Vector2 *pvec2,CChess *pchess){
	mChessGame->mChessBoard->GetPosition(pvec2->x,pvec2->y)->mPChess=pchess;
	pchess->GetPosition()->mPChess=0;
	//Vector2 pvec=*pvec2;
	pchess->SetPosition(pvec2->x,pvec2->y);	
	int temp=(12-pvec2->y)*16+pvec2->x+3;
	if(pchess->mColor=="Red"){		
		(mChessGame->vlWhite)+=cucvlPiecePos[pchess->ID][temp];
	}
	if(pchess->mColor=="Black"){
		(mChessGame->vlBlack)+=cucvlPiecePos[pchess->ID][254-temp];
	}
	pchess->bDead=0;
}
void CFindWay::DelPiece(Vector2 *pvec2,CChess *pchess){
	//if(pvec2->x!=DEL_VALUE)
		mChessGame->mChessBoard->GetPosition(pvec2->x,pvec2->y)->mPChess=0;		
	int temp=(12-pvec2->y)*16+pvec2->x+3;
	if(pchess->mColor=="Red"){		
		(mChessGame->vlWhite)-=cucvlPiecePos[pchess->ID][temp];
	}
	if(pchess->mColor=="Black"){
		(mChessGame->vlBlack)-=cucvlPiecePos[pchess->ID][254-temp];
	}
	pchess->bDead=1;
	//pchess->SetPosition(DEL_VALUE,DEL_VALUE);
}


int CFindWay::Evaluate() const{
	if(mPlayer1->GetIsChoosingChess()){
		if(mPlayer1->GetColor()=="Red")
			return mChessGame->vlWhite-mChessGame->vlBlack+ADVANCED_VALUE;
		else
			return mChessGame->vlBlack-mChessGame->vlWhite+ADVANCED_VALUE;
	}
	else{
		if(mPlayer2->GetColor()=="Red")
			return mChessGame->vlWhite-mChessGame->vlBlack+ADVANCED_VALUE;
		else
			return mChessGame->vlBlack-mChessGame->vlWhite+ADVANCED_VALUE;
	}
}

bool CFindWay::MoveChess(int x1,int y1,int x2,int y2){
	CChess *pchess=mChessGame->mChessBoard->GetPosition(x1,y1)->mPChess;
	Vector2 *pvec=mChessGame->mChessBoard->GetPosition(x2,y2);
	Moves *pmoves=new Moves(pvec,pchess);
	char *cColor="Red";
	//CChess *pchess=pmoves->chess;
	int iTmp=0;
	Vector2 *pVec2=0;
	if(pchess){
		pchess->FindCurAccess(cColor);
		iTmp=pchess->GetCurAccessLen();
		pVec2=pchess->GetCurAccess();
	}		

	for(int i=0;i<iTmp;i++){
		//printf(" %d %d\n",((Vector2*)((int)pVec2+i*sizeof(Vector2)))->x,((Vector2*)((int)pVec2+i*sizeof(Vector2)))->y);
		if(((Vector2*)((int)pVec2+i*sizeof(Vector2)))->x==pmoves->vec.x/*x2*/&&((Vector2*)((int)pVec2+i*sizeof(Vector2)))->y==pmoves->vec.y/*y2*/){
			MovePiece(pmoves);
			mChessGame->iStepNumber++;
			bool bTmp=mPlayer1->GetIsChoosingChess();
			mPlayer1->SetIsChoosingChess(1-bTmp);
			mPlayer2->SetIsChoosingChess(bTmp);
			return true;
		}
	}

	delete pmoves;
	return false;
}

void CFindWay::UndoMoveChess(/*Moves *pmoves,CChess *pchess*/int x1,int y1,int x2,int y2,CChess *pchess){
	CChess *pchess1=mChessGame->mChessBoard->GetPosition(x2,y2)->mPChess;
	Vector2 *pvec2=mChessGame->mChessBoard->GetPosition(x2,y2);
	Moves *pmoves=new Moves(pvec2,pchess1);	
	//int iTmp=0;
	//Vector2 *pVec2=0;
	UndoMovePiece(pmoves,pchess);
	/*DelPiece(pmoves->vec,pmoves->chess);
	AddPiece(pmoves->chess->GetPosition(),pmoves->chess);
	if(pchess){
		AddPiece(pmoves->vec,pchess);
	}*/
	mChessGame->iStepNumber--;
	bool bTmp=mPlayer1->GetIsChoosingChess();
	mPlayer1->SetIsChoosingChess(1-bTmp);
	mPlayer2->SetIsChoosingChess(bTmp);
	delete pmoves;
}

bool CFindWay::MoveChess(Moves *pmoves/*int x1,int y1,int x2,int y2,char *cColor*/){
	//CChess *pchess=mChessGame->mChessBoard->GetPosition(x1,y1)->mPChess;
	//Vector2 *pvec2=mChessGame->mChessBoard->GetPosition(x2,y2);
	//Moves *pmoves=new Moves(pvec2,pchess);
	char *cColor="Red";
	CChess *pchess=pmoves->chess;
	int iTmp=0;
	Vector2 *pVec2=0;
	if(pchess){
		pchess->FindCurAccess(cColor);
		iTmp=pchess->GetCurAccessLen();
		pVec2=pchess->GetCurAccess();
	}		
	
	for(int i=0;i<iTmp;i++){
		//printf(" %d %d\n",((Vector2*)((int)pVec2+i*sizeof(Vector2)))->x,((Vector2*)((int)pVec2+i*sizeof(Vector2)))->y);
		if(((Vector2*)((int)pVec2+i*sizeof(Vector2)))->x==pmoves->vec.x/*x2*/&&((Vector2*)((int)pVec2+i*sizeof(Vector2)))->y==pmoves->vec.y/*y2*/){
			MovePiece(pmoves);
			mChessGame->iStepNumber++;
			bool bTmp=mPlayer1->GetIsChoosingChess();
			mPlayer1->SetIsChoosingChess(1-bTmp);
			mPlayer2->SetIsChoosingChess(bTmp);
			return true;
		}
	}
	
	//delete pmoves;
	return false;
}

void CFindWay::UndoMoveChess(Moves *pmoves,CChess *pchess/*int x1,int y1,int x2,int y2,CChess *pchess*/){
	//CChess *pchess=mChessGame->mChessBoard->GetPosition(x1,y1)->mPChess;
	//Vector2 *pvec2=mChessGame->mChessBoard->GetPosition(x2,y2);
	//Moves *pmoves=new Moves(pvec2,pchess);	
	//int iTmp=0;
	//Vector2 *pVec2=0;
	UndoMovePiece(pmoves,pchess);
	/*DelPiece(pmoves->vec,pmoves->chess);
	AddPiece(pmoves->chess->GetPosition(),pmoves->chess);
	if(pchess){
		AddPiece(pmoves->vec,pchess);
	}*/
	mChessGame->iStepNumber--;
	bool bTmp=mPlayer1->GetIsChoosingChess();
	mPlayer1->SetIsChoosingChess(1-bTmp);
	mPlayer2->SetIsChoosingChess(bTmp);
	//delete pmoves;
}

CChess* CFindWay::MovePiece(Moves *pmoves){
	CChess *pchess=mChessGame->mChessBoard->GetPosition(pmoves->vec.x,pmoves->vec.y)->mPChess;
	if(pchess){
		DelPiece(&pmoves->vec,pchess);
	}
	DelPiece(&pmoves->vec2,pmoves->chess);
	AddPiece(&pmoves->vec,pmoves->chess);
	return pchess;
}

void CFindWay::UndoMovePiece(Moves *pmoves,CChess *pchess){
	DelPiece(&pmoves->vec,pmoves->chess);
	AddPiece(&(pmoves->vec2),pmoves->chess);
	if(pchess){
		AddPiece(&pmoves->vec,pchess);
	}
}

bool CFindWay::MakeMove(Moves *pmoves,int &pchess){
	pchess=(int)MovePiece(pmoves);
	if(pmoves->chess->mColor=="Black"){
		if(mChessGame->GetBlackChecked()){
			UndoMovePiece(pmoves,(CChess*)pchess);
			return false;
		}
	}
	if(pmoves->chess->mColor=="Red"){
		if(mChessGame->GetRedChecked()){
			UndoMovePiece(pmoves,(CChess*)pchess);
			return false;
		}
	}
	bool bTmp=mPlayer1->GetIsChoosingChess();
	mPlayer1->SetIsChoosingChess(1-bTmp);
	mPlayer2->SetIsChoosingChess(bTmp);
	(mChessGame->nDistance)++;
	iMove++;
	return true;
}

void CFindWay::UndoMakeMove(Moves *pmoves,int &pchess){
	(mChessGame->nDistance)--;
	iUndoMove++;
	bool bTmp=mPlayer1->GetIsChoosingChess();
	mPlayer1->SetIsChoosingChess(1-bTmp);
	mPlayer2->SetIsChoosingChess(bTmp);
	UndoMovePiece(pmoves,(CChess*)pchess);
}
int CFindWay::MOVE(Moves *pmoves) {
	int sqSrc=(12-pmoves->vec2.y)*16+pmoves->vec2.x+3;
	int sqDst=(12-pmoves->vec.y)*16+pmoves->vec.x+3;
	return sqSrc + sqDst * 256;
}
int CFindWay::CompareHistory(const void *lpmv1, const void *lpmv2){
	
	int a=((CFindWay*)0)->MOVE((Moves*)lpmv1);
	int b=((CFindWay*)0)->MOVE((Moves*)lpmv2);
	//int a=(12-((Moves*)lpmv1)->vec2.y)*16+((Moves*)lpmv1)->vec2.x+3;
	//int b=(12-((Moves*)lpmv2)->vec2.y)*16+((Moves*)lpmv2)->vec2.x+3;
	return Search.nHistoryTable[b] - Search.nHistoryTable[a];
}
int CFindWay::SearchFull(int vlAlpha, int vlBeta, int nDepth,char *cColor){
	
	if(nDepth==0){
		return this->Evaluate();
	}
	int vlBest = -MATE_VALUE; 
	Moves *pmvBest = 0;	
	//Moves *mvs=new Moves[MAX_GEN_MOVES];
	Moves mvs[MAX_GEN_MOVES];
	int nGenMoves = this->GenerateMoves(mvs,cColor);
	
	qsort(mvs, nGenMoves, sizeof(Moves), CompareHistory);
	int pchess=0;
	int vl=0;
	for (int i = 0; i < nGenMoves; i ++) {
		//Moves moves=mvs[i];
		if (this->MakeMove(&mvs[i],pchess)) {			
			vl = -SearchFull(-vlBeta, -vlAlpha, nDepth - 1,cColor);				
			this->UndoMakeMove(&mvs[i], pchess);			
			if (vl > vlBest) {   
				vlBest = vl;       
				if (vl >= vlBeta) { 
					pmvBest = &mvs[i];  
					break;            
				}
				if (vl > vlAlpha) {
					pmvBest = &mvs[i];  
					vlAlpha = vl;     
				}
			}
		}
	}
	if (vlBest == -MATE_VALUE) {
		// 如果是杀棋，就根据杀棋步数给出评价
		return mChessGame->nDistance - MATE_VALUE;
	}
	if (pmvBest != 0) {
		// 如果不是Alpha走法，就将最佳走法保存到历史表
		int a=MOVE(pmvBest);
		Search.nHistoryTable[MOVE(pmvBest)] += nDepth * nDepth;
		if (mChessGame->nDistance == 0) {
			// 搜索根节点时，总是有一个最佳走法(因为全窗口搜索不会超出边界)，将这个走法保存下来
			Search.mvResult =*pmvBest;
		}
	}
	return vlBest;
	
}

void CFindWay::SearchMain() {	
	char *cColor="Red";
	memset(Search.nHistoryTable, 0, 65536 * sizeof(int)); // 清空历史表
	int t = clock();       // 初始化定时器
	mChessGame->nDistance = 0; // 初始步数

	// 迭代加深过程
	for (int i = 1; i <= LIMIT_DEPTH; i ++) {
		int vl = SearchFull(-MATE_VALUE, MATE_VALUE, i,cColor);
		// 搜索到杀棋，就终止搜索
		if (vl > WIN_VALUE || vl < -WIN_VALUE) {
			break;
		}
		// 超过一秒，就终止搜索
		/*if (clock() - t > CLOCKS_PER_SEC) {
			break;
		}*/
	}
}

Moves CFindWay::FindWay(){
	this->SearchMain();
	return Search.mvResult;
}