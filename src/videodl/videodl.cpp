#include "videodl.h"
#include "ui_videodl.h"

Videodl::Videodl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Videodl)
{
    ui->setupUi(this);
    ui->pushButtonCancel->setEnabled(false);
    ui->pushButtonDwnload->setEnabled(false);
    blistExtrators=false;
    isUpdating=false;
    pgIndicator=new QProgressIndicator(this);
    pgIndicator->setColor(QColor(qRgb(0,100,0) ));
    pgIndicator->show();
    ui->statusBar->addPermanentWidget(pgIndicator);
    ui->pushButtonUpdate->setVisible(false);


}

Videodl::~Videodl()
{
    delete ui;
}
void Videodl::ydlConsole(QByteArray ba)
{
    QString ydlOutputLine(ba);
    qDebug()<<ydlOutputLine;
    if (isUpdating)
    {
        this->statusBar()->showMessage(ydlOutputLine);
        if (ydlOutputLine.contains("Waiting for file handle"))
        {
            ydlFe->ydlProcess->close();
            this->statusBar()->showMessage("Updated successfully");
            QMessageBox::information(this,"Videodl","Updated successfully");


        }
        if (ydlOutputLine.contains("up-to-date"))
        {
            QMessageBox::information(this,"Videodl",ydlOutputLine);

        }


    }
    else if (blistExtrators)
    {
        supDlg->addSite(ydlOutputLine);

    }
    else
    {

        if (!isdownloading)
        {

            if (formatsFound)
            {
                if( !ba.contains("video only")){
                  ui->formatsCombo->addItem(ba.replace(" ","-"));
                }
            }
            else
                this->statusBar()->showMessage(ba);
            if (rx_fmt.indexIn( ydlOutputLine) >-1 )
            {
                formatsFound=true;
                this->statusBar()->showMessage("");
                if (!ui->pushButtonChkFormats->isEnabled())
                {ui->pushButtonChkFormats->setText("Check formats Available");
                ui->pushButtonChkFormats->setEnabled(true);

                }

            }

        }
        else
        {
            if (ba.contains( "already been downloaded"))
                QMessageBox::information(this,"Videodl",ba);

            if (rx_pro.indexIn( ydlOutputLine) >-1 ){
                qDebug()<<QString::number(rx_pro.cap(1).toFloat()*10);
                ui->progressBarDwnldPg->setValue( rx_pro.cap(1).toFloat()*10);
                if (ui->pushButtonDwnload->isEnabled())
                {
                ui->pushButtonCancel->setEnabled(true);
                ui->pushButtonDwnload->setEnabled(false);
                pgIndicator->hide();
                }

            }
            this->statusBar()->showMessage(ba);
        }
    }

}

void Videodl::on_pushButtonChkFormats_clicked()
{

    //http://www.dailymotion.com/video/xctqbl_enigma-beyond-the-invisible_music
    //http://www.youtube.com/watch?v=FfRAiTtOVEY
    //ttps://www.facebook.com/photo.php?v=702226306466656&set=vb.105754412780518&type=2&theater
    //https://soundcloud.com/devinder-singh-1/stereo-love-akcent-astronomia

    if(ui->lineEditVurl->text()=="")
    {
        QMessageBox::information(this,"Videodl","Please enter a valid URL");
        return;
    }
    ui->pushButtonChkFormats->setText("Checking...");
    ui->pushButtonChkFormats->setEnabled(false);

    initYoutubeDl("E:/ydl/ydl.exe",ui->lineEditVurl->text());
    formatsFound=false;
    isdownloading=false;
    ui->formatsCombo->clear();
    ydlFe->queryAvailableFormats();
    pgIndicator->startAnimation();
    pgIndicator->show();
}

void Videodl::on_pushButtonDwnload_clicked()
{
    if(ui->lineEditVurl->text()=="")
    {
        QMessageBox::information(this,"Videodl","Please enter a valid URL");
        return;
    }
    QString oPath=QDesktopServices::storageLocation(QDesktopServices::MoviesLocation);
    qDebug()<<QDesktopServices::storageLocation(QDesktopServices::MoviesLocation);


    initYoutubeDl("E:/ydl/ydl.exe",ui->lineEditVurl->text());

    if (ui->formatsCombo->count()>1)
    { QString id=ui->formatsCombo->currentText().split("-").at(0);
        ydlFe->downloadVideo(oPath,id,false);
        pgIndicator->startAnimation();
        pgIndicator->show();
    }
    else
    {


            ydlFe->downloadVideo(oPath,0,true);
            pgIndicator->startAnimation();
            pgIndicator->show();

    }
    isdownloading=true;
    ui->toolButtonSupFormats->setEnabled(false);


}
void Videodl::emitProcessFinished(int)
{
    isdownloading=false;
    ui->pushButtonChkFormats->setEnabled(true);
    ui->toolButtonSupFormats->setEnabled(true);
    ui->pushButtonChkFormats->setText("Recheck formats Available");
    blistExtrators=false;
    pgIndicator->hide();


}
void  Videodl::initYoutubeDl(QString ydlPath,QString videoUrl)
{
    if (!ydlFe)
    {
        ydlFe=new YoutubedlFe(this,ydlPath);
        ydlFe->setVideoUrl(videoUrl);
        QObject::connect(ydlFe,SIGNAL(ytconsoleline(QByteArray)),this,SLOT(ydlConsole(QByteArray)));
        QObject::connect(ydlFe,SIGNAL(ytexit(int)),this,SLOT(emitProcessFinished(int)));
    }
     isUpdating=false;
}

void Videodl::on_pushButtonCancel_clicked()
{
    ui->pushButtonCancel->setEnabled(false);
    ui->pushButtonDwnload->setEnabled(true);
    ydlFe->ydlProcess->close();
    ui->progressBarDwnldPg->setValue( 0);
    this->statusBar()->showMessage("");
    ui->pushButtonChkFormats->setEnabled(true);
    ui->toolButtonSupFormats->setEnabled(true);
}

void Videodl::on_lineEditVurl_textChanged(const QString &arg1)
{
    if (arg1=="")
        ui->pushButtonDwnload->setEnabled(false);
    else
        ui->pushButtonDwnload->setEnabled(true);
    ui->pushButtonChkFormats->setText("Check formats Available");
}

void Videodl::on_toolButtonSettings_clicked()
{
    settingDlg = new VdlSettingsDialog(this);
    settingDlg->show();
}

void Videodl::on_toolButton_clicked()
{
    initYoutubeDl("E:/ydl/ydl.exe","");
    blistExtrators=true;
    ydlFe->querySupportedSites();
    supDlg = new SupSitesDialog(this);

    supDlg->show();
    ui->pushButtonChkFormats->setEnabled(false);

}

void Videodl::on_pushButtonUpdate_clicked()
{
     initYoutubeDl("E:/ydl/ydl.exe","");
     isUpdating=true;
     ui->statusBar->showMessage("Checking for updates...");
     pgIndicator->startAnimation();
     pgIndicator->show();
     ydlFe->updateYoutubedl();
     ui->groupBox->setEnabled(false);
     ui->lineEditVurl->setEnabled(false);
     ui->toolButtonSupFormats->setEnabled(false);
     ui->pushButtonDwnload->setEnabled(false);
     ui->pushButtonCancel->setEnabled(false);

}
