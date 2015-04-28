#include "BlackBachelor.h"

CBlackBachelor::CBlackBachelor(char *cColor,int x,CChessBoard *pChessBoard)
{
	mChessBoard=pChessBoard;
	mColor="Black";
	ID=1;
	bDead=0;
	mAllAccessLen=5;
	mCurAccessLen=4;
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

CBlackBachelor::~CBlackBachelor(void){
	delete []mAllAccess;
	delete []mCurAccess;
	delete mPosition;
}

void CBlackBachelor::FindCurAccess(char *cColor){	
	int x=mPosition->x;
	int y=mPosition->y;
	int iindex=0;
	
	if(cColor=="Black"){
		if(y+1<3&&x+1<6){		
			if((!(mChessBoard->GetPosition(x+1,y+1)->mPChess)||(mChessBoard->GetPosition(x+1,y+1)->mPChess->mColor=="Red"))){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y+1));
				iindex++;
			}
			
		}
		if(y-1>=0&&x-1>=3){		
			if((!((mChessBoard->GetPosition(x-1,y-1))->mPChess))||(mChessBoard->GetPosition(x-1,y-1)->mPChess->mColor=="Red")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y-1));
				iindex++;
			}
			
		}
		if(y+1<3&&x-1>=3){	
			if((!((mChessBoard->GetPosition(x-1,y+1))->mPChess))||(mChessBoard->GetPosition(x-1,y+1)->mPChess->mColor=="Red")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y+1));
				iindex++;
			}
			
		}
		if(y-1>=0&&x+1<6){
			if((!((mChessBoard->GetPosition(x+1,y-1))->mPChess))||(mChessBoard->GetPosition(x+1,y-1)->mPChess->mColor=="Red")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y-1));
				iindex++;
			}
			
		}
	}
	if(cColor=="Red"){
		if(y+1<10&&x+1<6){	
			if((!(mChessBoard->GetPosition(x+1,y+1)->mPChess)||(mChessBoard->GetPosition(x+1,y+1)->mPChess->mColor=="Red"))){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y+1));
				iindex++;
			}
			
		}
		if(y-1>=7&&x-1>=3){		
			if((!((mChessBoard->GetPosition(x-1,y-1))->mPChess))||(mChessBoard->GetPosition(x-1,y-1)->mPChess->mColor=="Red")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y-1));
				iindex++;
			}
			
		}
		if(y+1<10&&x-1>=3){		
			if((!((mChessBoard->GetPosition(x-1,y+1))->mPChess))||(mChessBoard->GetPosition(x-1,y+1)->mPChess->mColor=="Red")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x-1,y+1));
				iindex++;
			}
			
		}
		if(y-1>=7&&x+1<6){	
			if((!((mChessBoard->GetPosition(x+1,y-1))->mPChess))||(mChessBoard->GetPosition(x+1,y-1)->mPChess->mColor=="Red")){
				mCurAccess[iindex]=*(mChessBoard->GetPosition(x+1,y-1));
				iindex++;
			}
			
		}
	}	
	mCurAccessLen=iindex;
}
void CBlackBachelor::FindAllAccess(char *cColor){	
	if(cColor=="Black"){
		mAllAccess[0]=*(mChessBoard->GetPosition(3,0));
		mAllAccess[1]=*(mChessBoard->GetPosition(3,2));
		mAllAccess[2]=*(mChessBoard->GetPosition(4,1));
		mAllAccess[3]=*(mChessBoard->GetPosition(5,0));
		mAllAccess[4]=*(mChessBoard->GetPosition(5,2));
	}
	if(cColor=="Red"){
		mAllAccess[0]=*(mChessBoard->GetPosition(3,7));
		mAllAccess[1]=*(mChessBoard->GetPosition(3,9));
		mAllAccess[2]=*(mChessBoard->GetPosition(4,8));
		mAllAccess[3]=*(mChessBoard->GetPosition(5,7));
		mAllAccess[4]=*(mChessBoard->GetPosition(5,9));
	}
}