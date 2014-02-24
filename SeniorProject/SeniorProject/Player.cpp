#include "Player.h"



Player::Player()
{
	xvelocity = 0;
	yvelocity = 0;
	OnGround = true;
	IsJumping = false;
	lowJump = false;
	highJump = false;
	PowerActive = false;
	LastChangedTimer = 0;
	SelectedPower = 1;
	JumpTime = 0.0f;
	Time = 0.0f;
	float dx = 0.0f;
	float dy = 0.0f;
	//float x = 0.0f; 
	//float y = 0.0f;
	bool mayJumpAgain = false;
	bool isOnSolidGround = true;

}

Player::Player(const Player & p)
{
	sprite = p.sprite;
	xvelocity = 0;
	yvelocity = 0;
}

Player::~Player()
{
}

void Player::init(int c)
{
}

Player & Player::operator = (const Player & p)
{
	this->Player::Player(p);
	return *this;
}
void  Player::setObjectList(vector<Object> &objects)
{
	ObjectList = objects;
}
int Player::CollisionCheck(float x1,float y1,float x2,float y2, vector<Object> & ObjectList)
{
//int Collision = 0;
	for(int i=0; i< ObjectList.size(); i++) 
	{
		if(ObjectList[i].getID() != 0)
		{
			if(x1 <= ObjectList[i].getPosition().x &&  ObjectList[i].getPosition().x <= x2)
			{
				if(y1 <= ObjectList[i].getPosition().y && y2 >= ObjectList[i].getPosition().y)
				{
					//Collision = ObjectList[i].getID();
					//return Collision;
					return ObjectList[i].getID();
					//return
					//return i;
					//(ObjectList[i].getID() == 0)
				}
			}

			if(x1 <= ObjectList[i].rightside() && x2 >= ObjectList[i].rightside())
			{
				if(y1 <=  ObjectList[i].getPosition().y && y2 >=  ObjectList[i].getPosition().y)
				{
					//if(ObjectList[i].getID() != 0)
					//{
					return ObjectList[i].getID();//break;
					//Collision = ObjectList[i].getID();
					//return Collision;
					//return i;
					//}
				}
			}		

			if(x1 <= ObjectList[i].rightside() && x2 >= ObjectList[i].rightside() )
			{
				if(y1 <= ObjectList[i].bottom()  && y2 >= ObjectList[i].bottom())
				{
					//if(ObjectList[i].getID() != 0)
					//{
					return ObjectList[i].getID();//break;
					//return i;
					//}
					//Collision = ObjectList[i].getID();
					//return Collision;
				}
			}		

			if(x1 <=  ObjectList[i].getPosition().x && x2 >= ObjectList[i].getPosition().x)
			{
				if(y1 <= ObjectList[i].bottom() && y2 >= ObjectList[i].bottom())
				{
					//if(ObjectList[i].getID() != 0)
					//{				
					return ObjectList[i].getID();
					//return i;
					//break;
					//}
					//Collision = ObjectList[i].getID();
					//return Collision;
				}
			}
		}
		//else
		//{
		//return 0;
		//}
	}
	//return Collision; 
	//return 0;
	//return 0;
	//return 1;
	//return 2;
	//return 3;
}

