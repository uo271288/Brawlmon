#include "Animation.h"
#include "Game.h"

Animation::Animation(std::string filename, int actorWidth, int actorHeight,
	int fileWidth, int fileHeight, int updateFrequency, int currentFrameY, int totalFramesX, int totalFramesY, bool loop)
	:actorWidth(actorWidth), actorHeight(actorHeight),
	fileWidth(fileWidth), fileHeight(fileHeight),
	updateFrequency(updateFrequency),
	currentFrameY(currentFrameY), totalFramesX(totalFramesX), totalFramesY(totalFramesY),
	frameWidth(fileWidth / totalFramesX), frameHeight(fileHeight / totalFramesY),
	loop(loop)
{
	texture = Game::getTexture(filename);
	source = { 0,currentFrameY % totalFramesY,frameWidth,frameHeight };
}

bool Animation::update() {
	updateTime++;

	if (updateTime > updateFrequency) {
		updateTime = 0;

		currentFrameX = (currentFrameX + 1) % totalFramesX;

		if (currentFrameX == 0 && !loop) {
			return true;
		}
	}
	if (loop)
	{
		source.x = currentFrameX * frameWidth;
		source.y = currentFrameY * frameHeight;
	}
	else
	{
		source.x = 0;
	}

	return false;
}

void Animation::draw(float x, float y) {
	SDL_Rect destination{ x - actorWidth / 2,y - actorHeight / 2,actorWidth,actorHeight };
	SDL_RenderCopyEx(Game::getRenderer(), texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}