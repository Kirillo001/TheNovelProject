#ifndef LOADMENU_H
#define LOADMENU_H

#include <QWidget>

namespace Ui {
class LoadMenu;
}

class LoadMenu : public QWidget
{
    Q_OBJECT

public:
    explicit LoadMenu(QWidget *parent = nullptr);
    ~LoadMenu();

    void setupSaveList();

private slots:
    void loadGame(int saveIndex);
    void deleteSave(int saveIndex);

private:
    Ui::LoadMenu *ui;
};

#endif // LOADMENU_H
