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
#ifndef GIFGENERATOR_H
#define GIFGENERATOR_H

#include <QObject>
#include <QtCore>
#include <myprocess.h>
#include <QDebug>
#include <QString>
#include <paths.h>
#include "filefilters.h"
class GifGenerator : public QObject
{
    Q_OBJECT
public:
    explicit GifGenerator(QObject *parent = 0);
    void setFfmpegOptions(QString filename,double startPos,short duration,int fps,long width,long height,QString outpath);
    void generateGif();

signals:
    void ffmpegexit(int,QString);

public slots:
    void ffmpegConsole(QByteArray);
    void emitProcessFinished(int);

private:
    MyProcess *ffmpegProcess;
    QString gifPath;
    
};

#endif // GIFGENERATOR_H
