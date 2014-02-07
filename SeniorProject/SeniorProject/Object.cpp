#pragma once

#include "Object.h"

Object::Object()
{
}

int Object::CollisionCheck(float x1,float y1,float x2,float y2)
{
	 //   if(y1 >= y2 && (y1 + PLAYER_WIDTH) <= (y2 + PLAYER_WIDTH))
		//{
  //      if(x1 >= x2 && (x1 + PLAYER_HEIGHT) <= (x2 + PLAYER_HEIGHT))
  //      {
  //      
  //      }

	//for each object cheack if it collids with passed in rectangle
	//objects atribute 
	
	return 0;
	//return 1;
	//return 2;
	//return 3;
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