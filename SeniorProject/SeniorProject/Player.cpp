#include "Player.h"



Player::Player()
{
	xvelocity = 0;
	yvelocity = 0;
	OnGround = true;
	IsJumping = false;
	PowerActive = false;
	LastChangedTimer = 0;
	SelectedPower = 1;

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
	for(int i=0; i< ObjectList.size(); i++) 
	{
		if(x1 <= ObjectList[i].getPosition().x && x2 >= ObjectList[i].getPosition().x )
		{
			if(y1 >= ObjectList[i].getPosition().y && y2 <= ObjectList[i].getPosition().y)
			{
				return ObjectList[i].getID();
			}
		}

		if(x1 <= ObjectList[i].rightside() && x2 >= ObjectList[i].rightside())
		{
			if(y1 >=  ObjectList[i].getPosition().y && y2 <=  ObjectList[i].getPosition().y)
			{
				return ObjectList[i].getID();
			}
		}		

		if(x1 <= ObjectList[i].rightside() && x2 >= ObjectList[i].rightside() )
		{
			if(y1 >= ObjectList[i].bottom()  && y2 <= ObjectList[i].bottom())
			{
				return ObjectList[i].getID();
			}
		}		

		if(x1 <=  ObjectList[i].getPosition().x && x2 >= ObjectList[i].getPosition().x)
		{
			if(y1 >= ObjectList[i].bottom() && y2 <= ObjectList[i].bottom())
			{
				return ObjectList[i].getID();
			}
		}
	}
	//return 0;
	//return 1;
	//return 2;
	//return 3;
}
int Player::UpdateState(unsigned char updatevalue, float dt)
{
	//movment
	switch(SelectedPower)
	{
	case 1:
		PowerOne(updatevalue,dt);
		break;
	case 2:
		PowerTwo(updatevalue,dt);
		break;
	case 3:
		PowerThree(updatevalue,dt);
		break;
	}
	
	if (PowerActive == true)
	{
	return SelectedPower;
	// SelectedPower=1 -> Power1Active.png
	// SelectedPower=2 -> Power2Active.png
	// SelectedPower=3 -> Power3Active.png
	}
	else if(PowerActive == false)
	{
	return (SelectedPower + 3);
	// SelectedPower + 3 =4 -> Power1NotActive.png
	// SelectedPower + = 5 -> Power2NotActive.png
	// SelectedPower + =6 -> Power3NotActive.png
	}
	
}
void Player::PowerOne(unsigned char updatevalue,float dt) 
{
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(position.x + rect.right);
	float PY2 = (position.y + rect.bottom);

	if((updatevalue & M_LEFT)!=false)
	{
		//process Left movement
		if(PowerActive== false)
		{
			position.x -= dt* MovementSpeedX;
		}
		else
		{
			if(CollisionCheck(PX1,PY1+1,PX2,PY2+1,ObjectList) == 0 
				|| CollisionCheck(PX1,PY1-1,PX2,PY2-1,ObjectList) == 0)
			{
				position.x -= dt* MovementSpeedX;
			}		
		}
	}
	if((updatevalue & M_RIGHT)!=false)
	{
		//process right movement
		if(PowerActive == false)
		{
			position.x += dt* MovementSpeedX;
		}
		else
		{
			if(CollisionCheck(PX1,PY1+1,PX2,PY2+1,ObjectList) == 0 
				|| CollisionCheck(PX1,PY1-1,PX2,PY2-1,ObjectList) == 0)
			{
				position.x += dt* MovementSpeedX;
			}	
		}
	}
	if((updatevalue & M_JUMP)!= false)
	{
		if(PowerActive== false)
		{
			position.y -= dt* JumpingConstant;
		}
		else
		{
			if(CollisionCheck(PX1+1,PY1,PX2+1,PY2,ObjectList) == 0 
				|| CollisionCheck(PX1-1,PY1,PX2-1,PY2,ObjectList) == 0)
			{
				position.y -= dt* MovementSpeedY;
			}	
		}
		//float JumpStarted
		//JumpStarted+1 =<dt
	}
	//gravity
	if(PowerActive== false)
	{
		position.y += dt* Gravity;
	}
	else
	{
		if(CollisionCheck(PX1+1,PY1,PX2+1,PY2,ObjectList) == 0 
			|| CollisionCheck(PX1-1,PY1,PX2-1,PY2,ObjectList) == 0)
		{
			position.y += dt* Gravity;
		}	
	}
	//powers
	if((updatevalue & P1)!=false)
	{
		SelectedPower = 1;
	}
	if((updatevalue & P2)!=false)
	{
		SelectedPower = 2;
	}
	if((updatevalue & P3)!=false)
	{
		SelectedPower = 3;
	}
	if((updatevalue & P_On)!=false)
	{
		//if(LastChangedTimer >=dt+1)
		//{
		if(PowerActive !=false)
		{
			PowerActive = false;
			LastChangedTimer = dt;
		}
		else
		{
			PowerActive = true;
		}
		//}
	}
	//0 no collition
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 0){}
	//1 block
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 1)
	{
		position.x = oldX; position.y = oldY;
		//setPosition(D3DXVECTOR3(oldX, oldY, 0.0f));
	}
	//2 spike
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 2){/*reload current level*/}
	//3 goal
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 30){/*load next level*/}
}
void Player::PowerTwo(unsigned char updatevalue,float dt)
{
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(position.x + rect.right);
	float PY2 = (position.y + rect.bottom);

	if((updatevalue & M_LEFT)!=false)
	{
		//process Left movement
		position.x -= dt* MovementSpeedX;
	}
	if((updatevalue & M_RIGHT)!=false)
	{
		position.x += dt* MovementSpeedX;
		//process right movement
	}
	if((updatevalue & M_JUMP)!=false)
	{
		position.y -= dt* JumpingConstant;
		//float JumpStarted
		//JumpStarted+1 =<dt
	}
	position.y = dt* Gravity;
	//gravity
	//powers
	if((updatevalue & P1)!=false)
	{
		SelectedPower = 1;
	}
	if((updatevalue & P2)!=false)
	{
		SelectedPower = 2;
	}
	if((updatevalue & P3)!=false)
	{
		SelectedPower = 3;
	}
	if((updatevalue & P_On)!=false)
	{
		if(LastChangedTimer >=dt+1)
		{
			if(PowerActive !=false)
			{
				PowerActive = false;
				LastChangedTimer = dt;
			}
			else
			{
				PowerActive = true;
			}
		}
	}
	//0 no collition
	if(CollisionCheck( PX1,PY1,PX2,PY2,ObjectList) == 0)
	{}
	//1 block
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 1)
	{
		position.x = oldX;
		position.y = oldY;
		//setPosition(D3DXVECTOR3(oldX, oldY, 0.0f));
	}
	//2 spike
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 2){/*reload current level*/}
	//3 goal
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 30){/*load next level*/}
}
void Player::PowerThree(unsigned char updatevalue,float dt)
{
	float oldX = position.x;
	float oldY = position.y;
	float PX1 = position.x;
	float PY1 = position.y;
	float PX2 =(position.x + rect.right);
	float PY2 = (position.y + rect.bottom);
	if((updatevalue & M_LEFT)!=false)
	{
		//process Left movement
		position.x -= dt* MovementSpeedX;
	}
	if((updatevalue & M_RIGHT)!=false)
	{
		position.x += dt* MovementSpeedX;
		//process right movement
	}
	if((updatevalue & M_JUMP)!=false)
	{
		position.y -= dt* JumpingConstant;
		//float JumpStarted
		//JumpStarted+1 =<dt
	}
	position.y += dt* Gravity;
	//gravity
	//powers
	if((updatevalue & P1)!=false)
	{
		SelectedPower = 1;
	}
	if((updatevalue & P2)!=false)
	{
		SelectedPower = 2;
	}
	if((updatevalue & P3)!=false)
	{
		SelectedPower = 3;
	}
	if((updatevalue & P_On)!=false)
	{
		if(LastChangedTimer >=dt+1)
		{
			if(PowerActive !=false)
			{
				PowerActive = false;
				LastChangedTimer = dt;
			}
			else
			{
				PowerActive = true;
			}
		}
	}
	//0 no collition
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 0)
	{}
	//1 block
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 1)
	{
		//setPosition(D3DXVECTOR3(oldX, oldY, 0.0f));
		position.x = oldX;
		position.y = oldY;
	}
	//2 spike
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 2){/*reload current level*/}
	//3 goal
	if(CollisionCheck(PX1,PY1,PX2,PY2,ObjectList) == 30){/*load next level*/}
}
//void Player::draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *)
//{
//	//*a_world = calculateMatrix((int)getPosition().x, (int)getPosition().y, getScalex(), getScaley(), getRotation());
//	//a_sprite->SetTransform(a_world);
//	//a_sprite->Draw(getTexture(), NULL, &D3DXVECTOR3((float)(getWidth() / 2 + getPosition().x),
//	//							  (float)(getHeight() / 2 + getPosition().y), 0.0f),
//	//							   &D3DXVECTOR3((float)(getWidth() / 2 + getPosition().x),
//	//							   (float)(getHeight() / 2 + getPosition().y), 0.0f),
//	//						       D3DCOLOR_ARGB(255, 255, 255, 255));
//}
The_Sprite* Player::getSpritePointer()
{
	return &sprite;
}
