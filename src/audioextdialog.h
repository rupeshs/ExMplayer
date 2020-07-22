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
#ifndef AUDIOEXTDIALOG_H
#define AUDIOEXTDIALOG_H

#include <QDialog>
#include "mplayerfe.h"
#include <QtCore>
#include <QFileInfo>
#include <QProcess>
#include <QMessageBox>
#include "filefilters.h"
namespace Ui {
class audioextDialog;
}

class audioextDialog : public QDialog {
    Q_OBJECT
public:
    audioextDialog(QWidget *parent = 0);
    ~audioextDialog();

protected:
    void changeEvent(QEvent *e);
    void ExtractAudio();

private:
    Ui::audioextDialog *ui;
    QTimer *coreTimer;
    QPointer<mplayerfe> mp;
    QPointer<QProcess> ffProcess;
    QString cfn;
    QFileInfo *cfile;
signals:
    void showfile(QString opt,QString fn);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButtonof_clicked();
    void on_pex_clicked();
    void on_pushButton_clicked();
    //void readffmpegoutput();
    void updateStatus();
    void completed(int ec);
protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
};

#endif // AUDIOEXTDIALOG_H
