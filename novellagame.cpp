#include "novellagame.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QRegularExpression>

NovellaGame::NovellaGame(QWidget *parent) :
    QWidget(parent)
{
    // Пример установки UI
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Novella Game Screen", this);
    layout->addWidget(label);
    setLayout(layout);

    qDebug() << "NovellaGame widget created.";
}

void NovellaGame::loadChapter(const QString &chapterFile)
{
    qDebug() << "Loading chapter from file:" << chapterFile;
    parseChapterFile(chapterFile);
    displayDialogue(0); // Отобразить первый диалог
}

void NovellaGame::parseChapterFile(const QString &chapterFile)
{
    QFile file(chapterFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file" << chapterFile;
        return;
    }

    QTextStream in(&file);
    Dialogue currentDialogue;
    QRegularExpression reNumberedBlock(R"(\d+ \{)");
    QRegularExpression reKeyValue(R"((\w+)\s*=\s*([\w_]+);)");
    QRegularExpression reMethod(R"((\w+\.\w+\(\d+\));)");

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) continue;

        if (reNumberedBlock.match(line).hasMatch()) {
            if (!currentDialogue.sametext.isEmpty()) {
                dialogues.append(currentDialogue);
                currentDialogue = Dialogue();
            }
            continue;
        }

        if (line.startsWith("namespeak")) {
            currentDialogue.namespeak = line.section('"', 1, 1);
        } else if (line.startsWith("sametext")) {
            currentDialogue.sametext = line.section('"', 1, 1);
        } else if (line.startsWith("effect")) {
            currentDialogue.effect = line.section('"', 1, 1);
        } else if (line.startsWith("samecharacterimgxyz")) {
            currentDialogue.samecharacterimgxyz = line.section('=', 1, 1).trimmed();
        } else if (line.contains("musicMainMenu.playMusic")) {
            currentDialogue.music = line.section('(', 1, 1).section(')', 0, 0).toInt();
        }
    }

    if (!currentDialogue.sametext.isEmpty()) {
        dialogues.append(currentDialogue);
    }

    qDebug() << "Parsed dialogues:" << dialogues.size();
}

void NovellaGame::displayDialogue(int index)
{
    if (index < 0 || index >= dialogues.size()) return;

    Dialogue &dialogue = dialogues[index];
    qDebug() << "Displaying dialogue:" << dialogue.namespeak << dialogue.sametext;
    // Здесь можно добавить код для отображения диалога на экране

    // Пример вывода информации для отладки
    qDebug() << "Name:" << dialogue.namespeak;
    qDebug() << "Text:" << dialogue.sametext;
    qDebug() << "Effect:" << dialogue.effect;
    qDebug() << "Character Image:" << dialogue.samecharacterimgxyz;
    qDebug() << "Music:" << dialogue.music;
}
