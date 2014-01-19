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

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
    class helpDialog;
}

class helpDialog : public QDialog {
    Q_OBJECT
public:
    helpDialog(QWidget *parent = 0);
    ~helpDialog();
public slots:
    void setHelpText(QString str);
    void showContent();
    void showcutterHelp(QString str);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::helpDialog *ui;

private slots:

    void on_listWidgetContent_currentRowChanged(int currentRow);
};

#endif // HELPDIALOG_H
