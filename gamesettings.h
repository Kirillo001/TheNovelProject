#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QWidget>
#include <QMainWindow>
#include <QAudioOutput>
#include <QMediaPlayer>

namespace Ui {
class GameSettings;
}

class GameSettings : public QWidget
{
    Q_OBJECT

public:
    explicit GameSettings(QWidget *parent = nullptr);
    ~GameSettings();
    // В GameSettings.h
signals:
    void backToMainMenu();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::GameSettings *ui;
};

#endif // GAMESETTINGS_H
