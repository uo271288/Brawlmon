#pragma once

#include <list>

#include "Layer.h"
#include "Background.h"
#include "Tile.h"
#include "Player.h"
#include "Space.h"
#include "Enemy.h"
#include "Brawlmonster.h"
#include "Text.h"
#include "Lifebar.h"
#include "Menu.h"
#include "Audio.h"

class CombatLayer :
    public Layer
{
public:
	CombatLayer(Player* player, Enemy* enemy);

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void loadEnemyBrawlmon();
	void loadPlayerBrawlmon();

	void keysToControls(SDL_Event event) override;
	void mouseToControls(SDL_Event event) override;
	void gamepadToControls(SDL_Event event) override;

	Player* player;
	Enemy* enemy;
	Background* background;

	Audio* audioBackground;

	Brawlmonster* playerBrawlmon;
	Brawlmonster* enemyBrawlmon;

	Text* combatInfo;
	Text* enemyBrawlmonInfo;
	Text* playerBrawlmonInfo;

	Text* playerBrawlmonLife;
	Text* playerBrawlmonMaxLife;

	Lifebar* enemyBrawlmonLifebar;
	Lifebar* playerBrawlmonLifebar;

	Menu* menu;

	bool yourTurn = true;
};