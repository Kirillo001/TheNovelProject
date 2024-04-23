// gamesettings.cpp

#include "gamesettings.h"
#include "ui_gamesettings.h"
#include "musicmanager.h"

MusicManager musicMainMenu;

GameSettings::GameSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameSettings)
{
    ui->setupUi(this);

    QPixmap background(":/backgrounds/common/background/background.png");

    background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // Создание кисти с изображением фона
    QBrush brush(background);

    // Установка фона для виджета
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    setPalette(palette);

    setStyleSheet(
        "QPushButton {"
        "    background-color: #303030;"
        "    color: #ffffff;"
        "    border: 2px solid #000000;"
        "    border-radius: 5px;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #4d4d4d;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #303030;"
        "}"
        "QFrame {"
        "    background-color: rgba(48, 48, 48, 160);"  // Цвет фона
        "    border: 2px solid #000000;"  // Цвет границы и ее толщина
        "    border-radius: 5px;"         // Радиус скругления углов
        "}"
        "QLabel {"
        "    background-color: rgba(48, 48, 48, 0);"
        "    border: 0px solid #000000;"
        "}"
        );
}

GameSettings::~GameSettings()
{
    delete ui;
}

// gamesettings.cpp

void GameSettings::on_pushButton_3_clicked()
{
    emit backToMainMenu();
}


void GameSettings::on_pushButton_4_clicked() //СНПМОДОСТ
{
    musicMainMenu.playMusic(1);
}


void GameSettings::on_pushButton_5_clicked() //ПАСХОАЛКО 1499
{
    musicMainMenu.playMusic(2);
}


void GameSettings::on_horizontalSlider_valueChanged(int value)
{

    musicMainMenu.setVolume(value);
}


