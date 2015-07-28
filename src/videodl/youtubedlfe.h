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

#ifndef YOUTUBEDLFE_H
#define YOUTUBEDLFE_H

#include <QObject>
#include <QString>
#include <myprocess.h>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
static QRegExp rx_download(".*\\s+[download]\\s+.*");

class YoutubedlFe : public QObject
{
    Q_OBJECT
public:
    explicit YoutubedlFe(QObject *parent = 0,QString ydlPath="");
     MyProcess *ydlProcess;
    void setVideoUrl(QString url){_videoUrl=url;}
    void queryAvailableFormats();
    void querySupportedSites();
    void updateYoutubedl();
    bool isDownloading(){return _isdownloading;}
    void downloadVideo(QString outputPath,QString id,bool isDefault);
signals:
    void ytexit(int);
    void ytconsoleline(QByteArray);

public slots:
    void ydlConsole(QByteArray);
    void emitProcessFinished(int);

private:

    bool _formatsFound;
    bool _isdownloading;
    QString _videoUrl;
    QString _ydlPath;

    
};

#endif // YOUTUBEDLFE_H
