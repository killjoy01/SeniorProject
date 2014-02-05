//JJ
#pragma once

#include "sprite.h"

class Object : public The_Sprite
{
private:
	
	The_Sprite sprite;
	bool isSolid;
	//int type;
public:
	Object();
	~Object();
	void isGoal();
	int CollisionCheck(float x1,float y1,float x2,float y2);
	void getSprite();
};