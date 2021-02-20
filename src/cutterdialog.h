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

#ifndef CUTTERDIALOG_H
#define CUTTERDIALOG_H

#include <QDialog>
#include "mplayerfe.h"
#include <QtCore>
#include "helpdialog.h"
#include "rphmpfehelp.h"
namespace Ui {
    class cutterDialog;
}

class cutterDialog : public QDialog {
    Q_OBJECT
public:
    cutterDialog(QWidget *parent ,mplayerfe *mpf);
    ~cutterDialog();
    void setMp(mplayerfe *mpf){mp=mpf;}
    QString shortPathName(QString long_path);
protected:
    void changeEvent(QEvent *e);

private:

 Ui::cutterDialog *ui;
 QPointer<mplayerfe> mp;
 QPointer<mplayerfe> mpp;
 QPointer<QTimer> cTimer;
 float startPos;
 float stopPos;
 QProcess *ffProcess;
 QTimer *coreTimer;
 QFile *cfile;
 QString filepath;
 helpDialog *mainhlpDlg ;

signals:
    void showfile(QString opt,QString fn);

private slots:

    void on_pushButtonhelp_clicked();
    void on_seek_actionTriggered(int action);
    void on_toolButtonStop_clicked();
    void on_pushButtonpre_clicked();
    void on_pushButtonof_clicked();
    void on_pushButtonclose_clicked();
    void on_pushButton_2_clicked();
    void on_pushButtonCut_clicked();
    void on_pushButtonReset_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonStart_clicked();
    void readffmpegoutput();
    void completed(int val);
    void updateSeekbar();
    void updateStatus();


protected:
  void closeEvent(QCloseEvent * e ) ;

   //static void  winExplorer(QString opt,QString path);
};

#endif // CUTTERDIALOG_H
