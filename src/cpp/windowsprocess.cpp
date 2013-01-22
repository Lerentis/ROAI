#include "../h/windowsprocess.h"

void WindowsProcess::setProcessEnv(QString _path, QString _args)
{
    installationPath = _path;
    args = _args;
    env = "";
    mode = 0;
}

void WindowsProcess::setProcessEnvLauncher(QString _path, QString _env)
{
    installationPath = _path;
    env = _env;
    mode = 1;
}


void WindowsProcess::run()
{
#ifdef Q_OS_WIN
    if(mode != 0)
    {
        QString qPath = getenv("PATH");
        qPath += QString(";" + env + "launcher/bin");
        qPath += QString(";" + env + "launcher/lib");

        qPath.replace('/','\\');

        LPCWSTR path = reinterpret_cast<const wchar_t *>(qPath.utf16());
        LPCWSTR envVal = reinterpret_cast<const wchar_t *>(QString("PATH").utf16());

        SetEnvironmentVariable(envVal,path);

        ShellExecute(0, 0, reinterpret_cast<const WCHAR*>(installationPath.utf16()), 0, 0, SW_NORMAL);
    }
    else
    {
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = NULL;
        ShExecInfo.lpFile = reinterpret_cast<const WCHAR*>(installationPath.utf16());
        ShExecInfo.lpParameters = reinterpret_cast<const WCHAR*>(args.utf16());
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_HIDE;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);

        WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
    }
#endif
}
