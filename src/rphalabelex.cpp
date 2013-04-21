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
#include <rphlabelex.h>
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOption>
#include <QRubberBand>
#include <QMutex>
#include <qdebug.h>
rphLabelEx::rphLabelEx(QWidget  *parent) :
        QLabel(parent)
{
 md =false;
_title="";
_artist="";
mrubberBand=false;
step1 = 0;
step2 = 0;
step3= 0;
step4 = 0;
_suffix="";
_showeof=false;
at1=new QTimer(this);
at2=new QTimer(this);
at3=new QTimer(this);
at4=new QTimer(this);
QObject::connect(at1,SIGNAL(timeout()),this,SLOT(animatet1()));
QObject::connect(at2,SIGNAL(timeout()),this,SLOT(animatet2()));
QObject::connect(at3,SIGNAL(timeout()),this,SLOT(animatet3()));
QObject::connect(at4,SIGNAL(timeout()),this,SLOT(animatet4()));

}
void rphLabelEx::mousePressEvent(QMouseEvent *event)
{if (mrubberBand){
    origin = event->pos();
    if(!md)
    {rubberBand = new QRubberBand(QRubberBand::Rectangle,this);
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();

    md=true;

   }
  }
    QLabel::mousePressEvent(event);
 }

void rphLabelEx::mouseMoveEvent(QMouseEvent *event)
{
 if (mrubberBand){
   if (md)
      rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
   }
event->ignore();
 QLabel::mouseMoveEvent(event);
}

void rphLabelEx::mouseReleaseEvent(QMouseEvent *event)
 {//qDebug()<<mrubberBand;
   // if (mrubberBand)
    //{
        QRect *val;
    if (md)
    {rubberBand->hide();
     md=false;

    val=new QRect(origin, event->pos());

    emit rectRubberBand(val);
    }
   QLabel::mouseReleaseEvent(event);
//}

     // determine selection, for example using QRect::intersects()
     // and QRect::contains().
 }
void rphLabelEx::paintEvent ( QPaintEvent * event )
{

  QLabel::paintEvent(event);

   QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::blue);
    painter.setFont(QFont( painter.font().family(), _fontsize));


   if (!_text.isEmpty())
   {painter.setPen(QColor("#0450FC"));
       painter.drawText(QRect(5,0,size().width(),size().height()),Qt::AlignVCenter ,QString(painter.fontMetrics().elidedText(_text,Qt::ElideRight,size().width(),0)));
   }

    if (_showeof)
    {
        painter.setPen(Qt::white);
     painter.setFont(QFont("Arial", 16));
     painter.drawText(rect(), Qt::AlignCenter, "End of playback");

 }
    if (!_errtext.isEmpty())
    {
        painter.setPen(Qt::red);
     painter.setFont(QFont("Arial", 15));
     painter.drawText(rect(), Qt::AlignCenter, _errtext);

 }

/*
   //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   //draw title
    painter.setPen(Qt::white);
    painter.setFont(QFont(painter.font().family(), 15,false));

    tmp1=painter.fontMetrics().elidedText(_title,Qt::ElideRight,size().width(),0);

   / if (step1!=tmp1.length())
         painter.drawText(QRect(5,5,size().width(),100), tmp1.left(step1) );

    if(! at1->isActive())
        painter.drawText(QRect(5,5,size().width(),100), tmp1 );
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //draw artistname

    painter.setFont(QFont(painter.font().family(), 13,false));
    tmp2= painter.fontMetrics().elidedText(_artist,Qt::ElideRight,size().width(),0);

    if (! at1->isActive()&&at2->isActive())
    {
        if (step2!=tmp2.length())
           painter.drawText(QRect(5,27,size().width(),100), tmp2.left(step2) );
    }
    if(! at1->isActive()&& !at2->isActive())
        painter.drawText(QRect(5,27,size().width(),100), tmp2 );

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //draw artistname

    painter.setFont(QFont(painter.font().family(), 13,false));
    tmp3= painter.fontMetrics().elidedText(_album,Qt::ElideRight,size().width(),0);

    if (! at2->isActive()&&at3->isActive())
    {
        if (step3!=tmp3.length())
           painter.drawText(QRect(5,45,size().width(),100), tmp3.left(step3) );
    }
    if(! at1->isActive()&&! at2->isActive()&& !at3->isActive())
        painter.drawText(QRect(5,45,size().width(),100), tmp3 );

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //draw year

    painter.setFont(QFont(painter.font().family(), 13,false));
    tmp4= painter.fontMetrics().elidedText(_year,Qt::ElideRight,size().width(),0);

    if (! at3->isActive()&&at4->isActive())
    {
        if (step4!=tmp4.length())
           painter.drawText(QRect(5,63,size().width(),100), tmp4.left(step4) );
    }
    if(! at1->isActive()&&! at2->isActive()&& !at3->isActive()&& !at4->isActive())
        painter.drawText(QRect(5,63,size().width(),100), tmp4 );*/

}
void  rphLabelEx::drawTitle(QString title)
{
   _title= title;
    at1->start(5);//
  //_drawtext=true;
   // QTimer::singleShot(2000, at1, SLOT(stop()));
     //QTimer::singleShot(2000,this,SLOT(drawall()));

}
void  rphLabelEx::drawYearString(QString year)
{
    _year= year;
   //at4->start(2);//2
   // QTimer::singleShot(2000, at4, SLOT(stop()));
}

void  rphLabelEx::drawAlbumString(QString album)
{
    _album= album;
   // at3->start(2);//2
    // QTimer::singleShot(2000, at3, SLOT(stop()));
}
void  rphLabelEx::drawArtistName(QString artist)
{
    _artist=artist;
   // at2->start(2);//4
    // QTimer::singleShot(2000, at2, SLOT(stop()));


}
void  rphLabelEx::drawCustomText(QString txt,int fontsize)
{
    _text=txt;
    _fontsize=fontsize;

    update();

}
void rphLabelEx::animatet1()
{
   step1++;
   if(step1==tmp1.length())
   {at1->stop();
    at2->start(5);
   }
 update();
}
void rphLabelEx::animatet2()
{
    step2++;
    if(step2==tmp2.length())
    {at2->stop();
     at3->start(5);
    }
    update();
}
void rphLabelEx::animatet3()
{
    step3++;
    if(step3==tmp3.length())
    {at3->stop();
     at4->start(5);
    }

   update();

}
void rphLabelEx::animatet4()
{
    step4++;
    if(step4==tmp4.length())
    {at4->stop();

    }
    update();

}

void rphLabelEx::clearText()
{
// _drawtext=false;
_album="";
_year="";
_title="";
_artist="";
at1->stop();
at2->stop();
at3->stop();
at4->stop();
step1 = 0;
step2 = 0;
step3= 0;
step4 = 0;
//at2->start(1);
//at3->start(10);
//at4->start(10);
 update();
}
void rphLabelEx::forcedraw()
{
    if (_album=="")
        _album="Album :Unknown";
    if (_year=="")
        _year="Year :Unknown";
    if (_artist=="")
        _artist="Artist :Unknown";
//at1->start(5);
//at2->start(4);
//at3->start(3);
//at4->start(2);

    update();
}
void  rphLabelEx::setSuffix(QString suf)
{   _suffix=suf;
    labtex=this->text();
    this->setText(this->text()+suf);
}
void rphLabelEx::resizeEvent ( QResizeEvent * event )
{
    emit resizeVideo(event->size().width(),event->size().height());
}
