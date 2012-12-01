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
 * \file    	roapagecomponents.cpp
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
#include "../h/roapagecomponents.h"
#include "ui_roapagecomponents.h"

/******************************************************************************/
/*                                                                            */
/*    Constructor/Deconstructor                                               */
/*                                                                            */
/******************************************************************************/

ROAPageComponents::ROAPageComponents(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ROAPageComponents)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    ui->setupUi(this);

#ifdef Q_OS_LINUX
    ui->cbDX->hide();
    ui->cbMSVC->hide();
    ui->cbOAL->hide();
#endif

    // Center the whole window
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();

    this->move(center.x()-this->width()*0.5,  center.y()-this->height()*0.5);
}

ROAPageComponents::~ROAPageComponents()
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

QStringList ROAPageComponents::getSelectedComponents()
{
    // Create array
    QStringList list;

    list.append(QString::number(ui->cbLauncher->isChecked()));
    list.append(QString::number(ui->cbDX->isChecked()));
    list.append(QString::number(ui->cbMSVC->isChecked()));
    list.append(QString::number(ui->cbOAL->isChecked()));
    list.append(QString::number(ui->cbMenuEntry->isChecked()));
    list.append(QString::number(ui->cbDesktop->isChecked()));

    return list;
}

/******************************************************************************/
/*                                                                            */
/*    Slots                                                                   */
/*                                                                            */
/******************************************************************************/

void ROAPageComponents::on_qpNext_clicked()
{
    emit nextPage();
}

void ROAPageComponents::on_qpBack_clicked()
{
    emit previousPage();
}

void ROAPageComponents::on_qbCancel_clicked()
{
    QApplication::exit();
}
