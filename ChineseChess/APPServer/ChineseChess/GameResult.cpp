//#include "StdAfx.h"
#include "GameResult.h"


CGameResult::CGameResult(void)
{
}


CGameResult::~CGameResult(void)
{
}

int CGameResult::GetBlackResult()
{
	if (mBlack->GetDefeat())
	{
		return -1;
	}
	if (mBlack->GetSuccess())
	{
		return 1;
	}
	if (mBlack->GetDraw())
	{
		return 0;
	}
}

int CGameResult::GetRedResult()
{
	if (mRed->GetDefeat())
	{
		return -1;
	}
	if (mRed->GetSuccess())
	{
		return 1;
	}
	if (mRed->GetDraw())
	{
		return 0;
	}
}
