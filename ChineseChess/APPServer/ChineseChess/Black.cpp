//#include "StdAfx.h"
#include "Black.h"
CBlack::CBlack(char *mColor,CChessBoard *pChessBoard)
{
	//mColor="Black";
	int x=-2;
	for(int i=0;i<5;i++)
	{  
		mBlackSolidier[i]=new CBlackSolidier(mColor,x+=2,pChessBoard);
	}
		mBlackVehicle[0]=new CBlackVehicle(mColor,0,pChessBoard);
		mBlackVehicle[1]=new CBlackVehicle(mColor,8,pChessBoard);
		mBlackMinister[0]=new CBlackMinister(mColor,2,pChessBoard);
		mBlackMinister[1]=new CBlackMinister(mColor,6,pChessBoard);
		mBlackHorse[0]=new CBlackHorse(mColor,1,pChessBoard);
		mBlackHorse[1]=new CBlackHorse(mColor,7,pChessBoard);
		mBlackGun[0]=new CBlackGun(mColor,1,pChessBoard);
		mBlackGun[1]=new CBlackGun(mColor,7,pChessBoard);
		mBlackBachelor[0]=new CBlackBachelor(mColor,3,pChessBoard);
		mBlackBachelor[1]=new CBlackBachelor(mColor,5,pChessBoard);
	mBlackKing=new CBlackKing(mColor,pChessBoard);
	mFailed=false;
	mSuccess=false;
	mDraw=false;
}


CBlack::~CBlack(void)
{
	for(int i=0;i<5;i++)
	{
		delete mBlackSolidier[i];
	}
	for(int i=0;i<2;i++)
	{
		delete mBlackVehicle[i];
		delete mBlackMinister[i];
		delete mBlackHorse[i];
		delete mBlackGun[i];
		delete mBlackBachelor[i];
	}
	delete mBlackKing;
}

void CBlack::AdimitDefeat()
{
	if(!mDraw&&!mSuccess)
		mFailed=true;
	else
		mFailed=false;
}

bool CBlack::RequestWin()
{
	if(!mDraw&&!mFailed)
	{
		mSuccess=true;
		return mSuccess;
	}
	else
		return false;
	
}

void CBlack::RequestADraw()
{
	if(!mSuccess&&!mFailed)
	mDraw=true;
}

bool CBlack::GetDefeat()
{
	return (mBlackKing==0||mFailed);
}

bool CBlack::GetSuccess()
{
	return mSuccess;
}

bool CBlack::GetDraw()
{
     return mDraw;
}
