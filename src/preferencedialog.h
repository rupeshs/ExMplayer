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
#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QListWidgetItem>
#include <QSettings>
#include <QTableWidgetItem>
#include "shortcutgetter.h"
#include <QSettings>
#include "helpdialog.h"
namespace Ui {
    class preferenceDialog;
}

class preferenceDialog : public QDialog {
    Q_OBJECT
public:
    preferenceDialog(QWidget *parent ,QSettings *settings);
    ~preferenceDialog();

protected:
    void changeEvent(QEvent *e);

signals:
 void settingChanged(QString group,QString key,QString value);
 void reloadshortcut();
 void setmousewheelrole();
 void restart();
 void disableSS();
 void setAqua();
 void restartComplete();
private:
 Ui::preferenceDialog *ui;
QSettings *_settings;
public slots:
void setSettings(QSettings *settings){/*_settings=settings;*/};
void setSc(QWidget *w){_w=w;};
private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_chScDir_clicked();
    void on_pushButton_2_clicked();
    void on_rbVol_toggled(bool checked);
    void on_pushButton_clicked();
    void on_twsc_itemDoubleClicked(QTableWidgetItem* item);
    void on_listWidget_currentRowChanged(int currentRow);
    void on_buttonBox_clicked(QAbstractButton* button);
    void saveActionToXml();
    void on_hSliderVolumeBoost_valueChanged(int value);
    void on_pushButtonResetVolumeBoost_clicked();

private:
    QWidget *_w;
    ShortcutGetter *scg;
    helpDialog *hlpDlg;
    helpDialog *mDlg;
    bool resetsc;
    int mw;
    bool apply;
};


#endif // PREFERENCEDIALOG_H
