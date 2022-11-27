#include "Game.h"

constexpr int FRAME_TIME = 1000 / 30;

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error SDL_Init" << SDL_GetError() << std::endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		std::cout << "Error Window y Renderer" << SDL_GetError() << std::endl;
	}
	SDL_SetWindowTitle(window, "Brawlmon");
	// Escalado de imágenes de calidad 
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	TTF_Init();
	font = TTF_OpenFont("res/brawlmon_main_font.ttf", 24);
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
	layer = new GameLayer();
	loopActive = true; // bucle activo
	loop();
}

void Game::scale() {
	if (scaledToMax) {
		SDL_DisplayMode PCdisplay;
		SDL_GetCurrentDisplayMode(0, &PCdisplay);
		float scaleX = 954;
		float scaleY = 604;
		// Cambiar dimensiones ventana
		SDL_SetWindowSize(window, scaleX, scaleY);
		// Cambiar escala del render
		SDL_RenderSetScale(renderer, 2.5, 1);
		SDL_SetWindowPosition(window, 200, 150);
	}
	else { // Escala Original
		scaleLower = 1;
		// Cambiar dimensiones ventana
		SDL_SetWindowSize(window, WIDTH, HEIGHT);
		// Cambiar escala del render
		SDL_RenderSetScale(renderer, 1, 1);
	}
	scaledToMax = !scaledToMax;
}