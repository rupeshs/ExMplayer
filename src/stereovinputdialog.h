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
#ifndef STEREOVINPUTDIALOG_H
#define STEREOVINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class StereoVinputDialog;
}

class StereoVinputDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit StereoVinputDialog(QWidget *parent = 0);
    ~StereoVinputDialog();

    inline bool Stereo(){return _bstereo;} //for stereo selection dialogue
    inline void setStereo(bool b){_bstereo=b;}
signals:
    void stereoInputFormat(int mode);
    
private slots:
    void on_pushButtonOk_clicked();



private:
    Ui::StereoVinputDialog *ui;
    bool _bstereo;
};

#endif // STEREOVINPUTDIALOG_H
