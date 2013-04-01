/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2013 Rupesh Sreeraman

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


#ifndef AUDIOCONVDIALOG_H
#define AUDIOCONVDIALOG_H

#include <QDialog>

#include <QtCore>
#include <QFileInfo>
#include <QProcess>
#include <QMessageBox>
#include "filefilters.h"
namespace Ui {
    class audioconvDialog;
}

class audioconvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit audioconvDialog(QWidget *parent = 0);
    ~audioconvDialog();
    QWidget *extension;
    QTimer *coreTimer;
    QPointer<QProcess> ffProcess;

signals:
    void showfile(QString opt,QString fn);
private:
    Ui::audioconvDialog *ui;
    QString cfn;
    QFileInfo *cfile;
private slots:
    void on_comboBoxAfmts_currentIndexChanged(QString );
    void on_pushButtonof_clicked();
    void on_pushButton_2_clicked();
    void on_btnConv_clicked();
    void on_pushButton_clicked();
    void on_comboBoxSr_currentIndexChanged(int index);
    void on_comboBoxAfmts_currentIndexChanged(int index);
    void on_comboBoxCh_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(QString );
    void toggleExtension(bool) ;
    //void readffmpegoutput();
    void updateStatus();
    void completed(int ec);
    void encodeaudio(QString cfn,QString ofn,QString fmt,QString sr,QString ch,QString br);
    void on_detailsPushButton_clicked();

protected:
    void dropEvent(QDropEvent *event);
void dragEnterEvent(QDragEnterEvent *event);
void dragMoveEvent(QDragMoveEvent *event);
};

#endif // AUDIOCONVDIALOG_H
