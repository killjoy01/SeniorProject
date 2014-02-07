#include "Menu.h"

Menu::Menu()
	:selectedButton(0)
{
}

void Menu::initButtons()
{
	for(int i = 0; i < NUMSTATES; ++i)
	{
	buttons.insert(MenuButton(i,false);
	}
}

void Menu::Initialize()
{
initButtons();
}

int Menu::Update(int button)
{
	if(button & SELECT) //selected
	{
		return -1*selectedButton;
	}
	else if(button & UP) // up
	{
		select(selectedButton += 2 % NUMSTATES);
		return selectedButton+1;
	}
	else if(button & DOWN) //down
	{
		select(selectedButton += 1 % NUMSTATES);
		return selectedButton+1;
	}
}

void Menu::select(int state)
{
buttons[selectedButton].isSelected = false;
selectedButton = state;
buttons[state].isSelected = true;
}

