/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2021 Rupesh Sreeraman

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

#include "glassstyle.h"
#include <QStyleOption>
#include <QPainter>
#include <QLibrary>
#include <QApplication>
#include <QMainWindow>
#include <QAbstractButton>
#include <QToolBox>
#include <QScrollArea>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLayout>

GlassStyle::GlassStyle()
{

    m_colorBackgroundBegin = qRgb( 158, 190, 245 );
    m_colorBackgroundEnd = qRgb( 196, 218, 250 );

    m_colorMenuBorder = qRgba(167, 185, 221,100 );
    m_colorMenuBackground = qRgb( 250, 250, 255 );

    m_colorMenuTitleBegin = qRgb( 240, 240, 255 );
    m_colorMenuTitleEnd = qRgb( 250, 250, 255 );

    m_colorBarBegin = qRgb( 255, 255, 255 );
    m_colorBarMiddle = qRgb( 225, 225, 225 );
    m_colorBarEnd = qRgb( 255,255, 255 );

    m_colorHandle = qRgb( 250, 250, 250 );
    m_colorHandleLight = qRgb( 255, 255, 255 );
    m_colorSeparator = qRgba( 200, 200, 200,100 );
    m_colorSeparatorLight = qRgb( 255, 255, 255 );
    m_colorMenuItemBorder=qRgba(144,199, 227,255 );
    m_colorItemBorder = qRgba(255,255, 255,255 );

    m_colorItemBackgroundBegin = qRgb( 255, 255, 255 );
    m_colorItemBackgroundMiddle = QColor(29,186,255,5);
    m_colorItemBackgroundEnd = qRgb( 255, 255, 255 );

    m_colorItemCheckedBegin = QColor( 100,100,100,10 );
    m_colorItemCheckedMiddle =QColor( 200,230,200,50 ) ;
    m_colorItemCheckedEnd =QColor( 0,255,0,60 ) ;

    m_colorItemSunkenBegin = qRgb( 240, 240, 240 );
    m_colorItemSunkenMiddle = QColor(255,255,255,255);
    m_colorItemSunkenEnd = qRgb( 250, 250, 250 );

    m_colorBorder = qRgb( 255,0, 0 );
    m_colorBorderLight = qRgb(0 , 255, 0 );

}
int GlassStyle::pixelMetric( PixelMetric metric, const QStyleOption* option, const QWidget* widget ) const
{
    switch ( metric ) {
    case PM_LayoutVerticalSpacing:
        return 0;
    case PM_MenuBarPanelWidth:
        return 0;
    case PM_MenuBarVMargin:
        return 2;
    case PM_MenuBarHMargin:
        return 2;
    case PM_MenuPanelWidth:
        return 2;
    case PM_MenuHMargin:
        return 2;
    case PM_MenuVMargin:
        return 2;
    case PM_MenuButtonIndicator:
        return 12;
    case PM_ToolBarFrameWidth:
        return 2;
    case PM_ToolBarItemMargin:

    case PM_ToolBarItemSpacing:
        return 0;

        if ( widget && qobject_cast<QToolBar*>( widget->parentWidget() ) )
            return 0;

    default:
        break;
    }
    return QProxyStyle::pixelMetric( metric, option, widget );

}
QSize GlassStyle::sizeFromContents( ContentsType type, const QStyleOption* option,
                                    const QSize& contentsSize, const QWidget* widget ) const
{
    switch ( type ) {
    case CT_MenuBar:
        return contentsSize - QSize( 0, 1 );

    case CT_Menu:
#if ( QT_VERSION < 0x040400 )
        return contentsSize - QSize( 0, 1 );
#else
        return contentsSize;
#endif

    case CT_MenuBarItem:
        break;

    case CT_MenuItem:
        if ( const QStyleOptionMenuItem* menuItem = qstyleoption_cast<const QStyleOptionMenuItem*>( option ) ) {
            if ( menuItem->menuItemType == QStyleOptionMenuItem::Separator )
                return QSize( 10, 3 );
            int space = 32 + 16;
            if ( menuItem->text.contains( '\t' ) )
                space += 12;
            return QSize( contentsSize.width() + space, 22 );
        }
        break;

    default:
        break;
    }

    return QProxyStyle::sizeFromContents( type, option, contentsSize, widget );
}
void  GlassStyle::polish( QWidget* widget )
{
    if ( qobject_cast<QMainWindow*>( widget ) )
        widget->setAttribute( Qt::WA_StyledBackground );

    QProxyStyle::polish( widget );
}

