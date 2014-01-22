#pragma once
const static int Red = 0, Blue = 1, Green = 2 , White = 3, Black = 4, Yellow = 5, Orange = 6, Purple = 7;
class Power
{
private:
	//int ID;
	bool PowerActive;
public:
	Power();
	//int getID();
	//void setID(int);
	int TheState;
	void CheckAbility();
	void PowerSwitch();
};