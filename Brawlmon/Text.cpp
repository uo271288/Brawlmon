#include "Text.h"
#include "Game.h"

#include <SDL.h>



Text::Text(int size, std::string content, float x, float y)
	:content(content), x(x), y(y), font(TTF_OpenFont("res/brawlmon_main_font.ttf", size))
{
	
}

void Text::draw()
{
	SDL_Color color{ 0,0,0,255 };

	SDL_Surface* surface = TTF_RenderText_Blended(font, content.c_str(), color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);

	SDL_Rect rect
	{
		x,
		y,
		surface->w/1.8,
		surface->h*1.2
	};

	SDL_FreeSurface(surface);
	SDL_RenderCopy(Game::getRenderer(), texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}