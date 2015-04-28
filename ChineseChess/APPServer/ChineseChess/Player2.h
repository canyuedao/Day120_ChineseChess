#pragma once
//#include "Black.h"
//#include "Red.h"
class CMoveChess;
class CPlayer2
{
public:
	CPlayer2(char*);
	~CPlayer2(void);
	bool GetIsChoosingChess();
	void SetIsChoosingChess(bool);
	//void SetChoosingChess();
	void SetColor();
	char *GetColor();
	void SetName();
	char *GetName();
public:
	//CRed *mRed;
	//CBlack *mBlack;
private:
	
	CMoveChess *mPMoveChess;
	bool mChooseChess;
	char *mColor;
	char *mName;
};

