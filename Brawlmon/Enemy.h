#pragma once
#include "Actor.h"
#include "Animation.h"
#include "Player.h"

class Enemy : public Actor
{
public:
	Enemy(std::string filename, float x, float y, State state);
	void update();
	void draw(int scrollX, int scrollY) override;
	bool hit(Player* actor);

	Animation* aWalkingRight;
	Animation* aWalkingLeft;
	Animation* aWalkingUp;
	Animation* aWalkingDown;
	Animation* animation;

	State state = State::Moving;

	int vxIntelligence = 0, vyIntelligence = 0;
};