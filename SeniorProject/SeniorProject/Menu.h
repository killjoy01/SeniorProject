#pragma once
#include "templatedArray.h"
#include "sprite.h"

//note: Mask Check Value is 384

enum states{LEVELS, CREDITS, QUIT, NUMSTATES};

enum keys{UP = 4, DOWN = 8, SELECT = 384};

struct RECT
{
	float rectX, rectY, width, height;

	RECT():rectX(0),rectY(0),width(0),height(0){};
	RECT(float x, float y, float w, float h):rectX(x),rectY(y), width(w), height(h){};
};

struct MenuButton
{
	RECT rect;
	int state; 
	bool isSelected;

	MenuButton():state(NONE),isSelected(false){};
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