#include "ui_meta.h"

Ui_meta::Ui_meta(const char *path)
{
	playing = true;
	markIndex = -1;
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
		format = dynamic_cast<Format *>(*it);
		
		if(format != 0)
			break;
	}
	
}

void 
Ui_meta::setLabels()
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
Ui_meta::connections()
{
	connect(playOrPauseButton, SIGNAL(clicked()), this, SLOT(playOrPause()));
	connect(forwardButton,SIGNAL(clicked()), this, SLOT(forward()));
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


/*void 
Ui_meta::reset()
{		
	QIcon icon;

	icon.addFile(QString::fromUtf8(":/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);

    playOrPauseButton->setIcon(icon);
}*/

/*

void
Ui_meta::playOrPause()
{
    QIcon iicon;

    if(!playing)
    {
        iicon.addFile(QString::fromUtf8(":/images/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        playOrPauseButton->setIcon(iicon);
        playing = true;

	SDL_PauseAudio(0);
        cout << "PLAYING" << endl;
	
    }
    else
    {
        iicon.addFile(QString::fromUtf8(":/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        playOrPauseButton->setIcon(iicon);
        playing = false;

	SDL_PauseAudio(1);
        cout << "PAUSED" << endl;
    }

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

void
Ui_meta::rewind()
{
    cout << "REWIND" << endl;
}
*/

void
Ui_meta::forward()
{
    markIndex++;
    cout <<"forward slot: " << markIndex <<endl;
	
    if(markIndex >= lgmk->marks().size())
    {
	    markIndex = lgmk->marks().size();
	    //TODO:calcular o tamanho da wave em segundos e emitir sinal para o fim do arquivo
    }else
    {
	    emit nextMark(lgmk->marks()[markIndex], format);
    }
	    
}
