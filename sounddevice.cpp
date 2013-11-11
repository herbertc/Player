#include "sounddevice.h"

SDL_AudioSpec 
SoundDevice::desired() const
{
	return m_desired;
}

SDL_AudioSpec 
SoundDevice::obtained() const
{
	return m_obtained;
}

SDL_AudioSpec 
SoundDevice::wavSpec() const
{
	return m_wavSpec;
}

uint32_t 
SoundDevice::wavLen() const
{
	return m_wavLen;
}

uint8_t *
SoundDevice::wavBuffer() const
{
	return m_wavBuffer;
}
	
void 
SoundDevice::open(Sound *sound)
{
	int rc = SDL_Init(SDL_INIT_AUDIO);
	
	if (rc != 0) {
		cerr << "Erro na inicializacao do modulo de audio: " <<
			SDL_GetError() << endl;
		return;
	}
	
	m_desired.freq = 44100;
	m_desired.format = AUDIO_S16;
	m_desired.channels = 2;
	m_desired.samples = 4096;
	m_desired.callback = SoundCTRL::callback;
	m_desired.userdata = (void *) sound;
	
	rc = SDL_OpenAudio(&m_desired, &m_obtained);

	if (rc != 0)
	{
		cerr << "Erro na abertura do dispositivo de audio: " <<
			SDL_GetError() << endl;
		SDL_Quit();
		return;
	}
	
}

void
SoundDevice::openWAV(char *path)
{
	if (SDL_LoadWAV(path, &m_wavSpec, &m_wavBuffer, &m_wavLen) == NULL)
	{
		cout << "Falha! " << SDL_GetError() << endl;
		SDL_CloseAudio();
		SDL_Quit();
		return;
	}
	
	//cout << "SDL_LoadWAV: Ok!" << endl;
}

void 
SoundDevice::audioConverter()
{
	int rc = SDL_BuildAudioCVT(&m_cvt, m_wavSpec.format, m_wavSpec.channels, m_wavSpec.freq,
			m_obtained.format, m_obtained.channels, m_obtained.freq);

	if (rc != 0)
	{
		cout << "audioConverter(): Falha! " << SDL_GetError() << endl;
		SDL_FreeWAV(m_wavBuffer);
		SDL_Quit();

		return;
	}
	
	m_cvt.len = m_wavLen;
	uint8_t *wavNewBuf = (uint8_t *) malloc(m_cvt.len * m_cvt.len_mult);

	if (wavNewBuf == NULL)
	{
		cerr << "audioConverter(): Sem memoria para um novo buffer!" << endl;
		SDL_FreeWAV(m_wavBuffer);
		SDL_CloseAudio();
		SDL_Quit();

		return;
	}
	
	memcpy(wavNewBuf, m_wavBuffer, m_wavLen);
	m_cvt.buf = wavNewBuf;
	
	rc = SDL_ConvertAudio(&m_cvt);

	if (rc != 0)
	{
		cerr << "audioConverter(): Erro na conversao do audio!" << endl;
		SDL_FreeWAV(m_wavBuffer);
		free(wavNewBuf);
		SDL_CloseAudio();
		SDL_Quit();

		return;
	}
	
	SDL_FreeWAV(m_wavBuffer);

	//cout << "audioConverter(): Ok!" << endl;
}

void 
SoundDevice::setSound(Sound *sound)
{
	SDL_LockAudio();

	sound->m_position = 0;
	sound->setBuffer(m_cvt.buf);
	sound->setSize(m_cvt.len * m_cvt.len_mult);
	
	SDL_UnlockAudio();
	
	//cout << "setSound: Ok!" << endl;
}












