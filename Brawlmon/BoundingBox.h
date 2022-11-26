#pragma once

#include <unordered_set>

struct Vector2d 
{
	float x, y;
};

class BoundingBox
{
public:
	BoundingBox(float x, float y, int width, int height);

	void update(float x, float y);
	bool overlaps(BoundingBox& other);
	Vector2d sweep(std::unordered_set<class Actor*> actors, Vector2d& delta);

	bool contains(float x, float y);

	int width, height;
	float left, right, top, bottom;
	bool touchLeft, touchRight, touchTop, touchBottom;
};