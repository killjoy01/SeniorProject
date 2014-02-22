#pragma once
#include "templatedArray.h"
#include "sprite.h"

//note: Mask Check Value is 384

enum m_states{LEVELS, CREDITS, A_QUIT, NUMSTATES};

enum keys{UP = 4, DOWN = 8, SELECT = 384};

struct MenuButton
{
	RECT rect;
	int state; 
	bool isSelected;

	MenuButton():state(LEVELS),isSelected(false){};
	MenuButton(int STATE, bool selected):state(STATE), isSelected(selected){};
};

class Menu
{
private:
	tArray<MenuButton> buttons;
	int selectedButton;
public:
	Menu();
	void Initialize();
	int Update(int button);

private:
	void initButtons();
	void select(int state);
};