void GlassStyle::unpolish( QWidget* widget )
{
    if ( qobject_cast<QMainWindow*>( widget ) )
        widget->setAttribute( Qt::WA_StyledBackground, false );

    QProxyStyle::unpolish( widget );

}
void GlassStyle::drawPrimitive( PrimitiveElement element, const QStyleOption* option,
                                QPainter* painter, const QWidget* widget ) const
{


    switch ( element ) {
    case PE_Widget:
    {

        if ( qobject_cast<const QMainWindow*>( widget ) ) {
            QRect rect=option->rect;

            if (QToolBar*  toolBar = widget->findChild<QToolBar*>())
            {
                QRect rect =  toolBar ->geometry();

                QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());
                gradient.setColorAt( 0.0, m_colorBarBegin );
                gradient.setColorAt( 0.5, m_colorBarMiddle );
                gradient.setColorAt( 1.0,QColor(255,255,255,255));
                painter->fillRect( rect, gradient );
                QLinearGradient gradient2(rect.topLeft(), rect.bottomLeft()/2);
                gradient2.setColorAt( 0.0, QColor(255,255,255,100) );
                gradient2.setColorAt( 0.5, QColor(255,255,255,100));

                gradient.setColorAt( 0.0, QColor(255,255,255,150) );
                gradient.setColorAt( 0.4, QColor(255,255,255,150) );
                gradient.setColorAt( 0.6,QColor(240,240,240,250)  );
                gradient.setColorAt( 1.0,QColor(255,255,255,255) );
                QRect rect2 = rect;

                rect2.setHeight(rect.height()/2);
                painter->fillRect( rect2, gradient );
            }

            if (QMenuBar*  menuBar = widget->findChild<QMenuBar*>() )
            {
                QRect rect = menuBar->geometry();

                QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());
                gradient.setColorAt( 0.0,m_colorBarBegin );
                gradient.setColorAt( 1.0,QColor(255,255,255,255) );
                painter->fillRect( rect, gradient );
                gradient.setColorAt( 0.0, QColor(255,255,255,255) );
                gradient.setColorAt( 1.0,QColor(255,255,255,255) );

                QRect rect2 = rect;
                rect2.setHeight(rect.height()/2);
                painter->fillRect( rect2, gradient );

            }
            if ( QStatusBar* statusBar = widget->findChild<QStatusBar*>() )
            {
                QRect rect =  statusBar->geometry();
                QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());

                gradient.setColorAt( 0.0, m_colorBarBegin );
                gradient.setColorAt( 1.0,QColor(255,255,255,255));
                painter->fillRect( rect, gradient );
                gradient.setColorAt( 0.0, QColor(255,255,255,150) );
                gradient.setColorAt( 1.0,QColor(255,255,255,255) );

                QRect rect2 = rect;
                rect2.setHeight(rect.height()/2);
                painter->fillRect( rect2, gradient );

            }

            return;
        }

        if ( qobject_cast<const QToolBox*>( widget ) ) {
            QLinearGradient gradient( option->rect.topLeft(), option->rect.topRight() );
            gradient.setColorAt( 0.4, m_colorBackgroundBegin );
            gradient.setColorAt( 1.0, m_colorBackgroundEnd );
            painter->fillRect( option->rect, gradient );
            return;
        }


        break;

    }


    case PE_PanelToolBar:
    {QRect rect = option->rect;
        bool vertical = false;
        QRegion region = rect.adjusted( 2, 0, -2, 0 );
        region += rect.adjusted( 0, 2, 0, -2 );
        region += rect.adjusted( 1, 1, -1, -1 );
        painter->setClipRegion( region );
        QLinearGradient gradient;

        gradient = QLinearGradient( rect.topLeft(), rect.bottomLeft() );

        gradient.setColorAt( 0.0, m_colorBarBegin );
        gradient.setColorAt( 0.4, m_colorItemBackgroundMiddle );
        gradient.setColorAt( 0.6, m_colorItemBackgroundMiddle );
        gradient.setColorAt( 1.0, m_colorItemBackgroundEnd );
        painter->fillRect( rect, gradient );

    }
        return;
    case PE_FrameStatusBar:
    {
        QRect rect = option->rect;
        bool vertical = false;
        //rect.setRight( toolBar->childrenRect().right() + 2 );
        //painter->save();
        QRegion region = rect.adjusted( 2, 0, -2, 0 );
        region += rect.adjusted( 0, 2, 0, -2 );
        region += rect.adjusted( 1, 1, -1, -1 );
        painter->setClipRegion( region );
        QLinearGradient gradient;

        gradient = QLinearGradient( rect.topLeft(), rect.bottomLeft() );

        gradient.setColorAt( 0.0, m_colorBarBegin );
        gradient.setColorAt( 0.4, m_colorItemBackgroundMiddle );
        gradient.setColorAt( 0.6, m_colorItemBackgroundMiddle );
        gradient.setColorAt( 1.0, m_colorItemBackgroundEnd );
        painter->fillRect( rect, gradient );
        //qDebug("status");
    }

        return;
    case PE_PanelMenuBar:
        return;
    case PE_FrameMenu:
        painter->setPen( m_colorMenuBorder );
        painter->setBrush( Qt::NoBrush );
        painter->drawRect( option->rect.adjusted( 0, 0, -1, -1 ) );

        if ( const QMenu* menu = qobject_cast<const QMenu*>( widget ) ) {
            if ( const QMenuBar* menuBar = qobject_cast<const QMenuBar*>( menu->parent() ) ) {
                QRect rect = menuBar->actionGeometry( menu->menuAction() );
                if ( !rect.isEmpty() ) {
                    painter->setPen( m_colorMenuBackground );
                    painter->drawLine( 1, 0, rect.width() - 2, 0 );
                }
            }
        }

        if ( const QToolBar* toolBar = qobject_cast<const QToolBar*>( widget ) ) {
            QRect rect = option->rect.adjusted( 1, 1, -1, -1 );
            QLinearGradient gradient;
            if ( toolBar->orientation() == Qt::Vertical )
                gradient = QLinearGradient( rect.topLeft(), rect.topRight() );
            else
                gradient = QLinearGradient( rect.topLeft(), rect.bottomLeft() );
            gradient.setColorAt( 0.0, m_colorBarBegin );
            gradient.setColorAt( 0.4, m_colorBarMiddle );
            gradient.setColorAt( 0.6, m_colorBarMiddle );
            gradient.setColorAt( 1.0, m_colorBarEnd );
            painter->fillRect( rect, gradient );
        }
        return;

    case PE_IndicatorToolBarHandle:
        if ( option->state & State_Horizontal ) {
            for ( int i = option->rect.height() / 5; i <= 4 * ( option->rect.height() / 5 ); i += 5 ) {
                int x = option->rect.left() + 3;
                int y = option->rect.top() + i + 1;
                painter->fillRect( x + 1, y, 2, 2, m_colorHandleLight );
                painter->fillRect( x, y - 1, 2, 2, m_colorHandle );
            }
        } else {
            for ( int i = option->rect.width() / 5; i <= 4 * ( option->rect.width() / 5 ); i += 5 ) {
                int x = option->rect.left() + i + 1;
                int y = option->rect.top() + 3;
                painter->fillRect( x, y + 1, 2, 2, m_colorHandleLight );
                painter->fillRect( x - 1, y, 2, 2, m_colorHandle );
            }
        }
        return;

    case PE_IndicatorToolBarSeparator:
        painter->setPen( m_colorSeparator );
        if ( option->state & State_Horizontal )
            painter->drawLine( ( option->rect.left() + option->rect.right() - 1 ) / 2, option->rect.top() + 2,
                               ( option->rect.left() + option->rect.right() - 1 ) / 2, option->rect.bottom() - 2 );
        else
            painter->drawLine( option->rect.left() + 2, ( option->rect.top() + option->rect.bottom() - 1 ) / 2,
                               option->rect.right() - 2, ( option->rect.top() + option->rect.bottom() - 1 ) / 2 );
        painter->setPen( m_colorSeparatorLight );
        if ( option->state & State_Horizontal )
            painter->drawLine( ( option->rect.left() + option->rect.right() + 1 ) / 2, option->rect.top() + 2,
                               ( option->rect.left() + option->rect.right() + 1 ) / 2, option->rect.bottom() - 2 );
        else
            painter->drawLine( option->rect.left() + 2, ( option->rect.top() + option->rect.bottom() + 1 ) / 2,
                               option->rect.right() - 2, ( option->rect.top() + option->rect.bottom() + 1 ) / 2 );
        return;
    case PE_IndicatorButtonDropDown: {
        QToolBar* toolBar;
        if ( widget && ( toolBar = qobject_cast<QToolBar*>( widget->parentWidget() ) ) ) {
            QRect rect = option->rect.adjusted( -1, 0, -1, -1 );
            bool selected = option->state & State_MouseOver && option->state & State_Enabled;
            bool sunken = option->state & State_Sunken;
            if ( selected || sunken ) {
                // painter->setPen( m_colorItemBorder );
                if ( toolBar->orientation() == Qt::Vertical ) {
                    if ( sunken )
                        painter->setBrush( m_colorItemSunkenEnd );
                    else
                        painter->setBrush( m_colorItemBackgroundEnd );
                } else {
                    QLinearGradient gradient( rect.topLeft(), rect.bottomLeft() );
                    if ( sunken ) {
                        gradient.setColorAt( 0.0, m_colorItemSunkenBegin );
                        gradient.setColorAt( 0.5, m_colorItemSunkenMiddle );
                        gradient.setColorAt( 1.0, m_colorItemSunkenEnd );
                    } else {
                        gradient.setColorAt( 0.0, m_colorItemBackgroundBegin );
                        gradient.setColorAt( 0.5, m_colorItemBackgroundMiddle );
                        gradient.setColorAt( 1.0, m_colorItemBackgroundEnd );
                    }
                    painter->setBrush( gradient );
                }
                painter->drawRect( rect );
            }
            QStyleOption optionArrow = *option;
            optionArrow.rect.adjust( 2, 2, -2, -2 );
            drawPrimitive( PE_IndicatorArrowDown, &optionArrow, painter, widget );
            return;
        }

    }
    default: break;

    }
    QProxyStyle::drawPrimitive( element, option, painter, widget );
}


