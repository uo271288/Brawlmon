#pragma once

#include <string>

enum class Category
{
	Physical, Status
};

class Attack
{
public:
	Attack(std::string name, float damage, Category category);

	std::string name;
	float damage;
	Category category;
};