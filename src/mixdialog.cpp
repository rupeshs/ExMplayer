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

#include "mixdialog.h"
#include "ui_mixdialog.h"

mixDialog::mixDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mixDialog)
{
    ui->setupUi(this);
}

mixDialog::~mixDialog()
{
    delete ui;
}

void mixDialog::changeEvent(QEvent *e)
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

 void mixDialog::mix(QString cfn,QString afn,QString  dir)
 {
     if (!dir.isEmpty())
     {
       ffProcess = new QProcess(this);
       QObject::connect(ffProcess,SIGNAL(finished(int)),this,SLOT(completed(int)));
      
       coreTimer = new QTimer(this);
       QObject::connect(ffProcess,SIGNAL(started()),coreTimer ,SLOT(start()));
       QObject::connect(coreTimer, SIGNAL(timeout()), this,SLOT(updateStatus()));
       coreTimer->setInterval(1);
       ui->progressBar->setMaximum(0);
       ui->progressBar->setMaximum(0);
       ui->progressBar->setVisible(true);

       QStringList arguments;
       QFileInfo fi(cfn);
       filepath=dir+fi.fileName();
       cfile=new QFileInfo(filepath);
       arguments<<"-i"<<cfn<<"-i"<<afn<<"-c"<<"copy"<<"-map"<<"0:0"<<"-map"<<"1:0"<<"-y"<<filepath;
       qDebug()<<arguments;
#ifdef Q_OS_WIN
            ffProcess->start(qApp->applicationDirPath()+"/ffmpeg.exe", arguments);
#endif
#ifdef Q_OS_LINUX
             ffProcess->start(qApp->applicationDirPath()+"/ffmpeg", arguments);
#endif



   }

 }
void mixDialog::completed(int ec)
{

ui->progressBar->setMaximum(100);
ui->progressBar->setValue(0);
ui->progressBar->setVisible(false);
coreTimer->stop();

ui->labelst->setText("Completed.");
if (cfile->size()==0)
{ui->pushButton->setEnabled(false);
 ui->labelst->setText("Failed.");
 QMessageBox::critical(this,qApp->applicationName(),tr("Error while saving the file!"),QMessageBox::Ok,QMessageBox::Cancel);

}

}
void mixDialog::updateStatus()
{//qDebug()<<cfile->size()l
    //qDebug()<<cfile->size();
 //ui->labelst->setText(QString::number(cfile->size()/1024)+" Kbytes saved.");
ui->labelst->setText("Saving...");
}


void mixDialog::on_pushButton_clicked()
{if(ffProcess)
   ffProcess->close();
}
void mixDialog::closeEvent(QCloseEvent * e )
{if(ffProcess)
   ffProcess->close();
}
 void mixDialog::readffmpegoutput()
 {
     QString str= ffProcess->readAllStandardOutput();
     qDebug() <<str;
 }

void mixDialog::on_pushButtonof_clicked()
{
    emit  showfile(QString("/select,"),filepath);

}