void GlassStyle::drawControl( ControlElement element, const QStyleOption* option,
                              QPainter* painter, const QWidget* widget ) const
{
    switch ( element ) {


    case CE_MenuBarEmptyArea:
        return;
    case CE_DockWidgetTitle: {

        QLinearGradient gradient( option->rect.topLeft(), option->rect.bottomLeft() );

        gradient.setColorAt( 0.0, m_colorBarBegin );
        gradient.setColorAt( 1.0, m_colorBarEnd);

        painter->fillRect( option->rect, gradient );

        if ( const QStyleOptionDockWidget* optionDockWidget = qstyleoption_cast<const QStyleOptionDockWidget*>( option ) ) {
            QRect rect = option->rect.adjusted( 6, 0, -4, 0 );
            if ( optionDockWidget->closable )
                rect.adjust( 0, 0, -16, 0 );
            if ( optionDockWidget->floatable )
                rect.adjust( 0, 0, -16, 0 );
            QString text = painter->fontMetrics().elidedText( optionDockWidget->title, Qt::ElideRight, rect.width() );
            drawItemText( painter, rect, Qt::AlignLeft | Qt::AlignVCenter, option->palette,
                          option->state & State_Enabled, text, QPalette::WindowText );
        }
        return;

    }
    case CE_MenuBarItem:

        if ( option->state & QStyle::State_Sunken && option->state & QStyle::State_Enabled ) {
            painter->setPen( m_colorMenuBorder );
            QLinearGradient gradient( option->rect.topLeft(), option->rect.bottomLeft() );
            gradient.setColorAt( 0.0, m_colorMenuTitleBegin );
            gradient.setColorAt( 1.0, m_colorMenuTitleEnd );
            painter->setBrush( gradient );
            painter->drawRect( option->rect.adjusted( 0, 0, -1, 0 ) );
        } else if ( option->state & QStyle::State_Selected && option->state & QStyle::State_Enabled ) {
            painter->setPen( m_colorMenuItemBorder );
            QLinearGradient gradient( option->rect.topLeft(), option->rect.bottomLeft() );
            gradient.setColorAt( 0.0, m_colorItemBackgroundBegin );
            gradient.setColorAt( 0.5, QColor(29,186,255,150) );
            gradient.setColorAt( 1.0, m_colorItemBackgroundEnd );
            painter->setBrush( gradient );
            painter->drawRect( option->rect.adjusted( 0, 0, -1, -1 ) );
        }
        if ( const QStyleOptionMenuItem* optionItem = qstyleoption_cast<const QStyleOptionMenuItem*>( option ) ) {
            int flags = Qt::AlignCenter | Qt::TextShowMnemonic | Qt::TextDontClip | Qt::TextSingleLine;
            if ( !styleHint( SH_UnderlineShortcut, option, widget ) )
                flags |= Qt::TextHideMnemonic;
            if ( !optionItem->icon.isNull() ) {
                QPixmap pixmap = optionItem->icon.pixmap( pixelMetric( PM_SmallIconSize, option, widget ), QIcon::Normal );
                drawItemPixmap( painter, option->rect, flags, pixmap );
            } else {
                drawItemText( painter, option->rect, flags, option->palette, true, optionItem->text, QPalette::Text );
            }
        }
        return;

    case CE_MenuItem: {
        if (
                //menu select
                option->state & QStyle::State_Selected && option->state & QStyle::State_Enabled ) {
            painter->setPen(QColor(29,186,255,200) );

            QLinearGradient gradient (option->rect.topLeft(), option->rect.bottomLeft() );

            gradient.setColorAt( 0.0, m_colorItemBackgroundBegin );
            gradient.setColorAt( 0.5,  QColor(29,186,255,240) );
            gradient.setColorAt( 1.0,m_colorItemBackgroundEnd);
            painter->setBrush( gradient );

            painter->drawRect(option->rect.adjusted( 0, 0, -2,-2 ) );
            QLinearGradient gradient2 (option->rect.adjusted( 0, 0, -2,-2 ).topLeft(),option->rect.adjusted( 0, 0, -2,-2 ).bottomLeft() /2);
            //select
            gradient2.setColorAt( 0.0, QColor(255,255,255,120));
            gradient2.setColorAt( 1.0, QColor(255,255,255,120));
            painter->setBrush( gradient2 );
            painter->drawRect(option->rect.adjusted( 0, 0, -2,-2 ) );

        } else {
            QLinearGradient gradient( QPoint( 0, 0 ), QPoint( 25, 0 ) );
            //SIDE
            gradient.setColorAt( 0.0, QColor(220,220,220,255));
            //gradient.setColorAt( 0.5, QColor(29,186,255,200));
            gradient.setColorAt( 1.0,m_colorBarEnd );
            QRect margin = option->rect;
            margin.setWidth( 25 );
            painter->fillRect( margin, gradient );

            //====================
            QLinearGradient gradient2( QPoint( 0, 0 ), QPoint( 12, 0 ) );
            //SIDE
            gradient2.setColorAt( 0.0, QColor(255,255,255,130) );
            gradient2.setColorAt( 1.0,QColor(255,255,255,130) );
            QRect margin2 = option->rect;
            margin2.setWidth( 12 );
            painter->fillRect( margin2, gradient2 );

            QRect background = option->rect;
            background.setLeft( margin.right() + 1 );
            painter->fillRect( background, m_colorMenuBackground );
        }
        if ( const QStyleOptionMenuItem* optionItem = qstyleoption_cast<const QStyleOptionMenuItem*>( option ) ) {
            if ( optionItem->menuItemType == QStyleOptionMenuItem::Separator ) {
                painter->setPen( m_colorSeparator );
                painter->drawLine( option->rect.left() + 32, ( option->rect.top() + option->rect.bottom() ) / 2,
                                   option->rect.right(), ( option->rect.top() + option->rect.bottom() ) / 2 );
                return;
            }
            QRect checkRect = option->rect.adjusted( 2, 1, -2, -2 );
            checkRect.setWidth( 20 );
            if ( optionItem->checked && option->state & QStyle::State_Enabled ) {
                painter->setPen( m_colorItemBorder );
                if ( option->state & QStyle::State_Selected && option->state & QStyle::State_Enabled )
                    painter->setBrush( m_colorItemSunkenBegin );
                else
                    painter->setBrush( m_colorItemCheckedBegin );
                painter->drawRect( checkRect );
            }
            if ( !optionItem->icon.isNull() ) {
                QIcon::Mode mode;
                if ( optionItem->state & State_Enabled )
                    mode = ( optionItem->state & State_Selected ) ? QIcon::Active : QIcon::Normal;
                else
                    mode = QIcon::Disabled;
                QIcon::State state = optionItem->checked ? QIcon::On : QIcon::Off;
                QPixmap pixmap = optionItem->icon.pixmap( pixelMetric( PM_SmallIconSize, option, widget ), mode, state );
                QRect rect = pixmap.rect();
                rect.moveCenter( checkRect.center() );
                painter->drawPixmap( rect.topLeft(), pixmap );
            } else if ( optionItem->checked ) {
                QStyleOption optionCheckMark;
                optionCheckMark.initFrom( widget );
                optionCheckMark.rect = checkRect;
                if ( !( option->state & State_Enabled ) )
                    optionCheckMark.palette.setBrush( QPalette::Text, optionCheckMark.palette.brush( QPalette::Disabled, QPalette::Text ) );
                drawPrimitive( PE_IndicatorMenuCheckMark, &optionCheckMark, painter, widget );
            }
            QRect textRect = option->rect.adjusted( 32, 1, -16, -1 );
            int flags = Qt::AlignVCenter | Qt::TextShowMnemonic | Qt::TextDontClip | Qt::TextSingleLine;
            if ( !styleHint( SH_UnderlineShortcut, option, widget ) )
                flags |= Qt::TextHideMnemonic;
            QString text = optionItem->text;
            int pos = text.indexOf( '\t' );
            if ( pos >= 0 ) {
                drawItemText( painter, textRect, flags | Qt::AlignRight, option->palette, option->state & State_Enabled,
                              text.mid( pos + 1 ), QPalette::Text );
                text = text.left( pos );
            }
            drawItemText( painter, textRect, flags, option->palette, option->state & State_Enabled, text, QPalette::Text );
            if ( optionItem->menuItemType == QStyleOptionMenuItem::SubMenu ) {
                QStyleOption optionArrow;
                optionArrow.initFrom( widget );
                optionArrow.rect = option->rect.adjusted( 0, 4, -4, -4 );
                optionArrow.rect.setLeft( option->rect.right() - 12 );
                optionArrow.state = option->state & State_Enabled;
                drawPrimitive( PE_IndicatorArrowRight, &optionArrow, painter, widget );
            }
        }
        return;
    }

    case CE_ToolBar:{
        QRect rect = option->rect;
        bool vertical = false;
        if ( const QToolBar* toolBar = qobject_cast<const QToolBar*>( widget ) ) {
            vertical = ( toolBar->orientation() == Qt::Vertical );
            if ( vertical )
                rect.setBottom( toolBar->childrenRect().bottom() + 2 );
            else
                rect.setRight( toolBar->childrenRect().right() + 2 );
        }
       //painter->save();
        QRegion region = rect.adjusted( 2, 0, -2, 0 );
        region += rect.adjusted( 0, 2, 0, -2 );
        region += rect.adjusted( 1, 1, -1, -1 );
        painter->setClipRegion( region );
        QLinearGradient gradient;
        if ( vertical )
            gradient = QLinearGradient( rect.topLeft(), rect.topRight() );
        else
            gradient = QLinearGradient( rect.topLeft(), rect.bottomLeft() );

        gradient.setColorAt( 0.0, m_colorBarBegin );
        //gradient.setColorAt( 0.4, m_colorBarMiddle );
       // gradient.setColorAt( 0.6, m_colorBarMiddle );
        gradient.setColorAt( 1.0,QColor(255,255,255,255));
        painter->fillRect( rect, gradient );

        gradient.setColorAt( 0.0, QColor(255,255,255,150) );
        gradient.setColorAt( 0.4, QColor(255,255,255,150) );
        //gradient.setColorAt( 0.6,QColor(240,240,240,250)  );
        gradient.setColorAt( 1.0,QColor(255,255,255,255) );
        QRect rect2 = option->rect;

        rect2.setHeight(rect.height()/2);
        painter->fillRect( rect2, gradient );

        painter->setPen( vertical ? m_colorBorderLight : m_colorBorder );
        //painter->drawLine( rect.bottomLeft() + QPoint( 2, 0 ), rect.bottomRight() - QPoint( 2, 0 ) );
        painter->setPen( vertical ? m_colorBorder : m_colorBorderLight );
        //painter->drawLine( rect.topRight() + QPoint( 0, 2 ), rect.bottomRight() - QPoint( 0, 2 ) );
        painter->setPen( m_colorBorderLight );
        painter->drawPoint( rect.bottomRight() - QPoint( 1, 1 ) );

        return;
    }
    }
    QProxyStyle::drawControl( element, option, painter, widget );

}
void GlassStyle::drawComplexControl( ComplexControl control, const QStyleOptionComplex* option,
                                     QPainter* painter, const QWidget* widget ) const
{

    switch ( control ) {

    case CC_ToolButton: {
        QToolBar* toolBar;
        if ( widget && ( toolBar = qobject_cast<QToolBar*>( widget->parentWidget() ) ) ) {
            if ( const QStyleOptionToolButton* optionToolButton = qstyleoption_cast<const QStyleOptionToolButton*>( option ) ) {
                QRect buttonRect = subControlRect( control, option, SC_ToolButton, widget );

                QStyle::State buttonState = option->state & ~State_Sunken;
                if ( option->state & State_Sunken ) {
                    if ( optionToolButton->activeSubControls & SC_ToolButton )
                        buttonState |= State_Sunken;
                    else if ( optionToolButton->activeSubControls & SC_ToolButtonMenu )
                        buttonState |= State_MouseOver;
                }
                bool selected = buttonState & State_MouseOver && option->state & State_Enabled;
                bool checked = buttonState & State_On;
                bool sunken = buttonState & State_Sunken;
                if ( selected || checked || sunken ) {
                    QRect rect = buttonRect.adjusted( 0, 0, -1, -1 );
                    painter->setPen( m_colorItemBorder );
                    QLinearGradient gradient;
                    if ( toolBar->orientation() == Qt::Vertical )
                        gradient = QLinearGradient( rect.topLeft(), rect.topRight() );
                    else
                        gradient = QLinearGradient( rect.topLeft(), rect.bottomLeft() );
                    if ( sunken || selected && checked ) {
                        gradient.setColorAt( 0.0, m_colorItemSunkenBegin );
                        gradient.setColorAt( 0.5, m_colorItemSunkenMiddle );
                        gradient.setColorAt( 1.0, m_colorItemSunkenEnd );
                    } else if ( checked ) {
                        gradient.setColorAt( 0.0, m_colorItemCheckedBegin );
                        gradient.setColorAt( 0.5, m_colorItemCheckedMiddle );
                        gradient.setColorAt( 1.0, m_colorItemCheckedEnd );
                        //painter->drawLine(buttonRect.right()+1,buttonRect.bottom()+3,buttonRect.width()-2,buttonRect.bottom()+3);

                    } else {


                            gradient.setColorAt( 0.0, m_colorBarBegin );
                            gradient.setColorAt( 0.5,m_colorBarMiddle );
                            gradient.setColorAt( 1.0, m_colorBarEnd );

                    }

                    painter->setBrush( gradient );
                    painter->drawRect( rect );


                }
                QStyleOptionToolButton optionLabel = *optionToolButton;
                int fw = pixelMetric( PM_DefaultFrameWidth, option, widget );
                optionLabel.rect = buttonRect.adjusted( fw, fw, -fw, -fw );
                drawControl( CE_ToolButtonLabel, &optionLabel, painter, widget );
                if ( optionToolButton->subControls & SC_ToolButtonMenu ) {
                    QStyleOption optionMenu = *optionToolButton;
                    optionMenu.rect = subControlRect( control, option, SC_ToolButtonMenu, widget );
                    optionMenu.state = optionToolButton->state & ~State_Sunken;
                    if ( optionToolButton->state & State_Sunken ) {
                        if ( optionToolButton->activeSubControls & SC_ToolButton )
                            optionMenu.state |= State_MouseOver | State_Sunken;
                        else if ( optionToolButton->activeSubControls & SC_ToolButtonMenu )
                            optionMenu.state |= State_Sunken;
                    }
                    drawPrimitive( PE_IndicatorButtonDropDown, &optionMenu, painter, widget );
                }
                else if ( optionToolButton->features & QStyleOptionToolButton::HasMenu ) {

                    int size = pixelMetric( PM_MenuButtonIndicator, option, widget );
                    QRect rect = optionToolButton->rect;
                    QStyleOptionToolButton optionArrow = *optionToolButton;
                    optionArrow.rect = QRect( rect.right() + 4 - size, rect.height() - size + 4, size - 5, size - 5 );
                    drawPrimitive( PE_IndicatorArrowDown, &optionArrow, painter, widget );

                }
                return;
            }
        }
        break;
    }

    default:
        break;
    }


    QProxyStyle::drawComplexControl( control, option, painter, widget );
}
