// characterwidget.cpp

#include "characterwidget.h"
#include <QPainter>
#include <QDebug>

CharacterWidget::CharacterWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);
}

void CharacterWidget::setLeftCharacterImage(const QString &imagePath)
{
    if (!imagePath.isEmpty() && imagePath != "character_null") {
        if (m_leftCharacter.load(imagePath)) {
            qDebug() << "Left character image loaded successfully:" << imagePath;
        } else {
            qDebug() << "Error loading left character image:" << imagePath;
        }
    } else {
        m_leftCharacter = QPixmap(); // Сбрасываем изображение, если "character_null"
    }
    update();
}

void CharacterWidget::setRightCharacterImage(const QString &imagePath)
{
    if (!imagePath.isEmpty() && imagePath != "character_null") {
        if (m_rightCharacter.load(imagePath)) {
            qDebug() << "Right character image loaded successfully:" << imagePath;
        } else {
            qDebug() << "Error loading right character image:" << imagePath;
        }
    } else {
        m_rightCharacter = QPixmap(); // Сбрасываем изображение, если "character_null"
    }
    update();
}

void CharacterWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // Рисуем левого персонажа, если изображение загружено
    if (!m_leftCharacter.isNull()) {
        QRect leftRect(0, 0, width() / 2, height());
        painter.drawPixmap(leftRect, m_leftCharacter);
    }

    // Рисуем правого персонажа, если изображение загружено
    if (!m_rightCharacter.isNull()) {
        QRect rightRect(width() / 2, 0, width() / 2, height());
        painter.drawPixmap(rightRect, m_rightCharacter);
    }
}
