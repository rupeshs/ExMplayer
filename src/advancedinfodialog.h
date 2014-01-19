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
#ifndef ADVANCEDINFODIALOG_H
#define ADVANCEDINFODIALOG_H

#include <QDialog>
#include "mplayerfe.h"
#include <QTimer>
namespace Ui {
class AdvancedInfoDialog;
}

class AdvancedInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AdvancedInfoDialog(QWidget *parent = 0);
    void setMPlayer(QPointer<mplayerfe> mp);
    ~AdvancedInfoDialog();
public slots:
    void updateStatus();
    
private:
    Ui::AdvancedInfoDialog *ui;
    QPointer<mplayerfe> _mp;
    QPointer<QTimer> statusTimer;
};

#endif // ADVANCEDINFODIALOG_H
