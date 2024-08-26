#ifndef NOVELLAGAME_H
#define NOVELLAGAME_H

#include "ui_novellagame.h"
#include "backgroundwidget.h"
#include "characterwidget.h"
#include <QWidget>
#include <QVector>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

struct Dialogue {
    QString namespeak;
    QString sametext;
    QString effect;
    QString samecharacterimgxyz;
    int music;
    QString background;  // Добавляем поле для фона
};


class NovellaGame : public QWidget
{
    Q_OBJECT

public:
    explicit NovellaGame(QWidget *parent = nullptr);
    ~NovellaGame();
    void loadChapter(const QString &chapterFile);
    void setBackgroundImage(const QString &imagePath);
    void resizeEvent(QResizeEvent *event);
    void setCharacters(const QString &leftCharacter, const QString &rightCharacter);
    void addCharacterSprite(const QString &characterName, const QString &spritePath);
    QString getCharacterSprite(const QString &characterName) const;

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<Dialogue> dialogues;
    void parseChapterFile(const QString &chapterFile);
    void displayDialogue(int index);
    Ui::NovellaGame *ui;
    int currentDialogueIndex = 0;
    void processLine(const QString &line);
    QString extractValue(const QString &line);
    QGraphicsScene *scene = nullptr;
    BackgroundWidget *backgroundWidget;
    CharacterWidget *characterWidget;
    QMap<QString, QString> characterSprites;
};

#endif // NOVELLAGAME_H
