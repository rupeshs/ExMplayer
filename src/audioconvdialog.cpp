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

#include "audioconvdialog.h"
#include "ui_audioconvdialog.h"
#include "QFileDialog.h"
#include "filefilters.h"
#include "rphfile.h"
#include <QDesktopServices>
#include <QMessageBox>
#include <QDropEvent>
audioconvDialog::audioconvDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::audioconvDialog)
{
    ui->setupUi(this);
    ui->btnConv->setEnabled(false);
    ui->pushButton_2->setDisabled(true);
    ui->pushButtonof->setDisabled(true);
    extension = new QWidget(this);

    QObject::connect(ui->detailsPushButton, SIGNAL(toggled(bool)), extension, SLOT(setVisible(bool)));
    QObject::connect(ui->detailsPushButton, SIGNAL(toggled(bool)), this, SLOT(toggleExtension(bool)));

    QVBoxLayout *extensionLayout = new QVBoxLayout;
    extensionLayout->setMargin(0);


    extensionLayout->addWidget(ui->groupBox_2);
    extension->setLayout(extensionLayout);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    //mainLayout->setMargin(30);
    mainLayout->setVerticalSpacing(30);

    mainLayout->addWidget(ui->groupBox, 0, 0);
    mainLayout->addWidget(ui->btnConv, 0, 1);
    mainLayout->addWidget(ui->labfmt,2,0);
    mainLayout->addWidget(ui->detailsPushButton,2,1);
    mainLayout->addWidget(extension,3,0);

    setLayout(mainLayout);




    extension->hide();
    ui->comboBoxAfmts->setCurrentIndex(7);

}

audioconvDialog::~audioconvDialog()
{
    delete ui;
}

void audioconvDialog::on_comboBox_currentIndexChanged(QString val )
{

}

void audioconvDialog::on_comboBox_currentIndexChanged(int index)
{


}

void audioconvDialog::on_comboBoxCh_currentIndexChanged(int index)
{
    if (ui->comboBoxAfmts->currentText()=="wav")
    {
        ui->comboBoxBr->clear();
        //qDebug()<<ui->comboBoxSr->lineEdit()->text();
        long re=(ui->comboBoxSr->currentText().toLong()*ui->comboBoxCh->currentText().toLong()*16)/1000;
        ui->comboBoxBr->insertItem(0,QString::number(re));
    }
}

void audioconvDialog::on_comboBoxAfmts_currentIndexChanged(int index)
{

}

void audioconvDialog::on_comboBoxSr_currentIndexChanged(int index)
{
    if (ui->comboBoxAfmts->currentText()=="wav")
    {
        ui->comboBoxBr->clear();
        //qDebug()<<ui->comboBoxSr->lineEdit()->text();
        long re=(ui->comboBoxSr->currentText().toLong()*ui->comboBoxCh->currentText().toLong()*16)/1000;
        ui->comboBoxBr->insertItem(0,QString::number(re));
    }
}
void audioconvDialog::toggleExtension(bool fa)
{
    qDebug()<<fa;
    if (fa)
    {
        ui->detailsPushButton->setText(" Simple<<< ");
    }
    else
    {
        ui->detailsPushButton->setText(" Advanced>>> ");

    }
}

