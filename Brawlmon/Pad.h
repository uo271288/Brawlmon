#pragma once

#include "Actor.h"

class Pad : public Actor
{
public:
	Pad(float x, float y);
	float getOrientationX(float clickX);
	float getOrientationY(float clickY);
};