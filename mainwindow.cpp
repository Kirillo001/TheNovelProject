#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenu.h"
#include "gamesettings.h"
#include "chapterselection.h"
#include "novellagame.h"
#include "musicmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    mainMenu = new MainMenu(this);
    stackedWidget->addWidget(mainMenu);

    settingsWidget = new GameSettings(this);
    stackedWidget->addWidget(settingsWidget);

    chapterSelection = new ChapterSelection(this);
    stackedWidget->addWidget(chapterSelection);

    novellaGame = new NovellaGame(this);
    stackedWidget->addWidget(novellaGame);

    connect(mainMenu, &MainMenu::showSettings, this, &MainWindow::showSettingsWidget);
    connect(settingsWidget, &GameSettings::backToMainMenu, this, &MainWindow::showMainMenuWidget);
    connect(mainMenu, &MainMenu::showChapterSelection, this, &MainWindow::showChapterSelectionWidget);
    connect(chapterSelection, &ChapterSelection::chapterSelected, this, &MainWindow::showNovellaGameWidget);

    MusicManager musicManager;
    musicManager.playMusic(1);
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

void MainWindow::showNovellaGameWidget(int chapter)
{
    // Загрузка главы в виджет новеллы
    QString chapterFile = QString("chapter%1.txt").arg(chapter);
    novellaGame->loadChapter(chapterFile);
    stackedWidget->setCurrentWidget(novellaGame);
}
