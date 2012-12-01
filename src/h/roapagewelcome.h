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
 * \file    	roapagewelcome.h
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

#ifndef ROAPAGEWELCOME_H
#define ROAPAGEWELCOME_H

/******************************************************************************/
/*                                                                            */
/*    Qt includes                                                             */
/*                                                                            */
/******************************************************************************/
#include <QWidget>
#include <QTranslator>
#include <QApplication>
#include <QDesktopWidget>

namespace Ui
{
    class ROAPageWelcome;
}

/**
 * \brief The ROAPageWelcome class to show the welcome page
 */
class ROAPageWelcome : public QWidget
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
         * \brief Constuctor
         * \param The parent
         */
        explicit ROAPageWelcome(QWidget *parent = 0);

        /**
         * \brief Deconstructor
         */
        ~ROAPageWelcome();

    private:

        /******************************************************************************/
        /*                                                                            */
        /*    Members                                                                 */
        /*                                                                            */
        /******************************************************************************/

        /**
         * \brief The ui
         */
        Ui::ROAPageWelcome *ui;

        /**
         * \brief The translator
         */
        QTranslator *translator;

        /******************************************************************************/
        /*                                                                            */
        /*    Methods                                                                 */
        /*                                                                            */
        /******************************************************************************/
        void changeEvent(QEvent*);

    private slots:

        /**
         * \brief Shows next page
         */
        void on_qpNext_clicked();

        /**
         * \brief Changes the language to the selected one
         * \param _index The language index
         */
        void on_qcLanguage_currentIndexChanged(int _index);

        /**
         * \brief Cancels the installation
         */
        void on_qbCancel_clicked();

    signals:

        /**
         * \brief Signal for next page
         */
        void nextPage();
};

#endif // ROAPAGEWELCOME_H
