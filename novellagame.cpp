#include "novellagame.h"
#include "ui_novellagame.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

NovellaGame::NovellaGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NovellaGame)
{
    ui->setupUi(this);
    qDebug() << "NovellaGame widget created.";

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
}

NovellaGame::~NovellaGame()
{
    delete ui;
}

void NovellaGame::loadChapter(const QString &chapterFile)
{
    qDebug() << "Loading chapter from file:" << chapterFile;
    parseChapterFile(chapterFile);
    currentDialogueIndex = 0; // Установите начальный индекс на 0
    displayDialogue(currentDialogueIndex); // Отобразить первый диалог
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
    QRegularExpression reNumberedBlock(R"(\d+\s*\{)");
    QRegularExpression reKeyValue(R"((\w+)\s*=\s*([\w_]+);)");
    QRegularExpression reMethod(R"((\w+\.\w+\(\d+\));)");

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) continue;

        qDebug() << "Processing line:" << line;

        if (reNumberedBlock.match(line).hasMatch()) {
            if (!currentDialogue.sametext.isEmpty()) {
                dialogues.append(currentDialogue);
                qDebug() << "Added dialogue:" << currentDialogue.sametext;
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
        qDebug() << "Added final dialogue:" << currentDialogue.sametext;
    }

    qDebug() << "Parsed dialogues:" << dialogues.size();
}

void NovellaGame::displayDialogue(int index)
{
    if (index < 0 || index >= dialogues.size()) return;

    Dialogue &dialogue = dialogues[index];
    qDebug() << "Displaying dialogue:" << dialogue.namespeak << dialogue.sametext;

    // Отображение имени и текста
    ui->labelName->setText(dialogue.namespeak);
    ui->textEditDialogue->setPlainText(dialogue.sametext);
}

void NovellaGame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        currentDialogueIndex++;
        if (currentDialogueIndex < dialogues.size()) {
            displayDialogue(currentDialogueIndex);
        } else {
            qDebug() << "End of dialogues.";
            QApplication::quit();
        }
    }
    QWidget::mousePressEvent(event);
}
