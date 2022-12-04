#pragma once

#include "Text.h"
#include "Attack.h"

#include <SDL.h>
#include <vector>

class Menu
{
public:
	Menu(std::vector<Attack*> attacks);
	void draw();
	void select(int option);
	void clearSelection();

	Text* attack1;
	Text* attack2;
	Text* attack3;
	Text* attack4;

	Attack* selectedAttack;
	std::vector<Attack*> attacks;
};