void audioconvDialog::on_pushButton_clicked()
{  QFileDialog::Options options;
    QString selectedFilter;
    QString fileName;
    QSettings settings;

    QString filter =fileFilters::getaudiofilters();
    qDebug()<<settings.value("Playlist/OpenfileDlg","").toString();
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open a audio file..."),
                                            "",
                                            filter,
                                            &selectedFilter,
                                            options);


    if (!fileName.isEmpty())
    { ui->lineEdit->setText(fileName);
        ui->btnConv->setEnabled(true);
        cfn=fileName;
    }

}
void audioconvDialog::completed(int ec)
{
    //ui->progressBar->setVisible(false);
    coreTimer->stop();

    ui->labelst->setText("Completed.");

    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(1);
    ui->progressBar->update();

    if (cfile->size()==0)
    {ui->pushButton->setEnabled(false);
        ui->labelst->setText("Failed.");
        QMessageBox::critical(this,qApp->applicationName(),tr("Error while saving the file!"),QMessageBox::Ok,QMessageBox::Cancel);

    }

}
void audioconvDialog::updateStatus()
{if (!ui->pushButton_2->isEnabled())
    {ui->pushButton_2->setDisabled(false);
        ui->pushButtonof->setDisabled(false);
    }
    ui->labelst->setText("Saving...");
}
void audioconvDialog::on_btnConv_clicked()
{
    QString dir = rphFile::getDir(this,"Open a Directory for output:","");

    if (!dir.isEmpty())
    {

        QString filepath;
        cfn=fileFilters::shortPathName(cfn);
        QFileInfo fi(cfn);

        filepath=dir+fi.fileName()%QLatin1Literal("_Audio.")%ui->comboBoxAfmts->currentText();
        qDebug()<< fileFilters::shortPathName(filepath)+"k;k";

        cfile=new QFileInfo(filepath);
        coreTimer = new QTimer(this);
        QObject::connect(coreTimer, SIGNAL(timeout()), this,SLOT(updateStatus()));
        coreTimer->setInterval(1);

        ffProcess = new QProcess(this);

        QObject::connect(ffProcess,SIGNAL(started()),coreTimer ,SLOT(start()));
        QObject::connect(ffProcess,SIGNAL(finished(int)),this,SLOT(completed(int)));

        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(0);

        encodeaudio(cfn,filepath,ui->comboBoxAfmts->currentText(),ui->comboBoxSr->currentText(),ui->comboBoxCh->currentText(),ui->comboBoxBr->currentText());

        // QObject::connect(ffProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readffmpegoutput()));

        // arguments<<"-i"<<cfn<<"-ab"<<QString::number(128000)<<"-ac"<<QString::number(2)<<"-ar"<<QString::number(44100)<<"-y"<<filepath;
        // arguments<<"-i"<<cfn<<"-y"<<filepath;

        //  ffProcess->start(qApp->applicationDirPath()+"/ffmpeg.exe", arguments);

    }
}
void audioconvDialog::encodeaudio(QString cfn,QString ofn,  QString fmt,QString sr,QString ch,QString br)
{
    qDebug()<<cfn;
    QStringList arguments;
    arguments<<"-i"<<cfn;
    if(fmt=="amr")
    {
        //arguments<<"-acodec" <<"amr_nb";
    }
    if (fmt=="ogg")
    {
        arguments<<"-acodec"<<"libvorbis";
    }

    if (fmt=="wma")
    {
        arguments<<"-acodec"<<"wmav2";
    }
    qDebug()<<arguments;
    long bir=br.toFloat()*1000;
    qDebug()<<bir;
    if (fmt=="flac"||fmt=="m4a")
    {
        arguments<<"-ar"<<sr<<"-ac"<<ch<<"-y"<<ofn;
    }
    else
    {
        arguments<<"-ar"<<sr<<"-ac"<<ch<<"-ab"<<QString::number(bir)<<"-y"<<ofn;
    }
    //arguments<<"-i"<<cfn<<"-y"<<filepath;
    qDebug()<<arguments;
    ffProcess->start(qApp->applicationDirPath()+"/ffmpeg.exe", arguments);

}

void audioconvDialog::on_pushButton_2_clicked()
{if(ffProcess)
        ffProcess->close();

}

void audioconvDialog::on_pushButtonof_clicked()
{ emit  showfile(QString("/select,"),cfile->filePath());


}

