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
int Collision = 0;
	for(int i=0; i< ObjectList.size(); i++) 
	{
		if(ObjectList[i].getID() != 0)
		{
			if(x1 < ObjectList[i].getPosition().x &&  ObjectList[i].getPosition().x < x2)
			{
				if(y1 < ObjectList[i].getPosition().y && y2 > ObjectList[i].getPosition().y)
				{
					Collision = ObjectList[i].getID();
					return Collision;
					//return ObjectList[i].getID();
					//return
					//return i;
					//(ObjectList[i].getID() == 0)
				}
			}

			if(x1 < ObjectList[i].rightside() && x2 > ObjectList[i].rightside())
			{
				if(y1 <  ObjectList[i].getPosition().y && y2 >  ObjectList[i].getPosition().y)
				{
					//if(ObjectList[i].getID() != 0)
					//{
					//return ObjectList[i].getID();//break;
					Collision = ObjectList[i].getID();
					return Collision;
					//return i;
					//}
				}
			}		

			if(x1 < ObjectList[i].rightside() && x2 > ObjectList[i].rightside() )
			{
				if(y1 < ObjectList[i].bottom()  && y2 > ObjectList[i].bottom())
				{
					//if(ObjectList[i].getID() != 0)
					//{
					//return ObjectList[i].getID();//break;
					//return i;
					//}
					Collision = ObjectList[i].getID();
					return Collision;
				}
			}		

			if(x1 <  ObjectList[i].getPosition().x && x2 > ObjectList[i].getPosition().x)
			{
				if(y1 < ObjectList[i].bottom() && y2 > ObjectList[i].bottom())
				{
					//if(ObjectList[i].getID() != 0)
					//{				
					//return ObjectList[i].getID();
					//return i;
					//break;
					//}
					Collision = ObjectList[i].getID();
					return Collision;
				}
			}
		}
		//else
		//{
		//return 0;
		//}
	}
	return Collision; 
	//return 0;
	//return 0;
	//return 1;
	//return 2;
	//return 3;
}

