#include "BlackKing.h"

CBlackKing::CBlackKing(char* cColor,CChessBoard *pChessBoard){
	mChessBoard=pChessBoard;
	mColor="Black";
	ID=0;
	bDead=0;
	mAllAccessLen=9;
	mCurAccessLen=4;
	mAllAccess=new Vector2[mAllAccessLen];
	mCurAccess=new Vector2[mCurAccessLen];
	if(cColor=="Black"){
		mPosition=new Vector2(4,0)/*mChessBoard->GetPosition(4,0)*/;
		mChessBoard->GetPosition(4,0)->mPChess=this;
	}
	if(cColor=="Red"){
		mPosition=new Vector2(4,9)/*mChessBoard->GetPosition(4,9)*/;
		mChessBoard->GetPosition(4,9)->mPChess=this;
	}
	//FindAllAccess(cColor);
	//FindCurAccess(cColor);
}
CBlackKing::~CBlackKing(void){
	delete []mAllAccess;
	delete []mCurAccess;
	delete mPosition;
}

void CBlackKing::FindCurAccess(char *cColor){
	int x=mPosition->x;
	int y=mPosition->y;
	int iindex=0;
	
	if(cColor=="Black"){
		if(y+1<3){		
			if((!(mChessBoard->GetPosition(x,y+1)->mPChess)||(mChessBoard->GetPosition(x,y+1)->mPChess->mColor=="Red"))){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y+1));
				iindex++;
			}
			
		}
		if(y-1>=0){	
			if((!((mChessBoard->GetPosition(x,y-1))->mPChess))||(mChessBoard->GetPosition(x,y-1)->mPChess->mColor=="Red")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y-1));
				iindex++;
			}
			
		}

	}
	if(cColor=="Red"){
		if(y+1<10){	
			if((!(mChessBoard->GetPosition(x,y+1)->mPChess)||(mChessBoard->GetPosition(x,y+1)->mPChess->mColor=="Red"))){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y+1));
				iindex++;
			}
			
		}
		if(y-1>=7){	
			if((!((mChessBoard->GetPosition(x,y-1))->mPChess))||(mChessBoard->GetPosition(x,y-1)->mPChess->mColor=="Red")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y-1));
				iindex++;
			}
			
		}

	}
	if(x+1<6){	
		if((!((mChessBoard->GetPosition(x+1,y))->mPChess))||(mChessBoard->GetPosition(x+1,y)->mPChess->mColor=="Red")){
			mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y));
			iindex++;
		}
		
	}
	if(x-1>=3){	
		if((!((mChessBoard->GetPosition(x-1,y))->mPChess))||(mChessBoard->GetPosition(x-1,y)->mPChess->mColor=="Red")){
			mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y));
			iindex++;
		}
		
	}
	mCurAccessLen=iindex;
}
void CBlackKing::FindAllAccess(char *cColor){
	int iindex=0;
	if(cColor=="Black"){
		for(int i=3;i<6;i++){
			for(int j=0;j<3;j++){
				mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
				iindex++;
			}
		}
	}
	if(cColor=="Red"){
		for(int i=3;i<6;i++){
			for(int j=7;j<10;j++){
				mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
				iindex++;
			}
		}
	}
}