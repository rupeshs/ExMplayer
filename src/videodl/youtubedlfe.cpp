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

#include "youtubedlfe.h"

YoutubedlFe::YoutubedlFe(QObject *parent,QString ydlPath) :
    QObject(parent)
{
    _ydlPath=ydlPath;
    ydlProcess=new MyProcess(this);
    qDebug()<<"ydlpath :"<< ydlPath;

   QFileInfo checkFile(ydlPath);
   if(!checkFile.exists())
   {
       QMessageBox::critical(0,"ExMplayer",tr("Youtube-dl not found..please install youtube-dl. https://rg3.github.io/youtube-dl/"),QMessageBox::Ok);

   }

    QObject::connect(ydlProcess,SIGNAL(lineAvailable(QByteArray)),this,SLOT(ydlConsole(QByteArray)));
    QObject::connect(ydlProcess,SIGNAL(finished(int)),this,SLOT(emitProcessFinished(int)));


}
void YoutubedlFe::emitProcessFinished(int ec)
{

    emit ytexit(ec);

    _isdownloading=false;
}
void  YoutubedlFe::ydlConsole(QByteArray ba)
{

    if(QString(ba).contains("[download]")){
        _isdownloading=true;
    }
    emit ytconsoleline(ba);

}
void  YoutubedlFe::queryAvailableFormats()
{
    ydlProcess->clearArguments();
    ydlProcess->addArgument(_ydlPath);
    ydlProcess->addArgument("--list-formats");
    ydlProcess->addArgument(_videoUrl);
    //ydlProcess->setEnvironment();
    ydlProcess->start();
    _formatsFound=false;
}
void  YoutubedlFe::downloadVideo(QString outputPath,QString id,bool isDefault)
{

    ydlProcess->clearArguments();
    ydlProcess->addArgument(_ydlPath);
    ydlProcess->addArgument("-o");
    QString outFileName;
    outFileName =QString(QDir::separator())+"%(title)s-%(id)s"+ id+".%(ext)s";

    ydlProcess->addArgument(outputPath+outFileName);

    if (!isDefault)
    {   ydlProcess->addArgument("-f");

        ydlProcess->addArgument(id);
    }
    ydlProcess->addArgument(_videoUrl);

    qDebug()<<ydlProcess->arguments();
    ydlProcess->start();
    _isdownloading=true;
}
void YoutubedlFe::querySupportedSites()
{
    ydlProcess->clearArguments();

    ydlProcess->addArgument(_ydlPath);
    ydlProcess->addArgument("--list-extractors");
     qDebug()<<ydlProcess->arguments();
    ydlProcess->start();
    _formatsFound=false;
}
void YoutubedlFe::updateYoutubedl()
{
    ydlProcess->clearArguments();
    ydlProcess->addArgument(_ydlPath);
    ydlProcess->addArgument("-U");
    ydlProcess->start();
    _formatsFound=false;
}
