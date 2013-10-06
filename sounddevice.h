#ifndef SOUNDDEVICE_H
#define SOUNDDEVICE_H

#include <SDL/SDL.h>
#include "sound.h"
#include "soundCTRL.h"

using namespace std;

class SoundDevice
{
public:
	SDL_AudioSpec desired() const;
	SDL_AudioSpec obtained() const;
	
	SDL_AudioSpec wavSpec() const;
	uint32_t wavLen() const;
	uint8_t *wavBuffer() const;
	
	void open(Sound *sound);
	void openWAV(char *path);
	void audioConverter();
	void setSound(Sound *sound);
private:
	SDL_AudioSpec m_desired;
	SDL_AudioSpec m_obtained;
	
	SDL_AudioSpec m_wavSpec;
	uint32_t m_wavLen;
	uint8_t *m_wavBuffer;
	
	SDL_AudioCVT m_cvt;
};

#endif