void audioconvDialog::on_comboBoxAfmts_currentIndexChanged(QString fmt)
{
    if (fmt=="m4a")
    { ui->labfmt->setText("MPEG4 audio (*.mp4)");
        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"8000"
          <<"11025"
         <<"22050"
        <<"24000"
        <<"32000"
        <<"44100"
        <<"48000"
        <<"96000";

        chl <<"1"
           <<"2";



        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(5);
        ui->comboBoxCh->setCurrentIndex(1);
        // ui->comboBoxBr->setCurrentIndex(7);


    }
    if (fmt=="flac")
    { ui->labfmt->setText("Free Lossless Audio Codec (*.flac)");
        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"6000"
          <<"8000"
         <<"11025"
        <<"16000"
        <<"22050"
        <<"24000"
        <<"32000"
        <<"44100"
        <<"48000"
        <<"64000"
        <<"88200"
        <<"96000";


        chl <<"1"
           <<"2";



        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(8);
        ui->comboBoxCh->setCurrentIndex(1);
        // ui->comboBoxBr->setCurrentIndex(7);


    }
    if (fmt=="flac"||fmt=="m4a")
    {
        ui->comboBoxBr->setEnabled(false);
    }
    else
    {
        ui->comboBoxBr->setEnabled(true);
    }


    if (fmt=="aac")
    { ui->labfmt->setText("Advanced Audio Coding(*.aac)");

        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"11025"
          <<"12000"
         <<"16000"
        <<"22050"
        <<"24000"
        <<"32000"
        <<"44100"
        <<"48000";

        chl <<"1"
           <<"2"
          <<"6";

        brl <<"24"
           <<"32"
          <<"48"
         <<"56"
        <<"64"
        <<"96"
        <<"112"
        <<"128"
        <<"160"
        <<"192"
        <<"224"
        <<"256";

        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(6);
        ui->comboBoxCh->setCurrentIndex(1);
        ui->comboBoxBr->setCurrentIndex(7);


    }
    if (fmt=="ac3")
    {ui->labfmt->setText("Dolby Digital Audio(*.ac3)");
        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"12000"
          <<"22050"
         <<"24000"
        <<"48000";

        chl <<"1"
           <<"2"
          <<"6";

        brl <<"48"
           <<"56"
          <<"64"
         <<"96"
        <<"112"
        <<"128"
        <<"160"
        <<"192"
        <<"224"
        <<"256"
        <<"320"
        <<"384"
        <<"448";


        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(3);
        ui->comboBoxCh->setCurrentIndex(1);
        ui->comboBoxBr->setCurrentIndex(11);

    }
    if (fmt=="amr")
    {ui->labfmt->setText("Adaptive Multi-Rate audio codec (*.amr)");

        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"8000";
        chl <<"1";

        brl <<"5.9"
           <<"6.7"
          <<"7.4"
         <<"7.95"
        <<"10.2"
        <<"12.2";



        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(0);
        ui->comboBoxCh->setCurrentIndex(0);
        ui->comboBoxBr->setCurrentIndex(2);

    }
    if (fmt=="mmf")
    { ui->labfmt->setText( "Mobile phone ringtone format designed by YAMAHA(*.mmf)");
        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"8000";
        chl <<"1";

        brl <<"32";

        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(0);
        ui->comboBoxCh->setCurrentIndex(0);
        ui->comboBoxBr->setCurrentIndex(0);

    }
    if(fmt=="mp2")
    {ui->labfmt->setText("MPEG Audio(*.mp2)");

        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"16000"
          <<"22050"
         <<"24000"
        <<"32000"
        <<"44100"
        <<"48000";

        chl <<"1"
           <<"2";


        brl <<"24"
           <<"32"
          <<"48"
         <<"56"
        <<"64"
        <<"96"
        <<"112"
        <<"128"
        <<"160"
        <<"192"
        <<"224"
        <<"256"
        <<"320"
        <<"384";

        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(4);
        ui->comboBoxCh->setCurrentIndex(1);
        ui->comboBoxBr->setCurrentIndex(8);

    }
    if(fmt=="mp3")
    {ui->labfmt->setText("MPEG 1 Layer3 Audio(*.mp3)");
        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"11025"
          <<"12000"
         <<"16000"
        <<"22050"
        <<"24000"
        <<"32000"
        <<"44100"
        <<"48000";

        chl <<"1"
           <<"2";


        brl <<"24"
           <<"32"
          <<"48"
         <<"56"
        <<"64"
        <<"96"
        <<"112"
        <<"128"
        <<"160"
        <<"192"
        <<"224"
        <<"256"
        <<"320";

        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(6);
        ui->comboBoxCh->setCurrentIndex(1);
        ui->comboBoxBr->setCurrentIndex(7);

    }
    if(fmt=="mpc")
    {QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"32000"
          <<"44100"
         <<"48000";

        chl <<"1"
           <<"2";


        brl <<"32"
           <<"48"
          <<"56"
         <<"64"
        <<"96"
        <<"112"
        <<"128"
        <<"160"
        <<"192"
        <<"224"
        <<"256"
        <<"320";

        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(1);
        ui->comboBoxCh->setCurrentIndex(1);
        ui->comboBoxBr->setCurrentIndex(6);

    }
    if(fmt=="ogg")
    {ui->labfmt->setText("Ogg Vorbis (*.ogg)");
        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"22050"
          <<"24000"
         <<"44100"
        <<"48000";

        chl <<"1"
           <<"2";


        brl <<"32"
           <<"48"
          <<"56"
         <<"64"
        <<"80"
        <<"96"
        <<"112"
        <<"128"
        <<"160";


        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(0);
        ui->comboBoxCh->setCurrentIndex(1);
        ui->comboBoxBr->setCurrentIndex(4);

    }
    if(fmt=="wav")
    {ui->labfmt->setText("Waveform Audio(*.wav)");
        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"11025"
          <<"12000"
         <<"16000"
        <<"22050"
        <<"24000"
        <<"32000"
        <<"44100"
        <<"48000";

        chl <<"1"
           <<"2";





        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(6);
        ui->comboBoxCh->setCurrentIndex(1);
        ui->comboBoxBr->addItem("1411");
        ui->comboBoxBr->setCurrentIndex(0);

    }
    if(fmt=="wma")
    {ui->labfmt->setText("Windows Media Audio Format(*.wma)");
        QStringList srl;
        QStringList chl;
        QStringList brl;

        srl<<"22050"
          <<"32000"
         <<"44100"
        <<"48000";

        chl <<"1"
           <<"2";


        brl <<"32"
           <<"48"
          <<"56"
         <<"64"
        <<"96"
        <<"112"
        <<"128"
        <<"160"
        <<"192"
        <<"224"
        <<"256"
        <<"320";



        ui->comboBoxSr->clear();
        ui->comboBoxSr->insertItems(0,srl);
        ui->comboBoxCh->clear();
        ui->comboBoxCh->insertItems(0,chl);
        ui->comboBoxBr->clear();
        ui->comboBoxBr->insertItems(0,brl);
        ui->comboBoxSr->setCurrentIndex(2);
        ui->comboBoxCh->setCurrentIndex(1);
        ui->comboBoxBr->setCurrentIndex(6);

    }

}
void audioconvDialog::dropEvent(QDropEvent *event)
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
            ui->btnConv->setEnabled(true);
            cfn=url;
        }

    }
    event->acceptProposedAction();
}
void audioconvDialog::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();

}

void audioconvDialog::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();

}

void audioconvDialog::on_detailsPushButton_clicked()
{

}
