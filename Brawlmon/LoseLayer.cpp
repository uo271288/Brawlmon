#include "LoseLayer.h"
#include "Game.h"
#include "Gamelayer.h"

LoseLayer::LoseLayer()
	: Layer()
{
	init();
}

void LoseLayer::init() 
{
	background = new Background("res/lose.png", WIDTH * .5f, HEIGHT * .63f);

	audioBackground = Audio::createAudio("res/lose.mp3", true);
	audioBackground->play();
}

void LoseLayer::keysToControls(SDL_Event event)
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

void LoseLayer::mouseToControls(SDL_Event event)
{
	Layer::mouseToControls(event);

	float motionX = event.motion.x / Game::getInstance().scaleLower;
	float motionY = event.motion.y / Game::getInstance().scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		controlContinue = true;
	}
}

void LoseLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
}

void LoseLayer::processControls() 
{
	Layer::processControls();
	if (controlContinue) 
	{
		controlContinue = false;
		//Game::getInstance().scale();
		Game::getInstance().layer = new GameLayer();
	}
}
void LoseLayer::draw() 
{
	background->draw();

	SDL_RenderPresent(Game::getRenderer());
}