#pragma once
#include "Actor.h"
#include "Animation.h"
#include "Player.h"

class Enemy : public Actor
{
public:
	Enemy(std::string filename, float x, float y, State state);
	void update();
	void draw(float scrollX, float scrollY) override;
	void defeat();

	Animation* aWalkingRight;
	Animation* aWalkingLeft;
	Animation* aWalkingUp;
	Animation* aWalkingDown;
	Animation* animation;

	State state = State::Moving;

	float vxIntelligence = 0, vyIntelligence = 0;
	bool animationEnded = false;
};