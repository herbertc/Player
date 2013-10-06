#include <iostream>

#include <SDL/SDL.h>
#include <QApplication>

#include "sound.h"
#include "sounddevice.h"
#include "player.h"
#include "ui_meta.h"


using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " {wave_file.wav}\n";
		return -1;
	}
	
	char *path = argv[1];

	QApplication app(argc, argv);
	Player w;
	
	Ui_meta *uim = new Ui_meta(path);
	uim->setupUi(&w);
	uim->setLabels();
	uim->connections();

	//----------------------------------------------------
	SoundCTRL *control = new SoundCTRL();
	control->setView(uim);

	Sound *sound = new Sound;
	SoundDevice *device = new SoundDevice;
	
	device->open(sound);
	device->openWAV(path);
	device->audioConverter();
	device->setSound(sound);
	
	control->setSound(sound);

	//----------------------------------
	w.show();
	
	return app.exec();
}