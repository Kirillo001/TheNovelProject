#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1280, 740);                          //уууу говно закрепленное разширение, ДА ПОШЛИ ВЫ НАХУЙ ЭТО МОЙ ПЕРВЫЙ РАЗ КОТОРЫЙ НАДЕЮСЬ ОСТАНЕТЬСЯ ПОСЛЕДНИМ.
    w.setWindowIcon(QIcon(":/icon/icon.ico"));
    w.setWindowTitle("The Novel Project Alpha 0.1");    //шлюха
    w.initializeSaveSystem();

    w.show();
    return a.exec();
}

/**СУКА! КАК ЖЕ ХОЧЕТСЯ ВЪЕБАТЬ ЭТОМУ КРИСТИАНУ АНИМЕШНИКУ ЕБАНОМУ!! РАЗНЕСТИ ЕМУ ЕБАЛО ШТЫКОМ НАХУЙ,
 * ЧТОБ У НЕГО ЕБАЛО ПРЕВРАТИЛОСЬ В ФАРШ!!! НОГИ И РУКИ ОТОРВАТЬ НАХУЙ И СЖЕЧЬ К ЧЕРЯТМ СОБАЧИМ!!!
 * ГОЛОВУ ЭТОМУ МЕРЗКОМУ КРИСТИАНУ УНИЧТОЖИТЬ ТАК, ЧТОБ НИЧЕГО НЕ ОСТАЛОСЬ НАХУЙ!!! ЗИГ ХАЙЛЫ А ГЛЕБУ,
 * ПРОСТО МОЛОТОМ РАЗНЕСТИ ГОЛОВУ И СЖЕЧЬ ЕГО ОСТАТКИ БЛЯ НЕНАВИЖУ БЛЯТЬ ЦЫГАН НАХУЙ, ОНИ ВСЁ ВРЕМЯ ХОТЯТ ЗОЛОТО ТАК,
 * ЧТО ХОЧЕТСЯ СЛИТКОМ ЗОЛОТОМ РАЗНЕСТИ ИМ ЕБАЛНИК НАХУЙ!!! А ПОТОМ РАЗОРВАТЬ ИХ ТЕЛА. НА КУСКИ И СЖЕЧЬ НАХУЙ!!! ЗИГ ХАЙЛЬ! ЗИГ ХАЙЛЬ! ЗИГ ХАЙЛЬ! ЗИГ ХАЙЛЬ!**/
