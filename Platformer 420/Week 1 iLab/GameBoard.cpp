#include "GameBoard.h"
#include "Player.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

GameBoard::GameBoard()
{
}

GameBoard::GameBoard(const GameBoard & g)
{
}

GameBoard::~GameBoard()
{
}

void GameBoard::init()
{
		/*	
				
			main_sprite.InitialVelocity = 0.0f;
			ground[0] = new The_Sprite(graphics, new Texture2D("/Application/resources/ground.png", false), new Vector3((960.0F / 2.0F), (544.0F / 2.0f), 0.0F),
										 new Vector3(1.0f, 1.0f, 1.0f), 0.0f);							                                                        
			ground[0].position = new Vector3(ground[0].position.X - (ground[0].Width / 2), ground[0].position.Y + (ground[0].Height / 2), 0.0f);
			ground[0].Update ();
			ground[1] = new The_Sprite(graphics, new Texture2D("/Application/resources/ground.png", false), new Vector3((960.0F / 2.0F), (544.0F / 2.0f), 0.0F),
										 new Vector3(1.0f, 1.0f, 1.0f), 0.0f);							                                                        
			ground[1].position = new Vector3(ground[0].rect.max.X, ground[1].position.Y + (ground[1].Height / 2), 0.0f);
			ground[1].Update ();
			platform = new The_Sprite(graphics, new Texture2D("/Application/resources/platform.png", false), new Vector3((960.0F / 2.0F), (544.0F / 2.0f), 0.0F),
										 new Vector3(1.0f, 1.0f, 1.0f), 0.0f);
			platform.position = new Vector3(600.0f, ground[0].position.Y - platform.Height, 0.0f);
			platform.Update ();
		*/
}

GameBoard & GameBoard::operator = (const GameBoard & g)
{
	return Null;
}

Player * GameBoard::getPlayer()
{
	return &player;
}

void GameBoard::setPlayer(int i, Player * p)
{
}

int GameBoard::getActive()
{
	return Active;
}

void GameBoard::setActive(int a)
{
	Active = a;
}

void GameBoard::loadFromFile(IDirect3DDevice9* a_d, IDirect3DTexture9* a_t, char * filename)
{
	ifstream file;
	file.open(filename);
	The_Sprite * sprite = new The_Sprite;
	float x, y;
	int width, height, list;
	string imagefilename;
	file >> x >> y >> width >> height >> list;
	sprite->setTexture(a_t);
	sprite->setPosition(D3DXVECTOR3(x, y, 0.0f));
	sprite->setWidth(width);
	sprite->setHeight(height);
	sprite->setRect();
	sprite->setScalex(1.0f);
	sprite->setScaley(1.0f);
	sprite->setRotation(0.0f);
	if (list == 0)
	{
		ground.push_back(sprite);
	}
	else
	{
		platform.push_back(sprite);
	}
}

int GameBoard::getSize(int list)
{
	if (list == 0)
	{
		return ground.size();
	}
	else
	{
		return platform.size();
	}
}

The_Sprite * GameBoard::getSprite(int list, int i)
{
	if (list == 0)
	{
		return ground[i];
	}
	else if (list == 1)
	{
		return platform[i];
	}
	else
	{
		return &goal;
	}
}

void GameBoard::clearVectors()
{
	for (int i = 0; i < ground.size(); ++i)
	{
		delete ground[i];
	}
	ground.clear();
	for (int i = 0; i < platform.size(); ++i)
	{
		delete platform[i];
	}
	platform.clear();
}