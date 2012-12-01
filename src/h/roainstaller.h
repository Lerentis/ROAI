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
 * \file    	roainstaller.h
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

#ifndef ROAINSTALLER_H
#define ROAINSTALLER_H

/******************************************************************************/
/*                                                                            */
/*    Qt includes                                                             */
/*                                                                            */
/******************************************************************************/
#include <QObject>
#include <QSettings>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSslError>

/******************************************************************************/
/*                                                                            */
/*    Others includes                                                         */
/*                                                                            */
/******************************************************************************/
#ifdef Q_OS_WIN32
#include <Windows.h>
#endif

#include "../h/roapagecomponents.h"
#include "../h/roapagefinish.h"
#include "../h/roapageinstall.h"
#include "../h/roapagelicense.h"
#include "../h/roapagestatus.h"
#include "../h/roapagewelcome.h"

/**
 * \brief Installer logic for the Relics of Annorath Launcher and game files
 */
class ROAInstaller : public QObject
{
        Q_OBJECT
    public:

        /******************************************************************************/
        /*                                                                            */
        /*    Members                                                                 */
        /*                                                                            */
        /******************************************************************************/

        /******************************************************************************/
        /*                                                                            */
        /*    Methods                                                                 */
        /*                                                                            */
        /******************************************************************************/

        /**
         * \brief Constructor
         * \param parent The parent
         */
        explicit ROAInstaller(QObject *parent = 0);

        /**
         * \brief Deconstuctor
         */
        ~ROAInstaller();

        /**
         * \brief Start the installation process
         */
        void start();

    private:

        /******************************************************************************/
        /*                                                                            */
        /*    Members                                                                 */
        /*                                                                            */
        /******************************************************************************/

        /**
         * \brief The components page
         */
        ROAPageComponents *components;

        /**
         * \brief The finish page
         */
        ROAPageFinish *finish;

        /**
         * \brief The install page
         */
        ROAPageInstall *install;

        /**
         * \brief The license/nda page
         */
        ROAPageLicense *license;

        /**
         * \brief The status page
         */
        ROAPageStatus *status;

        /**
         * \brief The welcome page
         */
        ROAPageWelcome *welcome;

        /**
         * \brief Network manager for downloading files
         */
        QNetworkAccessManager manager;

        /**
         * \brief SSL config for custom CAs
         */
        QSslConfiguration sslConfig;

        /**
         * \brief Custom CAs
         */
        QList<QSslCertificate> certificates;

        /**
         * \brief Request for downloading
         */
        QNetworkRequest request;

        /**
         * \brief Installation path
         */
        QString installationPath;

        /**
         * \brief File list to download
         */
        QStringList fileList;

        /**
         * \brief List of selected components to install
         */
        QStringList componentsSelected;

        /**
         * \brief The user settings
         */
        QSettings *userSettings;

        /**
         * \brief Current page index
         */
        int curPage;

        /**
         * \brief Current download phase (0 init, 1 file download)
         */
        int downloadPhase;

        /**
         * \brief Files left to download
         */
        int filesLeft;

        /******************************************************************************/
        /*                                                                            */
        /*    Methods                                                                 */
        /*                                                                            */
        /******************************************************************************/

        /**
         * \brief Display the next page
         */
        void nextPage();

        /**
         * \brief Select the page to display
         */
        void selectPage();

        /**
         * \brief Hide the old, obosolet page
         */
        void hidePage();

        /**
         * \brief Start installation process
         */
        void startInstallation();

        /**
         * \brief Prepare the download
         */
        void prepareDownload();

        /**
         * \brief Download the next file in queue
         */
        void getNextFile();

#ifdef Q_OS_WIN32
        /**
         * \brief Create windows shortcuts (a bad joke of an api abuse!)
         */
        void createWindowsShortcuts();
#endif

    private slots:

        /**
         * \brief Select next page
         */
        void slot_nextPageTriggered();

        /**
         * \brief Select previous page
         */
        void slot_previousPageTriggered();

        /**
         * \brief Saves the file when download finished
         * @param reply The data of the downloaded file
         */
        void slot_downloadFinished(QNetworkReply *reply);

        /**
         * \brief Checks for SSL errors
         * \param reply The reply
         * \param errors Error list
         */
        void slot_getSSLError(QNetworkReply* reply, const QList<QSslError> &errors);

};

#endif // ROAINSTALLER_H
