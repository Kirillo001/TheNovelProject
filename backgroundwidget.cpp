#include "backgroundwidget.h" //бекграунд в новелле реализован с помощью виджета в виджете который в виджете
#include <QPainter>
#include <QDebug>

BackgroundWidget::BackgroundWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true); //чтобы белая хуйня на весь экран не вылазила.
}

void BackgroundWidget::setBackgroundImage(const QString &imagePath) //имя функции говорит само за себя.
{
    if (m_background.load(imagePath)) {
        qDebug() << "Background image loaded successfully:" << imagePath;
    } else {
        qDebug() << "Error loading background image:" << imagePath;
    }
    update();
}

void BackgroundWidget::paintEvent(QPaintEvent *event) //чтобы верхнее нормально работало.
{
    Q_UNUSED(event);

    QPainter painter(this);
    if (!m_background.isNull()) {
        painter.drawPixmap(rect(), m_background);
    }
}
