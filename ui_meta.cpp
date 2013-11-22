#include "ui_meta.h"

Ui_meta::Ui_meta(const char *path)
{
	playing = true;
	
	markIndex = 0;
	subMarkIndex = 0;
	level = 1;
	
	duration = 0;

	wave = Wave::load(path);
	
	vector<Chunk *> subchunks = wave->subchunks();
	
	for(vector<Chunk *>::iterator it = subchunks.begin(); it != subchunks.end(); it++)
	{
		lgmk = dynamic_cast<Lgmk *>(*it);
		
		if(lgmk != 0)
			break;
	}
	
	for(vector<Chunk *>::iterator it = subchunks.begin(); it != subchunks.end(); it++)
	{
		Generic *data = dynamic_cast<Generic *>(*it);
		
		if(data != 0 && data->id() == "data")
		{
			duration = data->size();
			break;
		}
			
	}
	
	for(vector<Chunk *>::iterator it = subchunks.begin(); it != subchunks.end(); it++)
	{
		format = dynamic_cast<Format *>(*it);
		
		if(format != 0)
			break;
	}
	
	duration /= (format->sampleRate() * format->numChannels());
	duration /= (format->bitsPerSample()/8);
	
	if(lgmk == 0)
	{		
		lgmk = new Lgmk;
		
		lgmk->add_mark(0);
		lgmk->add_markName("NONE");
		
		lgmk->add_mark(duration);
		lgmk->add_markName("NONE");
		
		lgmk->add_subMark(0);
		lgmk->add_subMarkName("NONE");
		
		lgmk->add_subMark(duration);
		lgmk->add_subMarkName("NONE");
	}
	
	m_marks = lgmk->marks();
	m_marksNames = lgmk->marksNames();
	
	m_subMarks = lgmk->subMarks();
	m_subMarksNames = lgmk->subMarksNames();
}

void 
Ui_meta::setMetaLabels()
{
	
	vector<Chunk *> subchunks = wave->subchunks();
	
	for(vector<Chunk *>::iterator it = subchunks.begin(); it != subchunks.end(); it++)
	{
		meta = dynamic_cast<Meta *>(*it);
		
		if(meta != 0)
			break;
	}
	
	if(meta == 0)
	{
		meta = new Meta;
	}
	
	QString title = QString::fromStdString(meta->title());
	QString author = QString::fromStdString(meta->author());
	QString language = QString::fromStdString(meta->language());
	QString publisher = QString::fromStdString(meta->publisher());
	QString year = QString::fromStdString(meta->year());
	QString address = QString::fromStdString(meta->address());
	QString pages = QString::fromStdString(meta->pages());

	titleLabel->setText(title);
	authorLabel->setText(author);
	languageLabel->setText(language);
	publisherLabel->setText(publisher);
	yearLabel->setText(year);
	addressLabel->setText(address);
	pagesLabel->setText(pages);
}

void 
Ui_meta::setMarksLabels()
{
	QString firstMark = QString::fromStdString(m_marksNames[0]);
	markLabel->setText(firstMark);
	markLabel->setAlignment(Qt::AlignCenter);
	
	QString firstSubMark  = QString::fromStdString(m_subMarksNames[0]);
	subMarkLabel->setText(firstSubMark);
	subMarkLabel->setAlignment(Qt::AlignCenter);
	
	QString level = QString::fromStdString("Level 1");
	levelLabel->setText(level);
	levelLabel->setAlignment(Qt::AlignCenter);
}

void 
Ui_meta::initLCDDisplay()
{
	lcdNumber->setNumDigits(7);
	lcdNumber->setPalette(Qt::black);
	lcdNumber->display(QString::fromStdString("0.00:00"));	
}

void 
Ui_meta::initSlider()
{
	songSlider->setRange(0, duration);
}

void
Ui_meta::connections()
{
	connect(playOrPauseButton, SIGNAL(clicked()), this, SLOT(playOrPause()));
	
	connect(forwardButton,SIGNAL(clicked()), this, SLOT(next()));
	connect(rewindButton, SIGNAL(clicked()), this, SLOT(prev()));
	
	connect(upLevelButton, SIGNAL(clicked()), this, SLOT(levelUp()));
	connect(downLevelButton, SIGNAL(clicked()), this, SLOT(levelDown()));
	
	connect(fastforwardButton, SIGNAL(pressed()), this, SLOT(fastForward()));
	
	connect(fastrewindButton, SIGNAL(pressed()) , this, SLOT(fastRewind()));
	
	connect(songSlider, SIGNAL(valueChanged(int)) , this, SLOT(updateClock(int)));
	connect(songSlider, SIGNAL(valueChanged(int)) , this, SLOT(change_song_position(int)));
}

