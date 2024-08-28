#include "characterwidget.h"        //идея заключалась в том чтобы сделать как с бекграундами но ток с чагачерами но я заебался пилить эту хуйню.
#include <QPainter>
#include <QDebug>

CharacterWidget::CharacterWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);
}

void CharacterWidget::setLeftCharacterImage(const QString &imagePath)                   //левый чагачер
{
    if (!imagePath.isEmpty() && imagePath != "character_null") {
        if (m_leftCharacter.load(imagePath)) {
            qDebug() << "Left character image loaded successfully:" << imagePath;
        } else {
            qDebug() << "Error loading left character image:" << imagePath;
        }
    } else {
        m_leftCharacter = QPixmap();
    }
    update();
}

void CharacterWidget::setRightCharacterImage(const QString &imagePath)                  //правый чагачер
{
    if (!imagePath.isEmpty() && imagePath != "character_null") {
        if (m_rightCharacter.load(imagePath)) {
            qDebug() << "Right character image loaded successfully:" << imagePath;
        } else {
            qDebug() << "Error loading right character image:" << imagePath;
        }
    } else {
        m_rightCharacter = QPixmap();
    }
    update();
}

void CharacterWidget::paintEvent(QPaintEvent *event)                                    //так-же как и с бекграундами.
{
    Q_UNUSED(event);

    QPainter painter(this);

    if (!m_leftCharacter.isNull()) {
        QRect leftRect(0, 0, width() / 2, height());
        painter.drawPixmap(leftRect, m_leftCharacter);
    }

    if (!m_rightCharacter.isNull()) {
        QRect rightRect(width() / 2, 0, width() / 2, height());
        painter.drawPixmap(rightRect, m_rightCharacter);
    }
}
