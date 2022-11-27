#pragma once

#include <list>

#include "Layer.h"
#include "Background.h"
#include "PauseLayer.h"
#include "Tile.h"
#include "Player.h"
#include "Space.h"
#include "Enemy.h"

class CombatLayer :
    public Layer
{
public:
	CombatLayer();

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void loadMap(std::string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();

	void keysToControls(SDL_Event event) override;
	void mouseToControls(SDL_Event event) override;
	void gamepadToControls(SDL_Event event) override;

	Background* background;
};