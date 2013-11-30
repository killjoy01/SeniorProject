#pragma once

#include "Player.h"

class Enemy : public Player
{
private:
	bool stationary;

public:
	//needs work
	void setMove();
	Enemy();

	bool getStationary();
	void setStationary(bool);

};


}

