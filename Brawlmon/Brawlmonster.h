#pragma once

#include "Actor.h"
#include "Attack.h"

class Brawlmonster :
	public Actor
{
public:
	Brawlmonster(std::string filename, std::string name, float x, float y, float maxlife, float defense, std::vector<Attack*> attacks);
	void attack(Brawlmonster* enemy, Attack* attack);

	std::string name;
	float life, maxlife, defense;
	std::vector<Attack*> attacks;
};