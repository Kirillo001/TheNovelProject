#include "novellagame.h"
#include <QFile>
#include <QTextStream>

NovellaGame::NovellaGame(QWidget *parent) :
    QWidget(parent),
    currentLine(0)
{
    dialogLabel = new QLabel(this);
    nextButton = new QPushButton("Next", this);
    layout = new QVBoxLayout(this);
    layout->addWidget(dialogLabel);
    layout->addWidget(nextButton);

    setLayout(layout);

    connect(nextButton, &QPushButton::clicked, this, &NovellaGame::onNextDialog);
}

NovellaGame::~NovellaGame()
{
}

void NovellaGame::loadChapter(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            chapterLines.append(line);
        }
        file.close();
    }
    onNextDialog(); // Display the first line
}

void NovellaGame::onNextDialog()
{
    if (currentLine < chapterLines.size())
    {
        parseLine(chapterLines[currentLine]);
        currentLine++;
    }
    else
    {
        dialogLabel->setText("End of Chapter");
    }
}

void NovellaGame::parseLine(const QString &line)
{
    // Пример простого разбора строк, это можно улучшить
    if (line.startsWith("namespeak"))
    {
        QString speaker = line.mid(line.indexOf("\"") + 1, line.lastIndexOf("\"") - line.indexOf("\"") - 1);
        dialogLabel->setText(speaker);
    }
    else if (line.startsWith("sametext"))
    {
        QString text = line.mid(line.indexOf("\"") + 1, line.lastIndexOf("\"") - line.indexOf("\"") - 1);
        dialogLabel->setText(text);
    }
    else if (line.startsWith("effect"))
    {
        // Добавьте логику для применения эффектов
    }
    else if (line.startsWith("samecharacterimgxyz"))
    {
        // Добавьте логику для отображения персонажа
    }
    else if (line.startsWith("playnewmusic"))
    {
        // Добавьте логику для воспроизведения музыки
    }
}
