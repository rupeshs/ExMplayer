/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2015 Rupesh Sreeraman

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

#ifndef GLASSSTYLE_H
#define GLASSSTYLE_H
#include <QProxyStyle>
#include <qdebug.h>

class GlassStyle : public  QProxyStyle
 {
     Q_OBJECT
 private:

 public:
     GlassStyle();
    ~GlassStyle() {}


     // toolbar, tab, toolbox
     QColor m_colorBarBegin;
     QColor m_colorBarMiddle;
     QColor m_colorBarEnd;

     // toolbar shadow, tab, toolbox tab
     QColor m_colorBorder;
     QColor m_colorBorderLight;

     // toolbar handle
     QColor m_colorHandle;
     QColor m_colorHandleLight;

     // menu, toolbar
     QColor m_colorSeparator;
     QColor m_colorSeparatorLight;

     // menu, toolbar, tab, toolbox
     QColor m_colorMenuItemBorder;
     QColor m_colorItemBorder;
     QColor m_colorItemBackgroundBegin;
     QColor m_colorItemBackgroundMiddle;
     QColor m_colorItemBackgroundEnd;
     QColor m_colorItemCheckedBegin;
     QColor m_colorItemCheckedMiddle;
     QColor m_colorItemCheckedEnd;
     QColor m_colorItemSunkenBegin;
     QColor m_colorItemSunkenMiddle;
     QColor m_colorItemSunkenEnd;


     // menu
     QColor m_colorMenuBorder;
     QColor m_colorMenuBackground;
     QColor m_colorMenuTitleBegin;
     QColor m_colorMenuTitleEnd;

     // main window, toolbox
     QColor m_colorBackgroundBegin;
     QColor m_colorBackgroundEnd;
     QSize sizeFromContents( ContentsType type, const QStyleOption* option,
         const QSize& contentsSize, const QWidget* widget ) const;

     void polish( QWidget* widget );
     void unpolish( QWidget* widget );
     int pixelMetric( PixelMetric metric, const QStyleOption* option, const QWidget* widget ) const;
     void   drawControl( ControlElement element, const QStyleOption* option,
         QPainter* painter, const QWidget* widget ) const;
     void drawPrimitive( PrimitiveElement element, const QStyleOption* option,
           QPainter* painter, const QWidget* widget ) const;
     void drawComplexControl( ComplexControl control, const QStyleOptionComplex* option,
         QPainter* painter, const QWidget* widget ) const;
      };
#endif // GLASSSTYLE_H
