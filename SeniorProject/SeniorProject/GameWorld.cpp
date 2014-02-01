//
#include "GameWorld.h"
#include "Player.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

GameWorld::GameWorld()
{
	currentLevel = 0;

}

GameWorld::GameWorld(const GameWorld & g)
{
}

GameWorld::~GameWorld()
{
release();
}

void GameWorld::init()
{
	GameLevel * newLevel = new GameLevel();
	levels.push_back(*newLevel);
	Active = 0;

}

GameWorld & GameWorld::operator = (const GameWorld & g)
{
	return * this;
}

Player * GameWorld::getPlayer()
{
	return &player;
}

void GameWorld::setPlayer(int i, Player * p)
{
}

int GameWorld::getActive()
{
	return Active;
}

void GameWorld::setActive(int a)
{
	Active = a;
}

void GameWorld::addLevel(GameLevel gl)
{
	levels.push_back(gl);
}

void GameWorld::loadFromFile(IDirect3DDevice9* a_d, IDirect3DTexture9* a_t, char * filename)
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
		//ground.push_back(sprite);
	}
	else
	{
		//platform.push_back(sprite);
	}
}

//The_Sprite * GameWorld::getSprite(int list, int i)
//{
//}

void GameWorld::clearVectors()
{
	
}

void GameWorld::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world)
{
	levels[Active].draw(a_device, a_sprite, a_world);
}

GameLevel * GameWorld::getLevel(int i)
{
	return &levels[i];
}

void GameWorld::release()
{
	for(int i = 0; i < levels.size(); ++i)
	{
		levels[i].release();
	}
	levels.empty();
}

int GameWorld::getCurrentLevel()
{
return currentLevel;
}

