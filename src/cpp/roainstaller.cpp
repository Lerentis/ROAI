/**
 * \copyright   Copyright © 2012 QuantumBytes inc.
 *
 *              For more information, see https://www.quantum-bytes.com/
 *
 * \section LICENSE
 *
 *              This file is part of Relics of Annorath Installer.
 *
 *              Relics of Annorath Installer is free software: you can redistribute it and/or modify
 *              it under the terms of the GNU General Public License as published by
 *              the Free Software Foundation, either version 3 of the License, or
 *              any later version.
 *
 *              Relics of Annorath Installer is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *              GNU General Public License for more details.
 *
 *              You should have received a copy of the GNU General Public License
 *              along with Relics of Annorath Installer.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \brief       Handels the update process for the Installer and related files
 *
 * \file    	roainstaller.cpp
 *
 * \note
 *
 * \version 	1.0
 *
 * \author  	Manuel Gysin <manuel.gysin@quantum-bytes.com>
 *
 * \date        2012/12/01 23:10:00 GMT+1
 *
 */

/******************************************************************************/
/*                                                                            */
/*    Others includes                                                         */
/*                                                                            */
/******************************************************************************/
#include "../h/roainstaller.h"

/******************************************************************************/
/*                                                                            */
/*    Constructor/Deconstructor                                               */
/*                                                                            */
/******************************************************************************/
ROAInstaller::ROAInstaller(QObject *parent) :
    QObject(parent)
{
    // Create all pages
    components = new ROAPageComponents();
    finish = new ROAPageFinish();
    install = new ROAPageInstall();
    license = new ROAPageLicense();
    status = new ROAPageStatus();
    welcome = new ROAPageWelcome();

    // Set download phase for later
    downloadPhase = 0;

    // Connect pages
    connect(welcome,SIGNAL(nextPage()),this,SLOT(slot_nextPageTriggered()));

    connect(license,SIGNAL(nextPage()),this,SLOT(slot_nextPageTriggered()));
    connect(license,SIGNAL(previousPage()),this,SLOT(slot_previousPageTriggered()));

    connect(components,SIGNAL(nextPage()),this,SLOT(slot_nextPageTriggered()));
    connect(components,SIGNAL(previousPage()),this,SLOT(slot_previousPageTriggered()));

    connect(install,SIGNAL(nextPage()),this,SLOT(slot_nextPageTriggered()));
    connect(install,SIGNAL(previousPage()),this,SLOT(slot_previousPageTriggered()));

    // Create settings object
    userSettings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Quantum Bytes GmbH", "Relics of Annorath");

    // Check path and remove old installation or outdated libs
    QString installPathOld = userSettings->value("installLocation","none").toString();

    if(installPathOld != "none")
    {
        /// \todo Remove slash

        // Cleanup old files
#ifdef Q_OS_LINUX
        QFile::remove(installPathOld + "/ROALauncher");
        QFile::remove(installPathOld + "/ROALauncher.sh");

        QFile::remove(installPathOld + "/files/bin/roa");
        QFile::remove(installPathOld + "/files/lib/libMd5_x64.so");
        QFile::remove(installPathOld + "/files/lib/libNetwork_x64.so");
        QFile::remove(installPathOld + "/files/lib/libRakNet_x64.so");
        QFile::remove(installPathOld + "/files/lib/libUnigine_x64.so");

        QFile::remove(installPathOld + "/imageformats/libqgif.so");

        QFile::remove(installPathOld + "/lib/libboost_filesystem.so.1.46.1");
        QFile::remove(installPathOld + "/lib/libboost_system.so.1.46.1");
        QFile::remove(installPathOld + "/lib/libboost_thread.so.1.46.1");
        QFile::remove(installPathOld + "/lib/libcrypto.so.1.0.0");
        QFile::remove(installPathOld + "/lib/libpcre.so.3");
        QFile::remove(installPathOld + "/lib/libQtCore.so.4");
        QFile::remove(installPathOld + "/lib/libQtDBus.so.4");
        QFile::remove(installPathOld + "/lib/libQtGui.so.4");
        QFile::remove(installPathOld + "/lib/libQtNetwork.so.4");
        QFile::remove(installPathOld + "/lib/libQtWebKit.so.4");
        QFile::remove(installPathOld + "/lib/libQtXml.so.4");
        QFile::remove(installPathOld + "/lib/libssl.so.1.0.0");
        QFile::remove(installPathOld + "/lib/libtorrent-rasterbar.so.6");
#endif
    }
}

ROAInstaller::~ROAInstaller()
{
    delete components;
    delete finish;
    delete install;
    delete license;
    delete status;
    delete welcome;

    delete userSettings;
}

