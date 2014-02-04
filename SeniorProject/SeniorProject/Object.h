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
	
	void getSprite();
};