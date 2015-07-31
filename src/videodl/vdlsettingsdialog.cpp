/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2015 Rupesh Sreeraman

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

#include "vdlsettingsdialog.h"
#include "ui_vdlsettingsdialog.h"

VdlSettingsDialog::VdlSettingsDialog(QWidget *parent,QSettings *settings) :
    QDialog(parent),
    ui(new Ui::vdlSettingsDialog)
{
    ui->setupUi(this);
    _settings=settings;
    oPath=QDesktopServices::storageLocation(QDesktopServices::MoviesLocation);

    ui->lineEditDomDir->setText(_settings->value("VideoDl/DownloadDir",oPath).toString());

    //For future use
    ui->pushButtonUpdate->setVisible(false);

#ifdef Q_OS_WIN


    ui->lineEditYoudlDir->setText(_settings->value("VideoDl/YoutubedlDir",qApp->applicationDirPath()).toString());
    ui->pushButtonUpdate->setVisible(true);
#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
     ui->lineEditYoudlDir->setText(_settings->value("VideoDl/YoutubedlDir","/usr/local/bin/").toString());
# endif


}

VdlSettingsDialog::~VdlSettingsDialog()
{
    delete ui;
}



void VdlSettingsDialog::on_toolButtonBrFolderYdl_clicked()
{

    QString root=_settings->value("VideoDl/YoutubedlDir","").toString();


    QString dir = QFileDialog::getExistingDirectory(this, tr("Browse for youtube-dl binary"),
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
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
     settingChanged("VideoDl","DownloadDir",oPath);
      ui->lineEditDomDir->setText(oPath);
     settingChanged("VideoDl","YoutubedlDir","/usr/local/bin/");
     ui->lineEditYoudlDir->setText(_settings->value("VideoDl/YoutubedlDir","/usr/local/bin/").toString());
# endif

}

void VdlSettingsDialog::on_pushButtonUpdate_clicked()
{
    close();
  #ifdef Q_OS_WIN
    QString exeFileName(qApp->applicationDirPath()+"/update-youtube-dl.exe");

    int result = (int)::ShellExecuteA(0, "open", exeFileName.toUtf8().constData(), 0, 0, SW_HIDE);
    if (SE_ERR_ACCESSDENIED == result)
    {
        // Requesting elevation(Windows Vista/Window7/window8)
        result = (int)::ShellExecuteA(0, "runas", exeFileName.toUtf8().constData(), 0, 0, SW_HIDE);
    }
 #endif
}

void VdlSettingsDialog::on_buttonBox_accepted()
{

}
