/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2013 Rupesh Sreeraman

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QFileInfo>
#include <QDateTime>
#include <QPropertyAnimation>
#include <version.h>
aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
      ui->setupUi(this);
      QFileInfo fi(qApp->applicationFilePath());
      QDateTime dt=fi.created();
      ui->labelDate->setText(QString("Build on "+dt.toString()));
      ui->labelVersion->setText("ExMplayer v"+Version::stable());
}

aboutDialog::~aboutDialog()
{
    delete ui;
}

void aboutDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void aboutDialog::on_pushButton_clicked()
{
    this->close();
}
