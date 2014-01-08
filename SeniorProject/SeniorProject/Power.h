#pragma once

class Power
{
private:
	int ID;
	bool PowerActive;
	enum PlayerState { Red, Blue, Green, Yellow, Black};
public:
	Power();
	int getID();
	void setID(int);
};