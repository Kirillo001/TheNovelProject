#include "SettingsManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

SettingsManager::SettingsManager(const QString &filePath)
    : filePath(filePath)
{
    // Создать файл, если он не существует
    QFile file(filePath);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << "volume=50\n"; // Например, установить громкость по умолчанию на 50
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
    return 50; // Громкость по умолчанию, если файл не найден или нет данных
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
