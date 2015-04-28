//#include "StdAfx.h"
#include "Player1.h"
#include "MoveChess.h"

CPlayer1::CPlayer1(char *cColor)
{
	if(cColor=="Red")
		mChooseChess=true;
	if(cColor=="Black")
		mChooseChess=false;
	mColor=cColor;
}


CPlayer1::~CPlayer1(void)
{
}

bool CPlayer1::GetIsChoosingChess()
{       
	return mChooseChess;
}

void CPlayer1::SetColor()
{
	mColor="Red";
}

char *CPlayer1::GetColor()
{
	return mColor;
}

void CPlayer1::SetName()
{
	mName="Player1";
}

char * CPlayer1::GetName()
{
	return mName;
}

void CPlayer1::SetIsChoosingChess(bool ib)
{
	mChooseChess=ib;//mPMoveChess->GetPlayer2MoveChessState();
}
