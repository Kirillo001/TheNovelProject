#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>

class SettingsManager
{
public:
    SettingsManager(const QString &filePath);
    int loadVolumeSetting();
    void saveVolumeSetting(int volume);

private:
    QString filePath;
};

#endif
