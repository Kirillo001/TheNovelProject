//mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QAudioOutput>

class MainMenu;
class GameSettings;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showSettingsWidget();
    void showMainMenuWidget();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    MainMenu *mainMenu;
    GameSettings *settingsWidget;
    QMediaPlayer *musicPlayer;
};

#endif // MAINWINDOW_H
