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
#include "cutterdialog.h"
#include "ui_cutterdialog.h"
#include <QDebug>
#include "rphfile.h"
#include <paths.h>

cutterDialog::cutterDialog(QWidget *parent, mplayerfe *mpf) :
    QDialog(parent),
    ui(new Ui::cutterDialog)
{

    ui->setupUi(this);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonCut->setEnabled(false);
    mp=mpf;
    startPos=0;
    stopPos=0;
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(false);
    ui->pushButtonof->setEnabled(false);
    ui->pushButtonclose->setEnabled(false);
    ui->pushButtonpre->setEnabled(false);
    ui->toolButtonStop->setEnabled(false);
    ui->seek->setEnabled(false);

}

cutterDialog::~cutterDialog()
{
    delete ui;
}

void cutterDialog::changeEvent(QEvent *e)
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

void cutterDialog::on_pushButtonStart_clicked()
{if (mp)
    {ui->lineEditStart->setText(mp->tcurpos().toString());
    startPos=mp->curpos();
    }
  if (!ui->lineEditStart->text().isEmpty())
    {ui->pushButtonStop->setEnabled(true);
     ui->pushButtonStart->setEnabled(false);
    }
}

void cutterDialog::on_pushButtonStop_clicked()
{if (mp) 
    {ui->lineEditStop->setText(mp->tcurpos().toString());
        stopPos=mp->curpos();
        QTime t;
        t = t.addSecs(stopPos-startPos);
        ui->lineEditLen->setText( t.toString());
    }

    if(stopPos-startPos>0)
    {
        ui->pushButtonStart->setEnabled(false);
        ui->pushButtonStop->setEnabled(false);
        ui->pushButtonCut->setEnabled(true);
        ui->pushButtonpre->setEnabled(true);
    }


}

void cutterDialog::on_pushButtonReset_clicked()
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->lineEditStart->clear();
    ui->lineEditStop->clear();
    ui->pushButtonCut->setEnabled(false);
    startPos=0;
    stopPos=0;
    if( mpp)
        mpp->stop();

}

void cutterDialog::on_pushButtonCut_clicked()
{
    if(stopPos-startPos>0)
    {QString dir = rphFile::getDir(this,"Open a Directory for output:","");


        if (!dir.isEmpty())
        {
            ffProcess = new QProcess(this);
            QObject::connect(ffProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readffmpegoutput()));
            QObject::connect(ffProcess,SIGNAL(finished(int)),this,SLOT(completed(int)));


            mp->stop();
            if (mpp)
                mpp->stop();

            coreTimer = new QTimer(this);

            QObject::connect(coreTimer, SIGNAL(timeout()), this,SLOT(updateStatus()));
            coreTimer->setInterval(1);
            QObject::connect(ffProcess,SIGNAL(started()),coreTimer ,SLOT(start()));

            ui->progressBar->setMaximum(0);
            ui->progressBar->setVisible(true);
            ui->pushButtonclose->setEnabled(true);
            QStringList arguments;
            QFileInfo fi(shortPathName(mp->filepath()));

            cfile=new  QFile(dir+"strip_"+fi.baseName()+"."+fi.suffix());
            filepath=shortPathName(dir+"strip_"+fi.baseName()+"."+fi.suffix());
            arguments<<"-ss"<<QString::number(startPos)<<"-t"<<QString::number(stopPos-startPos)<<"-i"<<shortPathName(mp->filepath())<<"-c"<<"copy"<<"-y"<<dir+"strip_"+fi.baseName()+"."+fi.suffix();
            qDebug()<< arguments;
#ifdef Q_OS_WIN
            ffProcess->start(qApp->applicationDirPath()+"/ffmpeg.exe", arguments);
#endif
#ifdef Q_OS_LINUX
             ffProcess->start(Paths::sharePath()+"/ffmpeg", arguments);
#endif
            \
            ui->pushButtonpre->setEnabled(false);

            //coreTimer->start();
        }
    }
}
void cutterDialog::readffmpegoutput()
{
    QString str= ffProcess->readAllStandardOutput();
    //qDebug() <<str;

}

