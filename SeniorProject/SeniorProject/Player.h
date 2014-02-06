//JJ
#pragma once

#include "sprite.h"
#include "object.h"

class Player: public The_Sprite
{
protected:
	int id;
	The_Sprite sprite;
	Object object;
	float xvelocity, yvelocity;
	bool OnGround;
	bool IsJumping;
	float JumpTime;

	//vector<The_Sprite> ObjectList;

	const float MovementSpeedX = 96.0f;
	const float MovementSpeedY = 96.0f;
	const float Gravity = 40.0f;
	const float JumpingConstant = 15.0f;
		
	const unsigned char M_LEFT = 1;
	const unsigned char M_RIGHT = 2;
	const unsigned char M_JUMP = 4;
	const unsigned char P1 = 8;
	const unsigned char P2 = 16;
	const unsigned char P3 = 32;
	const unsigned char P_On = 64;
public:
	Player();
	Player(const Player &);
	~Player();
	void init(int);
	Player & operator = (const Player &);
	int getID();
	void setID(int);
	//void ChangePosition(char keystate,float dt);
	//void SetObjectList(vector * ObjectList);
	//object list
	void UpdateState(unsigned char updatevalue,float dt);
	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);
	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *, const D3DXVECTOR3*);
};