#include "Pad.h"

Pad::Pad(float x, float y)
	: Actor("res/pad.png", x, y, 120, 120)
{}

float Pad::getOrientationX(float clickX)
{
	return clickX - this->x > 0 ? 1 : -1;
}

float Pad::getOrientationY(float clickY)
{
	return clickY - this->y > 0 ? 1 : -1;
}