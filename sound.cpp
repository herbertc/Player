#include "sound.h"


Sound::Sound()
{
	m_position = -1;
	m_buffer = 0;
	m_size = 0;
}
	
uint8_t *
Sound::buffer() const
{
	return m_buffer;
}
	
int 
Sound::size() const
{
	return m_size;
}

/*
void 
Sound::callback(void *userdata, uint8_t *audio, int length)
{    
	memset(audio, 0, length);

	Sound *sound = (Sound *) userdata;

	if (sound->m_position == -1 || sound->m_position >= sound->size())
	{
		cout << "ACABOU..." << endl;
		
		//sound->m_position = 0;
		
		return;
	}
	int nextSamplesLength;

	if (sound->m_position + length > sound->size())
		nextSamplesLength =  sound->size() - sound->m_position;
	else
		nextSamplesLength = length;

	SDL_MixAudio(audio, sound->buffer() + sound->m_position, nextSamplesLength, 
		SDL_MIX_MAXVOLUME / 2);

	sound->m_position += nextSamplesLength;
}
*/


void
Sound::setBuffer(uint8_t *buf)
{
	m_buffer = buf;
}

void
Sound::setSize(int size)
{
	m_size = size;
}

/*
void 
Sound::callback(void *userdata, uint8_t *audio, int length)
{    
	memset(audio, 0, length);

	Sound *sound = (Sound *) userdata;

	if (sound->position == -1 || sound->position >= sound->size)
		return;

	int nextSamplesLength;

	if (sound->position + length > sound->size)
		nextSamplesLength =  sound->size - sound->position;
	else
		nextSamplesLength = length;

	SDL_MixAudio(audio, sound->buffer + sound->position, nextSamplesLength, 
		SDL_MIX_MAXVOLUME / 2);

	sound->position += nextSamplesLength;
}
*/

/*ostream& 
operator<<(ostream& os, const SDL_AudioSpec& spec)
{
	os << "Frequencia: " << spec.freq << endl;
	os << "Formato: ";

	switch (spec.format) {
	case AUDIO_U8:
		os << "Amostras de 8-bits nao sinalizadas" << endl;
		break;

	case AUDIO_S8:
		os << "Amostras  de 8-bits sinalizadas" << endl;
		break;

	case AUDIO_U16:
		os << "Amostras de 16-bits nao sinalizadas (little endian)" << endl;
		break;

	case AUDIO_U16MSB:
		os << "Amostras de 16-bits nao sinalizadas e big endian" << endl;
		break;

	case AUDIO_S16:
		os << "Amostras de 16-bits sinalizadas (little endian)" << endl;
		break;

	case AUDIO_S16MSB:
		os << "Amostras de 16-bits sinalizadas e big endian" << endl;
		break;
	}

	os << "Canais: " << (int) spec.channels << endl;
	os << "Numero de amostras: " << spec.samples << endl;
	os << "Tamanho: " << spec.size << endl;
	os << "Silencio: " << spec.silence << endl;

	return os;
}*/
