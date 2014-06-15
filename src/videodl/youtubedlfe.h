#ifndef YOUTUBEDLFE_H
#define YOUTUBEDLFE_H

#include <QObject>
#include <QString>
#include <myprocess.h>

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
