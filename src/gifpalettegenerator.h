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
#ifndef GIFPALETTEGENERATOR_H
#define GIFPALETTEGENERATOR_H

#include <QObject>
#include <QtCore>
#include <myprocess.h>
#include <QDebug>
#include <QString>
#include <paths.h>
#include <QDesktopServices>
#include <QMessageBox>

//Purpose:
// Generate one palette for a whole video stream.

class GifPaletteGenerator : public QObject
{
    Q_OBJECT
public:
    explicit GifPaletteGenerator(QObject *parent = 0);
    void setFfmpegOptions(QString filename,double startPos,short duration,int fps,long width,long height);
    void generatePalette();

signals:
    void ffmpegexit(int);

public slots:
    void ffmpegConsole(QByteArray);
    void emitProcessFinished(int);

private:
    MyProcess *ffmpegProcess;

};

#endif // GIFPALETTEGENERATOR_H
