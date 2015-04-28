//#include "StdAfx.h"
#include "Red.h"


CRed::CRed(char *mColor,CChessBoard *pChessBoard)
{
	//mColor="Red";
	mRedVehicle[0]=new CRedVehicle(mColor,0,pChessBoard);
	mRedVehicle[1]=new CRedVehicle(mColor,8,pChessBoard);
	mRedMinister[0]=new CRedMinister(mColor,2,pChessBoard);
	mRedMinister[1]=new CRedMinister(mColor,6,pChessBoard);
	mRedHorse[0]=new CRedHorse(mColor,1,pChessBoard);
	mRedHorse[1]=new CRedHorse(mColor,7,pChessBoard);
	 mRedGun[0]=new CRedGun(mColor,1,pChessBoard);
	 mRedGun[1]=new CRedGun(mColor,7,pChessBoard);
	 mRedBachelor[0]=new CRedBachelor(mColor,3,pChessBoard);
	 mRedBachelor[1]=new CRedBachelor(mColor,5,pChessBoard);
	 int x=-2;
	for(int i=0;i<5;i++)
	{
		mRedSolidier[i]=new CRedSolidier(mColor,x+=2,pChessBoard);
	}
	mRedKing=new CRedKing(mColor,pChessBoard);
	mDraw=false;
	mFailed=false;
	mSuccess=false;
}


CRed::~CRed(void)
{
	for(int i=0;i<5;i++)
	{
		delete mRedSolidier[i];
	}
	for(int i=0;i<2;i++)
	{
		delete mRedVehicle[i];
		delete mRedMinister[i];
		delete mRedHorse[i];
		delete mRedGun[i];
		delete mRedBachelor[i];
	}
	delete mRedKing;
}

void CRed::AdimitDefeat()
{
	if(!mSuccess&&!mDraw)
		mFailed=true;
	else
		mFailed=false;
}

bool CRed::RequestWin()
{
	if(!mDraw&&!mFailed)
	{
		mSuccess=true;
		return true;
	}
	else
		return false;
}

void CRed::RequestADraw()
{
	if(!mSuccess&&!mFailed)
	mDraw=true;
}

bool CRed::GetDefeat()
{
	return (mRedKing==0||mFailed);
}

bool CRed::GetSuccess()
{
	return mSuccess;
}

bool CRed::GetDraw()
{
	return mDraw;
}
