/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2020 Rupesh Sreeraman

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
#include "gifanimatordialog.h"
#include "ui_gifanimatordialog.h"

GifAnimatorDialog::GifAnimatorDialog(QWidget *parent,mplayerfe *mpf) :
    QDialog(parent),
    ui(new Ui::GifAnimatorDialog)
{

    ui->setupUi(this);


    //ui->lineEditStart->setInputMask("99:99:99");
   // ui->lineEditStop->setInputMask("99:99:99");
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonAnimate->setEnabled(false);
    ui->spinBoxFps->setValue(15);
    ui->spinBoxWidth->setValue(320);
    ui->spinBoxHeight->setValue(-1);



    mp=mpf;
    if(!mp->hasvideo())
        ui->pushButtonStart->setEnabled(false);
    startPos=0;
    stopPos=0;
    movie = new QMovie(":/images/loaderanim.gif");
    ui->labelLoader->hide();
    ui->labelLoader->setMovie(movie);

    ui->pushButtonOpenFolder->setEnabled(false);

    extension = new QWidget(this);
    QObject::connect(ui->detailsPushButton, SIGNAL(toggled(bool)), extension, SLOT(setVisible(bool)));
    QObject::connect(ui->detailsPushButton, SIGNAL(toggled(bool)), this, SLOT(toggleExtension(bool)));

    QVBoxLayout *extensionLayout = new QVBoxLayout;
    extensionLayout->setMargin(0);


    extensionLayout->addWidget(ui->groupBox_2);
    extension->setLayout(extensionLayout);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    //mainLayout->setMargin(10);
    mainLayout->setVerticalSpacing(20);
    mainLayout->setHorizontalSpacing(20);

    mainLayout->addWidget(ui->groupBox, 0, 0);

    mainLayout->addWidget(ui->detailsPushButton,0,2);
    mainLayout->addWidget(extension,3,0);

    setLayout(mainLayout);


    extension->hide();


}
GifAnimatorDialog::~GifAnimatorDialog()
{
    delete ui;
}


void GifAnimatorDialog::on_pushButtonOpenFolder_clicked()
{

    emit  showfile(QString("/select,"),gifPath);
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
        QTime t(0,0);
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

   if (stopPos-startPos>120)
   {  QMessageBox::warning(this, tr("ExMplayer Movie Animator"),
                                   tr("Selected video length is too large") ,

                                   QMessageBox::Cancel);
       return;
   }
   if (stopPos-startPos<1)
   {
       QMessageBox::warning(this, tr("ExMplayer Movie Animator"),
                                          tr("Selected video length is too small") ,

                                          QMessageBox::Cancel);
       return;
   }
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

            gifPalettteGen->setFfmpegOptions(fileFilters::shortPathName(mp->filepath()),startPos,stopPos-startPos,ui->spinBoxFps->value(),ui->spinBoxWidth->value(),ui->spinBoxHeight->value());
            gifPalettteGen->generatePalette();



        }
    }
}

void GifAnimatorDialog::triggerGifGenerator(int ec)
{
    if(ec==0)
    {
        gifGene=new GifGenerator();
        gifGene->setFfmpegOptions(fileFilters::shortPathName(mp->filepath()),startPos,stopPos-startPos,ui->spinBoxFps->value(),ui->spinBoxWidth->value(),ui->spinBoxHeight->value(),outPath);
        QObject::connect(gifGene,SIGNAL(ffmpegexit(int,QString)),this,SLOT(ProcessingCompleted(int,QString)));

        gifGene->generateGif();
        ui->labelStatus->setText("Creating animation...");
    }
}

void GifAnimatorDialog::ProcessingCompleted(int ec,QString outpath)
{
gifPath=outpath;
ui->labelStatus->setText("Completed.");
movie->stop();
ui->labelLoader->hide();
ui->pushButtonOpenFolder->setEnabled(true);
}

void GifAnimatorDialog::on_pushButtonReset_clicked()
{
    if(mp->hasvideo())
        ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonAnimate->setEnabled(false);
    ui->lineEditStart->clear();
    ui->lineEditStop->clear();
}
void GifAnimatorDialog::toggleExtension(bool fa)
{

    if (fa)
    {
        ui->detailsPushButton->setText(" Simple<<< ");
    }
    else
    {
        ui->detailsPushButton->setText(" Advanced>>> ");

    }
}

void GifAnimatorDialog::on_checkBox_toggled(bool checked)
{
    if (checked)
    {
        ui->spinBoxHeight->setValue(-1);
        ui->spinBoxWidth->setValue(-1);

    }
    else
    {
        ui->spinBoxHeight->setValue(-1);
        ui->spinBoxWidth->setValue(320);

    }
}