void
Ui_meta::playOrPause()
{
   	if(playing)
	{
		icon.addFile(QString::fromUtf8(":/images/pause.png"), QSize(), QIcon::Normal, QIcon::Off);

		emit pauseSound();
	}
	else
	{
		icon.addFile(QString::fromUtf8(":/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);

		emit playSound();
	}

	playOrPauseButton->setIcon(icon);
	playing = !playing; 
}

void 
Ui_meta::resetMarkLabels()
{
	markIndex = 0;
	subMarkIndex = 0;
	
	QString firstMark = QString::fromStdString(m_marksNames[0]);
	markLabel->setText(firstMark);
	markLabel->setAlignment(Qt::AlignCenter);
	
	QString firstSubMark  = QString::fromStdString(m_subMarksNames[0]);
	
	subMarkLabel->setText(firstSubMark);
	subMarkLabel->setAlignment(Qt::AlignCenter);
}

void 
Ui_meta::resetClockAndSlider()
{
	songSlider->setValue(0);
	lcdNumber->setPalette(Qt::black);
	lcdNumber->display(QString::fromStdString("0.00:00"));
}

void 
Ui_meta::levelUp()
{
	level = 1;
	
	QString nivelLabel = QString::fromStdString("Level 1");
	levelLabel->setText(nivelLabel);
}

void 
Ui_meta::levelDown()
{
	level = 2;
	
	QString nivelLabel = QString::fromStdString("Level 2");
	levelLabel->setText(nivelLabel);
	
	//cout << "NIVEL "<< level << endl;
}


void
Ui_meta::fastForward()
{
	//cout << "FAST FORWARD" << endl;
		
	emit forwardTime(format);
}


void
Ui_meta::fastRewind()
{
	//cout << "FAST REWIND" << endl;
	
	emit rewindTime(format);
}

void
Ui_meta::next()
{
	//cout << "NIVEL "<< level << endl;
	if(level == 1)
	{
		forward();
	}else if(level == 2)
	{
		forwardSubMark();
	}
	
	synchronizeMarks();
}

void
Ui_meta::prev()
{
	//cout << "NIVEL "<< level << endl;
	if(level == 1)
	{
		rewind();
	}else if(level == 2)
	{
		rewindSubMark();
	}
		
	synchronizeMarks();
}

void
Ui_meta::forward()
{
	markIndex++;
	//cout << "(forward) markIndex: " << markIndex <<endl;
	
	if(markIndex >= (int) m_marks.size())
	{
		resetMarkLabels();
		
		emit nextMark(duration, format);
		
	}else
	{
		emit nextMark(m_marks[markIndex], format);
	}
}

void
Ui_meta::rewind()
{
	markIndex--;
	//cout << "(rewind) markIndex: " << markIndex <<endl;
	
	QString mark;
	
	if(markIndex < 0)
	{
		markIndex = 0;
		subMarkIndex = 0;
		
		emit prevMark(0, format);
	}else
	{
		emit prevMark(m_marks[markIndex], format);
	}
}

void
Ui_meta::forwardSubMark()
{
	subMarkIndex++;
	//cout << "(forward SubMark) subMarkIndex: " << subMarkIndex <<endl;
	
	if(subMarkIndex >= (int) m_subMarks.size())
	{
		resetMarkLabels();

		emit nextMark(duration, format);
		
	}else
	{
		emit nextMark(m_subMarks[subMarkIndex], format);
	}
}

void
Ui_meta::rewindSubMark()
{
	subMarkIndex--;
	//cout << "(rewind SubMark) subMarkIndex: " << subMarkIndex <<endl;
	
	QString subMark;
	
	if(subMarkIndex < 0)
	{
		markIndex = 0;
		subMarkIndex = 0;
	    
		emit prevMark(0, format);
		
	}else
	{
		emit prevMark(m_subMarks[subMarkIndex], format);
	}
}


void
Ui_meta::synchronizeMarks()
{
	uint32_t position;
	QString mark;
	QString subMark;
	
	if(level == 1)
	{
		// << "SINCRONIZACÃO NIVEL 1!!!!" << endl;
		
		position = m_marks[markIndex];
		
		for(uint32_t i = 0; i < m_subMarks.size(); i++)
		{
			if(position == 0)
			{
				subMarkIndex = 0;
				break;
			}else if(m_subMarks[i] == position)
			{
				subMarkIndex = i;
		
				break;
			}else if(m_subMarks[i] > position)
			{
				subMarkIndex = i - 1;
				break;
			}
		}
		
		//cout << "\tmarkIndex: " << markIndex << endl;
		//cout << "\tsubMarkIndex: " << subMarkIndex << endl;
				
		//cout << "\tmarks: " << m_marks[markIndex] << endl;
		//cout << "\tsubMarks: " << m_subMarks[subMarkIndex] << endl;
		
		mark  = QString::fromStdString(m_marksNames[markIndex]);
		subMark = QString::fromStdString(m_subMarksNames[subMarkIndex]);
		
		markLabel->setText(mark);
		subMarkLabel->setText(subMark);
		
	}else if(level == 2)
	{
		//cout << "SINCRONIZACÃO NIVEL 2!!!!" << endl;
		
		position = m_subMarks[subMarkIndex];
		
		for(uint32_t i = 0; i < m_marks.size(); i++)
		{
			if(position == 0)
			{
				markIndex = 0;
				break;
				
			}else if(m_marks[i] > position)
			{
				markIndex = i - 1;
				
		
				break;
			}else if(m_marks[i] == position )
			{
				markIndex = i;
				break;
			}
		}
		
		//cout << "\tmarkIndex: " << markIndex << endl;
		//cout << "\tsubMarkIndex: " << subMarkIndex << endl;
		
		//cout << "\tmarks: " << m_marks[markIndex] << endl;
		////cout << "\tsubMarks: " << m_subMarks[subMarkIndex] << endl;
		
		mark  = QString::fromStdString(m_marksNames[markIndex]);
		subMark = QString::fromStdString(m_subMarksNames[subMarkIndex]);
		
		markLabel->setText(mark);
		subMarkLabel->setText(subMark);
	}
}

int 
Ui_meta::MarkIndex() const
{
	return markIndex;
}
	
int 
Ui_meta::SubMarkIndex() const
{
	return subMarkIndex;
}
	
void 
Ui_meta::setMarkIndex(int newMarkIndex)
{
	if(markIndex != newMarkIndex)
		markIndex = newMarkIndex;
}
	
void 
Ui_meta::setSubMarkIndex(int newSubMarkIndex)
{
	if(subMarkIndex != newSubMarkIndex)
		subMarkIndex = newSubMarkIndex;
}
	
Lgmk *
Ui_meta::getLgmk() const
{
	return lgmk;
}

Format *
Ui_meta::getFormat() const
{
	return format;
}

vector<uint32_t> 
Ui_meta::marks() const
{
	return m_marks;
}

vector<uint32_t> 
Ui_meta::subMarks() const
{
	return m_subMarks;
}

void 
Ui_meta::changeMarksLabels()
{	
	QString mark;
	QString subMark;
	
	mark  = QString::fromStdString(m_marksNames[markIndex]);
	subMark = QString::fromStdString(m_subMarksNames[subMarkIndex]);
	
	markLabel->setText(mark);
	subMarkLabel->setText(subMark);	
}

void 
Ui_meta::updateClock(int time)
{
	int hours = time/3600;
	int minutes = time/60 - 60*hours;
	int seconds = time - 60*minutes - 3600*hours;
	
	string_stream << hours + '\0' << ".";
	
	if(minutes < 10)
	{
		string_stream << "0" << minutes + '\0' << ":";
	} else
	{
		string_stream << minutes + '\0' << ":";
	}
	
	if(seconds < 10)
	{
		string_stream << "0" << seconds + '\0';
	} else
	{
		string_stream << seconds + '\0';
	}
		
	lcdNumber->display(QString::fromStdString(string_stream.str()));
	songSlider->setValue(time);
}


void 
Ui_meta::change_song_position(int time)
{
	//cout << "ANDEI pelo slider"<< endl;
	emit update_m_position((uint32_t) time, format);
}
