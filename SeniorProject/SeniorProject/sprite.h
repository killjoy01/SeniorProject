#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class The_Sprite
{
protected:
	IDirect3DTexture9* texture;
	D3DXVECTOR3 position;
	float scalex;
	float scaley;
	float rotation;
	int width;
	int height;
	RECT rect;

public:
	The_Sprite();
	The_Sprite(const The_Sprite &);
	~The_Sprite();
	//The_Sprite & operator = (const The_Sprite &);

	IDirect3DTexture9* getTexture();
	void setTexture(IDirect3DTexture9*);
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3);
	float getScalex();
	void setScalex(float);
	float getScaley();
	void setScaley(float);
	float getRotation();
	void setRotation(float);
	void setWidth(int);
	int getWidth();
	void setHeight(int);
	int getHeight();
	void setRect();
	RECT & getRect();
	bool checkForCollision(const The_Sprite &);
	int rightside() const;
	int bottom() const;

	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);
	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *, const D3DXVECTOR3 * position);

	The_Sprite & operator =(const The_Sprite &s);
	//The_Sprite (const The_Sprite &s);
};