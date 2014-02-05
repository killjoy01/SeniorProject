#include "Player.h"

Player::Player()
{
	xvelocity = 0;
	yvelocity = 0;
	OnGround = true;
	IsJumping = false;
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
	int oldX = getPosition().x;
	int oldY = getPosition().y;
	
	//movment
	if((updatevalue & M_LEFT)==true)
	{
		//process Left movement
		position.x -= dt* MovementSpeedX;
	}
	if((updatevalue & M_RIGHT)==true)
	{
		position.x += dt* MovementSpeedX;
		//process right movement
	}
	if((updatevalue & M_JUMP)==true)
	{
		position.y -= dt* JumpingConstant;
		//float JumpStarted
		//JumpStarted+1 =<dt
	}


	//gravity


	//powers
	if((updatevalue & P1)==true)
	{
		//
	}
	if((updatevalue & P2)==true)
	{
		//
	}
	if((updatevalue & P3)==true)
	{
		//
	}
	if((updatevalue & P_On)==true)
	{
	
		//	if(PowerActive == true)
		//{
		//	PowerActive = false;
		//  LastChangedPowerTime
		//}
		//else
		//{
		//	PowerActive = true;
		//}
	}

	//if(sprite.checkForCollision() == 0)//0 no collition
	if(object.CollisionCheck( position.x,position.y, (position.x + rect.right), (position.y + rect.bottom)) == 0)
	{
		//do nothing
	}
	//if(sprite.checkForCollision() == 0)//1 block
	if(object.CollisionCheck( position.x,position.y, (position.x + rect.right), (position.y + rect.bottom)) == 1)
	{
		setPosition(D3DXVECTOR3(oldX, oldY, 0.0f));
	}
	//if(sprite.checkForCollision() == 0)//2 spike
	if(object.CollisionCheck( position.x,position.y, (position.x + rect.right), (position.y + rect.bottom)) == 2)
	{
		//reload current level
	}
	//if(sprite.checkForCollision() == 0)//3 goal
	if(object.CollisionCheck( position.x,position.y, (position.x + rect.right), (position.y + rect.bottom)) == 3)
	{
		//load next level
	}
}
//position.y -= dt* MovementSpeedX;

//	if (OnGround == true)
//	{
//		//process jumping
//		//W
//		//setPosition(D3DXVECTOR3(getPosition().x, getPosition().y - yvelocity, 0.0f));
//		IsJumping = true;
//		OnGround = false;
//		JumpTime = dt;
//	}
//
//if(IsJumping == true)
//{
//	if(JumpTime+1 >= dt)
//	{
//		setPosition(D3DXVECTOR3(getPosition().x, getPosition().y - yvelocity, 0.0f));
//	}
//	else
//	{
//		IsJumping = false;
//	}
//	//if(checkForCollision() == true)
//	//{
//	//setPosition(D3DXVECTOR3(oldX, oldY, 0.0f));
//	//}
//}
////process gravity
//if (OnGround == false && IsJumping == false)
//{
//	setPosition(D3DXVECTOR3(getPosition().x , getPosition().y + (updatevalue * 7), 0.0f));
//}


//bool Player::checkForCollision(const The_Sprite & a_s)
//{
//	return sprite.checkForCollision(a_s);
//}
