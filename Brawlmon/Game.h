#pragma once

#include <iostream>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>

#include "Layer.h"
#include "MenuLayer.h"

#define HEIGHT 480
#define WIDTH 380

class Game
{
public:
	Game();

	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}

	static SDL_Renderer* getRenderer() 
	{
		return getInstance().renderer;
	}

	static SDL_Texture* getTexture(std::string filename) 
	{
		static std::unordered_map<std::string, SDL_Texture*> textures;

		auto entry = textures.find(filename);
		if (entry == textures.end()) 
		{
			SDL_Surface* surface = IMG_Load(filename.c_str());
			SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
			SDL_FreeSurface(surface);
			textures[filename] = texture;
		}

		return textures[filename];
	}

	void scale();
	bool scaledToMax = true;
	float scaleLower = 1.f;

	void loop();

	void start();

	bool loopActive = true;
	Layer* layer;
	Layer* prevLayer;

	SDL_Window* window;
	SDL_Renderer* renderer;
};