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

#include "seekview.h"
#include "ui_seekview.h"
#include <QBitmap>
SeekView::SeekView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekView)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TranslucentBackground ,true );
    QPixmap pixmap(":/images/seekview.png");
    //QPixmap pixmap(":/images/seekview.png");

    this->setMask(pixmap.mask());

    movie = new QMovie(":/images/loader.gif");

    ui->frameView->setMovie(movie);
    movie->start();

            //topLevelLabel->show();
}

SeekView::~SeekView()
{
    delete ui;
}
long int SeekView::getwindowID()
{
return (long int)ui->frameView->winId();
}
void SeekView::setPosition(QString p)
{
  ui->timedisp->setText(p);
}
