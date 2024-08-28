#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>
#include <QPixmap>

class CharacterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterWidget(QWidget *parent = nullptr);

    void setLeftCharacterImage(const QString &imagePath);
    void setRightCharacterImage(const QString &imagePath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_leftCharacter;
    QPixmap m_rightCharacter;
};

#endif
