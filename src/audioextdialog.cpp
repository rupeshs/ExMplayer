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
#include "audioextdialog.h"
#include "ui_audioextdialog.h"
#include "rphfile.h"
#include <QDesktopServices>
#include "playerwindow.h"

audioextDialog::audioextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::audioextDialog)
{
    ui->setupUi(this);
    ui->pex->setEnabled(false);
    ui->pushButton_2->setDisabled(true);
    ui->pushButtonof->setDisabled(true);

}

audioextDialog::~audioextDialog()
{
    delete ui;
}

void audioextDialog::changeEvent(QEvent *e)
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
  void audioextDialog::ExtractAudio()
  {

   //ffProcess = new QProcess(this);
   //QObject::connect(ffProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readffmpegoutput()));

  }

void audioextDialog::on_pushButton_clicked()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName;
    QString filter =getFilter();
    fileName = QFileDialog::getOpenFileName(this,
                                             tr("Open a video file..."),
                                             "",
                                             filter,
                                             &selectedFilter,
                                             options);


    if (!fileName.isEmpty())
      { ui->lineEdit->setText(fileName);
        ui->pex->setEnabled(true);
        cfn=fileName;
      }
}

void audioextDialog::on_pex_clicked()
{
    QString dir = rphFile::getDir(this,"Open a Directory for output:","");

    if (!dir.isEmpty())
     {
        QStringList arguments;

        QString filepath;
        cfn=fileFilters::shortPathName(cfn);
        QFileInfo fi(cfn);

        filepath=dir+fi.fileName()+"_Audio.wav";
        cfile=new QFileInfo(filepath);
        coreTimer = new QTimer(this);
        QObject::connect(coreTimer, SIGNAL(timeout()), this,SLOT(updateStatus()));
        coreTimer->setInterval(1);

        ffProcess = new QProcess(this);

        QObject::connect(ffProcess,SIGNAL(started()),coreTimer ,SLOT(start()));
        QObject::connect(ffProcess,SIGNAL(finished(int)),this,SLOT(completed(int)));

        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(0);



      // QObject::connect(ffProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readffmpegoutput()));

      // arguments<<"-i"<<cfn<<"-ab"<<QString::number(128000)<<"-ac"<<QString::number(2)<<"-ar"<<QString::number(44100)<<"-y"<<filepath;
        arguments<<"-i"<<cfn<<"-y"<<filepath;

#ifdef Q_OS_WIN
            ffProcess->start(qApp->applicationDirPath()+"/ffmpeg.exe", arguments);
#endif
#ifdef Q_OS_LINUX
             ffProcess->start(qApp->applicationDirPath()+"/ffmpeg", arguments);
#endif

//coreTimer->start();
   }
}

 QString audioextDialog::getFilter()
 {

 QString fpl;
 QStringList faul;
 QString fau;
 QString mul;
 faul <<"*.wav"
      <<"*.ac3"
      <<"*.flac"
      <<"*.mka"
      <<"*.mp3"
      <<"*.m4a"
      <<"*.aac"
      <<"*.mpc"
      <<"*.ogg"
      <<"*.oga"
      <<"*.ra"
      <<"*.wma"
      <<"*.spx"
      <<"*.mmf"
      <<"*.amr"
      <<"*.ape";
 for (int i=0;i<faul.count();i++)
 {if (i==faul.count())
     fau+=faul.at(i);
  else
     fau+=faul.at(i)+" ";

    mul+=faul.at(i)+" ";
 }
  fau.prepend("Audio files (");
  fau.append(");;");
  QStringList fvil;
  QString fvi;
  fvil     <<"*.wmv"
           <<"*.3gp"
           <<"*.asf"
           <<"*.avi"
           <<"*.dat"
           <<"*.dv"
           <<"*.divx"
           <<"*.ext"
           <<"*.flv"
           <<"*.ifo"
           <<"*.mkv"
           <<"*.mpg"
           <<"*.mpe"
           <<"*.mov"
           <<"*.mp4"
           <<"*.ogm"
           <<"*.ogv"
           <<"*.rm"
           <<"*.rmvb"
           <<"*.nsv"
           <<"*.smk"
           <<"*.ts"
           <<"*.vob";
  for (int i=0;i<fvil.count();i++)
  {if (i==fvil.count())
      {fvi+=fvil.at(i);
       mul+=fvil.at(i);
   }
   else
      { fvi+=fvil.at(i)+" ";
      mul+=fvil.at(i)+" ";
  }
  }
   fvi.prepend("Video files (");
   fvi.append(");;");
   mul.prepend("Mutimedia files (");
   mul.append(");;");
   fpl="Playlists (*.m3u *.pls);;Any file (*.*)";

   return fvi;
 }
void audioextDialog::updateStatus()
{if (!ui->pushButton_2->isEnabled())
    {ui->pushButton_2->setDisabled(false);
    ui->pushButtonof->setDisabled(false);

}
ui->labelst->setText("Saving...");
}
void audioextDialog::completed(int ec)
{
    //ui->progressBar->setVisible(false);
    coreTimer->stop();

    ui->labelst->setText("Completed.");

    ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(0);
        ui->progressBar->update();

    if (cfile->size()==0)
    {ui->pushButton->setEnabled(false);
     ui->labelst->setText("Failed.");
     QMessageBox::critical(this,qApp->applicationName(),tr("Error while saving the file!"),QMessageBox::Ok,QMessageBox::Cancel);

    }

}

void audioextDialog::on_pushButtonof_clicked()
{
   // QDesktopServices::openUrl(cfile->filePath()) ;
     emit  showfile(QString("/select,"),cfile->filePath());
}

void audioextDialog::on_pushButton_2_clicked()
{
    if(ffProcess)
       ffProcess->close();
}
void audioextDialog::dropEvent(QDropEvent *event)
{  QList<QUrl> urlList;

   if (event->mimeData()->hasUrls())
      urlList = event->mimeData()->urls();

    for (int i = 0; i < urlList.size() && i < 32; ++i) {
       QString url = urlList.at(i).path();
       url=url.right(url.length()-1);

       QFileInfo fi(url);
       if(fi.isFile())
        {
           //myplaylist->addFile(url);
           ui->lineEdit->setText(url);
           ui->pex->setEnabled(true);
           cfn=url;
        }

    }
    event->acceptProposedAction();
}
void audioextDialog::dragEnterEvent(QDragEnterEvent *event)
{
if (event->mimeData()->hasUrls())
     event->acceptProposedAction();

}

void audioextDialog::dragMoveEvent(QDragMoveEvent *event)
    {
        event->acceptProposedAction();

    }
