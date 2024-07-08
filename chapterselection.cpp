#include "chapterselection.h"
#include "ui_chapterselection.h"

ChapterSelection::ChapterSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChapterSelection)
{
    ui->setupUi(this);
}

ChapterSelection::~ChapterSelection()
{
    delete ui;
}

void ChapterSelection::on_chapterSelectionButton_clicked()
{
    emit chapterSelected(1);
}


void ChapterSelection::on_chapterSelectionButton_2_clicked()
{
    emit chapterSelected(2);
}

