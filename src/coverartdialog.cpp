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
#include "coverartdialog.h"
#include "ui_coverartdialog.h"
#include <QBitmap>

CoverArtDialog::CoverArtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoverArtDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Popup);

    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);

    QString coverPath=QDir::tempPath()+"/mcover.jpeg";
    ui->labelCover->setPixmap(coverPath);
    ui->labelCover->setScaledContents(true);

    QGraphicsOpacityEffect* fade_effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(fade_effect);

    QPropertyAnimation *animation = new QPropertyAnimation(fade_effect, "opacity");
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setDuration(1000);
    animation->setStartValue(0.01);
    animation->setEndValue(1.0);
    animation->start();
    this->setVisible(true);


    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->toolButton, "geometry");
    animation2->setDuration(1000);
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->setStartValue(QRect(170, 0, 22, 22));
    animation2->setEndValue(QRect(170, 110, 22, 22));
    animation2->start();
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;

    group->addAnimation(animation);
    group->addAnimation(animation2);

    //group->start(QPropertyAnimation::DeleteWhenStopped);
}

CoverArtDialog::~CoverArtDialog()
{
    delete ui;
}

void CoverArtDialog::on_toolButton_clicked()
{
    emit showInfo();
}
