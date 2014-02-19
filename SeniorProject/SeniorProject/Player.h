//JJ
#pragma once
#include <vector>
#include "sprite.h"
#include "object.h"

const float MovementSpeedX = 0.1f;
const float MovementSpeedY = 0.1f;
const float Gravity = 0.1f;
const float JumpingConstant = 0.1f;	
const unsigned int M_LEFT = 1;
const unsigned int M_RIGHT = 2;
const unsigned int M_JUMP = 4;
const unsigned int M_DOWN = 8;
const unsigned int P1 = 16;
const unsigned int P2 = 32;
const unsigned int P3 = 64;
const unsigned int P4 = 128;
const unsigned int ENTER = 256;
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
	float Time;
	bool PowerActive;
	float LastChangedTimer;
	int SelectedPower;
	float dx, dy;
	float x, y;
	bool mayJumpAgain;
	bool isOnSolidGround;
	IDirect3DTexture9* PlayerTextures[4];
public:
	vector<Object> ObjectList;
	
	void setTextureList(IDirect3DTexture9*[]);
	Player();
	Player(const Player &);
	~Player();
	void init(int);
	Player & operator = (const Player &);
	void setPlayerTextur();
	int CollisionCheck(float x1,float y1,float x2,float y2,vector<Object> & ObjectList);
	void  setObjectList(vector<Object> &objects);
	void PowerOne(unsigned char updatevalue,float dt);
	void PowerTwo(unsigned char updatevalue,float dt);
	void PowerThree(unsigned char updatevalue,float dt);
	void NoPower(unsigned char updatevalue,float dt);
	The_Sprite* Player::getSpritePointer();
	//void ChangePosition(char keystate,float dt);
	//void SetObjectList(vector * ObjectList);
	//object list
	int UpdateState(unsigned char updatevalue,float dt);
	//void collisionResolution(float x1,float y1,float x2,float y2,vector<Object> & ObjectList);
	//void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);
	//void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *, const D3DXVECTOR3*);
};