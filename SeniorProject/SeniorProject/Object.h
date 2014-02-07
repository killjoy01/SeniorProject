//JJ
#pragma once

#include "sprite.h"

class Object : public The_Sprite
{
private:
	
	The_Sprite sprite;
	bool isSolid;
	int ID;
	//vetor  ObjectList;
	
	//int type;
public:
	int getID();
	void setID(int OId);
	
	Object();
	~Object();
	void isGoal();
	int CollisionCheck(float x1,float y1,float x2,float y2);
	void getSprite();
};