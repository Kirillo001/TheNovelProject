#ifndef NOVELLAGAME_H
#define NOVELLAGAME_H

#include <QWidget>
#include <QVector>

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
    void loadChapter(const QString &chapterFile);

private:
    QVector<Dialogue> dialogues;
    void parseChapterFile(const QString &chapterFile);
    void displayDialogue(int index);
};

#endif // NOVELLAGAME_H
