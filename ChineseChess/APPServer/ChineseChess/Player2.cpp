//#include "StdAfx.h"
#include "Player2.h"
#include "MoveChess.h"

CPlayer2::CPlayer2(char *cColor)
{
	if(cColor=="Red")
		mChooseChess=true;
	if(cColor=="Black")
		mChooseChess=false;
	mColor=cColor;
}


CPlayer2::~CPlayer2(void)
{
}

bool CPlayer2::GetIsChoosingChess()
{
	return mChooseChess;
}

void CPlayer2::SetColor()
{
	mColor="Black";
}

char *CPlayer2::GetColor()
{
	return mColor;
}

char * CPlayer2::GetName()
{
	return mName; 
}

void CPlayer2::SetName()
{
	mName="Player2";
}

void CPlayer2::SetIsChoosingChess(bool ib)
{
	mChooseChess=ib;//mPMoveChess->GetPlayer1MoveChessState();
}
