#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "chapterselection.h"
#include "novellagame.h"
#include "loadmenu.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class MainMenu;
class GameSettings;
class ChapterSelection;
class NovellaGame;

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
    void showChapterSelectionWidget();
    void onChapterSelected(int chapter);
    void showLoadMenu();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    MainMenu *mainMenu;
    GameSettings *settingsWidget;
    ChapterSelection *chapterSelection;
    NovellaGame *novellaGame;
    LoadMenu *loadMenu;
};

#endif // MAINWINDOW_H
