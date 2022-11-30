#pragma once

#include "Actor.h"
#include "Attack.h"

class Brawlmonster :
	public Actor
{
public:
	Brawlmonster(std::string filename, std::string name, float x, float y, float life, float defense, std::unordered_set<Attack*> attacks);
	void attack(Brawlmonster* enemy, Attack* attack);

	std::string name;
	float life, defense;
	std::unordered_set<Attack*> attacks;
};