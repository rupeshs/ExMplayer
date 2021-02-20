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

#include "updatecheckdlg.h"
#include "ui_updatecheckdlg.h"

updateCheckDlg::updateCheckDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateCheckDlg)
{
    ui->setupUi(this);
    updChecker=new UpdateCheck();
    updChecker->Check();
    QObject::connect(updChecker,SIGNAL(gotUpdateChkResponse(bool,QString,QString)),this,SLOT(gotUpdateChkResponse(bool,QString,QString)));
    QObject::connect(updChecker,SIGNAL(NetworkError(QString)),this,SLOT(NetworkError(QString)));

    pgIndicator=new QProgressIndicator(ui->labelPg);
    pgIndicator->setColor(QColor(qRgb(10,100,10) ));
    pgIndicator->show();
    pgIndicator->startAnimation();
    ui->labelCurVersion->setText("Current version :v" +Version::stable());
    ui->labelOk->setVisible(false);
}

updateCheckDlg::~updateCheckDlg()
{
    delete ui;
}
void updateCheckDlg::gotUpdateChkResponse(bool updAvail,QString version,QString releaseNotes)
{

    pgIndicator->stopAnimation();
    pgIndicator->hide();
    if (updAvail)
       {this->show();
        ui->labelVersionFound->setText("<b>Update available,Version "+version+"<\b>");
        QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
         animation->setDuration(500);
         animation->setEndValue(QSize(371,263));
         animation->start();
       }
    else
       {
        ui->labelOk->setVisible(true);
        ui->labelVersionFound->setText("<font color=\"green\"><b>ExMplayer is up to date</b></font>");
       }

    QStringList sList=releaseNotes.split(",");
    QString var;

    foreach (var, sList) {
        new QListWidgetItem(var, ui->listWidgetRel);
    }

}
void updateCheckDlg::NetworkError(QString strErr)
{
    pgIndicator->stopAnimation();
    pgIndicator->hide();
    ui->labelVersionFound->setText("<font color=\"red\"><b>Error..."+strErr+"</b></font>");

}
