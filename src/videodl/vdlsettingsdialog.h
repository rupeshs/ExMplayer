/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2014 Rupesh Sreeraman

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

#ifndef VDLSETTINGSDIALOG_H
#define VDLSETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDesktopServices>
#include <QFileDialog>
#ifdef Q_OS_WIN
#include <windows.h>
#endif
namespace Ui {
class vdlSettingsDialog;
}

class VdlSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit VdlSettingsDialog(QWidget *parent ,QSettings *settings);
    ~VdlSettingsDialog();
    
private slots:


    void on_toolButtonBrFolderYdl_clicked();

    void on_toolButtonBrFolder_clicked();
    void settingChanged(QString group,QString key,QString value);
    void on_pushButtonReset_clicked();

    void on_pushButtonUpdate_clicked();

    void on_buttonBox_accepted();

private:
    Ui::vdlSettingsDialog *ui;
    QSettings *_settings;
    QString oPath;
};

#endif // VDLSETTINGSDIALOG_H
