#ifndef SOUND_H
#define SOUND_H

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

using namespace std;

/*typedef struct Sound {
	int position;
	Uint8 *buffer;
	int size;
} Sound;

extern void callback(void *userdata, Uint8 *stream, int len);

extern ostream& operator<<(ostream& os, const SDL_AudioSpec& spec);*/

class Sound
{
public:
	Sound();
	//~Sound();

	uint8_t *buffer() const;
	int size() const;
	
	void setBuffer(uint8_t *buf);
	void setSize(int size);
	
	int m_position;
	
	//static void callback(void *userdata, uint8_t *stream, int len);

private:
	
	uint8_t *m_buffer;
	int m_size;
};

#endif