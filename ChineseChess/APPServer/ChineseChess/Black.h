#pragma once
#include "BlackBachelor.h"
#include "BlackMinister.h"
#include "BlackKing.h"
#include "BlackGun.h"
#include "BlackHorse.h"
#include "BlackSolidier.h"
#include "BlackVehicle.h"
#include "ChessBoard.h"
class CBlack
{
public:
	CBlack(char*,CChessBoard*);
	~CBlack(void);
	void AdimitDefeat();
	bool RequestWin();
	void RequestADraw();
	bool GetDefeat();
	bool GetSuccess();
	bool GetDraw();
	CBlackKing *mBlackKing;
	CBlackBachelor *mBlackBachelor[2];
	CBlackVehicle *mBlackVehicle[2];
	CBlackMinister *mBlackMinister[2];
	CBlackHorse *mBlackHorse[2];
	CBlackGun *mBlackGun[2];
	CBlackSolidier *mBlackSolidier[5];
private:
	
	bool mFailed;
	bool mSuccess;
	bool mDraw;
	//char *mColor;
};

