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
#ifndef RPHLABELEX_H
#define RPHLABELEX_H
#include <QLabel>
#include <QtGui>
#include <QTimer>
class QRubberBand;
class rphLabelEx : public QLabel
{
Q_OBJECT
public:
    rphLabelEx( QWidget  *parent = 0);
    QRubberBand *rubberBand;
    QPoint origin;
    bool  isemptyTitle(){_title.isEmpty();}
    void  forcedraw();
    void  clearText();
    QString tmp1,tmp2,tmp3,tmp4;
    void  drawYearString(QString year);
    void  drawAlbumString(QString album);
    void  drawTitle(QString title);
    void  drawCustomText(QString txt,int fontsize);
    void  drawArtistName(QString artist);
    void  setSuffix(QString suf);
    void showeof(bool en){_showeof=en;update();};

public slots:
    void showRubberBand(bool val){mrubberBand=val;};
    void  animatet1();
    void  animatet2();
    void  animatet3();
    void  animatet4();
    void  drawall(){_drawtext=true;};
    void showErrorText(QString tex){_errtext=tex;clearText();update();};
signals:
    void rectRubberBand(QRect *val);
     void resizeVideo(int wid,int hei);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool md ;
    bool mrubberBand;
    void paintEvent (QPaintEvent * event ) ;
    void resizeEvent ( QResizeEvent * event ) ;
private:
    QString _title;
    QString _artist;
    QString _album;
    QString _year;
    QString _text;
    QString _suffix;
    QString labtex;
    int  _fontsize;
    QTimer *at1;
    QTimer *at2;
    QTimer *at3;
    QTimer *at4;
    int step1;
    int step2;
    int step3;
    int step4;
    bool _showeof;
    bool _drawtext;
    QString _errtext;

};
#endif // RPHLABELEX_H
