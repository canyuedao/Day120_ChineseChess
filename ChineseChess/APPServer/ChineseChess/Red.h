#pragma once
#include "RedBachelor.h"
#include "RedGun.h"
#include "RedHorse.h"
#include "RedKing.h"
#include "RedMinister.h"
#include "RedSolidier.h"
#include "RedVehicle.h"
#include "ChessBoard.h"
class CRed
{
public:
	CRed(char*,CChessBoard*);
	~CRed(void);
	void AdimitDefeat();
	bool RequestWin();
	void RequestADraw();
	bool GetDefeat();
	bool GetSuccess();
	bool GetDraw();
	CRedKing *mRedKing;
	CRedBachelor *mRedBachelor[2];
	CRedVehicle *mRedVehicle[2];
	CRedMinister *mRedMinister[2];
	CRedHorse *mRedHorse[2];
	CRedGun *mRedGun[2];
	CRedSolidier *mRedSolidier[5];
private:

	bool mFailed;
	bool mSuccess;
	bool mDraw;
	char *mColor;
};