/******************************************************************************/
/*                                                                            */
/*    Public methods                                                          */
/*                                                                            */
/******************************************************************************/

void ROAInstaller::start()
{
    // Show initial page
    welcome->show();

    // Set current page
    curPage = 0;
}

/******************************************************************************/
/*                                                                            */
/*    Private methods                                                         */
/*                                                                            */
/******************************************************************************/

void ROAInstaller::selectPage()
{
    switch(curPage)
    {
        case 0:
            welcome->show();
            break;
        case 1:
            license->show();
            break;
        case 2:
            components->show();
            break;
        case 3:
            install->show();
            break;
        case 4:
            status->show();
            startInstallation();
            break;
        case 5:
            finish->show();
            break;
    }
}

void ROAInstaller::hidePage()
{
    switch(curPage)
    {
        case 0:
            welcome->hide();
            break;
        case 1:
            license->hide();
            break;
        case 2:
            components->hide();
            break;
        case 3:
            install->hide();
            break;
        case 4:
            status->hide();
            break;
        case 5:
            finish->hide();
            break;
    }
}

void ROAInstaller::startInstallation()
{
    // Set installation path
    installationPath = install->getInstallPath() + "/relics of annorath/";

    // Get components
    componentsSelected = components->getSelectedComponents();

    // Create all other folders - no checking here
    QDir().mkpath(installationPath + "/downloads");
    QDir().mkpath(installationPath + "/lib");
    QDir().mkpath(installationPath + "/imageformats");
    QDir().mkpath(installationPath + "/sounds");
    QDir().mkpath(installationPath + "/files/bin");
    QDir().mkpath(installationPath + "/files/data");
    QDir().mkpath(installationPath + "/files/lib");

    // Prepare downloading
    certificates.append(QSslCertificate::fromPath(":/certs/class2.pem"));
    certificates.append(QSslCertificate::fromPath(":/certs/ca.pem"));

    sslConfig.defaultConfiguration();
    sslConfig.setCaCertificates(certificates);

    request.setSslConfiguration(sslConfig);

    connect(&manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(slot_downloadFinished(QNetworkReply*)));
    connect(&manager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)),this, SLOT(slot_getSSLError(QNetworkReply*, const QList<QSslError>&)));

#ifdef Q_OS_LINUX
#ifdef __x86_64__
    request.setUrl(QUrl("https://launcher.annorath-game.com/launcher/files_linux_x86_64.txt"));
#else
    request.setUrl(QUrl("https://launcher.annorath-game.com/launcher/files_linux_x86.txt"));
#endif
#endif

#ifdef Q_OS_WIN32
#ifdef Q_OS_WIN64
    request.setUrl(QUrl("https://launcher.annorath-game.com/launcher/files_windows_x86_64.txt"));
#else
    request.setUrl(QUrl("https://launcher.annorath-game.com/launcher/files_windows_x86.txt"));
#endif
#endif

    // Start download
    manager.get(request);
}

void ROAInstaller::prepareDownload()
{
    // Open file and read it
    QFile file(installationPath + "/downloads/files.txt");

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while ( !in.atEnd() )
        {
            fileList.append(in.readLine());
        }
    }

    file.close();

    filesLeft = fileList.size();

    // Get the next file
    getNextFile();
}

