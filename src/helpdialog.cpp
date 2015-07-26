/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2015 Rupesh Sreeraman

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

#include "helpdialog.h"
#include "ui_helpdialog.h"
#include "rphmpfehelp.h"

helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{
     ui->setupUi(this);

     ui->listWidgetContent->hide();
     this->setWindowFlags(Qt::Window);

}

helpDialog::~helpDialog()
{
    delete ui;
}

void helpDialog::changeEvent(QEvent *e)
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
void helpDialog::setHelpText(QString str)
{
   ui->textEditHelp->setText(str);
}

void helpDialog::on_listWidgetContent_currentRowChanged(int currentRow)
{
    rphMPFEhelp hlp;
    switch(currentRow)
    {
     case 0:ui->textEditHelp->setText(hlp.playerhlpstrEx);
            break;
    case 1:ui->textEditHelp->setText(hlp.audiohlpstr);
           break;
    case 2:ui->textEditHelp->setText(hlp.videohlpstr);
           break;
    case 3:ui->textEditHelp->setText(hlp.subtitlehlpstr);
           break;
    case 4:ui->textEditHelp->setText(hlp.internethlpstr);
           break;
    case 5:ui->textEditHelp->setText(hlp.keyboardhlpstr);
           break;
    case 6:ui->textEditHelp->setText(hlp.mousehlpstr);
           break;
    }

}
void  helpDialog::showContent()
{
    ui->listWidgetContent->show();
    ui->listWidgetContent->setCurrentRow(0);
    this->resize(850,500);
}
void  helpDialog::showcutterHelp( QString tex)
{

    ui->textEditHelp->setText(tex);

}

