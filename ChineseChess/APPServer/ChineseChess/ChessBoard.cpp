#include "ChessBoard.h"

CChessBoard::CChessBoard(void)
{
	for(int i=0;i<9;i++){
		for(int j=0;j<10;j++){
			mAllBoardPosition[i][j]=new Vector2(i,j);
		}
	}
}


CChessBoard::~CChessBoard(void)
{
	for(int i=0;i<9;i++){
		for(int j=0;j<10;j++){
			delete mAllBoardPosition[i][j];
		}
	}
	//delete mAllBoardPosition;
}

Vector2* CChessBoard::GetPosition(int i,int j){
	return mAllBoardPosition[i][j];
}