void ROAInstaller::getNextFile()
{
    if(filesLeft > 0)
    {
        // Set URL and start download
#ifdef Q_OS_LINUX
#ifdef __x86_64__
        request.setUrl(QUrl("https://launcher.annorath-game.com/launcher/files_linux_x86_64/" + fileList.at(filesLeft-1)));
#else
        request.setUrl(QUrl("https://launcher.annorath-game.com/launcher/files_linux_x86/" + fileList.at(filesLeft-1)));
#endif
#endif

#ifdef Q_OS_WIN32
#ifdef Q_OS_WIN64
        request.setUrl(QUrl("https://launcher.annorath-game.com/launcher/files_windows_x86_64/" + fileList.at(filesLeft-1)));
#else
        request.setUrl(QUrl("https://launcher.annorath-game.com/launcher/files_windows_x86/" + fileList.at(filesLeft-1)));
#endif
#endif
        manager.get(request);

        // Update status
        status->setNewStatus(100/(fileList.size())*(fileList.size()-filesLeft));
        status->setNewLabelText(tr("Currently downloading: ") + fileList.at(filesLeft-1));

        filesLeft -= 1;
    }
    else
    {
        // Set status to 100
        status->setNewStatus(100);
        status->setNewLabelText("Installing additional software...");

#ifdef Q_OS_LINUX

        if(componentsSelected.at(4).toInt())
        {
            // Create menu entry
            QFile menuEntry(QDir::homePath() + "/.local/share/applications/Relics of Annorath.desktop");
            menuEntry.open(QIODevice::WriteOnly | QIODevice::Text);

            QTextStream out(&menuEntry);

            out << "[Desktop Entry]\n";
            out << "Encoding=UTF-8\n";
            out << "Version=1.0\n";
            out << "Type=Application\n";
            out << "Terminal=false\n";
            out << "Exec=\"" + installationPath + "ROALauncher.sh" + "\"\n";
            out << "Name=Relics of Annorath\n";
            out << "Icon=" + installationPath + "/roa.ico" + "\n";

            menuEntry.close();
        }

        if(componentsSelected.at(5).toInt())
        {
            // The same for the desktop - this is ugly oo
            QFile menuEntry(QDir::homePath() + "/Desktop/Relics of Annorath.desktop");
            menuEntry.open(QIODevice::WriteOnly | QIODevice::Text);

            QTextStream out(&menuEntry);

            out << "[Desktop Entry]\n";
            out << "Encoding=UTF-8\n";
            out << "Version=1.0\n";
            out << "Type=Application\n";
            out << "Terminal=false\n";
            out << "Exec=\"" + installationPath + "ROALauncher.sh" + "\"\n";
            out << "Name=Relics of Annorath\n";
            out << "Icon=" + installationPath + "/roa.ico" + "\n";

            menuEntry.close();
        }
#endif

#ifdef Q_OS_WIN32
        if(componentsSelected.at(1).toInt() == 1)
        {
            SHELLEXECUTEINFO ShExecInfo = {0};
            ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            ShExecInfo.hwnd = NULL;
            ShExecInfo.lpVerb = NULL;
            ShExecInfo.lpFile = reinterpret_cast<const WCHAR*>(QString(installationPath + "/downloads/dxwebsetup.exe").utf16());
            ShExecInfo.lpParameters = reinterpret_cast<const WCHAR*>(QString(" /q").utf16());
            ShExecInfo.lpDirectory = NULL;
            ShExecInfo.nShow = SW_HIDE;
            ShExecInfo.hInstApp = NULL;
            ShellExecuteEx(&ShExecInfo);
            WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
        }
        if(componentsSelected.at(2).toInt() == 1)
        {
            SHELLEXECUTEINFO ShExecInfo = {0};
            ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            ShExecInfo.hwnd = NULL;
            ShExecInfo.lpVerb = NULL;
            ShExecInfo.lpFile = reinterpret_cast<const WCHAR*>(QString(installationPath + "/downloads/vcredist_x64.exe").utf16());
            ShExecInfo.lpParameters = reinterpret_cast<const WCHAR*>(QString(" /q").utf16());
            ShExecInfo.lpDirectory = NULL;
            ShExecInfo.nShow = SW_HIDE;
            ShExecInfo.hInstApp = NULL;
            ShellExecuteEx(&ShExecInfo);
            WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
        }
        if(componentsSelected.at(3).toInt() == 1)
        {
            SHELLEXECUTEINFO ShExecInfo = {0};
            ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            ShExecInfo.hwnd = NULL;
            ShExecInfo.lpVerb = NULL;
            ShExecInfo.lpFile = reinterpret_cast<const WCHAR*>(QString(installationPath + "/downloads/oalinst.exe").utf16());
            ShExecInfo.lpParameters = reinterpret_cast<const WCHAR*>(QString(" /silent").utf16());
            ShExecInfo.lpDirectory = NULL;
            ShExecInfo.nShow = SW_HIDE;
            ShExecInfo.hInstApp = NULL;
            ShellExecuteEx(&ShExecInfo);
            WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
        }
#endif

        // Set last page
        slot_nextPageTriggered();
    }
}

