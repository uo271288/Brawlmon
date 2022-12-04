#include "CombatLayer.h"
#include "Game.h"

CombatLayer::CombatLayer(Player* player, Enemy* enemy)
	: Layer(), player(player), enemy(enemy)
{
	init();
}

void CombatLayer::init()
{
	background = new Background("res/combat_background.png", 191, 302);
	Game::getInstance().scale();

	combatInfo = new Text(15, "DEVIL ha usado placaje.", WIDTH * .05f, HEIGHT * .95f);

	enemyBrawlmonInfo = new Text(15, "DEVIL", WIDTH * .09f, HEIGHT * .19f);
	playerBrawlmonInfo = new Text(15, "DEVIL", WIDTH * .6f, HEIGHT * .63f);

	enemyBrawlmonLifebar = new Lifebar(WIDTH * .41f, HEIGHT * .25f, -100, 13, SDL_Color{ 0 ,150,0,255 }, SDL_Color{ 100,100,100,255 });
	playerBrawlmonLifebar = new Lifebar(WIDTH * .92f, HEIGHT * .7f, -100, 13, SDL_Color{ 0 ,150,0,255 }, SDL_Color{ 100,100,100,255 });

	loadEnemyBrawlmon();
	loadPlayerBrawlmon();
}

void CombatLayer::processControls()
{
	Layer::processControls();


}

void CombatLayer::update()
{
	playerBrawlmonLifebar->update(playerBrawlmon->life / playerBrawlmon->maxlife);
	enemyBrawlmonLifebar->update(enemyBrawlmon->life / enemyBrawlmon->maxlife);
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
		case SDLK_n: // derecha
			playerBrawlmon->attack(enemyBrawlmon, playerBrawlmon->attacks.at(2));
			break;
		case SDLK_m: // derecha
			playerBrawlmon->attack(enemyBrawlmon, playerBrawlmon->attacks.at(0));
			break;
		case SDLK_TAB:
			Game::getInstance().layer = new PauseLayer(this);
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
	enemyBrawlmon->x = 200;
	enemyBrawlmon->y = 100;
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