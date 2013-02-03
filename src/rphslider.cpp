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

#include "rphslider.h"
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOption>
#include <QToolTip>
rphSlider::rphSlider(QWidget  *parent) :
    QSlider(parent)
{
    this->setMouseTracking(true);

}
// Function copied from qslider.cpp
inline int rphSlider::pick(const QPoint &pt) const
{
    return orientation() == Qt::Horizontal ? pt.x() : pt.y();
}
void rphSlider::mousePressEvent( QMouseEvent* e )
{
    if (e->button() == Qt::LeftButton) {

        QStyleOptionSlider opt;
    initStyleOption(&opt);
    const QRect sliderRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    const QPoint center = sliderRect.center() - sliderRect.topLeft();
    // to take half of the slider off for the setSliderPosition call we use the center - topLeft

    if (!sliderRect.contains(e->pos())) {
        e->accept();

        setSliderPosition(pixelPosToRangeValue(pick(e->pos() - center)));
        triggerAction(SliderMove);
        setRepeatAction(SliderNoAction);
        pressedControl=QStyle::SC_SliderHandle;
    } else {
        QSlider::mousePressEvent(e);
            }
    } else {
            QSlider::mousePressEvent(e);
    }
}
// Function copied from qslider.cpp and modified to make it compile
int rphSlider::pixelPosToRangeValue(int pos) const
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect gr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    int sliderMin, sliderMax, sliderLength;

    if (orientation() == Qt::Horizontal) {
        sliderLength = sr.width();
        sliderMin = gr.x();
        sliderMax = gr.right() - sliderLength + 1;
    } else {
        sliderLength = sr.height();
        sliderMin = gr.y();
        sliderMax = gr.bottom() - sliderLength + 1;
    }
    return QStyle::sliderValueFromPosition(minimum(), maximum(), pos - sliderMin,
                                           sliderMax - sliderMin, opt.upsideDown);
}
void rphSlider::mouseMoveEvent(QMouseEvent *e){
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    const QRect sliderRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    const QPoint center = sliderRect.center() - sliderRect.topLeft();
    QPoint *pts;
    pts=new QPoint (e->pos());
    pt=new QPoint (e->pos());
    //qDebug("%d",pixelPosToRangeValue(pick(e->pos() - center)));
    emit hoverValue(QString::number(pixelPosToRangeValue(pick(e->pos() - center))),pts);
   //QToolTip::showText(e->globalPos(),this->toolTip());


        QSlider::mouseMoveEvent(e);

}
void rphSlider::mouseReleaseEvent(QMouseEvent *ev)
{
 pressedControl=QStyle::SC_None;
   ev->ignore();
   QSlider::mouseReleaseEvent(ev);
}
void rphSlider::wheelEvent ( QWheelEvent * event )
{
 event->ignore();
}
void rphSlider::leaveEvent ( QEvent * event )
{  emit hidetooltip();
   event->ignore();
   QSlider::leaveEvent(event);
}
void rphSlider::enterEvent ( QEvent * event )
{emit showtooltip(pt);
    event->ignore();
    QSlider::enterEvent(event);
}
