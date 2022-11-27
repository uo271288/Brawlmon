#pragma once

#include <SDL_image.h>
#include <string>

#include "BoundingBox.h"

enum class Orientation 
{
	Right, Left, Up, Down
};

enum class State 
{
	Moving, MovingHorizontal, MovingVertical, Dying, Dead, Defeated
};

class Actor
{
public:
	Actor(std::string filename, float x, float y, int width, int height);

	virtual void draw(float scrollX = 0, float scrollY = 0);

	bool isOverlapping(Actor* actor);
	bool containsPoint(float pointX, float pointY);

	bool clicked = false;

	float x, y;
	float vx, vy;
	int width, height, fileWidth, fileHeight;
	SDL_Texture* texture;

	void sweep(std::unordered_set <Actor*>& actors);

	BoundingBox boundingBox;
};