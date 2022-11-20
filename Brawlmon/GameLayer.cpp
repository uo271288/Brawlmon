#include <unordered_set>
#include <fstream>

#include "GameLayer.h"
#include "Game.h"

GameLayer::GameLayer()
	: Layer()
{
	init();
}

void GameLayer::init()
{
	background = new Background("res/gym_background.png", WIDTH * 0.5, HEIGHT * 0.3);

	tiles.clear();

	loadMap("res/1.txt");
}

void GameLayer::processControls()
{
	Layer::processControls();
}

void GameLayer::update()
{
	calculateScroll();
}

void GameLayer::draw()
{
	background->draw();

	for (auto const& tile : tiles)
	{
		tile->draw(scrollX, scrollY);
	}

	SDL_RenderPresent(Game::getRenderer());
}

void GameLayer::keysToControls(SDL_Event event)
{
	Layer::keysToControls(event);

	if (event.type == SDL_KEYDOWN)
	{
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code)
		{
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		case SDLK_TAB:
			Game::getInstance().layer = new PauseLayer(this);
			break;
		}
	}
	if (event.type == SDL_KEYUP)
	{
		int code = event.key.keysym.sym;
		// Levantada
		switch (code)
		{
		case SDLK_d: // derecha
			if (controlMoveX == 1)
			{
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1)
			{
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1)
			{
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1)
			{
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}
}

void GameLayer::mouseToControls(SDL_Event event)
{
	Layer::mouseToControls(event);

	float motionX = event.motion.x / Game::getInstance().scaleLower;
	float motionY = event.motion.y / Game::getInstance().scaleLower;
}

void GameLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
}

void GameLayer::loadMap(std::string name)
{
	std::ifstream file(name);
	int row = 0;
	std::string line;

	while (std::getline(file, line))
	{
		mapWidth = line.size();
		for (int column = 0; column < line.size(); column++)
		{
			int x = 14 / 2 + column * 14;
			int y = 22 + row * 22;
			loadMapObject(line[column], x, y);
			std::cout << line[column];
		}
		std::cout << std::endl;
		row++;
	}
	mapHeight = row;
}

void GameLayer::loadMapObject(char character, int x, int y)
{
	switch (character)
	{
	case 'F':
	{
		Tile* tile = new Tile("res/fence.png", x, y, 14, 22);
		tile->y -= tile->height / 2;
		tile->boundingBox.update(tile->x, tile->y);
		tiles.emplace_back(tile);
		break;
	}
	}
}

void GameLayer::calculateScroll()
{

}