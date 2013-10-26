#include "ui_meta.h"

Ui_meta::Ui_meta(const char *path)
{
	playing = true;
	
	markIndex = -1;
	subMarkIndex = -1;
	
	level = 1;
	
	wave = Wave::load(path);
	
	cout << wave <<endl;
	
	vector<Chunk *> subchunks = wave->subchunks();
	
	for(vector<Chunk *>::iterator it = subchunks.begin(); it != subchunks.end(); it++)
	{
		lgmk = dynamic_cast<Lgmk *>(*it);
		
		if(lgmk != 0)
			break;
	}
	
	/*for(vector<Chunk *>::iterator it = subchunks.begin(); it != subchunks.end(); it++)
	{
		data = dynamic_cast<WaveData *>(*it);
		
		if(data != 0)
			break;
	}*/
	
	
	for(vector<Chunk *>::iterator it = subchunks.begin(); it != subchunks.end(); it++)
	{
		format = dynamic_cast<Format *>(*it);
		
		if(format != 0)
			break;
	}	
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
		return;
	
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
	QString firstMark = QString::fromStdString(lgmk->marksNames()[0]);
	markLabel->setText(firstMark);
	markLabel->setAlignment(Qt::AlignCenter);
	
	QString firstSubMark  = QString::fromStdString(lgmk->subMarksNames()[0]);
	
	subMarkLabel->setText(firstSubMark);
	subMarkLabel->setAlignment(Qt::AlignCenter);
}

void
Ui_meta::connections()
{
	connect(playOrPauseButton, SIGNAL(clicked()), this, SLOT(playOrPause()));
	
	connect(forwardButton,SIGNAL(clicked()), this, SLOT(next()));
	connect(rewindButton, SIGNAL(clicked()), this, SLOT(prev()));
	
	connect(upLevelButton, SIGNAL(clicked()), this, SLOT(levelUp()));
	connect(downLevelButton, SIGNAL(clicked()), this, SLOT(levelDown()));
	
	//connect(removeMarkButton, SIGNAL(clicked()), this SLOT(playOrPause()));
	
	/*connect(forwardButton, SIGNAL(clicked()), this, SLOT(forward()));
	connect(rewindButton, SIGNAL(clicked()), this, SLOT(rewind()));

	connect(fastforwardButton, SIGNAL(clicked()), this, SLOT(fastForward()));
	connect(fastrewindButton, SIGNAL(clicked()), this, SLOT(fastRewind()));*/
}


void
Ui_meta::playOrPause()
{
	cout << "[Play or pause] pĺaying = " << playing << endl;

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
	markIndex = -1;
	subMarkIndex = -1;
	
	QString firstMark = QString::fromStdString(lgmk->marksNames()[0]);
	markLabel->setText(firstMark);
	markLabel->setAlignment(Qt::AlignCenter);
	
	QString firstSubMark  = QString::fromStdString(lgmk->subMarksNames()[0]);
	
	subMarkLabel->setText(firstSubMark);
	subMarkLabel->setAlignment(Qt::AlignCenter);
}

void 
Ui_meta::levelUp()
{
	level = 1;
	cout << "NIVEL "<< level << endl;
}

void 
Ui_meta::levelDown()
{
	level = 2;
	cout << "NIVEL "<< level << endl;
}

/*
void
Ui_meta::fastForward()
{
    cout << "FAST FORWARD" << endl;
}

void
Ui_meta::fastRewind()
{
    cout << "FAST REWIND" << endl;
}

*/

void
Ui_meta::next()
{
	cout << "NIVEL "<< level << endl;
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
	if(level == 1)
	{
		rewind();
	}else if(level == 2)
	{
		rewindSubMark();
	}
	
	//cout <<"prev()"<< endl;
	//cout << "\tmarkIndex: " << markIndex << endl;
 	//cout << "\tsubMarkIndex;: " << subMarkIndex << endl;
	
	synchronizeMarks();
}

void
Ui_meta::forward()
{
	markIndex++;
	cout << "(forward) markIndex: " << markIndex <<endl;
	
	if(markIndex >= lgmk->marks().size() - 1)
	{
		//markIndex = lgmk->marks().size() - 1;
		resetMarkLabels();
		
		//TODO:calcular o tamanho da wave em segundos e emitir sinal para o fim do arquivo
		emit nextMark(304, format);
		
	}else
	{
		emit nextMark(lgmk->marks()[markIndex + 1], format);
	}
}

