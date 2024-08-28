#include "SettingsManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

SettingsManager::SettingsManager(const QString &filePath)               //нерабочий класс по сути, а так где-то чут чут задействован и не работает нихуя
    : filePath(filePath)
{
    QFile file(filePath);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << "volume=50\n";
            file.close();
        }
    }
}

int SettingsManager::loadVolumeSetting()
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString line = in.readLine();
        file.close();

        if (line.startsWith("volume=")) {
            return line.section('=', 1, 1).toInt();
        }
    }
    return 50;
}

void SettingsManager::saveVolumeSetting(int volume)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << "volume=" << volume << "\n";
        file.close();
    } else {
        qDebug() << "Unable to open settings file for writing";
    }
}
