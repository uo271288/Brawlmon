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
	space = new Space();
	background = new Background("res/gym_background.png", WIDTH * 0.5, HEIGHT * 0.3);

	tiles.clear();
	enemies.clear();

	loadMap("res/1.txt");
}

void GameLayer::processControls()
{
	Layer::processControls();

	player->moveX(controlMoveX);
	player->moveY(controlMoveY);

}

void GameLayer::update()
{
	std::unordered_set<Enemy*> deleteEnemies;

	space->update();
	player->update();

	calculateScroll();

	for (auto const& enemy : enemies)
	{
		enemy->update();
		if (player->hit(enemy))
		{
			enemy->defeat();
			player->stop();
			// TODO: load combat layer
		}
	}


	for (auto const& delEnemy : deleteEnemies)
	{
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

}

void GameLayer::draw()
{
	background->draw(scrollX, scrollY);

	for (auto const& tile : tiles)
	{
		tile->draw(scrollX, scrollY);
	}

	for (auto const& enemy : enemies)
	{
		enemy->draw(scrollX, scrollY);
	}

	player->draw(scrollX, scrollY);

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
		for (unsigned int column = 0; column < line.size(); column++)
		{
			float x = 14 / 2 + column * 14;
			float y = 22 + row * 22;
			loadMapObject(line[column], x, y);
			std::cout << line[column];
		}
		std::cout << std::endl;
		row++;
	}
	mapHeight = row;
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character)
	{
	case 'F':
	{
		Tile* tile = new Tile("res/fence.png", x, y, 14, 22);
		tile->y -= tile->height / 2;
		//fix the bounding box. the bottom collission must be with player feet
		tile->boundingBox.update(tile->x, tile->y);
		tiles.emplace_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'P':
	{
		player = new Player(x, y);
		player->y -= player->height;
		player->boundingBox.update(player->x, player->y);
		space->addDynamicActor(player);
		break;
	}
	case 'H':
	case 'V':
	{
		Enemy* enemy = new Enemy(character == 'H' ? "res/rival1_walking.png" : "res/rival2_walking.png", 
			x, y, character == 'H' ? State::MovingHorizontal : State::MovingVertical);
		enemy->y -= enemy->height / 2;
		enemy->boundingBox.update(enemy->x, enemy->y);
		enemies.emplace_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	}
}

void GameLayer::calculateScroll()
{
	if (player->y > HEIGHT * .1f
		|| player->y < HEIGHT * .9f)
	{

		if (player->y - scrollY < HEIGHT * .1f)
		{
			scrollY = player->y - HEIGHT * .1f;
		}
		if (player->y - scrollY > HEIGHT * .9f)
		{
			scrollY = player->y - HEIGHT * .9f;
		}
	}
}