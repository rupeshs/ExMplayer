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
#ifndef SEEKVIEW_H
#define SEEKVIEW_H

#include <QDialog>

namespace Ui {
class SeekView;
}

class SeekView : public QDialog
{
    Q_OBJECT
    
public:
    explicit SeekView(QWidget *parent = 0);
    ~SeekView();
    long int getwindowID();
    void setPosition(QString p);

private:
    Ui::SeekView *ui;
};

#endif // SEEKVIEW_H
