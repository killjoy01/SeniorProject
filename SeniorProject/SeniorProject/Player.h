//JJ
#pragma once

#include "sprite.h"

class Player
{
protected:
	int id;
	The_Sprite sprite;
	float xvelocity, yvelocity;
	bool OnGround;
	bool IsJumping;
	float JumpTime;
public:
	Player();
	Player(const Player &);
	~Player();
	void init(int);
	Player & operator = (const Player &);

	int getID();
	void setID(int);
	float getXVelocity();
	float getYVelocity();
	void setXVelocity(float);
	void setYVelocity(float);
	void setTexture(IDirect3DTexture9*);
	IDirect3DTexture9* getTexture();
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3);
	int getWidth();
	void setWidth(int);
	int getHeight();
	void setHeight(int);
	void setRect();
	RECT & getRect();
	bool checkForCollision(const The_Sprite &);
	int rightside();
	int bottom();
	The_Sprite* getSpritePointer();
	void setScalex(float);
	void setScaley(float);
	void setRotation(float);

	//void ChangePosition(char keystate,float dt);
	void changePosition(unsigned char updatevalue,float dt);


	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);
	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *, const D3DXVECTOR3*);
};