#include "mainwindow.h"                                         //самое вкусьненое в виде торта с говном а не гашишем.
#include "ui_mainwindow.h"
#include "mainmenu.h"
#include "gamesettings.h"
#include "musicmanager.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stackedWidget(new QStackedWidget(this))
    , mainMenu(new MainMenu(this))
    , settingsWidget(new GameSettings(this))
    , chapterSelection(new ChapterSelection(this))
    , novellaGame(new NovellaGame(this))
    , loadMenu(new LoadMenu(this))
{
    ui->setupUi(this);

    initializeSaveSystem();

    setCentralWidget(stackedWidget);

    stackedWidget->addWidget(mainMenu);                         //стэки ммммм какое же это говно блять.
    stackedWidget->addWidget(settingsWidget);
    stackedWidget->addWidget(chapterSelection);
    stackedWidget->addWidget(novellaGame);
    stackedWidget->addWidget(loadMenu);

    connect(mainMenu, &MainMenu::showSettings, this, &MainWindow::showSettingsWidget);                      //ну тут чето нейронка показала вроде работает, но кажеться можно было и проще.
    connect(mainMenu, &MainMenu::showChapterSelection, this, &MainWindow::showChapterSelectionWidget);
    connect(mainMenu, &MainMenu::showLoadMenu, this, &MainWindow::showLoadMenu);
    connect(settingsWidget, &GameSettings::backToMainMenu, this, &MainWindow::showMainMenuWidget);
    connect(chapterSelection, &ChapterSelection::chapterSelected, this, &MainWindow::onChapterSelected);

    MusicManager musicManager;
    musicManager.playMusic(1);                                  //при желании можете закоментировать строчку чтобы не слышать И И И И И ОЙ ЕБАННЫЙ ВРОТ АЙЙЙЙЙЙЙЙЙЙНУАОП.

    qDebug() << "MainWindow initialized.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSettingsWidget()                           //отчасти нужен для того чтобы открывать странички, используються сигналы emit и подобная ересь которая работает тоже через говно.
{
    stackedWidget->setCurrentWidget(settingsWidget);
}
void MainWindow::showLoadMenu()
{
    stackedWidget->setCurrentWidget(loadMenu);
}
void MainWindow::showMainMenuWidget()
{
    stackedWidget->setCurrentWidget(mainMenu);
}

void MainWindow::showChapterSelectionWidget()
{
    stackedWidget->setCurrentWidget(chapterSelection);
}

void MainWindow::onChapterSelected(int chapter)                 //Чтобы главы загружать и подобная ебатня, в мейнвиндов почти половина логики приложения реализована.
{
    qDebug() << "Switching to novella game widget. Chapter:" << chapter;
    QString chapterFile = QString("E:/newPrograms/Qt/TheNovelProject/common/chapters/chapter%1.txt").arg(chapter);
    qDebug() << "Loading chapter from file:" << chapterFile;
    novellaGame->loadChapter(chapterFile);
    stackedWidget->setCurrentWidget(novellaGame);
}

void MainWindow::initializeSaveSystem()                         //Меня тоже заебал И И И И И ОЙ ЕБАННЫЙ ВРОТ АЙЙЙЙЙЙЙЙЙЙНУАОП, хотел сделать так чтобы он сейфил параметр громкости музыки чтобы не слышать это говно.
{
    qDebug() << "Initializing save system...";
                                                               // если чё оно НЕ РАБОТАЕТ.
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QString saveDirPath = appDataPath + "/saves";

    QDir saveDir(saveDirPath);
    if (!saveDir.exists()) {
        bool created = saveDir.mkpath(saveDirPath);
        if (created) {
            qDebug() << "Directory created successfully:" << saveDirPath;
        } else {
            qDebug() << "Failed to create directory:" << saveDirPath;
            return;
        }
    } else {
        qDebug() << "Directory already exists:" << saveDirPath;
    }

    // Попробуем создать файл other.txt
    QString filePath = saveDirPath + "/other.txt";          //хотя вы видите что он создаёт папку и тхт файл в виде вирусняка для вашего пк в каких-то ебенях.
    QFile testFile(filePath);
    if (testFile.open(QIODevice::WriteOnly)) {
        qDebug() << "File created successfully:" << filePath;
        testFile.close();
    } else {
        qDebug() << "Failed to create file:" << filePath;
        qDebug() << "Error code:" << testFile.error();
        qDebug() << "Error string:" << testFile.errorString();
    }

    qDebug() << "Save system initialized.";
}





