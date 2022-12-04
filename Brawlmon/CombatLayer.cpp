#include "CombatLayer.h"
#include "Game.h"

#include <unordered_set>

CombatLayer::CombatLayer(Player* player, Enemy* enemy)
	: Layer(), player(player), enemy(enemy)
{
	init();
}

void CombatLayer::init()
{
	background = new Background("res/combat_background.png", 191, 302);
	Game::getInstance().scale();

	loadEnemyBrawlmon();
	loadPlayerBrawlmon();

	combatInfo = new Text(12, "Select an attack!", WIDTH * .05f, HEIGHT * .95f);

	enemyBrawlmonInfo = new Text(15, enemyBrawlmon->name, WIDTH * .09f, HEIGHT * .19f);
	playerBrawlmonInfo = new Text(15, playerBrawlmon->name, WIDTH * .6f, HEIGHT * .63f);

	playerBrawlmonLife = new Text(12, std::to_string((int)playerBrawlmon->life), WIDTH * .8f, HEIGHT * .77f);
	playerBrawlmonMaxLife = new Text(12, "/" + std::to_string((int)playerBrawlmon->maxlife), WIDTH * .85f, HEIGHT * .77f);

	enemyBrawlmonLifebar = new Lifebar(WIDTH * .41f, HEIGHT * .25f, -100, 13, SDL_Color{ 0 ,150,0,255 }, SDL_Color{ 100,100,100,255 });
	playerBrawlmonLifebar = new Lifebar(WIDTH * .92f, HEIGHT * .7f, -100, 13, SDL_Color{ 0 ,150,0,255 }, SDL_Color{ 100,100,100,255 });

	menu = new Menu(playerBrawlmon->attacks);
}

void CombatLayer::processControls()
{
	Layer::processControls();


}

void CombatLayer::update()
{
	std::unordered_set<Brawlmonster*> deleteEnemies;

	playerBrawlmonLifebar->update(playerBrawlmon->life / playerBrawlmon->maxlife);
	enemyBrawlmonLifebar->update(enemyBrawlmon->life / enemyBrawlmon->maxlife);
	playerBrawlmonLife->content = std::to_string((int)playerBrawlmon->life);

	enemyBrawlmon->update();
	playerBrawlmon->update();

	if (playerBrawlmon->life <= 0)
	{

	}

	for (auto const& eb : enemy->brawlmons)
	{
		if (eb->state != State::Alive)
		{
			deleteEnemies.emplace(eb);
		}
	}

	for (auto const& delEnemy : deleteEnemies)
	{
		enemy->brawlmons.remove(delEnemy);
		if (enemy->brawlmons.size() == 0)
		{
			enemy->defeat();
			Game::getInstance().scale();
			Game::getInstance().layer = Game::getInstance().prevLayer;
		}
		else
		{
			loadEnemyBrawlmon();
			enemyBrawlmonInfo->content = enemyBrawlmon->name;
		}
	}
	deleteEnemies.clear();
}

void CombatLayer::draw()
{
	background->draw();

	playerBrawlmon->draw();
	enemyBrawlmon->draw();

	combatInfo->draw();
	enemyBrawlmonInfo->draw();
	playerBrawlmonInfo->draw();

	playerBrawlmonLifebar->draw();
	enemyBrawlmonLifebar->draw();

	playerBrawlmonLife->draw();
	playerBrawlmonMaxLife->draw();

	menu->draw();

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
		case SDLK_w: // derecha
			menu->select(0);
			break;
		case SDLK_e: // izquierda
			menu->select(1);
			break;
		case SDLK_s: // arriba
			menu->select(2);
			break;
		case SDLK_d: // abajo
			menu->select(3);
			break;
		case SDLK_t: // abajo
			playerBrawlmon->attack(enemyBrawlmon, menu->selectedAttack);
			combatInfo->content = playerBrawlmon->name + " used " + menu->selectedAttack->name + "!";
			break;
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

void CombatLayer::loadEnemyBrawlmon()
{
	enemyBrawlmon = enemy->brawlmons.back();
	enemyBrawlmon->x = 280;
	enemyBrawlmon->y = 250;
	enemyBrawlmon->y -= enemyBrawlmon->height / 2;
	enemyBrawlmon->boundingBox.update(enemyBrawlmon->x, enemyBrawlmon->y);
}
void CombatLayer::loadPlayerBrawlmon()
{
	playerBrawlmon = player->brawlmons.front();
	playerBrawlmon->x = 100;
	playerBrawlmon->y = 415;
	playerBrawlmon->y -= playerBrawlmon->height / 2;
	playerBrawlmon->boundingBox.update(playerBrawlmon->x, playerBrawlmon->y);
}