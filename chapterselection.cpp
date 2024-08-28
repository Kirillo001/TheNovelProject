#include "chapterselection.h"   //это страничка выбора главы (после нажатия Play)
#include "ui_chapterselection.h"
#include <QDebug>

ChapterSelection::ChapterSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChapterSelection)
{
    ui->setupUi(this);

    QPixmap background(":/backgrounds/common/background/background_chapter.png");               //бекграунд лично реализован по колхозному.
    background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QBrush brush(background);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    setPalette(palette);

    setStyleSheet(                                                                              //які красиві клацалки ммммм
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
}

ChapterSelection::~ChapterSelection()                                                           //Деконструктор субахиби
{
    delete ui;
}

void ChapterSelection::on_chapterSelectionButton_clicked()                                      //кнопочки ссаные
{
    qDebug() << "Chapter 1 button clicked.";
    emit chapterSelected(1);
}

void ChapterSelection::on_chapterSelectionButton_2_clicked()
{
    qDebug() << "Chapter 2 button clicked.";
    emit chapterSelected(2);
}
