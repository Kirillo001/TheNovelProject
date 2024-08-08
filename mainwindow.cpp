#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenu.h"
#include "gamesettings.h"
#include "musicmanager.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stackedWidget(new QStackedWidget(this))
    , mainMenu(new MainMenu(this))
    , settingsWidget(new GameSettings(this))
    , chapterSelection(new ChapterSelection(this))
    , novellaGame(new NovellaGame(this))
{
    ui->setupUi(this);

    setCentralWidget(stackedWidget);

    stackedWidget->addWidget(mainMenu);
    stackedWidget->addWidget(settingsWidget);
    stackedWidget->addWidget(chapterSelection);
    stackedWidget->addWidget(novellaGame);

    connect(mainMenu, &MainMenu::showSettings, this, &MainWindow::showSettingsWidget);
    connect(mainMenu, &MainMenu::showChapterSelection, this, &MainWindow::showChapterSelectionWidget);
    connect(settingsWidget, &GameSettings::backToMainMenu, this, &MainWindow::showMainMenuWidget);
    connect(chapterSelection, &ChapterSelection::chapterSelected, this, &MainWindow::onChapterSelected);

    MusicManager musicManager;
    musicManager.playMusic(1);

    qDebug() << "MainWindow initialized.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSettingsWidget()
{
    stackedWidget->setCurrentWidget(settingsWidget);
}

void MainWindow::showMainMenuWidget()
{
    stackedWidget->setCurrentWidget(mainMenu);
}

void MainWindow::showChapterSelectionWidget()
{
    stackedWidget->setCurrentWidget(chapterSelection);
}

void MainWindow::onChapterSelected(int chapter)
{
    qDebug() << "Switching to novella game widget. Chapter:" << chapter;
    QString chapterFile = QString("E:/newPrograms/Qt/TheNovelProject/common/chapters/chapter%1.txt").arg(chapter);
    qDebug() << "Loading chapter from file:" << chapterFile;
    novellaGame->loadChapter(chapterFile);
    stackedWidget->setCurrentWidget(novellaGame);
}

