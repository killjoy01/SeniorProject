#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Object.h"
#include "Map.h"
#include <vector>
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include <fstream>

using namespace std;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class GameLevel
{
private:
	Player * player;
	vector<Enemy> enemies;
	vector<Object> objects;
	Object goal;
	The_Sprite*** drawnLevel;
	Map charArray;
	int width, height;
	The_Sprite background;
	The_Sprite block;

public: 
	GameLevel();
	~GameLevel();
	void init(char* filename, Player * p);
	void init(char* filename, The_Sprite* bgTexture, The_Sprite* blockTexture, The_Sprite* playerTexture, int w, int h);
	Player * getPlayer();
	void setPlayer(Player *);
	int getActive();
	void setActive(int);
	bool checkForCollision(D3DXVECTOR3);
	void setBackground(The_Sprite*);
	
	
	int getEnemySize();
	int getObjectSize();
	void clearVectors();
	The_Sprite * getBackground();

	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);

	int getSize(int);


	
	void LoadMap (char * filename);
	void MapPointers (char** map);
	void DrawMap();
	The_Sprite* getBlock();

	void release();
};
