#include "CombatLayer.h"
#include "Game.h"

CombatLayer::CombatLayer()
	: Layer()
{
	init();
}

void CombatLayer::init()
{
	background = new Background("res/combat_background.png", 191, 302);
	Game::getInstance().scale();
}

void CombatLayer::processControls()
{
	Layer::processControls();


}

void CombatLayer::update()
{

}

void CombatLayer::draw()
{
	background->draw();



	SDL_RenderPresent(Game::getRenderer());
}

void CombatLayer::keysToControls(SDL_Event event)
{
	Layer::keysToControls(event);

	if (event.type == SDL_KEYDOWN)
	{
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code)
		{

		}
	}

	if (event.type == SDL_KEYUP)
	{
		int code = event.key.keysym.sym;
		// Levantada
		switch (code)
		{

		}
	}
}

void CombatLayer::mouseToControls(SDL_Event event)
{

}

void CombatLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
}

void CombatLayer::loadMap(std::string name)
{

}

void CombatLayer::loadMapObject(char character, float x, float y)
{

}