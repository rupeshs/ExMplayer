#include "vdlsettingsdialog.h"
#include "ui_vdlsettingsdialog.h"

VdlSettingsDialog::VdlSettingsDialog(QWidget *parent,QSettings *settings) :
    QDialog(parent),
    ui(new Ui::vdlSettingsDialog)
{
    ui->setupUi(this);
    _settings=settings;
    oPath=QDesktopServices::storageLocation(QDesktopServices::MoviesLocation);

    //For future use
    ui->pushButtonUpdate->setVisible(false);

#ifdef Q_OS_WIN

    ui->lineEditDomDir->setText(_settings->value("VideoDl/DownloadDir",oPath).toString());

    ui->lineEditYoudlDir->setText(_settings->value("VideoDl/YoutubedlDir",qApp->applicationDirPath()).toString());

#endif
#ifdef Q_OS_LINUX

# endif


}

VdlSettingsDialog::~VdlSettingsDialog()
{
    delete ui;
}



void VdlSettingsDialog::on_toolButtonBrFolderYdl_clicked()
{

    QString root=_settings->value("VideoDl/YoutubedlDir","").toString();


    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    root,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        ui->lineEditYoudlDir->setText( dir);
        settingChanged("VideoDl","YoutubedlDir",dir);

    }
}

void VdlSettingsDialog::on_toolButtonBrFolder_clicked()
{
    QString root=_settings->value("VideoDl/DownloadDir","").toString();


    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    root,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        ui->lineEditDomDir->setText( dir);
        settingChanged("VideoDl","DownloadDir",dir);

    }
}
void VdlSettingsDialog::settingChanged(QString group,QString key,QString value)
{
    _settings->beginGroup(group);
    _settings->setValue(key,value);
    _settings->endGroup();
}

void VdlSettingsDialog::on_pushButtonReset_clicked()
{
#ifdef Q_OS_WIN
    oPath=QDesktopServices::storageLocation(QDesktopServices::MoviesLocation);
    ui->lineEditDomDir->setText(oPath);
    settingChanged("VideoDl","DownloadDir",oPath);
    ui->lineEditYoudlDir->setText(qApp->applicationDirPath());
    settingChanged("VideoDl","YoutubedlDir",qApp->applicationDirPath());
#endif
}
