#pragma once

#include <string>
#include <SDL_ttf.h>

class Text
{
public:
	Text(int size, std::string content, float x, float y);

	float x, y;
	int width, height;
	std::string content;
	TTF_Font* font;

	void draw();
};