#ifndef UI_META_H
#define UI_META_H

#include <sstream>

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
	void resetClockAndSlider();

	void fastForward();
	void fastRewind();
	
	void next();
	void prev();
	
	void levelUp();
	void levelDown();
	
	void changeMarksLabels();
	
	void updateClock(int time);
	void change_song_position(int time);

signals:
	void playSound();
	void pauseSound();
	
	void nextMark(uint32_t timeInSeconds, Format *format);
	void prevMark(uint32_t timeInSeconds, Format *format);
	
	void forwardTime(Format *format);
	void rewindTime(Format *format);
	
	void remove();
	
	void update_m_position(uint32_t time, Format* format);

public:
	Ui_meta(const char *path);
	void setMetaLabels();
	void setMarksLabels();
	void initLCDDisplay();
	void initSlider();
	void connections();
	bool playing;
	
	void rewind();
	void forward();
	
	void forwardSubMark();
	void rewindSubMark();
	
	void synchronizeMarks();
	
	int MarkIndex() const;
	int SubMarkIndex() const;
	
	void setMarkIndex(int newMarkIndex);
	void setSubMarkIndex(int newSubMarkIndex);
	
	Lgmk *getLgmk() const;
	
	Format *getFormat() const;
	
	vector<uint32_t> marks() const;
	vector<uint32_t> subMarks() const;
private:
	int markIndex;
	int subMarkIndex;
	
	vector<uint32_t> m_marks;
	vector<string> m_marksNames;
	
	vector<uint32_t> m_subMarks;
	vector<string> m_subMarksNames;
	int level;
	
	Wave *wave;
	Meta *meta;
	Lgmk *lgmk;
	uint32_t duration;
	Format *format;
	
	QIcon icon;
	stringstream string_stream;
};


#endif