void
Ui_meta::rewind()
{
	markIndex--;
	cout << "(rewind) markIndex: " << markIndex <<endl;
	
	QString mark;
	
	if(markIndex < 0)
	{
		markIndex = -1;
		subMarkIndex = -1;
		
		emit prevMark(0, format);
	}else
	{
		emit prevMark(lgmk->marks()[markIndex + 1], format);
	}
}

void
Ui_meta::forwardSubMark()
{
	subMarkIndex++;
	cout << "(forward SubMark) subMarkIndex: " << subMarkIndex <<endl;
	
	if(subMarkIndex >= lgmk->subMarks().size() - 1)
	{
		//subMarkIndex = lgmk->subMarks().size();
		resetMarkLabels();
	    
		//TODO:calcular o tamanho da wave em segundos e emitir sinal para o fim do arquivo
		emit nextMark(304, format);
		
	}else
	{
		emit nextMark(lgmk->subMarks()[subMarkIndex + 1], format);
	}
}

void
Ui_meta::rewindSubMark()
{
	subMarkIndex--;
	cout << "(rewind SubMark) subMarkIndex: " << subMarkIndex <<endl;
	
	QString subMark;
	
	if(subMarkIndex < 0)
	{
		markIndex = -1;
		subMarkIndex = -1;
	    
		emit prevMark(0, format);
		
	}else
	{
		emit prevMark(lgmk->subMarks()[subMarkIndex + 1], format);
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
		cout << "SINCRONIZACÃO NIVEL 1!!!!" << endl;
		
		position = lgmk->marks()[markIndex+1];
		
		for(uint32_t i = 0; i < lgmk->subMarks().size(); i++)
		{
			if(position == 0)
			{
				subMarkIndex = -1;
				
				break;
			}else if(lgmk->subMarks()[i] == position)
			{
				subMarkIndex = i - 1;
		
				break;
			}else if(lgmk->subMarks()[i] > position)
			{
				// - 1
				subMarkIndex = i - 2;
			}
		}
		
		cout << "\tmarkIndex: " << markIndex << endl;
		cout << "\tsubMarkIndex: " << subMarkIndex << endl;
				
		cout << "\tmarks: " << lgmk->marks()[markIndex + 1] << endl;
		cout << "\tsubMarks: " << lgmk->subMarks()[subMarkIndex + 1] << endl;
		
		mark  = QString::fromStdString(lgmk->marksNames()[markIndex + 1]);
		subMark = QString::fromStdString(lgmk->subMarksNames()[subMarkIndex + 1]);
		
		markLabel->setText(mark);
		subMarkLabel->setText(subMark);
		
	}else if(level == 2)
	{
		cout << "SINCRONIZACÃO NIVEL 2!!!!" << endl;
		
		position = lgmk->subMarks()[subMarkIndex+1];
		
		for(uint32_t i = 0; i < lgmk->marks().size(); i++)
		{
			if(position == 0)
			{
				markIndex = -1;
				
				//mark  = QString::fromStdString(lgmk->marksNames()[markIndex + 1]);
				//markLabel->setText(mark);
				
			}else if(lgmk->marks()[i] > position)
			{
				markIndex = i - 2;
				
				//mark  = QString::fromStdString(lgmk->marksNames()[markIndex]);
				//markLabel->setText(mark);
		
				break;
			}else if(lgmk->marks()[i] == position )
			{
				markIndex = i - 1;
				
				//mark  = QString::fromStdString(lgmk->marksNames()[markIndex]);
				//markLabel->setText(mark);
		
				break;
			}
		}
		
		cout << "\tmarkIndex: " << markIndex << endl;
		cout << "\tsubMarkIndex: " << subMarkIndex << endl;
		
		cout << "\tmarks: " << lgmk->marks()[markIndex + 1] << endl;
		cout << "\tsubMarks: " << lgmk->subMarks()[subMarkIndex + 1] << endl;
		
		mark  = QString::fromStdString(lgmk->marksNames()[markIndex + 1]);
		subMark = QString::fromStdString(lgmk->subMarksNames()[subMarkIndex + 1]);
		
		markLabel->setText(mark);
		subMarkLabel->setText(subMark);
	}
}

