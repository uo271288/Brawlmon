#include "Player.h"

Player::Player(float x, float y) :Actor("res/jugador.png", x, y, 50, 58)
{
	
	aIdleRight = new Animation("res/player_idle.png", width, height, 192, 256, 14, 2, 3, 4);
	aIdleLeft = new Animation("res/player_idle.png", width, height, 192, 256, 14, 1, 3, 4);
	aIdleUp = new Animation("res/player_idle.png", width, height, 192, 256, 14, 3, 3, 4);
	aIdleDown = new Animation("res/player_idle.png", width, height, 192, 256, 14, 0, 3, 4);
	
	aWalkingRight = new Animation("res/player_walking.png", width, height, 256, 256, 6, 2, 4, 4);
	aWalkingLeft = new Animation("res/player_walking.png", width, height, 256, 256, 6, 1, 4, 4);
	aWalkingUp = new Animation("res/player_walking.png", width, height, 256, 256, 6, 3, 4, 4);
	aWalkingDown = new Animation("res/player_walking.png", width, height, 256, 256, 6, 0, 4, 4);

	animation = aIdleUp;
}

void Player::update()
{
	bool animationEnded = animation->update();
	
	if (vx > 0)
	{
		orientation = Orientation::Right;
	}
	else if (vx < 0)
	{
		orientation = Orientation::Left;
	}

	if (vy > 0)
	{
		orientation = Orientation::Down;
	}
	else if (vy < 0)
	{
		orientation = Orientation::Up;
	}

	if (orientation == Orientation::Up) 
	{
		animation = vy == 0 ? aIdleUp : aWalkingUp;
	}

	if (orientation == Orientation::Down) 
	{
		animation = vy == 0 ? aIdleDown : aWalkingDown;
	}

	if (orientation == Orientation::Right) 
	{
		animation = vx == 0 ? aIdleRight : aWalkingRight;
	}

	if (orientation == Orientation::Left) 
	{
		animation = vx == 0 ? aIdleLeft : aWalkingLeft;
	}
	boundingBox.update(x, y);
}

void Player::moveX(float direction) {
	vx = direction * 3;
}

void Player::moveY(float direction) {
	vy = direction * 3;
}

void Player::draw(int scrollX, int scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}