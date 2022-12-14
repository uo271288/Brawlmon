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

	audioBackground = Audio::createAudio("res/audio_gym.mp3", true);
	audioBackground->play();
	isPlaying = true;

 	pad = new Pad(WIDTH * 0.7, HEIGHT * 0.7);

	tiles.clear();
	enemies.clear();

	loadMap("res/1.txt");
	loadAttacks("res/attacks.txt");
	player->brawlmons = loadBrawlmonsters("res/playerBrawlmons.txt");
	loadEnemyBrawlmonsters();
	leader->brawlmons = loadBrawlmonsters("res/leaderBrawlmons.txt");

	Game::getInstance().scale();
}

void GameLayer::processControls()
{
	Layer::processControls();

	player->moveX(controlMoveX);
	player->moveY(controlMoveY);

}

void GameLayer::update()
{

	space->update();
	player->update();

	if (!isPlaying)
	{
		audioBackground->play();
		isPlaying = true;
	}

	calculateScroll();
	
	leader->update();
	for (auto const& enemy : enemies)
	{
		enemy->update();
		if (player->hit(enemy) && enemy->state != State::Defeated)
		{
			controlMoveX = 0;
			controlMoveY = 0;
			Game::getInstance().prevLayer = this;
			isPlaying = false;
			Game::getInstance().layer = new CombatLayer(player, enemy);
		}

		if (enemy->state == State::Defeated)
		{
			space->removeDynamicActor(enemy);
			space->addStaticActor(enemy);
		}
	}

	if (leader->state == State::Defeated)
	{
		Game::getInstance().scale();
		Game::getInstance().layer = new WinLayer();
	}
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
	leader->draw(0, 0);

	if (inputType == InputType::Mouse) {
		pad->draw();
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

	float motionX = event.motion.x;
	float motionY = event.motion.y;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (pad->containsPoint(motionX, motionY))
		{
			pad->clicked = true;
			controlMoveX = pad->getOrientationX(motionX);
			controlMoveY = pad->getOrientationY(motionY);
		}
	}

	if (event.type == SDL_MOUSEMOTION)
	{
		if (pad->clicked && pad->containsPoint(motionX, motionY))
		{
			controlMoveX = pad->containsPoint(motionX, motionY);

			if (controlMoveX > -20 && controlMoveX < 20)
			{
				controlMoveX = 0;
			}
		}
		else
		{
			pad->clicked = false;
			controlMoveX = 0;
		}

		if (!pad->containsPoint(motionX, motionY))
		{
			controlMoveY = 0;
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (pad->containsPoint(motionX, motionY))
		{
			pad->clicked = false;
			controlMoveX = 0;
		}

		if (pad->containsPoint(motionX, motionY))
		{
			controlMoveY = 0;
		}
	}
}

void GameLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
}

void GameLayer::loadMap(std::string name)
{
	std::ifstream file(name);
	int row = -1;
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

void GameLayer::loadAttacks(std::string name)
{
	std::ifstream file(name);
	int row = 0;
	std::string line;

	while (std::getline(file, line))
	{
		std::string delimiter = ";";
		std::vector<std::string> lista;
		size_t pos = 0;
		std::string token;
		Category category = Category::Physical;
		while ((pos = line.find(delimiter)) != std::string::npos)
		{
			token = line.substr(0, pos);
			lista.push_back(token);
			line.erase(0, pos + delimiter.length());
		}
		switch (line.c_str()[0])
		{
		case 'S':
			category = Category::Status;
			break;
		case 'P':
			category = Category::Physical;
			break;
		}
		attacks.insert({ lista.at(0), new Attack(lista.at(0), std::stof(lista.at(1)), category) });
	}
}

std::list<Brawlmonster*> GameLayer::loadBrawlmonsters(std::string name)
{
	std::ifstream file(name);
	int row = 0;
	std::string line;
	std::list<Brawlmonster*> brawlmons;

	while (std::getline(file, line))
	{
		std::string delimiter = ";";
		std::vector<std::string> lista;
		std::vector<Attack*> attacksList;
		size_t pos = 0;
		std::string token;

		while ((pos = line.find(delimiter)) != std::string::npos)
		{
			token = line.substr(0, pos);
			lista.push_back(token);
			line.erase(0, pos + delimiter.length());
		}
		delimiter = ",";
		pos = 0;
		while ((pos = line.find(delimiter)) != std::string::npos)
		{
			token = line.substr(0, pos);
			attacksList.push_back(attacks.at(token));
			line.erase(0, pos + delimiter.length());
		}
		attacksList.push_back(attacks.at(line));
		brawlmons.push_back(new Brawlmonster("res/" + lista.at(0) + ".png", lista.at(1),
			0, 0, std::stof(lista.at(2)), std::stof(lista.at(3)), attacksList));
	}

	return brawlmons;
}

void GameLayer::loadEnemyBrawlmonsters()
{
	for (auto const& enemy : enemies)
	{
		enemy->brawlmons = loadBrawlmonsters("res/enemyBrawlmons.txt");
	}
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
	case 'L':
	{
		leader = new Enemy("res/leader.png", x, y, State::Stay);
		leader->y -= leader->height / 2;
		leader->boundingBox.update(leader->x, leader->y);
		enemies.emplace_back(leader);
		space->addDynamicActor(leader);
		break;
	}
	}
}

void GameLayer::calculateScroll()
{
	if (player->y > HEIGHT * .2f
		|| player->y < HEIGHT * .8f)
	{

		if (player->y - scrollY < HEIGHT * .2f)
		{
			scrollY = player->y - HEIGHT * .2f;
		}
		if (player->y - scrollY > HEIGHT * .8f)
		{
			scrollY = player->y - HEIGHT * .8f;
		}
	}
}