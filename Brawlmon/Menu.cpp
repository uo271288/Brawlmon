#include "Menu.h"
#include "Game.h"

Menu::Menu(std::vector<Attack*> attacks):attacks(attacks)
{
	attack1 = new Text(14, attacks.at(0)->name, WIDTH * .51f, HEIGHT * .97f);
	attack2 = new Text(14, attacks.at(1)->name, WIDTH * .75f, HEIGHT * .97f);
	attack3 = new Text(14, attacks.at(2)->name, WIDTH * .51f, HEIGHT * 1.1f);
	attack4 = new Text(14, attacks.at(3)->name, WIDTH * .75f, HEIGHT * 1.1f);

	attack1->color = { 150,0,150,255 };
	selectedAttack = attacks.at(0);
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

void Menu::select(int option)
{
	switch (option)
	{
	case 0:
		clearSelection();
		attack1->color = { 150,0,150,255 };
		break;
	case 1:
		clearSelection();
		attack2->color = { 150,0,150,255 };
		break;
	case 2:
		clearSelection();
		attack3->color = { 150,0,150,255 };
		break;
	case 3:
		clearSelection();
		attack4->color = { 150,0,150,255 };
		break;
	}
	selectedAttack = attacks.at(option);
}

void Menu::clearSelection()
{
	attack1->color = { 0,0,0,255 };
	attack2->color = { 0,0,0,255 };
	attack3->color = { 0,0,0,255 };
	attack4->color = { 0,0,0,255 };
}