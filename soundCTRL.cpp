#include "soundCTRL.h"

SoundCTRL *g_control = 0;

SoundCTRL::SoundCTRL()
{
	playing = 1;
	view = 0;
	sound = 0;

	g_control = this;
}

void
SoundCTRL::setSound(Sound *sound)
{
	this->sound = sound;
}

void
SoundCTRL::setView(Ui_meta *view)
{
	this->view = view;
	connect(view, SIGNAL(playSound()), this, SLOT(playOrPauseCTRL()));
	connect(view, SIGNAL(pauseSound()), this, SLOT(playOrPauseCTRL()));
	connect(this, SIGNAL(soundPlayed()), this->view, SLOT(playOrPause()));
	
	connect(view, SIGNAL(nextMark(uint32_t, Format*)), this, SLOT(forward(uint32_t, Format*)));
	
}

void 
SoundCTRL::playOrPauseCTRL()
{
	cout << "[Toca ou para] playing = " << playing << endl;

	if (sound->m_position == -1)
		sound->m_position = 0;
	
	playing ^= 1;
	SDL_PauseAudio(playing);
}

void 
SoundCTRL::callback(void *userdata, uint8_t *audio, int length)
{    
	memset(audio, 0, length);
	
	Sound *sound = (Sound *) userdata;

	if (sound->m_position == -1)
		return;

	if (sound->m_position >= sound->size())
	{
		cout << "-----------------------------" << endl;
		cout << "ACABOU..." << endl;

		sound->m_position = -1;

		emit g_control->soundPlayed();
		
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

/*
void 
SoundCTRL::fastForward()
{
	
}
	
void 
SoundCTRL::fastRewind()
{
	
}

void 
SoundCTRL::rewind()
{
	
}
*/

void 
SoundCTRL::forward(uint32_t timeInSeconds, Format *format)
{
	cout << "control: " << timeInSeconds << endl;
	uint32_t position = timeInSeconds * format->numChannels() * format->sampleRate() * format->bitsPerSample()/8;
	
	sound->m_position = position;
}

