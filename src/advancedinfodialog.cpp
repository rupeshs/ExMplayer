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
#include "advancedinfodialog.h"
#include "ui_advancedinfodialog.h"

AdvancedInfoDialog::AdvancedInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedInfoDialog)
{

    ui->setupUi(this);
}

AdvancedInfoDialog::~AdvancedInfoDialog()
{
    delete ui;
}
void AdvancedInfoDialog::setMPlayer(QPointer<mplayerfe> mp)
{
    _mp=mp;

    if(mp){
        if(mp->listAudioTrack.count()>0)
            ui->checkBoxAudio->setChecked(true);
        if(mp->listVideoTrack.count()>0)
            ui->checkBoxVideo->setChecked(true);
        if(mp->listSubtitleTrack.count()>0)
            ui->checkBoxSub->setChecked(true);
        ui->groupBox->setAttribute(Qt::WA_TransparentForMouseEvents);

        ui->labelAudioCodec->setText(mp->mapCodecs["audio"]);
        ui->labelVideoCodec->setText(mp->mapCodecs["video"]);

        ui->labelAudioDevice->setText(mp->mapDevices["audio"]);
        ui->labelVideoDevice->setText(mp->mapDevices["video"]);

        statusTimer = new QTimer(this);
        QObject::connect(statusTimer , SIGNAL(timeout()), this,SLOT(updateStatus()));
        statusTimer->start(500);


    }
}
void AdvancedInfoDialog::updateStatus()
{


    ui->labelAudioCPU->setText(_mp->audio_cpu_usage());
    ui->labelVideoCPU->setText(_mp->video_cpu_usage());
    ui->labellSpeedFactor->setText(_mp->currentspeed());
    ui->labelAVdealy->setText(_mp->avdelay());
    if (_mp->framecount()==""){
    ui->labelFramesCap->setText("");
    ui->labelFrames->setText(_mp->framecount());
    }
    else
        ui->labelFrames->setText(_mp->framecount());
}

