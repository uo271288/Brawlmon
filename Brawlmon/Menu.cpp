#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
	attack1 = new Text(14, "Waterblast", WIDTH * .51f, HEIGHT * .97f);
	attack2 = new Text(14, "Roar", WIDTH * .75f, HEIGHT * .97f);
	attack3 = new Text(14, "Scare", WIDTH * .51f, HEIGHT * 1.1f);
	attack4 = new Text(14, "Smash", WIDTH * .75f, HEIGHT * 1.1f);
}

void Menu::draw() 
{
	SDL_Rect bgrect = { 190,435,180,150 };
	SDL_SetRenderDrawColor(Game::getRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(Game::getRenderer(), &bgrect);

	attack1->draw();
	attack2->draw();
	attack3->draw();
	attack4->draw();
}