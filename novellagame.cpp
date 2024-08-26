#include "novellagame.h"
#include "ui_novellagame.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>
#include <QPixmap>
#include <QPalette>
#include <QVBoxLayout>

NovellaGame::NovellaGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NovellaGame)
{
    ui->setupUi(this);
    qDebug() << "NovellaGame widget created.";

    backgroundWidget = new BackgroundWidget(this);
    backgroundWidget->setGeometry(this->rect()); // Устанавливаем размер виджета фона
    backgroundWidget->lower(); // Размещаем виджет под другими элементами

    characterWidget = new CharacterWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(characterWidget);
    setLayout(layout);

    characterWidget->raise();

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
            currentDialogue.background = line.section('"', 1, 1);  // Сохраняем фон в текущий диалог
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

    // Изменение фона только при необходимости
    if (!dialogue.background.isEmpty()) {
        setBackgroundImage(dialogue.background);
    }

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
    backgroundWidget->setBackgroundImage(imagePath);

    // Убеждаемся, что виджет фона занимает весь экран
    backgroundWidget->setGeometry(this->rect());
    backgroundWidget->lower();  // Виджет фона должен быть под другими элементами

    // Добавляем отладочные сообщения для проверки геометрии
    qDebug() << "Background widget geometry set to:" << backgroundWidget->geometry();
}

void NovellaGame::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Перемещаем и изменяем размер виджета фона при изменении размера окна
    if (backgroundWidget) {
        backgroundWidget->setGeometry(this->rect());
        backgroundWidget->lower();  // Ставим виджет под другие элементы интерфейса
        qDebug() << "Resized background widget to:" << backgroundWidget->geometry();
    }
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

void NovellaGame::setCharacters(const QString &leftCharacter, const QString &rightCharacter)
{
    QString leftSpritePath = getCharacterSprite(leftCharacter);
    QString rightSpritePath = getCharacterSprite(rightCharacter);

    characterWidget->setLeftCharacterImage(leftSpritePath);
    characterWidget->setRightCharacterImage(rightSpritePath);
}

void NovellaGame::addCharacterSprite(const QString &characterName, const QString &spritePath)
{
    characterSprites.insert(characterName, spritePath);
}

QString NovellaGame::getCharacterSprite(const QString &characterName) const
{
    return characterSprites.value(characterName, "character_null"); // Возвращаем "character_null", если персонаж не найден
}
