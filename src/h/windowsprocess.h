#ifndef WINDOWSPROCESS_H
#define WINDOWSPROCESS_H


#include <QThread>
#include <QString>

#ifdef Q_OS_WIN32
#include <Windows.h>
#endif


class WindowsProcess : public QThread
{
    public:
        void setProcessEnv(QString _path, QString _args);
        void setProcessEnvLauncher(QString _path, QString _env);
        void run();
        bool getResult();

    private:
        bool result;
        QString installationPath;
        QString args;
        QString env;
        int mode;
};

#endif // WINDOWSPROCESS_H
