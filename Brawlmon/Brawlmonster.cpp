#include "Brawlmonster.h"

Brawlmonster::Brawlmonster(std::string filename, std::string name, float x, float y, float maxlife, float defense, std::vector<Attack*> attacks)
	: Actor(filename, x, y, 130, 130), name(name), maxlife(maxlife), defense(defense), attacks(attacks)
{
	life = maxlife;
	idleAnimation = new Animation(filename, 130, 130, 295, 240, 14, 0, 2, 2);
	attackAnimation = new Animation(filename, 130, 130, 295, 240, 14, 1, 2, 2, false);
	animation = idleAnimation;
}

void Brawlmonster::attack(Brawlmonster* enemy, Attack* attack)
{
	animation = attackAnimation;
	switch (attack->category)
	{
	case Category::Physical:
		enemy->life -= attack->damage / enemy->defense;
	case Category::Status:
		enemy->defense -= enemy->defense > attack->damage ? attack->damage : 0;
	}
}

void Brawlmonster::update()
{
	bool animationEnded = animation->update();
	if (life <= 0)
	{
		state = State::Dead;
	}
	if (animationEnded)
	{
		animation = idleAnimation;
	}
}

void Brawlmonster::draw()
{
	animation->draw(x, y);
}