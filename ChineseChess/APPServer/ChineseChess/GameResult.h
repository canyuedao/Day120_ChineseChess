#pragma once
#include "BlockedRule.h"
#include "Black.h"
#include "Red.h"
class CGameResult
{

public:
	int GetBlackResult();
	int GetRedResult();
	CGameResult(void);
	~CGameResult(void);
private:
	CBlack * mBlack;
	CRed * mRed;
	CBlockedRule * mBlackedRule;
	
};