int Player::UpdateState(unsigned int updatevalue, float dt)
{
	//movment
	int number;
	number = CollisionCheck(position.x, position.y,position.x+rect.right,position.y+rect.bottom,ObjectList);
	switch(SelectedPower)
	{
	case 1:
		setTexture(PlayerTextures[0]);
		NoPower(updatevalue,dt);
		break;
	case 2:
		setTexture(PlayerTextures[1]);
		PowerOne(updatevalue,dt);
		break;
	case 3:
		setTexture(PlayerTextures[2]);
		PowerTwo(updatevalue,dt);
		break;
	case 4:
		setTexture(PlayerTextures[3]);
		PowerThree(updatevalue,dt);
		break;
	}
	//return SelectedPower;
	return number;
	//return 0;
}
int Player::getSelectedPower()
{
return SelectedPower;
}
void Player::NoPower(unsigned int updatevalue,float dt) 
{
	float Xmove = 0.0f;
	float Ymove = 0.0f;
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(PX1 + rect.right);
	float PY2 = (PY1 + rect.bottom);
	if((updatevalue & M_LEFT)!=false)
	{
		if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) != 1)
		{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1-=Xmove,PY1,PX2-=Xmove,PY2,ObjectList) != 1)
			{
				position.x -= Xmove;
			}
			//else
			//{
			//	for(int i =0; i<120; i++)
			//	{
			//		if(CollisionCheck(PX1-=2,PY1,PX2-=2,PY2,ObjectList) != 1)
			//		{
			//			position.x -= 1;
			//		}
			//		else
			//		{
			//			i = 120;
			//		}
			//	}
			//}
		}
	}
	if((updatevalue & M_RIGHT)!=false)
	{
		//process right movement

		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) != 1)
		//{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1+=Xmove,PY1,PX2+=Xmove,PY2,ObjectList) != 1)
			{
				position.x += Xmove;
			}
		//}
	}
	if((updatevalue & M_JUMP)!= false)
	{
		//		if(lowJump == true)
		//{
		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
		//{	
			Ymove = dt* JumpingConstant;
			if(CollisionCheck(PX1,PY1-=Ymove,PX2,PY2-=Ymove,ObjectList) != 1)
			{
				position.y -= Ymove;
				//IsJumping = true;
			}
		//}
	}
	//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
	//{
		Ymove = dt* Gravity;
		if(CollisionCheck(PX1,PY1+=Ymove,PX2,PY2+=Ymove,ObjectList) != 1)
		{
			position.y += Ymove;
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
}
void Player::PowerOne(unsigned int updatevalue,float dt)
{
	float Xmove = 0.0f;
	float Ymove = 0.0f;
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(PX1 + rect.right);
	float PY2 = (PY1 + rect.bottom);
	if((updatevalue & M_LEFT)!=false)
	{
		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) != 1)
		//{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1-=Xmove,PY1,PX2-=Xmove,PY2,ObjectList) != 1)
			{
				position.x -= Xmove;
			}
			//else
			//{
			//for(int i = 0; i < 32; i++)
			//	{
			//	if(CollisionCheck(PX1-=Xmove,PY1,PX2-=Xmove,PY2,ObjectList) != 1)
			//		{
			//			position.x -= Xmove;
			//		}
			//	}
			//}
		//}
	}
	if((updatevalue & M_RIGHT)!=false)
	{
		//process right movement

		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) != 1)
		//{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1+=Xmove,PY1,PX2+=Xmove,PY2,ObjectList) != 1)
			{
				position.x += Xmove;
			}
		//}
	}
	if((updatevalue & M_JUMP)!= false)
	{
		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
		//{	
		//	Ymove = dt* JumpingConstant;
		//	if(CollisionCheck(PX1,PY1+=Ymove,PX2,PY2+=Ymove,ObjectList) != 1)
		//	{
		//		position.y += Ymove;
		//		//IsJumping = true;
		//	}
		//}
	}
	//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
	//{
		//Ymove = dt* Gravity;
		Ymove = 1;
		if(CollisionCheck(PX1,PY1-=Ymove,PX2,PY2-=Ymove,ObjectList) != 1)
		{
			position.y -= Ymove;
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
}
void Player::PowerTwo(unsigned int updatevalue,float dt)
{
	float Xmove = 0.0f;
	float Ymove = 0.0f;
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(PX1 + rect.right);
	float PY2 = (PY1 + rect.bottom);
	if((updatevalue & M_LEFT)!=false)
	{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1-=Xmove,PY1,PX2-=Xmove,PY2,ObjectList) != 1)
			{
				position.x -= Xmove;
			}
	}
	if((updatevalue & M_RIGHT)!=false)
	{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1+=Xmove,PY1,PX2+=Xmove,PY2,ObjectList) != 1)
			{
				position.x += Xmove;
			}
	}
	if((updatevalue & M_JUMP)!= false)
	{
		//		if(lowJump == true)
		//{
		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
		//{	
			Ymove = dt* JumpingConstant;
			if(CollisionCheck(PX1,PY1-=Ymove,PX2,PY2-=Ymove,ObjectList) != 1)
			{
				position.y -= Ymove;
				IsJumping = true;
			}
		//}
	}
	//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
	//{
		Ymove = dt* Gravity;
		if(CollisionCheck(PX1,PY1+=Ymove,PX2,PY2+=Ymove,ObjectList) != 1)
		{
			position.y += Ymove;
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
}
void Player::PowerThree(unsigned int updatevalue,float dt)
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
	if((updatevalue & M_DOWN)!=false)
	{

	}
	if((updatevalue & M_LEFT)!=false)
	{
		//process Left movement

		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) != 1)
		//{
			//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) 

			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1-=Xmove,PY1,PX2-=Xmove,PY2,ObjectList) != 1)
			{
				position.x -= Xmove;
			}

		//}
	}
	if((updatevalue & M_RIGHT)!=false)
	{
		//process right movement
		//if(PowerActive == false)
		//{
		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) != 1)
		//{
			Xmove = dt* MovementSpeedX;
			if(CollisionCheck(PX1+=Xmove,PY1,PX2+=Xmove,PY2,ObjectList) != 1)
			{
				position.x += Xmove;
			}
		//}
		//}
	}
	if((updatevalue & M_JUMP)!= false)
	{
		//		if(lowJump == true)
		//{
		//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
		//{	
		Ymove = dt* JumpingConstant;
		if(CollisionCheck(PX1+Ymove,PY1,PX2+Ymove,PY2,ObjectList) == 1 || CollisionCheck(PX1-Ymove,PY1,PX2-Ymove,PY2,ObjectList) == 1)
		{
			if(CollisionCheck(PX1,PY1-=Ymove,PX2,PY2-=Ymove,ObjectList) != 1)
			{
				position.y -= Ymove;
			}
			else
			{
				yellowPower = false;
			}

		}
		else 
		{
		if(CollisionCheck(PX1,PY1-=Ymove,PX2,PY2-=Ymove,ObjectList) == 1)
		{
			
				yellowPower = true;
		}
		else
			{
			yellowPower = false;
			}
		}
	}
	//else
	//{
	//lowJump = false;
	//}
	//gravity



	//if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList)!= 1)
	//{
	//Ymove = dt* JumpingConstant;
	//if(CollisionCheck(PX1,PY1-=Ymove,PX2,PY2-=Ymove,ObjectList) != 0)
	//{
	//	position.y -= Ymove;
	//}

	//if((updatevalue & M_JUMP) == false && (updatevalue & M_LEFT) == false || 
	//	(updatevalue & M_JUMP) == false && (updatevalue & M_RIGHT) == false)
	//if(CollisionCheck(PX1,PY1+=20,PX2,PY2+=20,ObjectList) == 1)
	//{
	//}
	//else
	if(yellowPower == false)
	{
		Ymove = dt* Gravity;
		if(CollisionCheck(PX1,PY1+=Ymove,PX2,PY2+=Ymove,ObjectList) != 1)
		{
			position.y += Ymove;
		}
	}

	//}
	//else
	//{
	//Time = dt;
	//}
	//else
	//{
	//	if(CollisionCheck(PX1+1,PY1,PX2+1,PY2,ObjectList) == 0 
	//		|| CollisionCheck(PX1-1,PY1,PX2-1,PY2,ObjectList) == 0)
	//	{
	//		position.y += dt* Gravity;
	//	}	
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
