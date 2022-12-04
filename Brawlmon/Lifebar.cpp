#include "Lifebar.h"
#include "Game.h"

Lifebar::Lifebar(int x, int y, int width, int height, SDL_Color fGColor, SDL_Color bGColor)
	:x(x), y(y), width(width), height(height), fGColor(fGColor), bGColor(bGColor)
{

}

void Lifebar::update(float percent)
{
	this->percent = percent;
	fGColor = percent > .5 ? fGColor : SDL_Color{ 255,150,0,255 };
	fGColor = percent > .25 ? fGColor : SDL_Color{ 255,0,0,255 };
}

void Lifebar::draw()
{
	percent = percent > 1.f ? 1.f : percent;
	percent = percent < 0.f ? 0.f : percent;

	SDL_Rect bgrect = { x, y, width, height };
	SDL_SetRenderDrawColor(Game::getRenderer(), bGColor.r, bGColor.g, bGColor.b, bGColor.a);
	SDL_RenderFillRect(Game::getRenderer(), &bgrect);

	int pw = width * percent;
	int px = x + (width - pw);
	SDL_Rect fgrect = { px, y, pw, height };
	SDL_SetRenderDrawColor(Game::getRenderer(), fGColor.r, fGColor.g, fGColor.b, fGColor.a);
	SDL_RenderFillRect(Game::getRenderer(), &fgrect);
}