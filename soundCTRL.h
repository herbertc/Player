#ifndef SOUNDCTRL_H
#define SOUNDCTRL_H

#include <QObject>
#include <QIcon>
#include <SDL/SDL.h>
#include <iostream>

#include "sound.h"
#include "ui_meta.h"


using namespace std;

class SoundCTRL : public QObject
{
	 Q_OBJECT
	 
public slots:
	void tocaOUpara();

signals:
	void soundPlayed();

public:
	SoundCTRL();
	
	void setView(Ui_meta *view);
	void setSound(Sound *sound);

	static void callback(void *userdata, uint8_t *stream, int len);
	//void fastForward();
	//void fastRewind();
	//void rewind();
	//void forward();

	
public:
	int playing;
	Ui_meta *view;
	Sound *sound;
};


#endif
