#include "GameLevel.h"
#include "Player.h"
#include "Enemy.h"
#include "Object.h"
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
	width = 0;
	height = 0;
}
GameLevel::~GameLevel()
{}
void GameLevel::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world)
{

	background.draw(a_device, a_sprite, a_world);
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

void GameLevel::LoadMap (const char * filename)
{
	std::ifstream openfile (filename);
	//std::string tempLine;
	//std::vector<int> tempVector;
	if (openfile.is_open())
	{ 
		openfile >> height >> width;

		map = new char*[width];

		for(int i = 0; i < width; ++i)
		{
			map[i] = new char[height];
		}

		int countW = 0, countH = 0;
		char c;

		do{
			c = openfile.get();

			if(c !=EOF)
			{
				map[countH][countW] = c;
				countH++;

				if(countW>width)
				{
					countW = 0;
					countH++;

					if(countH>height)
						break;
				}
			}//while in file

		}while(!openfile.eof());//end do while
	}// file is open
	openfile.close();
}//end of loadFromFile

void GameLevel::DrawMap (char** map)
{
	for (int i = 0; i < width ; i++)
	{
		for (int j = 0; j < height ; j++)
		{
			if (map[i][j] != ' ')
			{

			}
			else
			{

			}

		}
	}
}