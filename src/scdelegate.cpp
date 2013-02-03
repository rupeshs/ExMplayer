/*  umplayer, GUI front-end for mplayer.
    Copyright (C) 2010 Ori Rejwan

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

#include "scdelegate.h"
#include <QPainter>
#include <QDebug>
#include <QTextLayout>
#include <QTextLine>
#include "scdataapi.h"



SCDelegate::SCDelegate(QObject *parent) :
    QStyledItemDelegate(parent), scIcon(":/images/bg-shoutcast-icon.png")
{
    hoverPixmap = QPixmap(":/images/sc-hover-background.png");
}

QSize SCDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 65);
}

void SCDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    bool white = false;
    if(index.data(ClickRole).toBool())
    {
        painter->drawPixmap(option.rect, hoverPixmap);
        white = true;
    }
    else
    {
        if(index.row() % 2 > 0)
        {
            painter->fillRect(option.rect, Qt::white);
        }
        else
        {
            painter->fillRect(option.rect, QColor("#F1F5FA") );
        }
    }
    painter->translate(option.rect.topLeft());    
    QPen pen(cr(QColor("#e3e3e3"), white));
    painter->setPen(pen);
    painter->drawLine(0, 64, option.rect.width(), 64);
    painter->drawPixmap( 8, 11, scIcon );
    painter->translate(scIcon.width() + 16, 0 );
    SingleSCResult* sc = qVariantValue<SingleSCResult*>(index.data());
    QFont font = painter->font();
    font.setPixelSize(11);
    painter->setFont(font);
    QFontMetrics fm(font);
    painter->setPen(cr(QColor("#636363"), white));
    QRect textRect(0, 7, 60, 13 );
    QRect actualTextRect;
    QRect rightTextRect;

    int wid = option.rect.width() - scIcon.width() - 16;
    painter->drawText(textRect, Qt::AlignTop | Qt::AlignLeft, "Station: ", &actualTextRect);
    painter->setPen(cr(Qt::black, white));

    rightTextRect = QRect(actualTextRect.topRight(), QSize(wid - actualTextRect.width(), actualTextRect.height()));
    painter->drawText(rightTextRect, Qt::AlignTop| Qt::AlignLeft, fm.elidedText(sc->name, Qt::ElideRight, rightTextRect.width()));


    painter->setPen(cr(QColor("#636363"), white));
    textRect.translate(0, 18);
    painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, "Now playing: ", &actualTextRect);
    painter->setPen(cr(Qt::black, white));
    rightTextRect = QRect(actualTextRect.topRight(), QSize(wid - actualTextRect.width(), actualTextRect.height()));
    painter->drawText(rightTextRect, Qt::AlignTop | Qt::AlignLeft, fm.elidedText(sc->song, Qt::ElideRight, rightTextRect.width()));
    painter->setPen(cr(QColor("#636363"), white));
    textRect.translate(0, 18);
    textRect.setWidth(wid);
    drawGenreLine(painter, textRect, sc, white);
    painter->restore();
}

void SCDelegate::drawGenreLine(QPainter *painter, QRect area, SingleSCResult *ssr, bool white) const
{
    area.setWidth(area.width() - 2);
    QString dataString = "%L1 Listeners, %2 kbps, %3";
    dataString = dataString.arg(ssr->listeners.toInt()).arg(ssr->bitrate);
    if(ssr->format.endsWith("mp3"))
        dataString = dataString.arg("MP3");
    else if(ssr->format.endsWith("aacp"))
        dataString = dataString.arg("AAC+");
    QString genreString = " Genre: %1";
    genreString = genreString.arg(ssr->genre);
    QString finalString = dataString + genreString;
    QTextLayout textLayout(finalString);
    // Formats
    QList<QTextLayout::FormatRange> formats;
    QTextLayout::FormatRange fr;
    QTextCharFormat greyFormat;
    greyFormat.setFont(painter->font());
    greyFormat.setForeground(cr(QColor("#636363"), white));
    QTextCharFormat blackUnderlineFormat;
    blackUnderlineFormat.setFont(painter->font());
    blackUnderlineFormat.setForeground(cr(QColor(Qt::black), white));
    blackUnderlineFormat.setFontUnderline(true);
    QTextCharFormat blackFormat;
    blackFormat.setFont(painter->font());
    blackFormat.setForeground(cr(QColor(Qt::black), white));
    int ListenIndex = finalString.indexOf("Listen");
    int kbpsIndex = finalString.indexOf("kbps");
    int genreIndex = finalString.indexOf("Genre");
    fr.start = ListenIndex ; fr.length = 10; fr.format = greyFormat;
    formats.append(fr);
    fr.start = kbpsIndex; fr.length = 4; fr.format = greyFormat;
    formats.append(fr);
    fr.start = 0; fr.length = ListenIndex - 1; fr.format = blackFormat;
    formats.append(fr);
    fr.start = ListenIndex + 9; fr.length = kbpsIndex - fr.start - 1 ; fr.format = blackFormat;
    formats.append(fr);
    fr.start = kbpsIndex + 5; fr.length = genreIndex - fr.start -1; fr.format = blackFormat;
    formats.append(fr);
    fr.start = genreIndex; fr.length = 7; fr.format = greyFormat;
    formats.append(fr);
    int start = genreIndex+ 7;
    while(true)
    {
        fr.start = start; fr.length = finalString.indexOf(" ", fr.start) - fr.start; fr.format = blackUnderlineFormat;
        if(fr.length < 0)
        {
            fr.length = finalString.length() - fr.start;
            formats.append(fr);
            break;
        }
        formats.append(fr);
        start = fr.start + fr.length + 1;
    }
    textLayout.setFont(painter->font());
    textLayout.beginLayout();
    textLayout.setAdditionalFormats(formats);
    QTextLine dataLine = textLayout.createLine();
    QFontMetrics fm = painter->fontMetrics();    
    dataLine.setNumColumns(dataString.length() + 1);    
    dataLine.setPosition(QPointF(area.width() - dataLine.naturalTextWidth(), fm.leading()));
    QTextLine genreLine = textLayout.createLine();
    genreLine.setLineWidth(area.width() - dataLine.naturalTextWidth()-2);
    genreLine.setPosition(QPointF(0,fm.leading()));
    textLayout.endLayout();
    textLayout.draw(painter, QPointF(0, area.top() + (area.height() - dataLine.height())/2.0 ));

}
