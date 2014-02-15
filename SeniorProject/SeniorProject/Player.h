//JJ
#pragma once
#include <vector>
#include "sprite.h"
#include "object.h"

const float MovementSpeedX = 0.1f;
const float MovementSpeedY = 0.1f;
const float Gravity = 0.1f;
const float JumpingConstant = 0.2f;	
const unsigned char M_LEFT = 1;
const unsigned char M_RIGHT = 2;
const unsigned char M_JUMP = 4;
const unsigned char P1 = 8;
const unsigned char P2 = 16;
const unsigned char P3 = 32;
const unsigned char P_On = 64;
using namespace std;
class Player: public The_Sprite
{
protected:
	int id;
	The_Sprite sprite;
	Object object;
	float xvelocity, yvelocity;
	bool OnGround;
	bool IsJumping;
	bool lowJump;
	bool highJump;
	float JumpTime;

	bool PowerActive;
	float LastChangedTimer;
	int SelectedPower;
public:
	vector<Object> ObjectList;
	Player();
	Player(const Player &);
	~Player();
	void init(int);
	Player & operator = (const Player &);
	int CollisionCheck(float x1,float y1,float x2,float y2,vector<Object> & ObjectList);
	void  setObjectList(vector<Object> &objects);
	void PowerOne(unsigned char updatevalue,float dt);
	void PowerTwo(unsigned char updatevalue,float dt);
	void PowerThree(unsigned char updatevalue,float dt);
	The_Sprite* Player::getSpritePointer();
	//void ChangePosition(char keystate,float dt);
	//void SetObjectList(vector * ObjectList);
	//object list
	int UpdateState(unsigned char updatevalue,float dt);
	//void collisionResolution(float x1,float y1,float x2,float y2,vector<Object> & ObjectList);
	//void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);
	//void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *, const D3DXVECTOR3*);
};