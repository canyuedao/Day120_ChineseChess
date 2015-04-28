#include "RedMinister.h"


CRedMinister::CRedMinister(char *cColor,int x,CChessBoard *pChessBoard)
{
	mChessBoard=pChessBoard;
	mColor="Red";
	ID=2;
	bDead=0;
	mAllAccessLen=7;
	mCurAccessLen=4;
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


CRedMinister::~CRedMinister(void)
{
	delete []mAllAccess;
	delete []mCurAccess;
	delete mPosition;
}

void CRedMinister::FindCurAccess(char *cColor){
	int x=mPosition->x;
	int y=mPosition->y;
	int iindex=0;
	
	if(cColor=="Red"){
		if(y+2<5&&x+2<9){	
			if(!(mChessBoard->GetPosition(x+1,y+1)->mPChess)){
				if(!(mChessBoard->GetPosition(x+2,y+2)->mPChess)){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y+2));
					iindex++;
				}
				else{
					if(mChessBoard->GetPosition(x+2,y+2)->mPChess->mColor=="Black"){
						mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y+2));
						iindex++;
					}
				}				
			}			
		}
		if(y-2>=0&&x-2>=0){
			if(!(mChessBoard->GetPosition(x-1,y-1)->mPChess)){
				if(!(mChessBoard->GetPosition(x-2,y-2)->mPChess)){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y-2));
					iindex++;
				}
				else{
					if(mChessBoard->GetPosition(x-2,y-2)->mPChess->mColor=="Black"){
						mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y-2));
						iindex++;
					}
				}				
			}			
		}
		if(y+2<5&&x-2>=0){	
			if(!(mChessBoard->GetPosition(x-1,y+1)->mPChess)){
				if(!(mChessBoard->GetPosition(x-2,y+2)->mPChess)){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y+2));
					iindex++;
				}
				else{
					if(mChessBoard->GetPosition(x-2,y+2)->mPChess->mColor=="Black"){
						mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y+2));
						iindex++;
					}
				}				
			}			
		}
		if(y-2>=0&&x+2<9){	
			if(!(mChessBoard->GetPosition(x+1,y-1)->mPChess)){
				if(!(mChessBoard->GetPosition(x+2,y-2)->mPChess)){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y-2));
					iindex++;
				}
				else{
					if(mChessBoard->GetPosition(x+2,y-2)->mPChess->mColor=="Black"){
						mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y-2));
						iindex++;
					}
				}				
			}			
		}
	}
	if(cColor=="Black"){
		if(y+2<10&&x+2<9){	
			if(!(mChessBoard->GetPosition(x+1,y+1)->mPChess)){
				if(!(mChessBoard->GetPosition(x+2,y+2)->mPChess)){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y+2));
					iindex++;
				}
				else{
					if(mChessBoard->GetPosition(x+2,y+2)->mPChess->mColor=="Black"){
						mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y+2));
						iindex++;
					}
				}				
			}			
		}
		if(y-2>=5&&x-2>=0){	
			if(!(mChessBoard->GetPosition(x-1,y-1)->mPChess)){
				if(!(mChessBoard->GetPosition(x-2,y-2)->mPChess)){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y-2));
					iindex++;
				}
				else{
					if(mChessBoard->GetPosition(x-2,y-2)->mPChess->mColor=="Black"){
						mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y-2));
						iindex++;
					}
				}				
			}			
		}
		if(y+2<10&&x-2>=0){	
			if(!(mChessBoard->GetPosition(x-1,y+1)->mPChess)){
				if(!((mChessBoard->GetPosition(x-2,y+2))->mPChess)){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y+2));
					iindex++;
				}
				else{
					if(mChessBoard->GetPosition(x-2,y+2)->mPChess->mColor=="Black"){
						mCurAccess[iindex]=*(mChessBoard->GetPosition(x-2,y+2));
						iindex++;
					}
				}			
			}			
		}
		if(y-2>=5&&x+2<9){
			if(!(mChessBoard->GetPosition(x+1,y-1)->mPChess)){
				if(!(mChessBoard->GetPosition(x+2,y-2)->mPChess)){
					mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y-2));
					iindex++;
				}
				else{
					if(mChessBoard->GetPosition(x+2,y-2)->mPChess->mColor=="Black"){
						mCurAccess[iindex]=*(mChessBoard->GetPosition(x+2,y-2));
						iindex++;
					}					
				}				
			}				
		}
	}	
	mCurAccessLen=iindex;
}
void CRedMinister::FindAllAccess(char *cColor){	
	if(cColor=="Red"){
		mAllAccess[0]=*(mChessBoard->GetPosition(0,2));
		mAllAccess[1]=*(mChessBoard->GetPosition(2,0));
		mAllAccess[2]=*(mChessBoard->GetPosition(2,4));
		mAllAccess[3]=*(mChessBoard->GetPosition(4,2));
		mAllAccess[4]=*(mChessBoard->GetPosition(6,0));
		mAllAccess[5]=*(mChessBoard->GetPosition(6,4));
		mAllAccess[6]=*(mChessBoard->GetPosition(8,2));
	}
	if(cColor=="Black"){
		mAllAccess[0]=*(mChessBoard->GetPosition(0,7));
		mAllAccess[1]=*(mChessBoard->GetPosition(2,5));
		mAllAccess[2]=*(mChessBoard->GetPosition(2,9));
		mAllAccess[3]=*(mChessBoard->GetPosition(4,7));
		mAllAccess[4]=*(mChessBoard->GetPosition(6,5));
		mAllAccess[5]=*(mChessBoard->GetPosition(6,9));
		mAllAccess[6]=*(mChessBoard->GetPosition(8,7));
	}
}