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

class GameBoard
{
private:
	Player player;
	vector<GameLevel> levels; 
	int Active;

public:
	GameBoard();
	GameBoard(const GameBoard &);
	~GameBoard();
	void init();
	GameBoard & operator = (const GameBoard &);

	Player * getPlayer();
	void setPlayer(int, Player *);
	int getActive();
	void setActive(int);
	bool checkForCollision(D3DXVECTOR3);
	void loadFromFile (IDirect3DDevice9*, IDirect3DTexture9*, char * filename);
	void clearVectors();
};