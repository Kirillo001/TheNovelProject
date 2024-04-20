#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1280, 720); // Устанавливаем фиксированный размер окна
    w.setWindowIcon(QIcon(":/icon/icon.ico")); // Устанавливаем иконку приложения
    w.setWindowTitle("The Novel Project Alpha 0.1");

    w.show();
    return a.exec();
}
