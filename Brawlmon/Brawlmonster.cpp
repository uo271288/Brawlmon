#include "Brawlmonster.h"

Brawlmonster::Brawlmonster(std::string filename, std::string name, float x, float y, float life, float defense, std::unordered_set<Attack*> attacks)
	: Actor(filename, x, y, 0, 0), name(name), life(life), defense(defense), attacks(attacks) {}

void Brawlmonster::attack(Brawlmonster* enemy, Attack* attack)
{
	switch (attack->category)
	{
	case Category::Physical:
		enemy->life -= attack->damage / defense;
	case Category::Status:
		enemy->defense -= defense > attack->damage ? attack->damage : 0;
	}
}