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
	block = NULL;

}
GameLevel::~GameLevel()
{}

void GameLevel::init(char* filename)
{
	charArray.load(filename);
	LoadMap(filename);
	MapPointers(charArray.getMap());
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
			D3DXVECTOR3 position((drawnLevel[i][j]->getPosition().x + (i*drawnLevel[i][j]->getWidth())),
				(drawnLevel[i][j]->getPosition().y + (j*drawnLevel[i][j]->getHeight())),
				0);
			drawnLevel[i][j]->draw(a_device,a_sprite,a_world, &position);
		}
	}
	//player.draw(a_device, a_sprite, a_world);
	/*for (int i = 0; i < getEnemySize(), ++i)
	{
	enemies[i].draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world);
	}

	for (int i = 0; i < getObjectSize(); ++i)
	{
	objects[i].draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world);
	}

	goal.draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world); */
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
		The_Sprite** testSprite = drawnLevel[i];
			int x = 0;
	}

}//end of loadFromFile

void GameLevel::MapPointers (char** map)
{
	for (int i = 0; i < width ; i++)
	{
		for (int j = 0; j < height ; j++)
		{
			switch(map[j][i])
			{

			case '#': drawnLevel[i][j] = block; break;
			case 'P': drawnLevel[i][j] = player.getSpritePointer(); break;
			default: break;
			};
		}
	}
}
void GameLevel::DrawMap()
{}

The_Sprite* GameLevel::getBlock()
{
	return block;
}