#pragma once

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

class GameLevel
{
private:
	Player player;
	vector<Enemy> enemies;
	vector<Object> objects;
	The_Sprite background;
	Object goal;
	
public: 
	void init();
	Player * getPlayer();
	void setPlayer(int, Player *);
	int getActive();
	void setActive(int);
	bool checkForCollision(D3DXVECTOR3);
	void loadFromFile (IDirect3DDevice9*, IDirect3DTexture9*, char * filename);
	int getEnemySize();
	int getObjectSize();
	void clearVectors();
	The_Sprite * getBackground();

	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);

	int getSize(int);
	

};
