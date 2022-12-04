#pragma once

#include <SDL.h>

class Lifebar
{
public:
	Lifebar(int x, int y, int width, int height, SDL_Color fGColor, SDL_Color bGColor);

	void draw();
	void update(float percent);

	float x, y;
	int width, height;
	float percent = 1.f; 
	SDL_Color bGColor, fGColor;
};