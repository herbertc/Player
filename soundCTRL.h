#ifndef SOUNDCTRL_H
#define SOUNDCTRL_H

#include <QObject>
#include <QIcon>
#include <SDL/SDL.h>
#include <iostream>

#include "sound.h"
#include "ui_meta.h"
#include "lgmk.h"


using namespace std;

class SoundCTRL : public QObject
{
	 Q_OBJECT
	 
public slots:
	void playOrPauseCTRL();
	void forward(uint32_t timeInSeconds, Format *format);
	void rewind(uint32_t timeInSeconds, Format *format);
		
signals:
	void soundPlayed();

public:
	SoundCTRL();
	
	void setView(Ui_meta *view);
	void setSound(Sound *sound);

	static void callback(void *userdata, uint8_t *stream, int len);
	//void fastForward();
	//void fastRewind();
	
public:
	int playing;
	Ui_meta *view;
	Sound *sound;
	
};


#endif
