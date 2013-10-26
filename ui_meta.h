#ifndef UI_META_H
#define UI_META_H

#include "ui_player.h"

#include "generic.h"
#include "wave.h"
#include "meta.h"
#include "lgmk.h"


class Ui_meta : public QObject, public Ui_Player
{
	Q_OBJECT

public slots:
	void playOrPause();
	void resetMarkLabels();
	
	//void reset();

	//void fastForward();
	//void fastRewind();
	void rewind();
	void forward();

signals:
	void playSound();
	void pauseSound();
	
	void nextMark(uint32_t timeInSeconds, Format *format);
	void prevMark(uint32_t timeInSeconds, Format *format);
		
	void remove();

public:
	Ui_meta(const char *path);
	void setMetaLabels();
	void setMarksLabels();
	void connections();
	bool playing;
	
	Wave *wave;
	Meta *meta;
	Lgmk *lgmk;
	//WaveData *data;
	Format *format;
	
	QIcon icon;
private:
	int markIndex;
	int subMarkIndex;
};


#endif
