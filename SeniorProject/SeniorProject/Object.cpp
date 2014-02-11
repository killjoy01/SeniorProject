#pragma once

#include "Object.h"
#include "Player.h"
Object::Object()
{
}

Object::~Object()
{
}
//Player::SetObjectList(vector*   ){}

int Object::getID()
{
	return ID;
//return sprite.get
}
void Object::setID(int OId)
{
	ID = OId;
//sprite.
}