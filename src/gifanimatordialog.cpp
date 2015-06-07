#include "gifanimatordialog.h"
#include "ui_gifanimatordialog.h"

GifAnimatorDialog::GifAnimatorDialog(QWidget *parent,mplayerfe *mpf) :
    QDialog(parent),
    ui(new Ui::GifAnimatorDialog)
{

    ui->setupUi(this);

    ui->lineEditStart->setInputMask("99:99:99");
    ui->lineEditStop->setInputMask("99:99:99");
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonAnimate->setEnabled(false);

    mp=mpf;
    startPos=0;
    stopPos=0;
    movie = new QMovie(":/images/loaderanim.gif");
    ui->labelLoader->hide();
    ui->labelLoader->setMovie(movie);

    ui->pushButtonOpenFolder->setEnabled(false);


}
GifAnimatorDialog::~GifAnimatorDialog()
{
    delete ui;
}


void GifAnimatorDialog::on_pushButtonOpenFolder_clicked()
{
    QFileInfo fi(fileFilters::shortPathName(mp->filepath()));


    filepath=outPath+fileFilters::shortPathName("Anim_"+fi.baseName()+".gif");
    qDebug()<< filepath;
    emit  showfile(QString("/select,"),filepath);
}

void GifAnimatorDialog::on_pushButtonStart_clicked()
{


    if (mp)
    {ui->lineEditStart->setText(mp->tcurpos().toString());
        startPos=mp->curpos();


    }
    if (!ui->lineEditStart->text().isEmpty())
    {ui->pushButtonStop->setEnabled(true);
       ui->pushButtonStart->setEnabled(false);
    }
}

void GifAnimatorDialog::on_pushButtonStop_clicked()
{
    if (mp)
    {ui->lineEditStop->setText(mp->tcurpos().toString());
        stopPos=mp->curpos();
        QTime t;
        t = t.addSecs(stopPos-startPos);
        //ui->lineEditLen->setText( t.toString());
    }

    if(stopPos-startPos>0)
    {
        ui->pushButtonStart->setEnabled(false);
        ui->pushButtonStop->setEnabled(false);
        ui->pushButtonAnimate->setEnabled(true);

    }


}

void GifAnimatorDialog::on_pushButtonAnimate_clicked()
{

    if(stopPos-startPos>0)
    {QString dir = rphFile::getDir(this,"Open a Directory for output:","");


        if (!dir.isEmpty())
        {

            outPath=dir;

            ui->labelLoader->show();
            movie->start();
            gifPalettteGen=new GifPaletteGenerator();
            ui->labelStatus->setText("Generating palette...");
            QObject::connect(gifPalettteGen,SIGNAL(ffmpegexit(int)),this,SLOT(triggerGifGenerator(int)));

            gifPalettteGen->setFfmpegOptions(fileFilters::shortPathName(mp->filepath()),startPos,stopPos-startPos);
            gifPalettteGen->generatePalette();



        }
    }
}

void GifAnimatorDialog::triggerGifGenerator(int ec)
{
    if(ec==0)
    {
        gifGene=new GifGenerator();
        gifGene->setFfmpegOptions(fileFilters::shortPathName(mp->filepath()),startPos,stopPos-startPos,outPath);
        QObject::connect(gifGene,SIGNAL(ffmpegexit(int)),this,SLOT(ProcessingCompleted(int)));

        gifGene->generateGif();
        ui->labelStatus->setText("Creating animation...");
    }
}

void GifAnimatorDialog::ProcessingCompleted(int ec)
{

ui->labelStatus->setText("Completed.");
movie->stop();
ui->labelLoader->hide();
ui->pushButtonOpenFolder->setEnabled(true);
}

void GifAnimatorDialog::on_pushButtonReset_clicked()
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonAnimate->setEnabled(false);
    ui->lineEditStart->clear();
    ui->lineEditStop->clear();
}
