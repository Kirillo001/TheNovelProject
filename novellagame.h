#ifndef NOVELLAGAME_H
#define NOVELLAGAME_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class NovellaGame : public QWidget
{
    Q_OBJECT

public:
    explicit NovellaGame(QWidget *parent = nullptr);
    void loadChapter(const QString &filePath);
    ~NovellaGame();

private slots:
    void onNextDialog();

private:
    QLabel *dialogLabel;
    QVBoxLayout *layout;
    QPushButton *nextButton;
    int currentLine;
    QStringList chapterLines;

    void parseLine(const QString &line);
};

#endif // NOVELLAGAME_H
