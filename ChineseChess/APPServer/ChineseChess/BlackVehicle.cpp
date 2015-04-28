#include "BlackVehicle.h"


CBlackVehicle::CBlackVehicle(char *cColor,int x,CChessBoard *pChessBoard)
{
	mChessBoard=pChessBoard;
	mColor="Black";
	ID=4;
	bDead=0;
	mAllAccessLen=90;
	mCurAccessLen=17;
	mAllAccess=new Vector2[mAllAccessLen];
	mCurAccess=new Vector2[mCurAccessLen];
	if(cColor=="Black"){
		mPosition=new Vector2(x,0)/*mChessBoard->GetPosition(x,0)*/;
		mChessBoard->GetPosition(x,0)->mPChess=this;
	}
	if(cColor=="Red"){
		mPosition=new Vector2(x,9)/*mChessBoard->GetPosition(x,9)*/;
		mChessBoard->GetPosition(x,9)->mPChess=this;
	}
	//FindAllAccess(cColor);
	//FindCurAccess(cColor);
}


CBlackVehicle::~CBlackVehicle(void)
{
	delete []mAllAccess;
	delete []mCurAccess;
	delete mPosition;
}
void CBlackVehicle::FindCurAccess(char *cColor){
	int x=mPosition->x;
	int y=mPosition->y;
	int iRight=0,iLeft=0,iUp=0,iDown=0;	
	
	while(x+iRight+1<9){		
		if(!((mChessBoard->GetPosition(x+iRight+1,y))->mPChess)){
			mCurAccess[iRight]=*(mChessBoard->GetPosition(x+iRight+1,y));
			iRight++;
			continue;
		}
		if(mChessBoard->GetPosition(x+iRight+1,y)->mPChess->mColor=="Red"){
			mCurAccess[iRight]=*(mChessBoard->GetPosition(x+iRight+1,y));
			iRight++;
			break;
		}
		break;
		/*else
			iRight--;
		break;*/
	}
	while(x-iLeft-1>=0){
		if(!((mChessBoard->GetPosition(x-iLeft-1,y))->mPChess)){
			mCurAccess[iRight+iLeft]=*(mChessBoard->GetPosition(x-iLeft-1,y));
			iLeft++;
			continue;
		}
		if(mChessBoard->GetPosition(x-iLeft-1,y)->mPChess->mColor=="Red"){
			mCurAccess[iRight+iLeft]=*(mChessBoard->GetPosition(x-iLeft-1,y));
			iLeft++;
			break;
		}
		break;
		/*else
			iLeft--;
		break;*/
	}	
	while(y+iUp+1<10){
		if(!((mChessBoard->GetPosition(x,y+iUp+1))->mPChess)){
			mCurAccess[iRight+iLeft+iUp]=*(mChessBoard->GetPosition(x,y+iUp+1));
			iUp++;
			continue;
		}
		if(mChessBoard->GetPosition(x,y+iUp+1)->mPChess->mColor=="Red"){
			mCurAccess[iRight+iLeft+iUp]=*(mChessBoard->GetPosition(x,y+iUp+1));
			iUp++;
			break;
		}
		break;
		/*else
			iUp--;
		break;*/
	}	
	while(y-iDown-1>=0){
		if(!((mChessBoard->GetPosition(x,y-iDown-1))->mPChess)){
			mCurAccess[iRight+iLeft+iUp+iDown]=*(mChessBoard->GetPosition(x,y-iDown-1));
			iDown++;
			continue;
		}
		if(mChessBoard->GetPosition(x,y-iDown-1)->mPChess->mColor=="Red"){
			mCurAccess[iRight+iLeft+iUp+iDown]=*(mChessBoard->GetPosition(x,y-iDown-1));
			iDown++;
			break;
		}
		break;
		/*else
			iDown--;
		break;*/
	}	
	mCurAccessLen=iRight+iLeft+iUp+iDown;
}
void CBlackVehicle::FindAllAccess(char *cColor){	
	int iindex=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<10;j++){
			mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
			iindex++;
		}	
	}
}