#include "mainmenu.h"                       //то чо вы видите при запуске игры.
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);                                      //Пискадёровский колхоз как всегда, похлеще Колхоз Мода.

    QPixmap background(":/backgrounds/common/background/background.png");
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
        );

    QString imagePath = ":/common/iconweb/discord.png";
    QPushButton *button = ui->pushButton_4;
    button->setStyleSheet(QString("QPushButton {"
                                  "    border-image: url(%1);"
                                  "}").arg(imagePath));
}

MainMenu::~MainMenu() {
    delete ui;
}

void MainMenu::on_pushButton_2_clicked() {              //уууу используешь ui редактор ебучий ДА ПОШЛИ ВЫ НАХУЙ Я ВАШ РОТ ЧИСТИЛ НАЖДАЧКОЙ ГОНДОНЫ.
    emit showSettings();
}

void MainMenu::on_pushButton_3_clicked() {
    QApplication::quit();
}

void MainMenu::on_pushButton_4_clicked() {
    QUrl url("https://discord.com/invite/rpC5crhj");
    QDesktopServices::openUrl(url);
}

void MainMenu::on_pushButton_clicked() {
    emit showChapterSelection();
}

void MainMenu::on_pushButton_5_clicked()
{
    emit showLoadMenu();
}

