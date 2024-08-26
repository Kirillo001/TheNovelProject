#include "backgroundwidget.h"
#include <QPainter>
#include <QDebug>

BackgroundWidget::BackgroundWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true); // Автоматически заполняем фон
}

void BackgroundWidget::setBackgroundImage(const QString &imagePath)
{
    if (m_background.load(imagePath)) {
        qDebug() << "Background image loaded successfully:" << imagePath;
    } else {
        qDebug() << "Error loading background image:" << imagePath;
    }
    update(); // Обновляем виджет после установки изображения
}

void BackgroundWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    if (!m_background.isNull()) {
        // Рисуем изображение, растянутое по размеру виджета
        painter.drawPixmap(rect(), m_background);
    }
}
