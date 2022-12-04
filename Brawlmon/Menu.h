#pragma once

#include "Text.h"

#include <SDL.h>

class Menu
{
public:
	Menu();
	void draw();

	Text* attack1;
	Text* attack2;
	Text* attack3;
	Text* attack4;
};