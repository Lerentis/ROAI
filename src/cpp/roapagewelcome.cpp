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

/******************************************************************************/
/*                                                                            */
/*    Others includes                                                         */
/*                                                                            */
/******************************************************************************/
#include "../h/roapagewelcome.h"
#include "ui_roapagewelcome.h"

/******************************************************************************/
/*                                                                            */
/*    Constructor/Deconstructor                                               */
/*                                                                            */
/******************************************************************************/

ROAPageWelcome::ROAPageWelcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ROAPageWelcome)
{
    translator = new QTranslator();

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    ui->setupUi(this);

    ui->qlDesc->setText(tr("The wizard installs the Relics of Annorath Alpha with all dependencies.\n\n\n"
                          "Please select your language to proceed:"));

    ui->qcLanguage->setStyleSheet("QComboBox QAbstractItemView { background-color: lightgray; }"
                                  "QComboBox { border-width:1px;"
                                  "border-style:solid;"
                                  "border-radius:4px;"
                                  "border-color: rgba(0, 0, 0, 120);"
                                  "selection-background-color: #b79155; }");

    // Center the whole window
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();

    this->move(center.x()-this->width()*0.5,  center.y()-this->height()*0.5);
}

ROAPageWelcome::~ROAPageWelcome()
{
    delete ui;
}

/******************************************************************************/
/*                                                                            */
/*    Public methods                                                          */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*    Private methods                                                         */
/*                                                                            */
/******************************************************************************/

void ROAPageWelcome::changeEvent(QEvent *_event)
{
    if (_event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
    else
    {
        QWidget::changeEvent(_event);
    }
}

/******************************************************************************/
/*                                                                            */
/*    Slots                                                                   */
/*                                                                            */
/******************************************************************************/

void ROAPageWelcome::on_qpNext_clicked()
{
    emit nextPage();
}

void ROAPageWelcome::on_qcLanguage_currentIndexChanged(int _index)
{
    // Remove translation
    //QApplication::removeTranslator(translator);

    // Load new translation
    QString trans;

    switch(_index)
    {
        case 0:
            trans = "roai_eng";
            break;
        case 1:
            trans = "roai_ger";
            break;
        case 2:
            trans = "roai_fra";
            break;
        case 3:
            trans = "roai_spa";
            break;
        case 4:
            trans = "roai_ita";
            break;
        default:
            trans = "roai_eng";
    }

   // translator->load(trans,":/translation/");

    // Retranslate
    //QApplication::installTranslator(translator);
}

void ROAPageWelcome::on_qbCancel_clicked()
{
    QApplication::exit();
}
