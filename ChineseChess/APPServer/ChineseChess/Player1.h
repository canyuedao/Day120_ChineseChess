#pragma once
//#include "Black.h"
//#include "Red.h"
//class CMoveChess;
class CPlayer1
{
public:
	CPlayer1(char*);
	~CPlayer1(void);
	bool GetIsChoosingChess();
	void SetIsChoosingChess(bool);
	void SetColor();
	void SetName();
	char *GetColor();
	char *GetName();
public:
	//CRed *mRed;
	//CBlack *mBlack;
private:
	
	//CMoveChess *mPMoveChess;
	bool mChooseChess;
	char *mColor;
	char *mName;
};

