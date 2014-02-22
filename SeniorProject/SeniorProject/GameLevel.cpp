#include "GameLevel.h"
#include "Player.h"
#include "Enemy.h"
#include "Object.h"
#include "sprite.h"
#include <vector>
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
GameLevel::GameLevel()
{
	width =  height = 0;

}

GameLevel::~GameLevel()
{
	charArray.Shutdown();
}

void GameLevel::init(char* filename, /*The_Sprite * bgtexture*/ Player * p)
{
	player = p;
	charArray.load(filename);
	LoadMap(filename);
	//MapPointers(charArray.getMap());
	//DrawMap();
	player->setObjectList(objects);
	player->setPosition(D3DXVECTOR3(5.0f * 32.0f, 12.0f * 32.0f, 0.0f));
	//for(int i = 0; i < width; ++i)
	//	for(int j = 0; j < height; ++j)
	//		drawnLevel[i][j] = new The_Sprite;
}

void GameLevel::init(char* filename, The_Sprite* bgTexture, The_Sprite* blockTexture, The_Sprite* playerTexture, int w, int h)
{
//	LoadMap(filename);
	//MapPointers(charArray.getMap());
	player->setObjectList(objects);
}

void GameLevel::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world)
{

	background.draw(a_device, a_sprite, a_world);

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i].draw(a_device, a_sprite, a_world);
	}
	player->draw(a_device, a_sprite, a_world);

}

The_Sprite * GameLevel::getBackground()
{
	return &background;
}

void GameLevel::LoadMap (char * filename /*The_Sprite * bgtexture*/)
{
	//charArray.load(filename);
	width = charArray.getW();
	height = charArray.getH();

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			Object * o = new Object();
			o->setID(0);
			o->setPosition(D3DXVECTOR3((float)(32 * i), (float)(32 * j), 0.0f));
			o->setWidth(32);
			o->setHeight(32);
			o->setScalex(1.0f);
			o->setScaley(1.0f);
			o->setRotation(0.0f);
			o->setRect();
			if (charArray.get(j, i) == '#')
			{
				o->setID(1);
				o->setTexture(block.getTexture());
			}
			else if (charArray.get(j, i) == 'G')
			{
				o->setID(3);
				o->setTexture(goal.getTexture());
			}
			objects.push_back(*o);
		}
	}
}



//end of loadFromFile

//void GameLevel::MapPointers (char** map)
//{
//	for (int j = 0; j < width ; j++)
//	{
//		for (int i = 0; i < height ; i++)
//		{
//
//			switch(map[i][j])
//			{
//			case '#': drawnLevel[i][j] = new The_Sprite; *drawnLevel[i][j] = block; break;
//			case 'P': drawnLevel[i][j] = player->getSpritePointer(); player->setPosition(D3DXVECTOR3((float)(player->getWidth() * i),
//						  (float)(player->getHeight() * j), 0.0f)); break;
//			default: drawnLevel[i][j] = new The_Sprite;break;
//			};
//		}
//	}
//}
void GameLevel::DrawMap()
{
	for(int i = 0; i < width; ++i)
	{
		for(int j = 0; j < height; ++j)
		{
			int H = drawnLevel[i][j]->getHeight() * i; 
			int W = drawnLevel[i][j]->getWidth() * j;
			drawnLevel[i][j]->setPosition(W, H);
		}
	}
}

The_Sprite * GameLevel::getBlock()
{
	return &block;
}

void GameLevel::release()
{
	objects.empty();
	charArray.Shutdown();
}
//there is a getter for getlevel allready on line 101 in Game world
//getEnemy getObject are not working properly i will keep working on it but i think the rest are ok
//Enemy * GameLevel::getEnemy(int Ene)
//{
////return enemy of place int
//return &enemies[Ene];
Object * GameLevel::getObject(int obj)
{
//return object of place int
return &objects[obj];
}
//GameLevel * GameWorld::getLevel(int i){return &levels[i];}
//Map * GameLevel::getLevel(int map){return &charArray;}
The_Sprite * GameLevel::getGoal()
{
return &goal;
}
int GameLevel::getEnemySize()
{
	return enemies.size();
}
//return size of enemy vector;

int GameLevel::getObjectSize()
{
	return objects.size();
//return size of object vector
}

int GameLevel::checkForCollision()
{
	int oldpositionx = player->getPosition().x;
	int oldpositiony = player->getPosition().y;
	for (int i = 0; i < objects.size(); ++i)
	{
		int statememory = 0;
		if (player->checkForCollision(objects[i]))
		{
			if (objects[i].getID() == 0)
			{
				D3DXVECTOR3 resetPosition = D3DXVECTOR3(oldpositionx, oldpositiony, 0.0f);
				player->setPosition(resetPosition);
			}
			if (objects[i].getID() == 3)
			{
				return objects[i].getID();
			}
		}
	}
}

void GameLevel::setObjectList()
{
	player->setObjectList(objects);
}