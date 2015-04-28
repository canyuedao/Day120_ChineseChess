#include "RedHorse.h"


CRedHorse::CRedHorse(char *cColor,int x,CChessBoard *pChessBoard)
{
	mChessBoard=pChessBoard;
	mColor="Red";
	ID=3;
	bDead=0;
	mAllAccessLen=90;
	mCurAccessLen=8;
	mAllAccess=new Vector2[mAllAccessLen];
	mCurAccess=new Vector2[mCurAccessLen];
	if(cColor=="Red"){
		mPosition=new Vector2(x,0)/*mChessBoard->GetPosition(x,0)*/;
		mChessBoard->GetPosition(x,0)->mPChess=this;
	}
	if(cColor=="Black"){
		mPosition=new Vector2(x,9)/*mChessBoard->GetPosition(x,9)*/;
		mChessBoard->GetPosition(x,9)->mPChess=this;
	}
	//FindAllAccess(cColor);
	//FindCurAccess(cColor);
}


CRedHorse::~CRedHorse(void)
{
	delete []mAllAccess;
	delete []mCurAccess;
	delete mPosition;
}

void CRedHorse::FindCurAccess(char *cColor){
	int x=mPosition->x;
	int y=mPosition->y;
	int iindex=0;
	
	if(y+2<10&&x+1<9){	
		if(!(mChessBoard->GetPosition(x,y+1)->mPChess)){
			if(!(mChessBoard->GetPosition(x+1,y+2)->mPChess)){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y+2));
				iindex++;
			}
			else{
				if(mChessBoard->GetPosition(x+1,y+2)->mPChess->mColor=="Black"){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y+2));
					iindex++;
				}
			}
			
		}
		
	}
	if(y+1<10&&x+2<9){	
		if(!(mChessBoard->GetPosition(x+1,y)->mPChess)){
			if(!(mChessBoard->GetPosition(x+2,y+1)->mPChess)){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y+1));
				iindex++;
			}
			else{
				if(mChessBoard->GetPosition(x+2,y+1)->mPChess->mColor=="Black"){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y+1));
					iindex++;
				}
			}
			
		}
		
	}
	if(y+2<10&&x-1>=0){
		if(!(mChessBoard->GetPosition(x,y+1)->mPChess)){
			if(!(mChessBoard->GetPosition(x-1,y+2)->mPChess)){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y+2));
				iindex++;
			}
			else{
				if(mChessBoard->GetPosition(x-1,y+2)->mPChess->mColor=="Black"){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y+2));
					iindex++;
				}
			}		
			
		}
		
	}
	if(y+1<10&&x-2>=0){	
		if(!(mChessBoard->GetPosition(x-1,y)->mPChess)){
			if(!(mChessBoard->GetPosition(x-2,y+1)->mPChess)){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y+1));
				iindex++;
			}
			else{
				if(mChessBoard->GetPosition(x-2,y+1)->mPChess->mColor=="Black"){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y+1));
					iindex++;
				}
			}
			
		}
		
	}
	if(y-2>=0&&x-1>=0){
		if(!(mChessBoard->GetPosition(x,y-1)->mPChess)){
			if(!(mChessBoard->GetPosition(x-1,y-2)->mPChess)){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y-2));
				iindex++;
			}
			else{
				if(mChessBoard->GetPosition(x-1,y-2)->mPChess->mColor=="Black"){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y-2));
					iindex++;
				}
			}
			
		}
		
	}
	if(y-1>=0&&x-2>=0){	
		if(!(mChessBoard->GetPosition(x-1,y)->mPChess)){
			if(!(mChessBoard->GetPosition(x-2,y-1)->mPChess)){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y-1));
				iindex++;
			}
			else{
				if(mChessBoard->GetPosition(x-2,y-1)->mPChess->mColor=="Black"){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y-1));
					iindex++;
				}
			}
			
		}
		
	}
	if(y-2>=0&&x+1<9){		
		if(!(mChessBoard->GetPosition(x,y-1)->mPChess)){
			if(!(mChessBoard->GetPosition(x+1,y-2)->mPChess)){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y-2));
				iindex++;
			}
			else{
				if(mChessBoard->GetPosition(x+1,y-2)->mPChess->mColor=="Black"){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y-2));
					iindex++;
				}
			}
			
		}
		
	}
	if(y-1>=0&&x+2<9){		
		if(!(mChessBoard->GetPosition(x+1,y)->mPChess)){
			if(!(mChessBoard->GetPosition(x+2,y-1)->mPChess)){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y-1));
				iindex++;
			}
			else{
				if(mChessBoard->GetPosition(x+2,y-1)->mPChess->mColor=="Black"){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y-1));
					iindex++;
				}
			}
			
		}
		
	}
	mCurAccessLen=iindex;
}

void CRedHorse::FindAllAccess(char *cColor){	
	int iindex=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<10;j++){
			mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
		}	
	}
}