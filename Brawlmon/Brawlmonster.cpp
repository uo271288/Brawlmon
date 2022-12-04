#include "Brawlmonster.h"

Brawlmonster::Brawlmonster(std::string filename, std::string name, float x, float y, float maxlife, float defense, std::vector<Attack*> attacks)
	: Actor(filename, x, y, 120, 150), name(name), maxlife(maxlife), defense(defense), attacks(attacks) 
{
	life = maxlife;
}

void Brawlmonster::attack(Brawlmonster* enemy, Attack* attack)
{
	switch (attack->category)
	{
	case Category::Physical:
		enemy->life -= attack->damage / enemy->defense;
	case Category::Status:
		enemy->defense -= enemy->defense > attack->damage ? attack->damage : 0;
	}
}