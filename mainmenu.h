#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QDesktopServices>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

signals:
    void showSettings();
    void showChapterSelection();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
