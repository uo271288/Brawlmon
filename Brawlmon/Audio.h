#pragma once
#include <iostream> 
#include <string> 
#include <map>
#include <SDL.h>
#include <SDL_mixer.h> 
class Audio 
{
	Audio(std::string filename, bool loop);
public:
	static Audio* createAudio(std::string filename, bool loop)
	{ 
		static std::map<std::string, Audio*> instancedAudios;
		if (instancedAudios.find(filename) == instancedAudios.end())
		{
			std::cout << "Audio no cacheado lo creo " + filename << std::endl;
			instancedAudios[filename] = new Audio(filename, loop);
		}
		return instancedAudios[filename];
	} 
	~Audio();
	void play(); 
	bool loop; 
	Mix_Music* mix;
	SDL_AudioSpec wavSpec;
	Uint32 wavLength; 
	Uint8* wavBuffer; 
	SDL_AudioDeviceID deviceId;
};