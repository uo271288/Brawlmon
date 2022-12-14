#include "BoundingBox.h"
#include "Actor.h"

BoundingBox::BoundingBox(float x, float y, int width, int height) :width(width), height(height)
{
	update(x, y);
}

void BoundingBox::update(float x, float y)
{
	left = x - width / 2;
	right = x + width / 2;
	top = y - height / 2;
	bottom = y + height / 2;
}

bool BoundingBox::overlaps(BoundingBox& other) 
{
	return other.left < right
		&& other.right > left
		&& other.top < bottom
		&& other.bottom > top;
}

Vector2d BoundingBox::sweep(std::unordered_set<class Actor*> actors, Vector2d& delta) 
{
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	float x = left + halfWidth;
	float y = top + halfHeight;
	float oldX = x;
	float oldY = y;

	touchLeft = false;
	touchRight = false;
	touchTop = false;
	touchBottom = false;

	x += delta.x;
	update(x, y);
	for (auto const& actor : actors) 
	{
		if (overlaps(actor->boundingBox)) 
		{
			if (delta.x > 0)
			{
				x = actor->boundingBox.left - halfWidth;
				touchRight = true;
			}
			else 
			{
				x = actor->boundingBox.right + halfWidth;
				touchLeft = true;
			}
			update(x, y);
		}
	}

	y += delta.y;
	update(x, y);
	for (auto const& actor : actors) 
	{
		if (overlaps(actor->boundingBox)) 
		{
			if (delta.y > 0) 
			{
				y = actor->boundingBox.top - halfHeight;
				touchBottom = true;
			}
			else 
			{
				y = actor->boundingBox.bottom + halfHeight;
				touchTop = true;
			}
			update(x, y);
		}
	}

	return { x - oldX,y - oldY };
}

bool BoundingBox::contains(float x, float y)
{
	return left <= x
		&& right >= x
		&& top <= y
		&& bottom >= y;
}