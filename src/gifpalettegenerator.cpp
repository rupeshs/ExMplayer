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
#include "gifpalettegenerator.h"

GifPaletteGenerator::GifPaletteGenerator(QObject *parent) :
    QObject(parent)
{

    ffmpegProcess=new MyProcess(this);
    QObject::connect(ffmpegProcess,SIGNAL(lineAvailable(QByteArray)),this,SLOT(ffmpegConsole(QByteArray)));
    QObject::connect(ffmpegProcess,SIGNAL(finished(int)),this,SLOT(emitProcessFinished(int)));

}
void GifPaletteGenerator::setFfmpegOptions(QString filename,double startPos,short duration,int fps,long width,long height){

    QString ffmpegBinPath;
    QString gifQualityStr;
#ifdef Q_OS_WIN
    ffmpegBinPath=qApp->applicationDirPath()+"/ffmpeg.exe";
#endif
#ifdef Q_OS_LINUX
    ffmpegBinPath=Paths::sharePath()+"/ffmpeg";

#endif
    ffmpegProcess->clearArguments();
    ffmpegProcess->addArgument(ffmpegBinPath);
    ffmpegProcess->addArgument("-ss");
    ffmpegProcess->addArgument(QString::number(startPos));
    ffmpegProcess->addArgument("-t");
    ffmpegProcess->addArgument(QString::number(duration));
    ffmpegProcess->addArgument("-i");
    ffmpegProcess->addArgument(filename);
    ffmpegProcess->addArgument("-vf");
    gifQualityStr="fps="+QString::number(fps)+",scale="+QString::number(width)+":"+QString::number(height)+":flags=lanczos,palettegen";
    qDebug()<<gifQualityStr;
    ffmpegProcess->addArgument(gifQualityStr);
    ffmpegProcess->addArgument("-y");
    ffmpegProcess->addArgument(QDir::tempPath()+QString(QString(QDir::separator())+"exm_gf_palette.png"));
   // QDir::temp();

}
void GifPaletteGenerator::generatePalette()
{
    ffmpegProcess->start();

}
void GifPaletteGenerator::ffmpegConsole(QByteArray ba)
{
    qDebug()<<QString(ba);
     if (ba.contains("Error opening filters"))
     {
             QMessageBox::critical(0,qApp->applicationName(),tr("Error..Please update ffmpeg binary."),QMessageBox::Ok);

     }
}

void GifPaletteGenerator::emitProcessFinished(int ec)
{
    emit ffmpegexit(ec);
    qDebug()<<"GifPaletteGenerator Exit code :"<<QString::number(ec);
}
