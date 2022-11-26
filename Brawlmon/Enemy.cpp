#include "Enemy.h"

Enemy::Enemy(std::string filename, float x, float y, State state) :Actor(filename, x, y, 50, 58), state(state) {

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
	else
	{
		animation = aWalkingUp;
		vyIntelligence = -1;
		vy = -1;
	}
}
void Enemy::update() {
	animation->update();
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
	}
	boundingBox.update(x, y);
}

void Enemy::draw(int scrollX, int scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}