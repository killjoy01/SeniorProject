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

<<<<<<< HEAD:Platformer/Week 1 iLab/GameLevel.h
};


	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);
}

=======
	int getSize(int);
	The_Sprite * getSprite(int, int);
//<<<<<<< HEAD
//};
//=======

	void draw(IDirect3DDevice9*, ID3DXSprite*, D3DXMATRIX *);
};
//>>>>>>> 3cdb007fb1c63540d0042496a95d724a163797bf
>>>>>>> 95bf76cb742cc87f82923ef2f47cec68402d4dd3:SeniorProject/SeniorProject/GameLevel.h
