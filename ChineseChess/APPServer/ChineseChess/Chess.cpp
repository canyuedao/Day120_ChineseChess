#include "Chess.h"

void CChess::SetPosition(int i,int j){
	//mPosition=mChessBoard->GetPosition(i,j);
	mPosition->x=i;
	mPosition->y=j;
	mPosition->mPChess=this;
}
Vector2* CChess::GetPosition(){
	return mPosition;
}

Vector2* CChess::GetCurAccess(){
	return mCurAccess;
}
Vector2* CChess::GetAllAccess(){
	return mAllAccess;
}
int CChess::GetCurAccessLen(){
	return mCurAccessLen;
}
int CChess::GetAllAccessLen(){
	return mAllAccessLen;
}
