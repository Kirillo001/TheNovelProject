// musicmanager.h

#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class MusicManager : public QObject
{
    Q_OBJECT
public:
    explicit MusicManager(QObject *parent = nullptr);

    static QMediaPlayer *mainmusic;
    static QAudioOutput *audioOutput;

public slots:
    void playMusic(int trackNumber);
    void setVolume(int volume);
};

#endif // MUSICMANAGER_H
