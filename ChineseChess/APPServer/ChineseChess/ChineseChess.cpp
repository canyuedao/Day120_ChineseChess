#include <stdio.h>
#include "ChessGame.h"
//#include "Player1.h"
//#include "Player2.h"
//#include "FindWay.h"

int ttmain(){
	CChessGame *pChessGame=new CChessGame();
	//CPlayer1 *pPlayer1=new CPlayer1("Red");
	//CPlayer2 *pPlayer2=new CPlayer2("Black");
	//CFindWay *pFindWay=new CFindWay(/*pPlayer1,pPlayer2,*/pChessGame);
	/*pChessGame->mChessBoard->GetPosition(7,7)->mPChess->FindCurAccess("Red");
	int k=pChessGame->mChessBoard->GetPosition(7,7)->mPChess->GetCurAccessLen();
	printf("可走坐标数：%d",k);
	
	if(pFindWay->MoveChess(7 ,7, 7,0,"Red"))
		{
			
			printf("\n朕准了");	
			
		}*/
	
	

	//CChess *pchess=pChessGame->mChessBoard->GetPosition(0,0)->mPChess;
	//Vector2 *vec2=pChessGame->mChessBoard->GetPosition(0,1);
	//CChess *pchess2=vec2->mPChess;
	//Moves *pmoves=new Moves(vec2,pchess);
	//pChessGame->mFindWay->MoveChess(1,2,4,2);
	
	//pFindWay->UndoMoveChess(pmoves,pchess2);

	Moves *pmoves1=&pChessGame->mFindWay->FindWay();
	pChessGame->mFindWay->MoveChess(pmoves1);

	//pchess=pChessGame->mChessBoard->GetPosition(0,1)->mPChess;
	//vec2=pChessGame->mChessBoard->GetPosition(0,0);
	//pmoves=new Moves(vec2,pchess);
	pChessGame->mFindWay->MoveChess(1,7,4,7);

	pmoves1=&pChessGame->mFindWay->FindWay();
	pChessGame->mFindWay->MoveChess(pmoves1);

	pChessGame->mFindWay->MoveChess(2,6,2,5);
	
	pmoves1=&pChessGame->mFindWay->FindWay();
	pChessGame->mFindWay->MoveChess(pmoves1);
	//CChess *pchess=pChessGame->mChessBoard->GetPosition(7,7)->mPChess;
	//pchess=pChessGame->mChessBoard->GetPosition(7,0)->mPChess;
	//int i=pChessGame->mChessBoard->GetPosition(7,7)->mPChess->GetCurAccessLen();
	//printf("可走坐标数：%d",i);
	return 0;
}