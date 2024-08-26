#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include <QWidget>
#include <QPixmap>

class BackgroundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BackgroundWidget(QWidget *parent = nullptr);
    void setBackgroundImage(const QString &imagePath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_background;
};

#endif // BACKGROUNDWIDGET_H
