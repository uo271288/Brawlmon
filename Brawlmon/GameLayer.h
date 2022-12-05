#pragma once

#include <list>
#include <unordered_map>

#include "Layer.h"
#include "Background.h"
#include "PauseLayer.h"
#include "Tile.h"
#include "Player.h"
#include "Space.h"
#include "Enemy.h"
#include "CombatLayer.h"
#include "Attack.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void loadMap(std::string name);
	void loadAttacks(std::string name);
	std::list<Brawlmonster*> loadBrawlmonsters(std::string name);
	void loadEnemyBrawlmonsters();
	void loadMapObject(char character, float x, float y);
	void calculateScroll();

	void keysToControls(SDL_Event event) override;
	void mouseToControls(SDL_Event event) override;
	void gamepadToControls(SDL_Event event) override;

	Space* space;
	Player* player;
	Background* background;

	std::list<Tile*> tiles; 
	std::list<Enemy*> enemies;
	Enemy* leader;
	std::unordered_map<std::string, Attack*> attacks;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	float scrollX = 0;
	float scrollY = 0;
	int mapWidth = 0;
	int mapHeight = 0;

	int newEnemyTime = 0;
};