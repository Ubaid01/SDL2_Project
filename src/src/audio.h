#pragma once

#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>

class Audio
{
public:
	Audio();
	void load(const char* filename);
	void play();
	~Audio();
private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceID;
};

#endif //AUDIO_H