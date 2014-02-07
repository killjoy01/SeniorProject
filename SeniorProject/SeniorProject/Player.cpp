#include "Player.h"

const float MovementSpeedX = 96.0f;
const float MovementSpeedY = 96.0f;
const float Gravity = 40.0f;
const float JumpingConstant = 80.0f;	
const unsigned char M_LEFT = 1;
const unsigned char M_RIGHT = 2;
const unsigned char M_JUMP = 4;
const unsigned char P1 = 8;
const unsigned char P2 = 16;
const unsigned char P3 = 32;
const unsigned char P_On = 64;

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


void Player::UpdateState(unsigned char updatevalue, float dt)
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
			if(object.CollisionCheck(PX1,PY1+1,PX2,PY2+1) == 0 
			|| object.CollisionCheck(PX1,PY1-1,PX2,PY2-1) == 0)
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
			if(object.CollisionCheck(PX1,PY1+1,PX2,PY2+1) == 0 
			|| object.CollisionCheck(PX1,PY1-1,PX2,PY2-1) == 0)
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
			if(object.CollisionCheck(PX1+1,PY1,PX2+1,PY2) == 0 
			|| object.CollisionCheck(PX1-1,PY1,PX2-1,PY2) == 0)
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
		if(object.CollisionCheck(PX1+1,PY1,PX2+1,PY2) == 0 
		|| object.CollisionCheck(PX1-1,PY1,PX2-1,PY2) == 0)
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
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 0){}
	//1 block
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 1)
	{
	position.x = oldX; position.y = oldY;
	//setPosition(D3DXVECTOR3(oldX, oldY, 0.0f));
	}
	//2 spike
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 2){/*reload current level*/}
	//3 goal
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 30){/*load next level*/}
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
	if(object.CollisionCheck( PX1,PY1,PX2,PY2) == 0)
	{}
	//1 block
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 1)
	{
	position.x = oldX;
	position.y = oldY;
	//setPosition(D3DXVECTOR3(oldX, oldY, 0.0f));
	}
	//2 spike
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 2){/*reload current level*/}
	//3 goal
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 30){/*load next level*/}
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
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 0)
	{}
	//1 block
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 1)
	{
	//setPosition(D3DXVECTOR3(oldX, oldY, 0.0f));
	position.x = oldX;
	position.y = oldY;
	}
	//2 spike
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 2){/*reload current level*/}
	//3 goal
	if(object.CollisionCheck(PX1,PY1,PX2,PY2) == 30){/*load next level*/}
}