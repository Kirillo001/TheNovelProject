#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QWidget>

namespace Ui {
class GameSettings;
}

class GameSettings : public QWidget
{
    Q_OBJECT

public:
    explicit GameSettings(QWidget *parent = nullptr);
    ~GameSettings();
    // В GameSettings.h
signals:
    void backToMainMenu();
private slots:
    void on_pushButton_3_clicked();

private:
    Ui::GameSettings *ui;
};

#endif // GAMESETTINGS_H
