//#include "StdAfx.h"
#include "MoveChess.h"


CMoveChess::CMoveChess(CChessGame *pChessGame,CChooseChess *pChooseChess)
{
	//mChooseChess->SetPlayer1Suc(false);
	//mChooseChess->SetPlayer2Suc(false);
	mPlayer1Success=false;
	mPlayer2Success=false;
	mPChessGame=pChessGame;
	mPChooseChess=pChooseChess;
}


CMoveChess::~CMoveChess(void)
{
}

bool CMoveChess::MoveChess(int x1,int y1,int x2,int y2){
	CChess *pChess=mPChooseChess->GetChess(x1,y1);
	Vector2 *pVec2=pChess->GetCurAccess();
	int iTmp=pChess->GetCurAccessLen();
	for(int i=0;i<iTmp;i++){
		Vector2 *vecTmp=new Vector2(x2,y2);
		if(((Vector2*)(pVec2+i*sizeof(Vector2)))->x==x2&&((Vector2*)(pVec2+i*sizeof(Vector2)))->y==y2){

			return true;
		}
	}
	return false;
}

bool CMoveChess::Player1MoveChess( Vector2 *v2 )
{
	/*for(int i=0;i<mFindWay->GetCurAccessLen();i++)
	{
	if((Vector2*)(mFindWay->FindWay()+i*sizeof(Vector2))==v2)
	{
	mPlayer1Success=true;
	break;
	}
	}*/
	return mPlayer1Success;
}

bool CMoveChess::Player2MoveChess( Vector2 *v2 )
{
	/*for(int i=0;i<mFindWay->GetCurAccessLen();i++)
	{
	if((mFindWay->FindWay()+i)==v2)
	{
	mPlayer2Success=true;
	break;
	}
	}*/
	return mPlayer2Success;
}

bool CMoveChess::GetPlayer1MoveChessState()
{
	return mPlayer1Success;
}

bool CMoveChess::GetPlayer2MoveChessState()
{
	return mPlayer2Success;
}

void CMoveChess::SetPlayer1Suc(bool ib)
{
	mPlayer1Success=ib;
}

void CMoveChess::SetPlayer2Suc( bool ib)
{
	mPlayer2Success=ib;
}
