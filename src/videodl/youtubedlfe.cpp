#include "youtubedlfe.h"

YoutubedlFe::YoutubedlFe(QObject *parent,QString ydlPath) :
    QObject(parent)
{
    _ydlPath=ydlPath;
    ydlProcess=new MyProcess(this);
    qDebug()<<"ydlpath :"<< ydlPath;

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
    emit ytconsoleline(ba);

}
void  YoutubedlFe::queryAvailableFormats()
{
    ydlProcess->clearArguments();
    ydlProcess->addArgument(_ydlPath);
    ydlProcess->addArgument("--list-formats");
    ydlProcess->addArgument(_videoUrl);
    ydlProcess->start();
    _formatsFound=false;
}
void  YoutubedlFe::downloadVideo(QString outputPath,QString id,bool isDefault)
{
    ydlProcess->clearArguments();
    ydlProcess->addArgument(_ydlPath);
    ydlProcess->addArgument("-o");
    ydlProcess->addArgument(outputPath+"\\%(title)s-%(id)s.%(ext)s");
    if (!isDefault)
    {   ydlProcess->addArgument("-f");

        ydlProcess->addArgument(id);
    }
    ydlProcess->addArgument(_videoUrl);
    ydlProcess->start();
    _isdownloading=true;
}
void YoutubedlFe::querySupportedSites()
{
    ydlProcess->clearArguments();
    ydlProcess->addArgument(_ydlPath);
    ydlProcess->addArgument("--list-extractors");
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
