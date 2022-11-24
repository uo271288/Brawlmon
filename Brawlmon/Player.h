#pragma once

#include "Actor.h"
#include "Animation.h"

class Player : public Actor
{
public:
	Player(float x, float y);

	void update();
	void draw(int scrollX, int scrollY) override;
	void moveX(float direction);
	void moveY(float direction);

	int shootCadence = 30;
	int shootTime = 0;

	Animation* animation;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;
	Animation* aWalkingRight;
	Animation* aWalkingLeft;
	Animation* aWalkingUp;
	Animation* aWalkingDown;

	State state = State::Moving;
	Orientation orientation = Orientation::Right;
};