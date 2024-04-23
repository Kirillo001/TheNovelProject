// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenu.h"
#include "gamesettings.h"
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

    connect(mainMenu, &MainMenu::showSettings, this, &MainWindow::showSettingsWidget);
    connect(settingsWidget, &GameSettings::backToMainMenu, this, &MainWindow::showMainMenuWidget);
    MusicManager musicManager;
    musicManager.playMusic(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSettingsWidget()
{
    // Переключаемся на виджет настроек
    stackedWidget->setCurrentWidget(settingsWidget);
}

void MainWindow::showMainMenuWidget()
{
    // Переключаемся на главное меню
    stackedWidget->setCurrentWidget(mainMenu);
}
