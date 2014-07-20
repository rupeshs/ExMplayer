#include "videodl.h"
#include "ui_videodl.h"

Videodl::Videodl(QWidget *parent,QSettings *settings) :
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
   // ui->pushButtonUpdate->setVisible(false);
    _settings=settings;

    animateUi();



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

    initYoutubeDl(getYoutubeDlPath(),ui->lineEditVurl->text());
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
    //Advanced options enabled
    if (ui->groupBox->isChecked())
    {
     if (ui->formatsCombo->count()>0)
         initDownload();
     else
         QMessageBox::information(this,"Videodl","Advacned options enabled,so first check formats available");

    }
    else
    {
       initDownload();
    }


}
void Videodl::emitProcessFinished(int)
{
    if(isdownloading)
    {
        QMessageBox msgBox;
        ui->pushButtonCancel->setEnabled(false);
        ui->pushButtonDwnload->setEnabled(true);
        msgBox.setText("Downloading finished successfully.");
        msgBox.exec();
    }
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
    ydlFe->ydlProcess->close();
    ui->pushButtonCancel->setEnabled(false);
    ui->pushButtonDwnload->setEnabled(true);
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
    settingDlg = new VdlSettingsDialog(this,_settings);
    settingDlg->show();
}

void Videodl::on_toolButton_clicked()
{
    initYoutubeDl(getYoutubeDlPath(),"");
    blistExtrators=true;
    ydlFe->querySupportedSites();
    supDlg = new SupSitesDialog(this);

    supDlg->show();
    ui->pushButtonChkFormats->setEnabled(false);

}

void Videodl::on_pushButtonUpdate_clicked()
{
     initYoutubeDl(getYoutubeDlPath(),"");
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
QString Videodl::getYoutubeDlPath()
{
#ifdef Q_OS_WIN
    return _settings->value("VideoDl/YoutubedlDir",qApp->applicationDirPath()).toString()+"/ydl.exe";
#endif

}
QString Videodl::getDownloadPath()
{
#ifdef Q_OS_WIN
   return _settings->value("VideoDl/DownloadDir",QDesktopServices::storageLocation(QDesktopServices::MoviesLocation)).toString();
#endif
}
void  Videodl::initDownload()
{
    QString oPath=getDownloadPath();
   // qDebug()<<QDesktopServices::storageLocation(QDesktopServices::MoviesLocation);


    initYoutubeDl(getYoutubeDlPath(),ui->lineEditVurl->text());

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

void Videodl::on_pushButtonOpenOutput_clicked()
{
    emit  showfile(QString(""),getDownloadPath());
}

void Videodl::on_toolButtonSupFormats_clicked()
{

}
 void Videodl::animateUi()
 {
     /*QGraphicsOpacityEffect* fade_effect = new QGraphicsOpacityEffect(this);
     ui->label_4->setGraphicsEffect(fade_effect);

     QPropertyAnimation *animation = new QPropertyAnimation(fade_effect, "opacity");
     animation->setEasingCurve(QEasingCurve::InOutQuad);
     animation->setDuration(600);
     animation->setStartValue(0.01);
     animation->setEndValue(1.0);
     animation->start();

      fade_effect = new QGraphicsOpacityEffect(this);
     ui->label_5->setGraphicsEffect(fade_effect);

     animation = new QPropertyAnimation(fade_effect, "opacity");
     animation->setEasingCurve(QEasingCurve::InOutQuad);
     animation->setDuration(700);
     animation->setStartValue(0.01);
     animation->setEndValue(1.0);
     animation->start();

     fade_effect = new QGraphicsOpacityEffect(this);
     ui->label_6->setGraphicsEffect(fade_effect);

     animation = new QPropertyAnimation(fade_effect, "opacity");
     animation->setEasingCurve(QEasingCurve::InOutQuad);
     animation->setDuration(800);
     animation->setStartValue(0.01);
     animation->setEndValue(1.0);
     animation->start();

     fade_effect = new QGraphicsOpacityEffect(this);
     ui->label_7->setGraphicsEffect(fade_effect);

     animation = new QPropertyAnimation(fade_effect, "opacity");
     animation->setEasingCurve(QEasingCurve::InOutQuad);
     animation->setDuration(900);
     animation->setStartValue(0.01);
     animation->setEndValue(1.0);
     animation->start();

     fade_effect = new QGraphicsOpacityEffect(this);
     ui->label_8->setGraphicsEffect(fade_effect);

     animation = new QPropertyAnimation(fade_effect, "opacity");
     animation->setEasingCurve(QEasingCurve::InOutQuad);
     animation->setDuration(1000);
     animation->setStartValue(0.01);
     animation->setEndValue(1.0);
     animation->start();*/

     QPropertyAnimation *animation = new QPropertyAnimation(ui->label_4, "geometry");
     animation->setDuration(300);
     animation->setStartValue(QRect(ui->label_4->x(), 0, ui->label_4->width(), ui->label_4->height()));
     animation->setEndValue(QRect(ui->label_4->x(), 20, ui->label_4->width(), ui->label_4->height()));

     animation->start();

     QPropertyAnimation *animation2 = new QPropertyAnimation(ui->label_5, "geometry");
     animation2->setDuration(300);
     animation2->setStartValue(QRect(ui->label_5->x(), 0, ui->label_5->width(), ui->label_5->height()));
     animation2->setEndValue(QRect(ui->label_5->x(), 20, ui->label_5->width(), ui->label_5->height()));

     animation2->start();

     QPropertyAnimation *animation3 = new QPropertyAnimation(ui->label_6, "geometry");
     animation3->setDuration(300);
     animation3->setStartValue(QRect(ui->label_6->x(), 0, ui->label_6->width(), ui->label_6->height()));
     animation3->setEndValue(QRect(ui->label_6->x(), 10, ui->label_6->width(), ui->label_6->height()));

     animation3->start();

     QPropertyAnimation *animation4 = new QPropertyAnimation(ui->label_7, "geometry");
     animation4->setDuration(300);
     animation4->setStartValue(QRect(ui->label_7->x(), 0, ui->label_7->width(), ui->label_7->height()));
     animation4->setEndValue(QRect(ui->label_7->x(), 20, ui->label_7->width(), ui->label_7->height()));

     animation4->start();

     QPropertyAnimation *animation5 = new QPropertyAnimation(ui->label_8, "geometry");
     animation5->setDuration(300);
     animation5->setStartValue(QRect(ui->label_8->x(), 0, ui->label_8->width(), ui->label_8->height()));
     animation5->setEndValue(QRect(ui->label_8->x(), 30, ui->label_8->width(), ui->label_8->height()));

     animation5->start();

     QPropertyAnimation *animation6 = new QPropertyAnimation(ui->label_3, "geometry");
     animation6->setDuration(200);
     animation6->setStartValue(QRect(ui->label_3->x(), 0, ui->label_3->width(), ui->label_3->height()));
     animation6->setEndValue(QRect(ui->label_3->x(), 20, ui->label_3->width(), ui->label_3->height()));

     animation6->start();


 }