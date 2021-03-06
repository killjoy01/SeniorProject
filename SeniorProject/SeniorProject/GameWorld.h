//james
#pragma once

#include "GameLevel.h"
#include <vector>
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class GameWorld
{
private:
	Player player;
	vector<GameLevel> levels; 
	int Active;
	
public:
	
	int getSize(int list);
	//getSprite(int list, int i);
	GameWorld();
	GameWorld (const GameWorld &);
	~GameWorld();
	void init();
	GameWorld & operator = (const GameWorld &);

	void update();
	Player * getPlayer();
	void setPlayer(int, Player *);
	int getActive();
	void setActive(int);
	int checkForCollision();
	void loadFromFile (IDirect3DDevice9*, IDirect3DTexture9*, char * filename);
	void clearVectors();
	void addLevel();
	void nextLevel();

	GameLevel * getLevel(int);

	void draw(IDirect3DDevice9* a_device, ID3DXSprite* a_sprite, D3DXMATRIX * a_world);

	void setLevelVars(int forLevel);

	void release();

	void setObjectList(int);

	bool outOfLevels();

	void reset();

	GameLevel * getCurrentLevel();
};