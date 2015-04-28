#pragma once

class CChess;
struct Vector2{
	int x;
	int y;
	Vector2(){x=-1;y=-1;mPChess=0;}
	Vector2(int i,int j){
		x=i;y=j;mPChess=0;
	}	
	bool operator ==(const Vector2 &vec){
		if(vec.x==x&&vec.y==y&&vec.mPChess==mPChess)
			return true;
		return false;
	}
	CChess* mPChess;	
};