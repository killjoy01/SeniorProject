#include "Player.h"

Player::Player()
{
	xvelocity = 0;
	yvelocity = 0;
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

float Player::getXVelocity()
{
	return xvelocity;
}

float Player::getYVelocity()
{
	return yvelocity;
}

void Player::setXVelocity(float x)
{
	xvelocity = x;
}

void Player::setYVelocity(float y)
{
	yvelocity = y;
}

IDirect3DTexture9* Player::getTexture()
{
	return sprite.getTexture();
}

void Player::setTexture(IDirect3DTexture9* t)
{
	sprite.setTexture(t);
}

D3DXVECTOR3 Player::getPosition()
{
	return sprite.getPosition();
}

void Player::setPosition(D3DXVECTOR3 v)
{
	sprite.setPosition(v);
}

void Player::setWidth(int w)
{
	sprite.setWidth(w);
}

int Player::getWidth()
{
	return sprite.getWidth();
}

void Player::setHeight(int h)
{
	sprite.setHeight(h);
}

int Player::getHeight()
{
	return sprite.getHeight();
}

void Player::setRect()
{
	sprite.setRect();
}

RECT & Player::getRect()
{
	return sprite.getRect();
}

bool Player::checkForCollision(const The_Sprite & a_s)
{
	return sprite.checkForCollision(a_s);
}

int Player::rightside()
{
	return sprite.rightside();
}

int Player::bottom()
{
	return sprite.bottom();
}

void Player::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world)
{

	sprite.draw(a_device, a_sprite, a_world);
}

void Player::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world, const D3DXVECTOR3 *pos)
{

	sprite.draw(a_device, a_sprite, a_world, pos);
}

The_Sprite* Player::getSpritePointer()
{
	return &sprite;
}