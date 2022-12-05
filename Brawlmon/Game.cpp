#include "Game.h"
#include <SDL_ttf.h>

constexpr int FRAME_TIME = 1000 / 30;

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error SDL_Init" << SDL_GetError() << std::endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		std::cout << "Error Window y Renderer" << SDL_GetError() << std::endl;
	}
	SDL_SetWindowTitle(window, "Brawlmon");
	
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	TTF_Init();
}

void Game::loop() {
	int initTick, endTick, deltaTick;

	while (loopActive) {
		initTick = SDL_GetTicks();

		layer->processControls();
		layer->update();
		layer->draw();

		endTick = SDL_GetTicks();
		deltaTick = endTick - initTick;

		if (deltaTick < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - deltaTick);
		}
	}
}

void Game::start() {
	layer = new MenuLayer();
	loopActive = true; 
	loop();
}

void Game::scale() {
	if (scaledToMax) {
		SDL_DisplayMode PCdisplay;
		SDL_GetCurrentDisplayMode(0, &PCdisplay);
		float scaleX = 687;
		float scaleY = 483;
		
		SDL_SetWindowSize(window, scaleX, scaleY);
		
		SDL_RenderSetScale(renderer, 1.8, .8);
	}
	else { 
		scaleLower = 1;
		
		SDL_SetWindowSize(window, WIDTH, HEIGHT);
		
		SDL_RenderSetScale(renderer, 1, 1);
	}
	scaledToMax = !scaledToMax;
}