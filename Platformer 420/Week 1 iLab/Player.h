#pragma once

#include "sprite.h"

class Player
{
private:
	The_Sprite sprite;
	float xvelocity, yvelocity;

public:
	Player();
	Player(const Player &);
	~Player();
	void init(int);
	Player & operator = (const Player &);

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

};