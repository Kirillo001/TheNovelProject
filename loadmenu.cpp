#include "loadmenu.h"
#include "ui_loadmenu.h"

#include <QPushButton>
#include <QDateTime>
#include <QHBoxLayout>
#include <QListWidgetItem>

LoadMenu::LoadMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoadMenu)
{
    ui->setupUi(this);

    setupSaveList(); //вызывает функцию связанную с тем скролл-блоком.

    // Установка фона виджета
    QPixmap background(":/backgrounds/common/background/background.png");
    background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QBrush brush(background);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    setPalette(palette);

    // Установка стилей для кнопок и скролл-блоков
    setStyleSheet(
        "QPushButton {"
        "    background-color: #303030;"
        "    color: #ffffff;"
        "    border: 2px solid #000000;"
        "    border-radius: 5px;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #4d4d4d;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #303030;"
        "}"
        "QListWidget {"
        "    background-color: rgba(0, 0, 0, 60);"
        "    color: #ffffff;"
        "    border: 2px solid #000000;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar:vertical {"
        "    border: 2px solid #bbb;"
        "    background: #f1f1f1;"
        "    width: 10px;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #888;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical {"
        "    height: 20px;"
        "    subcontrol-position: bottom;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:vertical {"
        "    height: 20px;"
        "    subcontrol-position: top;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: #f1f1f1;"
        "}"
        "QScrollBar:horizontal {"
        "    border: 2px solid #bbb;"
        "    background: #f1f1f1;"
        "    height: 10px;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: #888;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::add-line:horizontal {"
        "    width: 20px;"
        "    subcontrol-position: right;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:horizontal {"
        "    width: 20px;"
        "    subcontrol-position: left;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
        "    background: #f1f1f1;"
        "}"
        );

}

LoadMenu::~LoadMenu()
{
    delete ui;
}

void LoadMenu::setupSaveList()
{
    if (!ui->saveListWidget) {
        qDebug() << "saveListWidget не найден!";
        return;
    }

    ui->saveListWidget->clear(); // Очистим список, чтобы избежать дубликатов

    for (int i = 0; i < 5; ++i) {
        QListWidgetItem *item = new QListWidgetItem(ui->saveListWidget);
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout();

        QLabel *saveLabel = new QLabel(QString("Save %1 - %2").arg(i + 1).arg(QDateTime::currentDateTime().toString()));
        QPushButton *loadButton = new QPushButton("Загрузить");
        QPushButton *deleteButton = new QPushButton("Удалить");

        layout->addWidget(saveLabel);
        layout->addWidget(loadButton);
        layout->addWidget(deleteButton);
        layout->addStretch();

        widget->setLayout(layout);
        item->setSizeHint(widget->sizeHint());

        ui->saveListWidget->addItem(item);
        ui->saveListWidget->setItemWidget(item, widget);

        connect(loadButton, &QPushButton::clicked, this, [this, i]() { loadGame(i); });
        connect(deleteButton, &QPushButton::clicked, this, [this, i]() { deleteSave(i); });
    }
}
void LoadMenu::loadGame(int saveIndex)
{
    qDebug() << "Загрузка сохранения: " << saveIndex;
}

void LoadMenu::deleteSave(int saveIndex)
{
    qDebug() << "Удаление сохранения: " << saveIndex;
    setupSaveList();
}
