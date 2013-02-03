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
#ifndef WINAMPDSPDIALOG_H
#define WINAMPDSPDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QPointer>
namespace Ui {
    class WinampDspDialog;
}

class WinampDspDialog : public QDialog {
    Q_OBJECT
public:
    WinampDspDialog(QWidget *parent = 0);
    ~WinampDspDialog();

signals:
 void settingChanged(QString group,QString key,QString value);

public slots:
    void getPlugins();
    void dlgsettings(QSettings *se);
protected:
    void changeEvent(QEvent *e);
    void showEvent ( QShowEvent * event ) ;
signals:
    void enableWinampPlugin(bool enable,QString path);
private:
    Ui::WinampDspDialog *ui;
QPointer<QSettings>_settings;
private slots:
    void on_buttonBox_accepted();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

};

#endif // WINAMPDSPDIALOG_H
