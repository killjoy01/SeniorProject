#include "Power.h"

//check ability 
Power::Power()
{
	PowerActive = false;
	TheState = 0;
}
void Power::CheckAbility()
{
//if (TheState == Red)
//{
	//if(PowerActive == true)
		//{
		//
		//}
	//break;
//}
//if (TheState == Blue)
	//{
	//if(PowerActive == true)
		//{
		//if player is colliding with water allow jump
		//after a jump dont allow jump for 1 second
		//}
	//break;
	//}
//if (TheState == Green)
	//{
	//if(PowerActive == true)
		//{
		//dont allow movement (momentum only)
		//if moving in X results in a collition
			//if X is positive make it negitive
			//else if X is negitive make it positive
			
		//if moving in Y results in a collition
		//if Y is positive make it negitive
		//else if Y is negitive make it positive
		//}
	//break;
//}
//if (TheState == White)
	//{
	//if(PowerActive == true)
		//{
		//turn of gravity
		//if player can move up do so
		//}
		//break;
	//}
//if (TheState == Yellow)
	//{
	//if(PowerActive == true)
		//{
		
		//if the player wants to move up or down and there is a wall to players left or right allow the move
		//if the move would make player collied with a wall dont allow move

		//if the player wants to left up or right and there is a wall to players up or down allow the move
		//if the move would make player collied with a wall dont allow the move
		//}
	//}
//if (TheState == Black)
	//{
	//if(PowerActive == true)
		//{
		//
		//}
	//}
//if (TheState == Orange)
	//{
	//if(PowerActive == true)
		//{
		//
		//}
//}
//if (TheState == Purple)
	//{
	//if(PowerActive == true)
		//{
		//
		//}
	//}

}

void Power::PowerSwitch()
{
if(PowerActive == true)
	{
		PowerActive = false;
	}
else
	{
		PowerActive = true;
	}
}