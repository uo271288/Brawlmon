#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Brawlmonster.h"

class Player : public Actor
{
public:
	Player(float x, float y, std::list<Brawlmonster*> brawlmons);

	void update();
	void draw(float scrollX, float scrollY) override;
	void moveX(float direction);
	void moveY(float direction);
	bool hit(Actor* enemy);
	void stop();

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

	std::list<Brawlmonster*> brawlmons;
};