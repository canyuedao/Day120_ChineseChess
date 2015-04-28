#include "RedGun.h"


CRedGun::CRedGun(char *cColor,int x,CChessBoard *pChessBoard)
{
	mChessBoard=pChessBoard;
	mColor="Red";
	ID=5;
	bDead=0;
	mAllAccessLen=90;
	mCurAccessLen=17;
	mAllAccess=new Vector2[mAllAccessLen];
	mCurAccess=new Vector2[mCurAccessLen];
	if(cColor=="Red"){
		mPosition=new Vector2(x,2)/*mChessBoard->GetPosition(x,2)*/;
		mChessBoard->GetPosition(x,2)->mPChess=this;
	}
	if(cColor=="Black"){
		mPosition=new Vector2(x,7)/*mChessBoard->GetPosition(x,7)*/;
		mChessBoard->GetPosition(x,7)->mPChess=this;
	}
	//FindAllAccess(cColor);
	//FindCurAccess(cColor);
}


CRedGun::~CRedGun(void)
{
	delete []mAllAccess;
	delete []mCurAccess;
	delete mPosition;
}

void CRedGun::FindCurAccess(char *cColor){
	int x=mPosition->x;
	int y=mPosition->y;
	int iRight=0,iLeft=0,iUp=0,iDown=0;	
	int iRightTmp=0,iLeftTmp=0,iUpTmp=0,iDownTmp=0;
	bool bRight=false,bLeft=false,bUp=false,bDown=false;
	while(x+iRight+1<9){		
		if(!((mChessBoard->GetPosition(x+iRight+1,y))->mPChess)){
			if(!bRight){				
				mCurAccess[iRightTmp]=*(mChessBoard->GetPosition(x+iRight+1,y));	
				iRight++;
				iRightTmp=iRight;
			}	
			else
				iRight++;
			continue;
		}
		else{
			if(bRight&&(mChessBoard->GetPosition(x+iRight+1,y)->mPChess->mColor=="Black")){
				mCurAccess[iRightTmp]=*(mChessBoard->GetPosition(x+iRight+1,y));
				iRightTmp++;
				break;
			}
			if(bRight&&(mChessBoard->GetPosition(x+iRight+1,y)->mPChess->mColor=="Red")){
				//iRightTmp--;
				break;
			}				
			//iRightTmp=iRight;
			bRight=true;
			iRight++;
		}		
	}
	while(x-iLeft-1>=0){		
		if(!((mChessBoard->GetPosition(x-iLeft-1,y))->mPChess)){
			if(!bLeft){				
				mCurAccess[iRightTmp+iLeftTmp]=*(mChessBoard->GetPosition(x-iLeft-1,y));	
				iLeft++;
				iLeftTmp=iLeft;
			}
			else
				iLeft++;
			continue;
		}
		else{
			if(bLeft&&(mChessBoard->GetPosition(x-iLeft-1,y)->mPChess->mColor=="Black")){
				mCurAccess[iRightTmp+iLeftTmp]=*(mChessBoard->GetPosition(x-iLeft-1,y));
				iLeftTmp++;
				break;
			}
			if(bLeft&&(mChessBoard->GetPosition(x-iLeft-1,y)->mPChess->mColor=="Red")){
				//iLeftTmp--;
				break;
			}				
			//iLeftTmp=iLeft;
			bLeft=true;
			iLeft++;
		}		
	}
	while(y+iUp+1<10){		
		if(!((mChessBoard->GetPosition(x,y+iUp+1))->mPChess)){
			if(!bUp){				
				mCurAccess[iRightTmp+iLeftTmp+iUpTmp]=*(mChessBoard->GetPosition(x,y+iUp+1));
				iUp++;
				iUpTmp=iUp;
			}	
			else
				iUp++;
			continue;
		}
		else{
			if(bUp&&(mChessBoard->GetPosition(x,y+iUp+1)->mPChess->mColor=="Black")){
				mCurAccess[iRightTmp+iLeftTmp+iUpTmp]=*(mChessBoard->GetPosition(x,y+iUp+1));
				iUpTmp++;
				break;
			}
			if(bUp&&(mChessBoard->GetPosition(x,y+iUp+1)->mPChess->mColor=="Red")){
				//iUpTmp--;
				break;
			}				
			//iUpTmp=iUp;
			bUp=true;
			iUp++;
		}		
	}
	while(y-iDown-1>=0){		
		if(!((mChessBoard->GetPosition(x,y-iDown-1))->mPChess)){
			if(!bDown){				
				mCurAccess[iRightTmp+iLeftTmp+iUpTmp+iDownTmp]=*(mChessBoard->GetPosition(x,y-iDown-1));
				iDown++;
				iDownTmp=iDown;
			}	
			else
				iDown++;
			continue;
		}
		else{
			if(bDown&&(mChessBoard->GetPosition(x,y-iDown-1)->mPChess->mColor=="Black")){
				mCurAccess[iRightTmp+iLeftTmp+iUpTmp+iDownTmp]=*(mChessBoard->GetPosition(x,y-iDown-1));
				iDownTmp++;
				break;
			}
			if(bDown&&(mChessBoard->GetPosition(x,y-iDown-1)->mPChess->mColor=="Red")){
				//iDownTmp--;
				break;
			}				
			//iDownTmp=iDown;
			bDown=true;
			iDown++;
		}		
	}
	mCurAccessLen=iRightTmp+iLeftTmp+iUpTmp+iDownTmp;
}
void CRedGun::FindAllAccess(char *cColor){	
	int iindex=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<10;j++){
			mAllAccess[iindex]=*(mChessBoard->GetPosition(i,j));
			iindex++;
		}	
	}
}