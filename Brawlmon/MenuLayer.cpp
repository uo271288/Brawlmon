#include "MenuLayer.h"
#include "Game.h"
#include "Gamelayer.h"

MenuLayer::MenuLayer()
	: Layer()
{
	Game::getInstance().scale();
	init();
}

void MenuLayer::init() 
{
	background = new Background("res/menu.png", WIDTH * .5f, HEIGHT * .63f);
	button = new Actor("res/boton_jugar.png", WIDTH * .5f, HEIGHT * .7f, 232, 72);
}

void MenuLayer::keysToControls(SDL_Event event)
{
	Layer::keysToControls(event);

	if (event.type == SDL_KEYDOWN)
	{
		int code = event.key.keysym.sym;
		switch (code)
		{
		case SDLK_SPACE:
			controlContinue = true;
			break;
		}
	}
}

void MenuLayer::mouseToControls(SDL_Event event)
{
	Layer::mouseToControls(event);

	float motionX = event.motion.x / Game::getInstance().scaleLower;
	float motionY = event.motion.y / Game::getInstance().scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (button->containsPoint(motionX, motionY)) 
		{
			controlContinue = true;
		}
	}

}

void MenuLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
}

void MenuLayer::processControls() 
{
	Layer::processControls();
	if (controlContinue) 
	{
		controlContinue = false;
		Game::getInstance().layer = new GameLayer();
	}
}
void MenuLayer::draw() 
{
	background->draw();
	button->draw();

	SDL_RenderPresent(Game::getRenderer());
}