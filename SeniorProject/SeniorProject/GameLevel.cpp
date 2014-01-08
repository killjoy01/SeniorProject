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
{}

void GameLevel::init(char* filename, Player * p)
{
	player = p;
	charArray.load(filename);
	LoadMap(filename);
	MapPointers(charArray.getMap());
	DrawMap();

	//for(int i = 0; i < width; ++i)
	//	for(int j = 0; j < height; ++j)
	//		drawnLevel[i][j] = new The_Sprite;
}

void GameLevel::init(char* filename, The_Sprite* bgTexture, The_Sprite* blockTexture, The_Sprite* playerTexture, int w, int h)
{
	charArray.load(filename);
	MapPointers(charArray.getMap());
}

void GameLevel::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world)
{

	background.draw(a_device, a_sprite, a_world);

	for(int i = 0; i < width; ++i)
	{
		for(int j = 0; j < height; ++j)
		{
			if(drawnLevel[i][j] != NULL)
			{
				//float X = drawnLevel[i][j]->getPosition().x; float Y= drawnLevel[i][j]->getPosition().y;
				drawnLevel[i][j]->draw(a_device,a_sprite,a_world);//, &D3DXVECTOR3(	X,//drawnLevel[i][j]->getPosition().x,
				//Y,//drawnLevel[i][j]->getPosition().y,
				//0));
			}
		}
	}
	player->draw(a_device, a_sprite, a_world);

}

The_Sprite * GameLevel::getBackground()
{
	return &background;
}

void GameLevel::LoadMap (char * filename)
{
	charArray.load(filename);
	width = charArray.getW();
	height = charArray.getH();


	drawnLevel = new The_Sprite**[width];

	for(int i = 0; i < width; ++i)
	{
		drawnLevel[i] = new The_Sprite*[height];
	}



}//end of loadFromFile

void GameLevel::MapPointers (char** map)
{
	for (int j = 0; j < width ; j++)
	{
		for (int i = 0; i < height ; i++)
		{

			switch(map[i][j])
			{
			case '#': drawnLevel[i][j] = new The_Sprite; *drawnLevel[i][j] = block; break;
			case 'P': drawnLevel[i][j] = player->getSpritePointer(); player->setPosition(D3DXVECTOR3((float)(player->getWidth() * i),
						  (float)(player->getHeight() * j), 0.0f)); break;
			default: drawnLevel[i][j] = new The_Sprite;break;
			};
		}
	}
}
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
	for(int i = 0; i < height; ++i)
	{
		delete drawnLevel[i];
	}
	delete drawnLevel;

	charArray.Shutdown();
}