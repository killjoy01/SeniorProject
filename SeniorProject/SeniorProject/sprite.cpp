#include "sprite.h"

D3DXMATRIX & calculateMatrix(int, int, float, float, float);

The_Sprite::The_Sprite()
{
	texture = NULL;
	position = D3DXVECTOR3(0, 0, 0);
	scalex = 0;
	scaley = 0;
	rotation = 0;
	rect.bottom = 0;
	rect.top = 0;
	rect.left = 0;
	rect.right = 0;
}

The_Sprite::The_Sprite(const The_Sprite & s)
{
	texture = s.texture;
	position = s.position;
	scalex = s.scalex;
	scaley = s.scaley;
	rotation = s.rotation;
	rect.bottom = s.rect.bottom;
	rect.top = s.rect.top;
	rect.left = s.rect.left;
	rect.right = s.rect.right;
	width = s.width;
	height = s.height;
}

The_Sprite::~The_Sprite()
{
}

void The_Sprite::setTexture(IDirect3DTexture9* t)
{
	texture = t;
}

IDirect3DTexture9* The_Sprite::getTexture()
{
	return texture;
}

void The_Sprite::setPosition(D3DXVECTOR3 p)
{
	position = p;
}

void The_Sprite::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

D3DXVECTOR3 The_Sprite::getPosition()
{
	return position;
}

void The_Sprite::setScalex(float s)
{
	scalex = s;
}

float The_Sprite::getScalex()
{
	return scalex;
}

void The_Sprite::setScaley(float s)
{
	scaley = s;
}

float The_Sprite::getScaley()
{
	return scaley;
}

void The_Sprite::setRotation(float r)
{
	rotation = r;
}

float The_Sprite::getRotation()
{
	return rotation;
}

The_Sprite & The_Sprite::operator = (const The_Sprite & s)
{
	//this->The_Sprite::The_Sprite(s);
	this->texture = s.texture;
	this->position = s.position;
	this->scalex = s.scalex;
	this->scaley = s.scaley;
	this->rotation = s.rotation;
	this->rect.bottom = s.rect.bottom;
	this->rect.top = s.rect.top;
	this->rect.left = s.rect.left;
	this->rect.right = s.rect.right;
	this->width = s.width;
	this->height = s.height;
	return *this;
}

void The_Sprite::setWidth(int w)
{
	width = w;
}

int The_Sprite::getWidth()
{
	return width;
}

void The_Sprite::setHeight(int h)
{
	height = h;
}

int The_Sprite::getHeight()
{
	return height;
}

void The_Sprite::setRect()
{
	rect.right = width;
	rect.bottom = height;
	//needs an overloaded function to set the rect based on passed values
}

void The_Sprite::setRect(int r, int b)
{
	rect.right = r;
	rect.bottom = b;
	//needs an overloaded function to set the rect based on passed values
}

RECT & The_Sprite::getRect()
{
	return rect;
}

bool The_Sprite::checkForCollision(const The_Sprite & a_s)
{
	if (!(((int)a_s.position.y > (int)bottom()) || ((int)a_s.position.x > (int)rightside())||
		((int)a_s.bottom()) < (int)position.y) || ((int)rightside() < (int)position.x))
		//try to make this less confusing ^^^. i can understand it if I read it hard enough, but 
		//it takes a bit of rereading. I may do it if we don't get around to it. -Phil
		{
			return true;
		}
		else
		{
			return false;
		}
}

int The_Sprite::rightside() const
{
	return (int) position.x + rect.right;
}

int The_Sprite::bottom() const
{
	return (int) position.y + rect.bottom;
}

void The_Sprite::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world)
{

	*a_world = calculateMatrix((int)getPosition().x, (int)getPosition().y, getScalex(), getScaley(), getRotation());
	a_sprite->SetTransform(a_world);
	a_sprite->Draw(getTexture(), NULL, &D3DXVECTOR3((float)(getWidth() / 2 + getPosition().x),
								  (float)(getHeight() / 2 + getPosition().y), 0.0f),
								   &D3DXVECTOR3((float)(getWidth() / 2 + getPosition().x),
								   (float)(getHeight() / 2 + getPosition().y), 0.0f),
							       D3DCOLOR_ARGB(255, 255, 255, 255));
}

void The_Sprite::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world, const D3DXVECTOR3 * a_position)
{
	position.x = a_position->x;
	position.y = a_position->y;
	*a_world = calculateMatrix((int)getPosition().x, (int)getPosition().y, getScalex(), getScaley(), getRotation());
	a_sprite->SetTransform(a_world);
	a_sprite->Draw(texture, NULL, &D3DXVECTOR3(//(float)(getWidth() + 
		getPosition().x,//),
		(float)(getHeight() + getPosition().y), 0.0f), a_position, D3DCOLOR_ARGB(255, 255, 255, 255));
}
