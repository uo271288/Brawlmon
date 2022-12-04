#include "Enemy.h"

Enemy::Enemy(std::string filename, float x, float y, State state) 
	:Actor(filename, x, y, 50, 58), state(state) {

	aWalkingRight = new Animation(filename, width, height, 256, 256, 6, 2, 4, 4);
	aWalkingLeft = new Animation(filename, width, height, 256, 256, 6, 1, 4, 4);
	aWalkingUp = new Animation(filename, width, height, 256, 256, 6, 3, 4, 4);
	aWalkingDown = new Animation(filename, width, height, 256, 256, 6, 0, 4, 4);

	if (state == State::MovingHorizontal)
	{
		animation = aWalkingLeft;
		vxIntelligence = -1;
		vx = -1;
	}
	if (state == State::MovingVertical)
	{
		animation = aWalkingUp;
		vyIntelligence = -1;
		vy = -1;
	}
}
void Enemy::update() {

	animationEnded = animation->update();
	switch (state)
	{
	case State::MovingHorizontal:
		if (vx == 0) {
			vxIntelligence *= -1;
			animation = animation == aWalkingRight ? aWalkingLeft : aWalkingRight;
			vx = vxIntelligence;
		}
		break;
	case State::MovingVertical:
		if (vy == 0) {
			vyIntelligence *= -1;
			animation = animation == aWalkingDown ? aWalkingUp : aWalkingDown;
			vy = vyIntelligence;
		}
		break;
	case State::Defeated:
		vx = 0;
		vy = 0;
		break;
	}

	if (x < 45)
	{
		x = 45;
		vx = 0;
	}

	if (x > 325)
	{
		x = 325;
		vx = 0;
	}

	if (y > 410)
	{
		y = 410;
		vy = 0;
	}

	if (y < -50)
	{
		y = -50;
		vy = 0;
	}

	boundingBox.update(x, y);
}

void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Enemy::defeat()
{
	animation->loop = false;
	state = State::Defeated;
}