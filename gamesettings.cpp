#include "gamesettings.h"                   //Виджет настроек, все приблуды и хуйни для настроек должны были находиться отчасти здесь и отчасти в mainwindow.
#include "ui_gamesettings.h"
#include "musicmanager.h"

MusicManager musicMainMenu;

GameSettings::GameSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameSettings)
{
    ui->setupUi(this);

    QPixmap background(":/backgrounds/common/background/background.png");                   //этот колхоз будете видеть почти во всех виджетах.

    background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QBrush brush(background);

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
        "    background-color: rgba(48, 48, 48, 160);"
        "    border: 2px solid #000000;"
        "    border-radius: 5px;"
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


void GameSettings::on_pushButton_3_clicked()
{
    emit backToMainMenu();
}


void GameSettings::on_pushButton_4_clicked()
{
    musicMainMenu.playMusic(1);
}


void GameSettings::on_pushButton_5_clicked()
{
    musicMainMenu.playMusic(2);
}


void GameSettings::on_horizontalSlider_valueChanged(int value)
{

    musicMainMenu.setVolume(value);
}


