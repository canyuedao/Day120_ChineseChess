
#include "ChessGame.h"
//#include "FindWay.h"

//CChessGame::CChessGame(bool bManVSCnum,char *cColor)
CChessGame::CChessGame()
{
	char *cColor="Red";
	//mIsManVSComputer = bManVSCnum;
	mChessBoard=new CChessBoard();
	mBlack=new CBlack(cColor,mChessBoard);
	mRed=new CRed(cColor,mChessBoard);	
	vlWhite=888;vlBlack=888;nDistance=0;
	mColor=cColor;
	iStepNumber=0;
	iPersonID[0]=0;
	iPersonID[1]=0;
	mFindWay=new CFindWay(this);
}


CChessGame::~CChessGame(void)
{
	delete mFindWay;
	delete mRed;
	delete mBlack;	
	delete mChessBoard;
}

void CChessGame::Reset(){
	this->~CChessGame();
	CChessGame();
}

bool CChessGame::GetManVStComputer()
{
	return mIsManVSComputer;

}

bool CChessGame::GetBlackChecked(){
	Vector2 *VBlackKing=mBlack->mBlackKing->GetPosition();
	//兵将
	char *cColor="Red";
	for(int i=0;i<5;i++){
		mRed->mRedSolidier[i]->FindCurAccess(cColor);
		for(int j=0;j<mRed->mRedSolidier[i]->GetCurAccessLen();j++){
			if(*(Vector2*)((int)(mRed->mRedSolidier[i]->GetCurAccess())+j*sizeof(Vector2))==*VBlackKing){
				return true;
			}
		}		
	}
	//马将
	for(int i=0;i<2;i++){
		mRed->mRedHorse[i]->FindCurAccess(cColor);
		for(int j=0;j<mRed->mRedHorse[i]->GetCurAccessLen();j++){
			if(*(Vector2*)((int)(mRed->mRedHorse[i]->GetCurAccess())+j*sizeof(Vector2))==*VBlackKing){
				return true;
			}
		}
	}
	//车将
	for(int i=0;i<2;i++){
		mRed->mRedVehicle[i]->FindCurAccess(cColor);
		for(int j=0;j<mRed->mRedVehicle[i]->GetCurAccessLen();j++){
			if(*(Vector2*)((int)(mRed->mRedVehicle[i]->GetCurAccess())+j*sizeof(Vector2))==*VBlackKing){
				return true;
			}
		}
	}
	//炮将
	for(int i=0;i<2;i++){
		mRed->mRedGun[i]->FindCurAccess(cColor);
		for(int j=0;j<mRed->mRedGun[i]->GetCurAccessLen();j++){
			if(*(Vector2*)((int)(mRed->mRedGun[i]->GetCurAccess())+j*sizeof(Vector2))==*VBlackKing){
				return true;
			}
		}
	}
	//帅对面
	Vector2 *VRedKing=mRed->mRedKing->GetPosition();
	if(VBlackKing->x==VRedKing->x){
		int maxY=(VBlackKing->y>VRedKing->y)?VBlackKing->y:VRedKing->y;
		int minY=(VBlackKing->y>VRedKing->y)?VRedKing->y:VBlackKing->y;
		for(int i=minY+1;i<maxY;i++){
			if(mChessBoard->GetPosition(VBlackKing->x,i)->mPChess){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool CChessGame::GetRedChecked(){
	Vector2 *VRedKing=mRed->mRedKing->GetPosition();
	//兵将
	char *cColor="Red";
	for(int i=0;i<5;i++){
		mBlack->mBlackSolidier[i]->FindCurAccess(cColor);
		for(int j=0;j<mBlack->mBlackSolidier[i]->GetCurAccessLen();j++){
			if(*(Vector2*)((int)(mBlack->mBlackSolidier[i]->GetCurAccess())+j*sizeof(Vector2))==*VRedKing){
				return true;
			}
		}		
	}
	//马将
	for(int i=0;i<2;i++){
		mBlack->mBlackHorse[i]->FindCurAccess(cColor);
		for(int j=0;j<mBlack->mBlackHorse[i]->GetCurAccessLen();j++){
			if(*(Vector2*)((int)(mBlack->mBlackHorse[i]->GetCurAccess())+j*sizeof(Vector2))==*VRedKing){
				return true;
			}
		}
	}
	//车将
	for(int i=0;i<2;i++){
		mBlack->mBlackVehicle[i]->FindCurAccess(cColor);
		for(int j=0;j<mBlack->mBlackVehicle[i]->GetCurAccessLen();j++){
			if(*(Vector2*)((int)(mBlack->mBlackVehicle[i]->GetCurAccess())+j*sizeof(Vector2))==*VRedKing){
				return true;
			}
		}
	}
	//炮将
	for(int i=0;i<2;i++){
		mBlack->mBlackGun[i]->FindCurAccess(cColor);
		for(int j=0;j<mBlack->mBlackGun[i]->GetCurAccessLen();j++){
			if(*(Vector2*)((int)(mBlack->mBlackGun[i]->GetCurAccess())+j*sizeof(Vector2))==*VRedKing){
				return true;
			}
		}
	}
	//帅对面
	Vector2 *VBlackKing=mBlack->mBlackKing->GetPosition();
	if(VBlackKing->x==VRedKing->x){
		int maxY=(VBlackKing->y>VRedKing->y)?VBlackKing->y:VRedKing->y;
		int minY=(VBlackKing->y>VRedKing->y)?VRedKing->y:VBlackKing->y;
		for(int i=minY+1;i<maxY;i++){
			if(mChessBoard->GetPosition(VBlackKing->x,i)->mPChess){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool CChessGame::GetBlackBlocked(){
	//兵是否堵死
	for(int i=0;i<5;i++){
		if(mBlack->mBlackSolidier[i]->GetCurAccessLen()!=0)
			return false;
		/*for(int j=0;j<mBlack->mBlackSolidier[i]->GetCurAccessLen();j++){
			if(((Vector2*)(mBlack->mBlackSolidier[i]+j*sizeof(Vector2)))->x!=-1){
				return false;
			}
		}*/
	}
	//马是否堵死
	for(int i=0;i<2;i++){
		if(mBlack->mBlackHorse[i]->GetCurAccessLen()!=0)
			return false;
	}
	//车是否堵死
	for(int i=0;i<2;i++){
		if(mBlack->mBlackVehicle[i]->GetCurAccessLen()!=0)
			return false;
	}
	//炮是否堵死
	for(int i=0;i<2;i++){
		if(mBlack->mBlackGun[i]->GetCurAccessLen()!=0)
			return false;
	}
	//将是否堵死
	if(mBlack->mBlackKing->GetCurAccessLen()!=0)
		return false;
	//相是否堵死
	for(int i=0;i<2;i++){
		if(mBlack->mBlackMinister[i]->GetCurAccessLen()!=0)
			return false;
	}
	//士是否堵死
	for(int i=0;i<2;i++){
		if(mBlack->mBlackBachelor[i]->GetCurAccessLen()!=0)
			return false;
	}
	return true;
}

bool CChessGame::GetRedBlocked(){
	//兵是否堵死
	for(int i=0;i<5;i++){
		if(mRed->mRedSolidier[i]->GetCurAccessLen()!=0)
			return false;		
	}
	//马是否堵死
	for(int i=0;i<2;i++){
		if(mRed->mRedHorse[i]->GetCurAccessLen()!=0)
			return false;
	}
	//车是否堵死
	for(int i=0;i<2;i++){
		if(mRed->mRedVehicle[i]->GetCurAccessLen()!=0)
			return false;
	}
	//炮是否堵死
	for(int i=0;i<2;i++){
		if(mRed->mRedGun[i]->GetCurAccessLen()!=0)
			return false;
	}
	//将是否堵死
	if(mRed->mRedKing->GetCurAccessLen()!=0)
		return false;
	//相是否堵死
	for(int i=0;i<2;i++){
		if(mRed->mRedMinister[i]->GetCurAccessLen()!=0)
			return false;
	}
	//士是否堵死
	for(int i=0;i<2;i++){
		if(mRed->mRedBachelor[i]->GetCurAccessLen()!=0)
			return false;
	}
	return true;
}



//int CChessGame::GetBlackResult(){
//	if(GetRedBlocked())
//}

int CChessGame::GetRedResult(){
	if (mRed->GetDefeat())
	{
		return -1;
	}
	if (mRed->GetSuccess())
	{
		return 1;
	}
	if (mRed->GetDraw())
	{
		return 0;
	}
}