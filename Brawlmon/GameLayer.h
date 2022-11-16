#pragma once

#include <list>

#include "Layer.h"
#include "Background.h"
#include "PauseLayer.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void loadMap(std::string name);
	void loadMapObject(char character, int x, int y);
	void calculateScroll();

	void keysToControls(SDL_Event event) override;
	void mouseToControls(SDL_Event event) override;
	void gamepadToControls(SDL_Event event) override;

	Background* background;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	float scrollX = 0;
	float scrollY = 0;
	int mapWidth = 0;
	int mapHeight = 0;

	int newEnemyTime = 0;
};