#include "novellagame.h"
#include "ui_novellagame.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>
#include <QPixmap>
#include <QPalette>

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
    // Предположим, вы находитесь в методе, связанном с вашим главным окном или виджетом
    QPixmap sprite(":/common/interface/novella/novellatable.png");
    QLabel *spriteLabel = new QLabel(ui->frameInterface);
    spriteLabel->setPixmap(sprite.scaled(ui->frameInterface->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    spriteLabel->setGeometry(0, 0, ui->frameInterface->width(), ui->frameInterface->height()); // Установка размеров как у QFrame
    spriteLabel->show();

    ui->frameInterface->lower();  // Перемещаем QFrame на задний план
    ui->labelName->raise();       // Поднимаем лейбл имени на передний план
    ui->textEditDialogue->raise(); // Поднимаем текстовое поле на передний план
    ui->pushButton_4->raise();
    ui->pushButton_5->raise();
    ui->pushButton_6->raise();
    ui->pushButton_7->raise();
    ui->pushButton_8->raise();
    ui->backgroundLabel->stackUnder(ui->frameInterface);
    ui->textEditDialogue->setStyleSheet(
        "background: rgba(255, 255, 255, 0);"
        "color: #FFFFFF;" // Цвет шрифта
        );
    ui->labelName->setStyleSheet(
        "color: #FFFFFF;"
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

        if (line.startsWith("background")) {
            QString backgroundName = line.section('"', 1, 1);
            setBackgroundImage(backgroundName);
        } else if (line.startsWith("namespeak")) {
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

void NovellaGame::setBackgroundImage(const QString &imageName)
{
    QString imagePath = QString(":/common/background/novellabg/%1.jpg").arg(imageName);
    QPixmap background(imagePath);
    if (background.isNull()) {
        qDebug() << "Ошибка загрузки фонового изображения:" << imagePath;
        return;
    }

    QLabel *backgroundLabel = this->findChild<QLabel *>("backgroundLabel");
    if (!backgroundLabel) {
        qDebug() << "QLabel для фона не найден!";
        return;
    }

    backgroundLabel->setPixmap(background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setGeometry(this->rect());
    //backgroundLabel->stackUnder(ui->frameInterface);
}

QString NovellaGame::extractValue(const QString &line)
{
    int start = line.indexOf('"') + 1;
    int end = line.lastIndexOf('"');
    if (start > 0 && end > start) {
        return line.mid(start, end - start);
    }
    return QString();
}
