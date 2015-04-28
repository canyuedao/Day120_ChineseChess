#include "RedKing.h"


CRedKing::CRedKing(char *cColor,CChessBoard *pChessBoard)
{
	mChessBoard=pChessBoard;
	mColor="Red";
	ID=0;
	bDead=0;
	mAllAccessLen=9;
	mCurAccessLen=4;
	mAllAccess=new Vector2[mAllAccessLen];
	mCurAccess=new Vector2[mCurAccessLen];
	if(cColor=="Red"){
		mPosition=new Vector2(4,0)/*mChessBoard->GetPosition(4,0)*/;
		mChessBoard->GetPosition(4,0)->mPChess=this;
	}
	if(cColor=="Black"){
		mPosition=new Vector2(4,9)/*mChessBoard->GetPosition(4,9)*/;
		mChessBoard->GetPosition(4,9)->mPChess=this;
	}
	//FindAllAccess(cColor);
	//FindCurAccess(cColor);
}


CRedKing::~CRedKing(void)
{
	delete []mAllAccess;
	delete []mCurAccess;
	delete mPosition;
}

void CRedKing::FindCurAccess(char *cColor){
	int x=mPosition->x;
	int y=mPosition->y;
	int iindex=0;
	
	if(cColor=="Red"){
		if(y+1<3){	
			if((!(mChessBoard->GetPosition(x,y+1)->mPChess)||(mChessBoard->GetPosition(x,y+1)->mPChess->mColor=="Black"))){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y+1));
				iindex++;
			}			
		}
		if(y-1>=0){		
			if((!((mChessBoard->GetPosition(x,y-1))->mPChess))||(mChessBoard->GetPosition(x,y-1)->mPChess->mColor=="Black")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y-1));
				iindex++;
			}			
		}

	}
	if(cColor=="Black"){
		if(y+1<10){	
			if((!(mChessBoard->GetPosition(x,y+1)->mPChess)||(mChessBoard->GetPosition(x,y+1)->mPChess->mColor=="Black"))){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y+1));
				iindex++;
			}			
		}
		if(y-1>=7){	
			if((!((mChessBoard->GetPosition(x,y-1))->mPChess))||(mChessBoard->GetPosition(x,y-1)->mPChess->mColor=="Black")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y-1));
				iindex++;
			}
			
		}

	}
	if(x+1<6){	
		if((!((mChessBoard->GetPosition(x+1,y))->mPChess))||(mChessBoard->GetPosition(x+1,y)->mPChess->mColor=="Black")){
			mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y));
			iindex++;
		}
		
	}
	if(x-1>=3){	
		if((!((mChessBoard->GetPosition(x-1,y))->mPChess))||(mChessBoard->GetPosition(x-1,y)->mPChess->mColor=="Black")){
			mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y));
			iindex++;
		}
		
	}
	mCurAccessLen=iindex;
}
void CRedKing::FindAllAccess(char *cColor){
	int iindex=0;
	if(cColor=="Red"){
		for(int i=3;i<6;i++){
			for(int j=0;j<3;j++){
				mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
				iindex++;
			}
		}
	}
	if(cColor=="Black"){
		for(int i=3;i<6;i++){
			for(int j=7;j<10;j++){
				mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
				iindex++;
			}
		}
	}
}
