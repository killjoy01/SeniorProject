#pragma once

#include "sprite.h"

class Object : public The_Sprite
{
private:
	bool solid;
	The_Sprite sprite;
	void getSprite();
	//int type;
public:
	Object();
};