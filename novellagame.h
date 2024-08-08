#ifndef NOVELLAGAME_H
#define NOVELLAGAME_H

#include "ui_novellagame.h"
#include <QWidget>
#include <QVector>
#include <QMouseEvent>

struct Dialogue {
    QString namespeak;
    QString sametext;
    QString effect;
    QString samecharacterimgxyz;
    int music;
};

class NovellaGame : public QWidget
{
    Q_OBJECT

public:
    explicit NovellaGame(QWidget *parent = nullptr);
    ~NovellaGame();
    void loadChapter(const QString &chapterFile);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<Dialogue> dialogues;
    void parseChapterFile(const QString &chapterFile);
    void displayDialogue(int index);
    Ui::NovellaGame *ui;
    int currentDialogueIndex = 0;
};

#endif // NOVELLAGAME_H