void cutterDialog::on_pushButton_2_clicked()
{
    this->close();
    if (mpp)
        mpp->stop();
}
void cutterDialog::completed(int val)
{    coreTimer->stop();
    //qDebug()<<val;
    ui->pushButtonof->setEnabled(true);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(false);
    if (cfile->size()==0){

        QMessageBox::critical(this,qApp->applicationName(),tr("Error while saving the file!"),QMessageBox::Ok,QMessageBox::Cancel);

    }

}
void cutterDialog::updateStatus()
{//qDebug()<<"fafsf";
    float  val;

    QString tex;
    val=cfile->size();

    if (val<1024)
        tex=QString::number(val)+" bytes saved.";
    else if (val>1024&&val<1024*1024)
        tex=QString::number(val/1024,'f',2)+" Kbytes saved.";
    else if (val>1024*1024)
        tex=QString::number(val/(1024*1024),'f',2)+" Mbytes saved.";

    ui->labelst->setText(tex);
}






void cutterDialog::on_pushButtonclose_clicked()
{

    ffProcess->close();
    ui->pushButtonclose->setEnabled(false);

}

void cutterDialog::on_pushButtonStop_pressed()
{

}

void cutterDialog::on_pushButtonof_clicked()
{
    //qDebug()<<filepath;
    //winExplorer(,filepath);
    emit  showfile(QString("/select,"),filepath);

}


void cutterDialog::on_pushButtonpre_clicked()
{
    mp->stop();
    if (mpp)
    {
        mpp->stop();
    }
    mpp=new mplayerfe(this,this);
    mpp->setVideoWinid((long int)ui->vid->winId());
    mpp->setColorkey(QColor(1,0,0).toRgb().value());

    ui->toolButtonStop->setEnabled(true);
    cTimer = new QTimer(this);
    cTimer->setInterval(500);
    QObject::connect(cTimer, SIGNAL(timeout()), this,SLOT(updateSeekbar()));
    cTimer->start();
    ui->seek->setEnabled(true);

    mpp->setStartStop(startPos,(stopPos-startPos));

    mpp->play(mp->filepath(),mp->getVolume());

}

void cutterDialog::on_toolButtonStop_clicked()
{if( mpp)
        mpp->stop();
}
void cutterDialog::closeEvent ( QCloseEvent * e )
{
    if( mpp)
        mpp->stop();

}
void cutterDialog::updateSeekbar()
{if(mpp)
    {

        ui->seek->setValue(((mpp->curpos()-startPos)/(stopPos-startPos))*100);

    }
}

void cutterDialog::on_seek_actionTriggered(int action)
{
    if (mpp)
    {this->cTimer->stop();
        mpp->seek(ui->seek->value());
        this->cTimer->start();
    }
}

void cutterDialog::on_pushButtonhelp_clicked()
{
    mainhlpDlg=new helpDialog(this);
    rphMPFEhelp mph;
    mainhlpDlg->showcutterHelp(mph.helpcutterstr);
    mainhlpDlg->show();

}

// This function has been copied (and modified a little bit) from Scribus (program under GPL license):
// http://docs.scribus.net/devel/util_8cpp-source.html#l00112
QString cutterDialog::shortPathName(QString long_path) {
#ifdef Q_OS_WIN
    if ((QSysInfo::WindowsVersion >= QSysInfo::WV_NT) && (QFile::exists(long_path))) {
        QString short_path = long_path;

        const int max_path = 4096;
        WCHAR shortName[max_path];

        QString nativePath = QDir::convertSeparators(long_path);
        int ret = GetShortPathNameW((LPCWSTR) nativePath.utf16(), shortName, max_path);
        if (ret != ERROR_INVALID_PARAMETER && ret < MAX_PATH)
            short_path = QString::fromUtf16((const ushort*) shortName);

        return short_path;
    } else {
        return long_path;
    }
#endif
     return long_path;

}

