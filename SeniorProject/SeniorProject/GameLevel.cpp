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
	width = 0;
	height = 0;

	//to be put into an init function
	
}
GameLevel::~GameLevel()
{}

void GameLevel::draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world)
{

	background.draw(a_device, a_sprite, a_world);

	for(int i = 0; i < width; ++i)
		for(int j = 0; j < height; ++j)
			drawnLevel[i][j].draw(a_device,a_sprite,a_world);
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

void GameLevel::MapPointers (char** map)
{
	for (int i = 0; i < width ; i++)
	{
		for (int j = 0; j < height ; j++)
		{

			switch(map[i][j])
			{
			case ' ':
			//space is empty 
			//
			break;
			case '#': 
			drawnLevel[i][j] = block;
			break;
			case '\n':
				//new line
			break;
			case 'P':
				//draw  player
			break;
			default: break;
			};
		}
	}
}
void GameLevel::DrawMap()
{}
//The_Sprite & The_Sprite::operator = (const The_Sprite & s)
//{
//	this->The_Sprite::The_Sprite(s);
//	return *this;
//}
//The_Sprite & ::operator =(const The_Sprite &s);
//{
// 1.  Deallocate any memory that TheClass is using internally
// 2.  Allocate some memory to hold the contents of s
// 3.  Copy the values from s into this instance
// 4.  Return *this
//}

The_Sprite* GameLevel::getBlock()
{
	return block;
}