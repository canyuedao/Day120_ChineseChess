//#include "StdAfx.h"
#include "ChooseChess.h"


CChooseChess::CChooseChess(CChessBoard *pChessBoard)
{
	//mPlayer1->SetIsChoosingChess(false);
	//mPlayer2->SetIsChoosingChess(false);
	mPlayer1Success=false;
	mPlayer2Success=false;
	mPChessBoard=pChessBoard;
}


CChooseChess::~CChooseChess(void)
{
}

bool CChooseChess::GetPlayer1Suc()
{
	return mPlayer1Success;
}
bool CChooseChess::GetPlayer2Suc()
{
	return mPlayer2Success;
}

CChess * CChooseChess::GetChess(int x,int y)
{
	mChess=mPChessBoard->GetPosition(x,y)->mPChess;
	return mChess;
}

//CChess * CChooseChess::GetPlayer2Chess( Vector2 v2 )
//{
//	mChess=mPChessBoard->GetPosition(v2.x,v2.y)->mPChess;
//	return mChess;
//}

void CChooseChess::SetPlayer1Suc(bool ib)
{
	mPlayer1Success=ib;
	//mPlayer1Success=m_pPlayer2->GetIsChoosingChess()&&mChess->mColor==m_pPlayer1->GetColor();
}

void CChooseChess::SetPlayer2Suc(bool ib)
{
    
	mPlayer2Success=ib;//m_pPlayer1->GetIsChoosingChess()&&mChess->mColor==m_pPlayer2->GetColor();
}
