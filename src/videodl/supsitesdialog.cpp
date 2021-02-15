/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2021 Rupesh Sreeraman

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

#include "supsitesdialog.h"
#include "ui_supsitesdialog.h"

SupSitesDialog::SupSitesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supSitesDialog)
{
    ui->setupUi(this);
    bkCount=0;
    ui->listWidget->clear();
}

SupSitesDialog::~SupSitesDialog()
{
    delete ui;
}
void SupSitesDialog::addSite(QString serviceName)
{
    QListWidgetItem* pItem =new QListWidgetItem(serviceName);

    if (serviceName.toUpper().contains("BROKEN"))
    {bkCount++;
        pItem->setForeground(Qt::white);
        pItem->setBackground(Qt::red);
           ui->listWidget->addItem(pItem);
    }
    else
    {
        ui->listWidget->addItem(pItem);
    }

    ui->labelSiteCount->setText("Working services:"+QString::number(ui->listWidget->count())+"<br><font color=\"red\">Broken:" +QString::number(bkCount)+"</font>");
}

void SupSitesDialog::on_buttonBox_accepted()
{
    close();
}
void SupSitesDialog::closeEvent ( QCloseEvent * event )
{
    event->ignore();
    qDebug("close");
    event->accept();

}
