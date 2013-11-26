#pragma once

#include "sprite.h"

class Item : public The_Sprite
{
private:
	int ID;
	char * name;

public:
	Item();
	int getID();
	void setID(int);
};