int Player::UpdateState(unsigned int updatevalue, float dt)
{
	//movment
	int aNumber;
	//int number;
	//number = CollisionCheck(position.x, position.y,position.x+rect.right,position.y+rect.bottom,ObjectList);
	switch(SelectedPower)
	{
	case 1:
		setTexture(PlayerTextures[0]);
		aNumber = NoPower(updatevalue,dt);
		
		break;
	case 2:
		setTexture(PlayerTextures[1]);
		aNumber = PowerOne(updatevalue,dt);
		break;
	case 3:
		setTexture(PlayerTextures[2]);
		aNumber = PowerTwo(updatevalue,dt);
		break;
	case 4:
		setTexture(PlayerTextures[3]);
		aNumber = PowerThree(updatevalue,dt);
		break;
	}
	//return SelectedPower;
	return aNumber;
	//return 0;
}
int Player::getSelectedPower()
{
return SelectedPower;
}
int Player::NoPower(unsigned int updatevalue,float dt) 
{
	float Xmove = 0.0f;
	float Ymove = 0.0f;
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	//float PX1new;//float PX2new;//float PY1new;//float PY1new;
	float PX2 =(PX1 + rect.right);
	float PY2 = (PY1 + rect.bottom);
	int theNumber = 0;
	if((updatevalue & M_LEFT)!=false)
	{
			Xmove = dt* MovementSpeedX;
			oldX = position.x;
			position.x -= Xmove;
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 1)
			{
				position.x = oldX;
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
	}
	if((updatevalue & M_RIGHT)!=false)
	{
			Xmove = dt* MovementSpeedX;
			oldX = position.x;
			position.x += Xmove;
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 1)
			{
				position.x = oldX;
				position.y = oldY;
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
	}
	if((updatevalue & M_JUMP)!=false)
	{
			Ymove = dt* JumpingConstant;
			oldY = position.y;
			position.y -= Ymove;
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 1)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				position.y = oldY;
				//return
			}
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				//return
			}
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				//return
			}
	}
	if((updatevalue & M_JUMP)==false)
	{
	Ymove = dt* Gravity;
	oldY = position.y;
	position.y += Ymove;
	if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 1)
	{
		position.y = oldY;
		theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
	}
	if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 2)
	{
		theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
	}
	if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 3)
	{
		theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
	}
	}
	//powers
	if((updatevalue & P1)!=false)
	{
		SelectedPower = 2;
	}
	if((updatevalue & P2)!=false)
	{
		SelectedPower = 3;
	}
	if((updatevalue & P3)!=false)
	{
		SelectedPower = 4;
	}
	if((updatevalue & P4)!=false)
	{
		SelectedPower = 1;
	}
	return theNumber;
	//xvelocity = position.x - oldX;
	//yvelocity = position.y - oldY;
	//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 1)
	//{
	//	position.x = oldX;
	//	position.y = oldY;
	//			theNumber = CollisionCheck(PX1+=Xmove,PY1,PX2+=Xmove,PY2,ObjectList);
	//}
}
int Player::PowerOne(unsigned int updatevalue,float dt)
{
	float Xmove = 0.0f;
	float Ymove = 0.0f;
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(PX1 + rect.right);
	float PY2 = (PY1 + rect.bottom);
	int theNumber= 0;
	if((updatevalue & M_LEFT)!=false)
	{
			Xmove = dt* MovementSpeedX;
			oldX = position.x;
			position.x -= Xmove;
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 1)
			{
				position.x = oldX;
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
	}
	if((updatevalue & M_RIGHT)!=false)
	{
		//process right movement

		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) != 1)
		//{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) != 1)
			{
				position.x += Xmove;
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 1)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
		//}
	}
	if((updatevalue & M_JUMP)!= false)
	{
	}
	//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
	//{
		Ymove = dt* Gravity;
		//Ymove = 1;
		if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) != 1)
		{
			position.y -= Ymove;
		}
		if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 1)
		{
			theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
		}
		if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 2)
		{
			theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
		}
		if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 3)
		{
			theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
		}
	//}
	//powers
	if((updatevalue & P1)!=false)
	{
		SelectedPower = 2;
	}
	if((updatevalue & P2)!=false)
	{
		SelectedPower = 3;
	}
	if((updatevalue & P3)!=false)
	{
		SelectedPower = 4;
	}
	if((updatevalue & P4)!=false)
	{
		SelectedPower = 1;
	}
	xvelocity = position.x - oldX;
	yvelocity = position.y - oldY;

	return theNumber;
}
int Player::PowerTwo(unsigned int updatevalue,float dt)
{
	float Xmove = 0.0f;
	float Ymove = 0.0f;
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(PX1 + rect.right);
	float PY2 = (PY1 + rect.bottom);
	int theNumber = 0;
		Xmove = xvelocity; 

		if(Xmove > 0)
		{
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) != 1)
			{
				position.x -= Xmove;
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 1)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
//			else if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 1)
//			{
////				position.x += Xmove;
//			}
		}
		if(Xmove < 0)
		{
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) != 1)
			{
				position.x += Xmove;
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 1)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+=Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
		}
		if(Ymove < 0)
		{
		Ymove = yvelocity;
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) != 1)
			{
				position.y -= Ymove;
				//IsJumping = true;
			}
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 1)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				//return
			}
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				//return
			}
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				//return
			}
		}
		if(Ymove > 0)
		{
		Ymove = yvelocity;
			if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) != 1)
			{
				position.y += Ymove;
				//IsJumping = true;
			}
			if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 1)
			{
				theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
				//return
			}
			if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
				//return
			}
			if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
				//return
			}
		}
	//if((updatevalue & M_LEFT)!=false)
	//{
	//	Xmove = dt* MovementSpeedX;
	//		if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) != 1)
	//		{
	//			position.x -= Xmove;
	//		}
	//}
	//if((updatevalue & M_RIGHT)!=false)
	//{
	//		Xmove = dt* MovementSpeedX;
	//		if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) != 1)
	//		{
	//			position.x += Xmove;
	//		}
	//}
	//if((updatevalue & M_JUMP)!= false)
	//{
	//	//		if(lowJump == true)
	//	//{
	//	//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
	//	//{	
	//		Ymove = dt* JumpingConstant;
	//		if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) != 1)
	//		{
	//			position.y -= Ymove;
	//			IsJumping = true;
	//		}
	//	//}
	//}
	//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
	//{
		Ymove = dt* Gravity;
		if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) != 1)
		{
			position.y += Ymove;
		}
		if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 1)
		{
			theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
		}
		if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 2)
		{
			theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
		}
		if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 3)
		{
			theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
		}
	//}
	//powers
	if((updatevalue & P1)!=false)
	{
		SelectedPower = 2;
	}
	if((updatevalue & P2)!=false)
	{
		SelectedPower = 3;
	}
	if((updatevalue & P3)!=false)
	{
		SelectedPower = 4;
	}
	if((updatevalue & P4)!=false)
	{
		SelectedPower = 1;
	}
	xvelocity = position.x - oldX;
	yvelocity = position.y - oldY;
	return theNumber;
}
int Player::PowerThree(unsigned int updatevalue,float dt)
{
	float Xmove = 0.0f;
	float Ymove = 0.0f;
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(PX1 + rect.right);
	float PY2 = (PY1 + rect.bottom);
	bool yellowPower;
	yellowPower	= false;
	int theNumber= 0;
	if((updatevalue & M_LEFT)!=false)
	{
			Xmove = dt* MovementSpeedX;
			oldX = position.x;
			position.x -= Xmove;
			if(CollisionCheck(PX1-=Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 1)
			{
				position.x = oldX;
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1-Xmove,PY1,PX2-Xmove,PY2,ObjectList);
			}
	}
	if((updatevalue & M_RIGHT)!=false)
	{
		//process right movement
		//if(PowerActive == false)
		//{
		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) != 1)
		//{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) != 1)
			{
				position.x += Xmove;
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 1)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
			if(CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1+Xmove,PY1,PX2+Xmove,PY2,ObjectList);
			}
		//}
		//}
	}
	if((updatevalue & M_JUMP)!= false)
	{
		Ymove = dt* JumpingConstant;
		if(CollisionCheck(PX1+Ymove,PY1,PX2+Ymove,PY2,ObjectList) == 1 || CollisionCheck(PX1-Ymove,PY1,PX2-Ymove,PY2,ObjectList) == 1)
		{
			//Ymove = dt* JumpingConstant;
			oldY = position.y;
			position.y -= Ymove;
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 1)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				position.y = oldY;
				//return
			}
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 2)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				//return
			}
			if(CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList) == 3)
			{
				theNumber = CollisionCheck(PX1,PY1-Ymove,PX2,PY2-Ymove,ObjectList);
				//return
			}

		}
	}
	if((updatevalue & M_JUMP)==false)
	{
	Ymove = dt* Gravity;
	oldY = position.y;
	position.y += Ymove;
	if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 1)
	{
		position.y = oldY;
		theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
	}
	if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 2)
	{
		theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
	}
	if(CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList) == 3)
	{
		theNumber = CollisionCheck(PX1,PY1+Ymove,PX2,PY2+Ymove,ObjectList);
	}
	}
	//powers
	if((updatevalue & P1)!=false)
	{
		SelectedPower = 2;
	}
	if((updatevalue & P2)!=false)
	{
		SelectedPower = 3;
	}
	if((updatevalue & P3)!=false)
	{
		SelectedPower = 4;
	}
	if((updatevalue & P4)!=false)
	{
		SelectedPower = 1;
	}
	xvelocity = position.x - oldX;
	yvelocity = position.y - oldY;
	return theNumber;
}

The_Sprite* Player::getSpritePointer()
{
	return &sprite;
}
void Player::setTextureList(IDirect3DTexture9* texturelist[])
{
	//
	for(int i = 0; i < 4; i++)
	{
		PlayerTextures[i] = texturelist[i];
	}
}
