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

