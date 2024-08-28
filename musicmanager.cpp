#include "musicmanager.h"                                       //Сука гондоны вырезали пол соунд возможностей в виде простой регулировки громкости поэтому пришлось использовать костыли нейронки.

QMediaPlayer *MusicManager::mainmusic = nullptr;
QAudioOutput *MusicManager::audioOutput = nullptr;

MusicManager::MusicManager(QObject *parent) : QObject(parent)
{
    mainmusic = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    mainmusic->setAudioOutput(audioOutput);
}

void MusicManager::playMusic(int trackNumber)
{
    QString source;
    switch (trackNumber) {
    case 1:
        source = "qrc:/common/sound/music/fenazepam.mp3";
        break;
    case 2:
        source = "qrc:/common/sound/music/pashalko.mp3";
        break;
    default:
        return;
    }

    mainmusic->setSource(QUrl(source));
    mainmusic->play();
}
void MusicManager::setVolume(int volume)                    //эта хуета могла быть намного меньше если бы не 6 версия Qt
{
    qreal linearVolume = QAudio::convertVolume(volume / qreal(100.0),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);
    audioOutput->setVolume(qreal(linearVolume));
}

