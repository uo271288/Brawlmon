#include "Lifebar.h"
#include "Game.h"

Lifebar::Lifebar(int x, int y, int width, int height, SDL_Color fGColor, SDL_Color bGColor)
	:x(x),y(y),width(width),height(height), fGColor(fGColor), bGColor(bGColor)
{
	
}

void Lifebar::draw() 
{
	percent = percent > 1.f ? 1.f : percent < 0.f ? 0.f : percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(Game::getRenderer(), &old.r, &old.g, &old.g, &old.a);
	SDL_Rect bgrect = { x, y, width, height };
	SDL_SetRenderDrawColor(Game::getRenderer(), bGColor.r, bGColor.g, bGColor.b, bGColor.a);
	SDL_RenderFillRect(Game::getRenderer(), &bgrect);
	SDL_SetRenderDrawColor(Game::getRenderer(), fGColor.r, fGColor.g, fGColor.b, fGColor.a);
	int pw = width * percent;
	int px = x + (width - pw);
	SDL_Rect fgrect = { px, y, pw, height };
	SDL_RenderFillRect(Game::getRenderer(), &fgrect);
	SDL_SetRenderDrawColor(Game::getRenderer(), old.r, old.g, old.b, old.a);
}