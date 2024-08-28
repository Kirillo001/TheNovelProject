#ifndef CHAPTERSELECTION_H
#define CHAPTERSELECTION_H

#include <QWidget>

namespace Ui {
class ChapterSelection;
}

class ChapterSelection : public QWidget
{
    Q_OBJECT

public:
    explicit ChapterSelection(QWidget *parent = nullptr);
    ~ChapterSelection();

signals:
    void chapterSelected(int chapter);

private slots:
    void on_chapterSelectionButton_clicked();
    void on_chapterSelectionButton_2_clicked();

private:
    Ui::ChapterSelection *ui;
};

#endif