#ifdef Q_OS_WIN32
void ROAInstaller::createWindowsShortcuts()
{
    // Get COM
    CoInitialize(NULL);

    // File system directory that contains the directories for the
    // common program groups that appear on the Start menu for all users.
    LPITEMIDLIST group;

    // Get a pointer to an item ID list that represents the path of a special folder.
    HRESULT result = SHGetSpecialFolderLocation(NULL, SpecialFolderName, &group);

    // Convert the item ID list's binary representation into a file system path.
    char SpecialFolderPath[_MAX_PATH-1];

    // SpecialFolderPath is now Start Menu -> Programs path.
    BOOL f = SHGetPathFromIDList(group, SpecialFolderPath);

    // Allocate a pointer to an IMalloc interface
    LPMALLOC pMalloc;

    // Get the address of our task allocator's IMalloc interface
    result = SHGetMalloc(&pMalloc);

    // Free the item ID list allocated by SHGetSpecialFolderLocation
    pMalloc->Free(group);

    // Free our task allocator
    pMalloc->Release();

    if (SpecialFolderName == CSIDL_COMMON_PROGRAMS)
    {
        char MyDirectory[_MAX_PATH-1];

        // SpecialFolderPath = Start Menu -> Programs or Desktop path.
        strcpy(MyDirectory, SpecialFolderPath);

        // MyDirectory = Start Menu -> Programs -> My Program or Desktop Path -> My Program
        strcat(MyDirectory, "My Program");

        // Create Directory as Start Menu -> Programs -> My Program or Desktop Path -> My Program
        CreateDirectory(MyDirectory, NULL);

        char szTemp[_MAX_PATH-1];
        strcpy(szTemp, MyDirectory);
        strcat(szTemp, "");
        strcat(szTemp, LinkName );
        strcpy(LinkName, szTemp);
        strcat(LinkName, ".lnk");       // LinkName should have .lnk extension."
    }
    else
    {
        char szTemp[_MAX_PATH-1];
        strcpy(szTemp, SpecialFolderPath);
        strcat(szTemp, "");
        strcat(szTemp, LinkName );
        strcpy(LinkName, szTemp);
        strcat(LinkName, ".lnk");       // LinkName should have .lnk extension."
    }

    HRESULT hres = NULL;
    IShellLink* psl = NULL;

    // Get a pointer to the IShellLink interface.
    hres = CoCreateInstance(CLSID_ShellLink,
                            NULL,
                            CLSCTX_INPROC_SERVER,
                            IID_IShellLink,
                            reinterpret_cast<void**>(&psl));

    if (SUCCEEDED(hres))
    {
        IPersistFile* ppf = NULL;
        psl->SetPath(FilePath); // Set the path to the shortcut target

        char buf[_MAX_PATH-1];
        ::GetCurrentDirectory(_MAX_PATH, buf);
        strcat(buf,"IconDLL.dll");
        psl->SetIconLocation(buf, 0);

        // Query IShellLink for the IPersistFile interface for saving
        // the shortcut in persistent storage.
        hres = psl->QueryInterface(IID_IPersistFile, reinterpret_cast<void**>(&ppf));

        if (SUCCEEDED(hres))
        {
            WCHAR WideCharacterBuffer[_MAX_PATH-1];

            // Ensure that the string is ANSI.
            MultiByteToWideChar(CP_ACP, 0, LinkName, -1, WideCharacterBuffer, MAX_PATH);

            // Save the link by calling IPersistFile::Save.
            hres = ppf->Save(WideCharacterBuffer, TRUE);
            ppf->Release();
        }
        psl->Release();
    }
}
#endif

/******************************************************************************/
/*                                                                            */
/*    Slots                                                                   */
/*                                                                            */
/******************************************************************************/

void ROAInstaller::slot_nextPageTriggered()
{
    hidePage();
    curPage += 1;
    selectPage();
}

void ROAInstaller::slot_previousPageTriggered()
{
    hidePage();
    curPage -= 1;
    selectPage();
}


void ROAInstaller::slot_downloadFinished(QNetworkReply *reply)
{
    QString fileName;

    switch(downloadPhase)
    {
        case 0:
            fileName = "/downloads/files.txt";
            break;
        case 1:
            fileName = "/" + fileList.at(filesLeft);
            break;
    }

    // Open the file to write to
    QFile file(installationPath + fileName);
    file.open(QIODevice::WriteOnly);

    // Open a stream to write into the file
    QDataStream stream(&file);

    // Get the size of the torrent
    int size = reply->size();

    // Get the data of the torrent
    QByteArray temp = reply->readAll();

    // Write the file
    stream.writeRawData(temp, size);

    // Set exe permissions
    file.setPermissions(QFile::ExeUser | QFile::ExeGroup | QFile::ExeOwner | QFile::WriteUser | QFile::WriteGroup | QFile::WriteOwner | QFile::ReadGroup | QFile::ReadOwner | QFile::ReadUser);

    // Close the file
    file.close();

    // If phase 0 take future steps
    switch(downloadPhase)
    {
        case 0:
            prepareDownload();
            downloadPhase = 1;
            break;
        case 1:
            getNextFile();
            break;
    }
}

void ROAInstaller::slot_getSSLError(QNetworkReply* reply, const QList<QSslError> &errors)
{
    QSslError sslError = errors.first();

    if(sslError.error() == 11 )
    {
        //reply->ignoreSslErrors();
        status->setNewLabelText(reply->errorString());
    }
}
