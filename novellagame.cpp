#include "novellagame.h"                                                //Опять говно в пюрешку подсыпали, виджет и логика самой игры.
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
    backgroundWidget->setGeometry(this->rect());
    backgroundWidget->lower();

    characterWidget = new CharacterWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(characterWidget);
    setLayout(layout);

    characterWidget->raise();

    addCharacterSprite("niggasoy_ch", ":/common/characters/sprite/niggasoy.png");
    addCharacterSprite("yakub_ch", ":/common/characters/sprite/yakub.png");

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
    QPixmap sprite(":/common/interface/novella/novellatable.png");
    QLabel *spriteLabel = new QLabel(ui->frameInterface);
    spriteLabel->setPixmap(sprite.scaled(ui->frameInterface->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    spriteLabel->setGeometry(0, 0, ui->frameInterface->width(), ui->frameInterface->height());
    spriteLabel->show();

    ui->frameInterface->lower();
    ui->labelName->raise();
    ui->textEditDialogue->raise();
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

void NovellaGame::loadChapter(const QString &chapterFile)               //ну блять имя функции само за себя говорит
{
    qDebug() << "Loading chapter from file:" << chapterFile;
    parseChapterFile(chapterFile);
    currentDialogueIndex = 0;
    displayDialogue(currentDialogueIndex);
}

void NovellaGame::parseChapterFile(const QString &chapterFile)          //Тут короче chapter*НОМЕР*.txt ищет разные строчки и ищет содержимое и читает его.
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

        if (line.startsWith("background")) {                                            //тут вы сами пон.
            currentDialogue.background = line.section('"', 1, 1);
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


void NovellaGame::displayDialogue(int index)                                        //я называю это динамической функцией которая сама показывает и изменяет детали в игре, тип текст изменяет на следующий и т.п.
{
    if (index < 0 || index >= dialogues.size()) return;

    Dialogue &dialogue = dialogues[index];
    qDebug() << "Displaying dialogue:" << dialogue.namespeak << dialogue.sametext;

    if (!dialogue.background.isEmpty()) {
        setBackgroundImage(dialogue.background);                                   //дада тут бекграунды
    }

    QString leftCharacter = extractValue(dialogue.samecharacterimgxyz.section(';', 0, 0).trimmed());
    QString rightCharacter = extractValue(dialogue.samecharacterimgxyz.section(';', 1, 1).trimmed());
    setCharacters(leftCharacter, rightCharacter);

    ui->labelName->setText(dialogue.namespeak);
    ui->textEditDialogue->setPlainText(dialogue.sametext);
}



void NovellaGame::mousePressEvent(QMouseEvent *event)                               //шоб листать текст и главу думайте сами.
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

void NovellaGame::setBackgroundImage(const QString &imageName)                      //адская дрочильня 1
{
    QString imagePath = QString(":/common/background/novellabg/%1.jpg").arg(imageName);
    backgroundWidget->setBackgroundImage(imagePath);

    backgroundWidget->setGeometry(this->rect());
    backgroundWidget->lower();

    qDebug() << "Background widget geometry set to:" << backgroundWidget->geometry();
}

void NovellaGame::resizeEvent(QResizeEvent *event)                                  //адская дрочильня 1.2
{
    QWidget::resizeEvent(event);

    if (backgroundWidget) {
        backgroundWidget->setGeometry(this->rect());
        backgroundWidget->lower();
        qDebug() << "Resized background widget to:" << backgroundWidget->geometry();
    }
}

QString NovellaGame::extractValue(const QString &line)                              //адская дрочильня 1.3
{
    int start = line.indexOf('"') + 1;
    int end = line.lastIndexOf('"');
    if (start > 0 && end > start) {
        return line.mid(start, end - start);
    }
    return QString();
}

void NovellaGame::setCharacters(const QString &leftCharacter, const QString &rightCharacter)    //хотел сделать МОЖЕМ ПОВТОРИТЬ (так-же как с бекграундами) а в итоге говно получилось.
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
    return characterSprites.value(characterName, "character_null");
}
