#pragma once

#include <string>
#include <SDL.h>
class Animation
{
public:
	Animation(std::string filename, int actorWidth, int actorHeight, int fileWidth,
		int fileHeight, int updateFrequency, int currentFrameY, int totalFramesX, int totalFramesY, bool loop = true);

	bool update();
	void draw(float x, float y);

	int actorWidth, actorHeight, fileWidth,
		fileHeight, frameWidth, frameHeight;
	int totalFramesX, totalFramesY, currentFrameX = 0, currentFrameY;
	int updateFrequency, updateTime = 0;
	bool loop = false;

	SDL_Texture* texture;
	SDL_Rect source;
};