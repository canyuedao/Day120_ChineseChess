#include "RedSolidier.h"


CRedSolidier::CRedSolidier(char *cColor,int x,CChessBoard *pChessBoard)
{
	mChessBoard=pChessBoard;
	mColor="Red";	
	ID=6;
	bDead=0;
	mAllAccessLen=47;
	mCurAccessLen=3;
	mAllAccess=new Vector2[mAllAccessLen];
	mCurAccess=new Vector2[mCurAccessLen];
	if(cColor=="Red"){
		mPosition=new Vector2(x,3)/*mChessBoard->GetPosition(x,3)*/;
		mChessBoard->GetPosition(x,3)->mPChess=this;
	}
	if(cColor=="Black"){
		mPosition=new Vector2(x,6)/*mChessBoard->GetPosition(x,6)*/;
		mChessBoard->GetPosition(x,6)->mPChess=this;
	}
	//FindAllAccess(cColor);
	//FindCurAccess(cColor);
}


CRedSolidier::~CRedSolidier(void)
{
	delete []mAllAccess;
	delete []mCurAccess;
	delete mPosition;
}

void CRedSolidier::FindCurAccess(char *cColor){
	int x=mPosition->x;
	int y=mPosition->y;
	int iindex=0;
	
	if(cColor=="Red"){		
		if(y==3||y==4){
			if((!(mChessBoard->GetPosition(x,y+1)->mPChess)||(mChessBoard->GetPosition(x,y+1)->mPChess->mColor=="Black"))){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y+1));
				iindex++;
			}
			
		}
		if(y>4){
			if(y+1<10){	
				if((!(mChessBoard->GetPosition(x,y+1)->mPChess)||(mChessBoard->GetPosition(x,y+1)->mPChess->mColor=="Black"))){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y+1));
					iindex++;
				}
				
			}
			if(x+1<9){		
				if((!((mChessBoard->GetPosition(x+1,y))->mPChess))||(mChessBoard->GetPosition(x+1,y)->mPChess->mColor=="Black")){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y));
					iindex++;
				}
				
			}
			if(x-1>=0){	
				if((!((mChessBoard->GetPosition(x-1,y))->mPChess))||(mChessBoard->GetPosition(x-1,y)->mPChess->mColor=="Black")){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y));
					iindex++;
				}				
			}
		}		
	}
	if(cColor=="Black"){
		if(y==5||y==6){
			if((!(mChessBoard->GetPosition(x,y-1)->mPChess)||(mChessBoard->GetPosition(x,y-1)->mPChess->mColor=="Black"))){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y-1));
				iindex++;
			}
			
		}
		if(y<=4){
			if(y-1>=0){		
				if((!(mChessBoard->GetPosition(x,y-1)->mPChess)||(mChessBoard->GetPosition(x,y-1)->mPChess->mColor=="Black"))){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x,y-1));
					iindex++;
				}				
			}
			if(x+1<9){	
				if((!((mChessBoard->GetPosition(x+1,y))->mPChess))||(mChessBoard->GetPosition(x+1,y)->mPChess->mColor=="Black")){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y));
					iindex++;
				}
				
			}
			if(x-1>=0){	
				if((!((mChessBoard->GetPosition(x-1,y))->mPChess))||(mChessBoard->GetPosition(x-1,y)->mPChess->mColor=="Black")){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y));
					iindex++;
				}				
			}
		}
	}	
	mCurAccessLen=iindex;
}

void CRedSolidier::FindAllAccess(char *cColor){
	int iindex=10;
	if(cColor=="Red"){
		mAllAccess[0]=*(mChessBoard->GetPosition(0,3));
		mAllAccess[1]=*(mChessBoard->GetPosition(2,3));
		mAllAccess[2]=*(mChessBoard->GetPosition(4,3));
		mAllAccess[3]=*(mChessBoard->GetPosition(6,3));
		mAllAccess[4]=*(mChessBoard->GetPosition(8,3));
		mAllAccess[5]=*(mChessBoard->GetPosition(0,4));
		mAllAccess[6]=*(mChessBoard->GetPosition(2,4));
		mAllAccess[7]=*(mChessBoard->GetPosition(4,4));
		mAllAccess[8]=*(mChessBoard->GetPosition(6,4));
		mAllAccess[9]=*(mChessBoard->GetPosition(8,4));
		for(int i=0;i<9;i++){
			for(int j=5;j<10;j++){
				mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
				iindex++;
			}
		}
	}
	if(cColor=="Black"){
		mAllAccess[0]=*(mChessBoard->GetPosition(0,6));
		mAllAccess[1]=*(mChessBoard->GetPosition(2,6));
		mAllAccess[2]=*(mChessBoard->GetPosition(4,6));
		mAllAccess[3]=*(mChessBoard->GetPosition(6,6));
		mAllAccess[4]=*(mChessBoard->GetPosition(8,6));
		mAllAccess[5]=*(mChessBoard->GetPosition(0,5));
		mAllAccess[6]=*(mChessBoard->GetPosition(2,5));
		mAllAccess[7]=*(mChessBoard->GetPosition(4,5));
		mAllAccess[8]=*(mChessBoard->GetPosition(6,5));
		mAllAccess[9]=*(mChessBoard->GetPosition(8,5));
		for(int i=0;i<9;i++){
			for(int j=0;j<5;j++){
				mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
				iindex++;


			}
		}

	}
}
