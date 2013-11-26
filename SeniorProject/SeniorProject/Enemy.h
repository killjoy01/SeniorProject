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
//<<<<<<< HEAD
//};
//=======
	bool getStationary();
	void setStationary(bool);
};
//>>>>>>> 3cdb007fb1c63540d0042496a95d724a163797bf
