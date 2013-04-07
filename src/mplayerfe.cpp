/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2013 Rupesh Sreeraman

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

#include "mplayerfe.h"
#include <QColor>

/*A: 2.1 V: 2.2 A-V: -0.167 ct: 0.042 57/57 41% 0% 2.6% 0 4 49% 1.00x
A: 2.1
     audio position in seconds
V: 2.2
    video position in seconds
A-V: -0.167
    audio-video difference in seconds (delay)
ct: 0.042
    total A-V sync correction done
57/57
    frames played/decoded (counting from last seek)
41%
    video codec CPU usage in percent (for slice rendering and direct rendering this includes video_out)
0%
    video_out CPU usage
2.6%
    audio codec CPU usage in percent
0
    frames dropped to maintain A-V sync
4
    current level of image postprocessing (when using -autoq)
49%
    current cache size used (around 50% is normal)
1.00x
    playback speed as a factor of original speed*/

static QRegExp rx_pos("^[AV]: *([0-9.]+)");
static QRegExp rx_audiocpu_usage0("^[AV]:.*([0-9.]+%)");
static QRegExp rx_audiocpu_usage1("^[AV]:.*[0-9.]+%.*([0-9.]+%)");
static QRegExp rx_videocpu_usage("^[AV]:.*([0-9.]+%)");
static QRegExp rx_speed("^[AV]:.*([0-9.]+x)");
static QRegExp rx_frame_ct("^[AV]:.* (\\d+)\\/.\\d+");
static QRegExp rx_delay("A-V:.*([0-9.]+).ct");
static QRegExp rx_frame("^[AV]:.* (\\d+)\\/.\\d+");
static QRegExp rx_screenshot(".*screenshot '(.*)'");
static QRegExp rx_gin("Generating Index:.* (\\d+)");
static QRegExp rx_cache("Cache not filling!");
static QRegExp rx_audioinfo("^[AUDIO:].*(\\d+).*Hz.*(\\d+).*ch.*(\\d+).*(\\d+).*kbit.*");
static QRegExp rx_bufferfill("^Cache fill:.*([0-9,.]+)% .*");

mplayerfe::mplayerfe(QObject *parent, QWidget* wparent)
{
    isnet=false;
    _wparent=wparent;

    isurl=false;
    _bgotdimension=false;
#ifdef Q_OS_WIN
    mPath= qApp->applicationDirPath()+ "/mplayer/mplayer.exe";
#endif
#ifdef Q_OS_LINUX
    mPath= qApp->applicationDirPath()+ "/usr/bin/mplayer";
# endif
    mutelock=true;

    qDebug()<<"Checking for MPlayer binary...";
    if (!QFile(qApp->applicationDirPath()+ "/mplayer/mplayer.exe").exists())
    {
        QMessageBox::critical(wparent,qApp->applicationName(),tr("MPlayer not found!"),QMessageBox::Ok,QMessageBox::Cancel);

    }

   /* mProcess = new QProcess(parent);
    QObject::connect(mProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readmpconsole()));
    QObject::connect(mProcess,SIGNAL(finished(int)),this,SLOT(emitProcessFinished(int)));
*/
    mProcess=new MyProcess(parent);
    QObject::connect(mProcess,SIGNAL(lineAvailable(QByteArray)),this,SLOT(mplayerConsole(QByteArray)));
    QObject::connect(mProcess,SIGNAL(finished(int)),this,SLOT(emitProcessFinished(int)));


    qDebug()<<"Starting mplayer process...";
    wdlg=new WinampDspDialog(wparent);
    QObject::connect(wdlg,SIGNAL(enableWinampPlugin(bool,QString)),this,SLOT(enableWinampPlugin(bool,QString)));
    QObject::connect(wdlg,SIGNAL(settingChanged(QString,QString,QString)),this,SLOT(mpsettingChanged(QString,QString,QString)));
    internalrestart=false;
    bwinampdsp=false;
    bstopping=false;
    cachefill=false;
    _hideFontDlg=false;
    _videowidth=0;
    _curpos=0;
    _subpos=100;
    bsubtvisible=true;
    bstop=false;
    ckey=colorToRGB(5);

    keepaspect=true;

    _priority="abovenormal";

    foundsub =false;
    init();
    _silent=true;
    bfullscreen=false;
    _state=STOPPED;
    bmute=false;
}
void mplayerfe::init()
{
    _align=2;
    _isRestarting=false;
    _tduration = QTime(0,0,0,0);
    _started=false;
    _hasaudio=false;
    _hasvideo=false;
    _currentspeed="1.00x";
    bpause=false;
    rx_videocpu_usage.setMinimal(true);
    bedlstart=false;
    uselavf=true;


}
mplayerfe::~mplayerfe()
{
    qDebug()<<"closing...";
    mProcess->write("quit\n");
    mProcess->close();
    mProcess->kill();
    delete mProcess;
    delete wdlg;

}
void mplayerfe::play(QString File,int volume)
{
    _curvolume=  volume;
    qDebug()<<"Starting mplayer process...";

    //FrontEnd options
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef Q_OS_WIN
    argfrontEnd<<"-slave"<<"-identify"<<"-noquiet"<<"-priority"<<_priority;
#endif
#ifdef Q_OS_LINUX
    argfrontEnd<<"-slave"<<"-identify"<<"-noquiet";
# endif

    //Mp3 file smooth seeking
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (File.contains("mp3",Qt::CaseInsensitive)){
        // if (uselavf)
        //argDemuxerOpt<<"-demuxer"<<"lavf";


    }

    //Audio options
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    argAudioOpt<<"-volume"<<QString::number(volume);
    //<<"-softvol"<<"-softvol-max"<<QString::number(400)<<"-volstep"<<QString::number(1);

    if(bwinampdsp){
        removeFilter(equlizerstr);
    }
    //Video options
    //qDebug()<<"ckey"<<_videowinid;
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //<<"-monitorpixelaspect"<< QString::number(1)
#ifdef Q_WS_WIN
    switch(QSysInfo::windowsVersion())
    {
    case QSysInfo::WV_XP:
        argVideoOpt<<"-vo"<<"direct3d";
        break;
    case QSysInfo::WV_VISTA:
        argVideoOpt<<"-vo"<<"direct3d";
        break;
    case QSysInfo::WV_WINDOWS7:
        argVideoOpt<<"-vo"<<"direct3d";
        break;
    }
#endif

    argVideoOpt<<"-nodr" <<"-double"<<"-nocolorkey"<<"-wid"<<QString::number(_videowinid)<<"-nokeepaspect";
    if(!keepaspect){
        arguments<<"-nokeepaspect";
    }
    //
    argSubOpt<<"-sub-fuzziness"<<QString::number(1)<<"-ass"<<"-embeddedfonts"<<"-ass-styles"<<qApp->applicationDirPath()+"/styles.ass";
    //
    argvideofilters<<"-vf"<<"screenshot";
    //All options
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //arguments <<shortPathName(File);
    ////qDebug()<<"prrrrrrrrr"<<arguments;

    if (    File.contains(".m3u")||
            File.contains(".pls")||
            File.contains(".asx")||
            File.contains(".wvx"))
    {//qDebug("nbnbn");
        arguments <<argfrontEnd<<argDemuxerOpt<<argAudioOpt<<argVideoOpt<<argSubOpt<<argvideofilters<<argao<<"-playlist"<<shortPathName(File);

    }

    else
    {
        arguments <<argfrontEnd<<argDemuxerOpt<<argAudioOpt<<argVideoOpt<<argSubOpt<<argvideofilters<<argao<<shortPathName(File);

    }
    if (!_silent)
    {QFileInfo fi(File);
        edlfile=new QFile(qApp->applicationDirPath()+"/"+fi.baseName()+"_edl.txt");
        edl= qApp->applicationDirPath()+"/"+fi.baseName()+"_edl.txt";
        QFileInfo fn(edl);

        if (fn.exists())
        {
            int bt;
            bt= QMessageBox::question (0,"ExMplayer","EDL file found do you want to play this file in family friendly mode?",QMessageBox::Yes,QMessageBox::No);

            //qDebug()<<bt<<"fgdf";
            if(bt==QMessageBox::Yes)
                arguments<<"-edl"<<fn.filePath();
            if(bt==QMessageBox::No)
            {QFile edl(fn.filePath());
                edl.remove() ;

            }
        }
    }
    //Starting mplayer
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    qDebug()<<"Starting mplayer...";

    _filepath=File;

    //arguments<<argfrontEnd<<argDemuxerOpt<<argAudioOpt<<argVideoOpt<<argSubOpt<<argvideofilters<<argao<<shortPathName(File);
    //mProcess->start( mPath, arguments);
     startMplayer();

     emit starting();
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    //QString subcp("ISO-8859-1");
    //qDebug()<<"-v"<<qApp->applicationDirPath()+"/styles.ass";
    //argaudiofilters<<"-af"<<"wadsp=C:\Program Files\Winamp\Plugins\dsp_sps.dll:cfg=0,equalizer=0:0:0:0:0:0:0:0:0:0,volume=0:0";

    //arguments<<"-subcc"  <<"-ass"<<"-embeddedfonts"  <<"-ass-styles"<<qApp->applicationDirPath()+"/styles.ass"<<"-ass-line-spacing"<< QString::number(0)<<"-ass-font-scale" <<QString::number(1)<<"-subcp"<<subcp<<"-nobps"<<"-ni"<<"-hr-mp3-seek"<<"-forceidx"<<"-priority"<<"abovenormal"<<"-volume"<<QString::number(volume)<<"-slave" <<"-identify"<<"-colorkey"<<ckey<<"-wid"<<QString::number(_videowinid)<<"-noquiet"<<"-subfont-autoscale"<<QString::number(3)<<shortPathName(File);
    //arguments<<"-af-add" <<"wadsp=\"C//Program Files\Winamp\Plugins\dsp_enh.dll\"";


}
void mplayerfe::readmpconsole()
{

    QString str= mProcess->readAllStandardOutput();

   QStringList lines;

   // if (!_started)
    //    lines=str.split("\r\n",QString::SkipEmptyParts);
    //else
        //lines=str.split("\r",QString::SkipEmptyParts);
//

    //if (lines.filter("AUDIO").count()>0) _hasaudio=true;
    //if (lines.filter("VIDEO").count()>0) _hasvideo=true;
   for(int i=0;i<lines.count();i++)
    {
       QString tmp;
        tmp=lines.at(i);
        if(!_started)
        {  emit lineavailable (tmp);
//            if( tmp.contains("Connecting to server"))
//            {//isurl=true;
//                //emit  download();
//                isnet=true;

//                emit show_message(QString("Connecting to server..."),2000) ;
//            }
//            else if( tmp.contains("Resolving"))
//            {
//                emit show_message(QString("Resolving"),2000) ;
//            }
//            else if( tmp.contains("Cache fill"))
//            {
//                emit show_message(QString("Buffering"),2000) ;
//            }
            /*if (this->filepath().contains("mp3",Qt::CaseInsensitive)){
       if( tmp.contains("Header missing"))
       {qDebug()<<"Header missing";
           uselavf=false;
          restart();
       }
     }*/
//            if( tmp.contains("Scanning file"))
//            {if(!_hideFontDlg)
//                {
//                    if (!fldDlg)
//                    {fldDlg=new fontLoadDialog(_wparent);
//                        fldDlg->setModal(true);
//                        fldDlg->setGeometry(_wparent->width()/2-fldDlg->width()/2,_wparent->height()/2-fldDlg->height()/2,fldDlg->width(),fldDlg->height());
//                        fldDlg->show();
//                        qDebug()<<"++++++++++++++++++++"<<_hideFontDlg;
//                        emit show_message("Please wait...Scanning font files...",4000) ;
//                    }
//                }

//            }

//            if(rx_audioinfo.indexIn(tmp) >-1)
//            {
//                //qDebug()<<"lllllllll0000"+rx_audioinfo.cap(1);
//                 _audio_rate=QString::number(rx_audioinfo.cap(1).toInt()/1000);
//                 _audio_nch=rx_audioinfo.cap(2);
//                _audio_bitrate=rx_audioinfo.cap(4);
//                //qDebug()<<"lllllllll0000"+rx_audioinfo.cap(2);
//                //qDebug()<<"lllllllll0000"+rx_audioinfo.cap(4);
//            }
//            if (rx_gin.indexIn(tmp) >-1 )
//            { if( rx_gin.cap(1).toInt()>1)
//                {
//                    emit showpg();
//                }
//                emit show_message("Generating Index: "+QString::number(rx_gin.cap(1).toInt())+"%",2000);
//            }
//            if(tmp.contains("ID_"))
//                idlist<<tmp;
//            if (tmp.contains("ac3"))
//            {
//                emit foundac3();
//            }
        }
        else{

//            if(_hasvideo)
//            {if (!_isRestarting)
//                { //qDebug()<< "listSubtitleTrack";
//                    if (tmp.contains("ID_SUBTITLE_ID"))
//                    { //qDebug()<<"bastard subbbbbbbbbbbbbbbbbbbbbbbbb";
//                        if (!internalrestart)
//                        {
//                            listSubtitleTrack<< parsevalue("ID_SUBTITLE_ID","=",tmp);
//                            listSubtitleTrack.removeDuplicates();
//                            //qDebug()<<listSubtitleTrack;
//                            // listSubtitleTrack.clear();
//                            emit foundSubtitletrack(listSubtitleTrack);
//                        }
//                        //qDebug()<< listSubtitleTrack;
//                    }
//                }

//            }
//            if (!(tmp.contains(QLatin1String("A:"))||tmp.contains("V:")))
//            { emit lineavailable (tmp);
//                // qDebug()<<"tmp";
//                if (this->mutelock)
//                {
//                    if (!this->bmute)
//                    {if(!mutelock)
//                        {this->mProcess->write("mute\n");
//                            mutelock=true;

//                        }
//                    }
//                }

//            }
//            if(rx_screenshot.indexIn(tmp)>-1)
//            {//qDebug()<<"screenshot";
//                //qDebug()<<rx_screenshot.cap(1);
//                this->usercommand("osd_show_text \"Screenshot is saved as " + rx_screenshot.cap(1) + "\" 2000 1");
//            }
//            if(rx_pos.indexIn(tmp)>-1){
//                _curpos=rx_pos.cap(1).toFloat();

//                _tcurpos=QTime();
//                _tcurpos=_tcurpos.addSecs(_curpos);
//                // tmpcurpos=_curpos;

//            }

//            if(rx_speed.indexIn(tmp)>-1)
//                _currentspeed =rx_speed.cap(1);
//            else
//                _currentspeed="1.00x";
//            if(rx_audiocpu_usage0.indexIn(tmp)>-1)
//                _audio_cpu_usage= rx_audiocpu_usage0.cap(1);
//            if(_hasvideo)
//            {if(rx_audiocpu_usage1.indexIn(tmp)>-1)
//                { _audio_cpu_usage= rx_audiocpu_usage1.cap(1);

//                }
//                if(rx_videocpu_usage.indexIn(tmp)>-1)
//                    _video_cpu_usage=rx_videocpu_usage.cap(1);
//                if(rx_frame.indexIn(tmp)>-1)
//                    _framecount=rx_frame.cap(1);
//                if(rx_delay.indexIn(tmp)>-1)
//                    _avdelay=rx_delay.cap(1);
//            }
//            if(str.contains("ANS_LENGTH",Qt::CaseInsensitive))
//            {
//                tmpstr=parsevalue("ANS_LENGTH=","=",str);

//                _duration=tmpstr.toFloat();

//                _tduration=QTime();
//                _tduration=  _tduration.addSecs(_duration);
//                emit lengthChanged();
//                //qDebug()<<"duration" <<_tduration;
//            }

        }
    }
//    if ( str.contains("Cache not",Qt::CaseInsensitive))
//    {    cachefill=true;
//        qDebug()<<"cache...........";
//    }

//    if ( str.contains("Position",Qt::CaseInsensitive))
//    {

//        if (!this->bmute)
//        {if(!mutelock)
//            {this->mProcess->write("mute\n");
//                mutelock=true;

//            }
//        }

//    }
//    if ( str.contains("ID_SIGNAL=11",Qt::CaseInsensitive))
//    {
//        if (_filepath.contains("av",Qt::CaseInsensitive)){
//            //qDebug()<<"ghgfhgh";
//            emit useidx();
//        }

//    }


//    if ( str.contains("ID_EXIT=EOF",Qt::CaseInsensitive))
//    {if (!_hasvideo&&!_hasaudio)
//        {_isRestarting=false;
//            if (_filepath.contains("mp3",Qt::CaseInsensitive)){
//                if (uselavf)
//                    emit removelavf();
//                else
//                {  _state=STOPPED;
//                    emit showerrortext("Oops!!!! No audio,Video.");
//                    //emit showmsgBox("Cann't play this file...\n""Not found any audio or video stream.");
//                    //QMessageBox::information(_wparent,qApp->applicationName(),tr("Cann't play this file...\n""Not found any audio or video stream."),QMessageBox::Ok,QMessageBox::NoButton);
//                    //emit playNextFile();
//                    //  _state=STOPPED ;
//                    ///bstop=true;
//                    // emit stopping();
//                }
//            }
//            else

//            {   //_state=STOPPED;
//                emit showerrortext("Oops!!!! No audio,Video.");
//                //emit showmsgBox("Cann't play this file...\n""Not found any audio or video stream.");
//                //QMessageBox::information(_wparent,qApp->applicationName(),tr("Cann't play this file...\n""Not found any audio or video stream."),QMessageBox::Ok,QMessageBox::NoButton);
//                //emit playNextFile();
//                //_state=STOPPED ;
//                //  bstop=true;
//                //emit stopping();
//            }
//        }
//        emit eof();
//        //emit processFinished(0,bstopping);
//        //_state=this->STOPPED;

//        emit this->show_endmessage("End of playback(EOF)");
//    }
//    if ( str.contains("ID_EXIT=QUIT",Qt::CaseInsensitive))
//    {qDebug()<<"stopped......";
//        bstop=true;
//        _state=STOPPED;
//        bstopping=true;
//        emit stopping();

//    }


    if (!_started)
    {/* if(str.contains("ID_VIDEO_WIDTH"))
        {   tmpstr= parsevalue("ID_VIDEO_WIDTH","=",str);
            _videowidth=tmpstr.toInt();
            _video_width=QString::number(tmpstr.toInt());
            _hasvideo=true;

            qDebug()<<"Got Video width:"<<_video_width;
            _bgotdimension=true;
            show_message("Found video stream",1000) ;
            emit showvideoui();
            emit hidepg();
        }



        if(str.contains("ID_VIDEO_HEIGHT"))
        {    tmpstr= parsevalue("ID_VIDEO_HEIGHT","=",str);
            _videoheight=tmpstr.toInt();
            _video_height=QString::number(tmpstr.toInt());
        }*/

//        if(str.contains("Starting playback",Qt::CaseInsensitive))
//        {qDebug()<<"<---- emit startingplayback() ----->";
//            if  (_hasvideo)
//                qDebug()<<"Video Width :"<<_video_width<<"Video Height :"<<_videoheight;
//            if(_bgotdimension && _hasvideo)
//                emit startingplayback();
//            if  (_hasaudio &&!_hasvideo)
//                emit startingplayback();
//            _started=true;
//            if(isurl)
//            {//this->usercommand("quit");
//                // qDebug()  <<"Sdfdf";
//                //emit  progressiveStreaming();
//                // this->play(qApp->applicationDirPath()+ "/thetrain01(www.songs.pk).mp3",_curvolume);
//            }

//            QString fn;
//            QFileInfo fi(this->filepath());
//            fn = fi.baseName();

//            this->usercommand("osd_show_text \""+ fn+"\" 2000 1");


//            idlist.removeDuplicates();
//            cmd=QString("get_time_length\n");
//            mProcess->write(cmd.toAscii());
//            if(fldDlg)
//            {
//                fldDlg->close();
//            }




//        }
        //_state=this->PARSING;
        if(str.contains("AUDIO:"))
        {metainfo << "AUDIO: "+ parsevalue("AUDIO:",":",str);

        }
        if(str.contains("VIDEO:"))
            metainfo << "VIDEO: "+ parsevalue("VIDEO:",":",str);

        //qDebug()<<"Parsing...";
//        metainfoname=lines.filter("ID_CLIP_INFO_NAME");
//        metainfovalue=lines.filter("ID_CLIP_INFO_VALUE");

//        if(metainfoname.count()==metainfovalue.count())
//        {for(int i=0;i<metainfoname.count();i++)
//                metainfo<< parsevalue("ID_CLIP_INFO_NAME","=",metainfoname.at(i))+" : "+  parsevalue("ID_CLIP_INFO_VALUE","=",metainfovalue.at(i));
//        }
//        listTemp.clear();

//        listTemp=lines.filter("ID_SUBTITLE_ID");
//        if (!internalrestart)
//        {for(int i=0;i<listTemp.count();i++){
//                {listSubtitleTrack<< parsevalue("ID_SUBTITLE_ID","=",listTemp.at(i));
//                    ///emit foundSubtitletrack(listSubtitleTrack);
//                }
//            }
//        }
       // listTemp.clear();
//        listTemp=lines.filter("ID_AUDIO_ID");

//        for(int i=0;i<listTemp.count();i++){
//            listAudioTrack<< parsevalue("ID_AUDIO_ID","=",listTemp.at(i));
//        }
//        listTemp.clear();
//        listTemp=lines.filter("ID_VIDEO_ID");


//        for(int i=0;i<listTemp.count();i++){
//            listVideoTrack<< parsevalue("ID_VIDEO_ID","=",listTemp.at(i));
//        }
//        //qDebug()<<listVideoTrack;
//        if(str.contains("ID_LENGTH",Qt::CaseInsensitive))
//        {//qDebug()<<"zzzzzzzzzzzzzzzzzzzzzzzzzz";
//            tmpstr=parsevalue("ID_LENGTH=","=",str);
//            _duration=tmpstr.toFloat();
//            emit gotduration(_duration);
//            _tduration=  _tduration.addSecs(_duration);
//            if (isurl)
//            {
//                emit streamingDuration(_duration);
//            }

//            //cmd=QString("get_time_length\n");
//            //mProcess->write(cmd.toAscii());
//        }
        //if(str.contains("ID_CLIP_INFO_N=",Qt::CaseInsensitive))
        //    _metainfocount=parsevalue("ID_CLIP_INFO_N=","=",str).toInt();

        if(str.contains("ID_AUDIO_CODEC"))
        {metainfo <<"AUDIO_CODEC: "+ parsevalue("ID_AUDIO_CODEC","=",str);
        }
        if(str.contains("ID_VIDEO_CODEC",Qt::CaseInsensitive))
            metainfo <<"VIDEO_CODEC: "+ parsevalue("ID_VIDEO_CODEC","=",str);

//        if(str.contains("ID_AUDIO_ID"))
//        {
//            show_message("Found audio stream",1000);
//            //qDebug()<<isurl;

//        }




//        if(str.contains("Video: no video")){
//         _hasvideo=false;

//        }

//        if  ( _hasvideo&& _hasaudio)
//        {
//            emit foundAudioandVideo();
//        }
//        if(str.contains("ID_SEEKABLE"))
//        { tmpstr= parsevalue("ID_SEEKABLE","=",str);
//            _isseekable =(bool)tmpstr.toInt();
//        }

//        if (_video_width>0 && _video_height>0)
//        {
//            emit resizeVideoWindow(_videowidth,_videoheight);
//        }


        //if(str.contains("ID_VIDEO_ID"))
        //    _hasvideo=true;



    }
    else
    {
//        if(str.contains("A:",Qt::CaseInsensitive)){
//            _state=this->PLAYING;
//            if (!bstop)
//                emit playing();
//            _isRestarting=false;

//            if(str.contains("ID_PAUSED",Qt::CaseInsensitive)){
//                _state=this->PAUSED;
//                emit paused();

//            }
//        }
    }
}
QString mplayerfe::parsestatusline(QString serstr, QString str)
{
    return str.mid(str.indexOf(serstr),str.indexOf("\r",str.indexOf(serstr)));
}
QString mplayerfe::parsevalue( QString serstr,QString sep,QString str)
{
    QString tmp;
    tmp=str.mid(str.indexOf(serstr));
    tmp=tmp.left(tmp.indexOf("\n"));

    qDebug()<<"Parsed ->"<<tmp.mid(tmp.indexOf(sep)+1);

    return tmp.mid(tmp.indexOf(sep)+1).trimmed();
}
void mplayerfe::goturl(int per)
{
   // qDebug()<<"%%%%%%%%%%%%%%%%%%%%%%%%%"<<QString::number(per);
    float pos=(this->duration()*(float)per)/100.0;
    //bmute

    //this->smoothSeek();
    cmd =QString("pausing_keep seek " + QString::number(pos) + " 2\n");
    mProcess->write(cmd.toAscii());
    emit show_message("Seeking :"+ QString::number(per)+"% ",1000);

}
void mplayerfe::pause()
{
    bpause=!bpause;
    cmd=QString("pause\n");
    mProcess->write(cmd.toAscii());

}
void mplayerfe::stop()
{
    mProcess->write(QString("quit\n").toAscii());
    emit this->show_endmessage("Stopped");
}

void mplayerfe::setVolume(int vol)
{if (!_isRestarting)
    {if(bmute)
            bmute=!bmute;
        _curvolume=vol;
        cmd=QString("volume " + QString::number(vol) + " 1\n");
        mProcess->write(cmd.toAscii()) ;
        emit show_message("Volume :"+ QString::number(vol)+"% ",1000);
    }
}
void mplayerfe::toggleMute()
{
    bmute=!bmute;

    mProcess->write(QString("pausing_keep mute\n").toAscii()) ;
    if(bmute)
        emit show_message("Mute enabled",1000);
    else
    {emit show_message("Mute disabled",1000);


    }
}
void mplayerfe::setOSDlevel(int osdlevel)
{
    cmd="osd "+QString::number(osdlevel)+"\n";
    mProcess->write(cmd.toAscii()) ;

}
void mplayerfe::setframedroplevel(int framedroplevel)
{
    cmd="frame_drop "+QString::number(framedroplevel)+"\n";
    mProcess->write(cmd.toAscii()) ;
    qDebug()<<cmd.toAscii();
}
void mplayerfe::framestep()
{

    mProcess->write(QString("frame_step\n").toAscii());
}

void  mplayerfe::seeknseconds(int nsec)
{
   // this->smoothSeek();
    cmd=QString("seek " + QString::number(nsec) + " 0\n");
qDebug()<<cmd;
    mProcess->write(cmd.toAscii());
    if(nsec>0)
        emit show_message("Forward "+QString::number(nsec)+" Seconds",1000);
    else
        emit show_message("Rewind "+QString::number(abs(nsec))+" Seconds",1000);

}
void  mplayerfe::setSpeed(float speed, int type)
{QString speedstr;
    if (type<3)
    {
        switch(type)
        {case 0:
            cmd=QString("pausing_keep speed_incr " + QString::number(speed) + "\n");
            if (speed>0)
                speedstr=QString("Increasing speed by "+QString::number(speed*100)+"%");
            else
                speedstr=QString("Decreasing speed by "+QString::number(abs(speed*100))+"%");
            break;
        case 1:
            cmd=QString("pausing_keep speed_mult " + QString::number(speed) + "\n");
            if(speed==0.5)
                speedstr=QString("Halving speed");
            else if (speed==2.0)
                speedstr=QString("Doubling speed");
            else
                speedstr=QString("Changing speed by a factor" +QString::number(speed) );
            break;
        case 2:
            cmd=QString("pausing_keep speed_set 1\n");
            speedstr=QString("Normal speed 1.00x");
            _currentspeed="1.00x";
            break;
        }
        emit show_message(speedstr,1000);
        mProcess->write(cmd.toAscii()) ;
    }
}
void  mplayerfe::setaudiodelay(float delay,QWidget* par)
{
    if (delay==-1.0)
    {
        bool ok;
        int i ;

        i= QInputDialog::getInteger(par, tr("Set Audio delay"), tr("Delay:(in milliseconds)"),100, -1000000, 1000000, 1, &ok);
        if(ok)
        {cmd="audio_delay "+QString::number((float)i/1000)+" 1\n";
            mProcess->write(cmd.toAscii()) ;
        }
    }
    else
    {
        if (delay>0)
            emit  show_message("Increasing Audio delay by " + QString::number(delay*1000) +" milliseconds",1000);
        else
            emit  show_message("Decreasing Audio delay by "+QString::number(abs(delay*1000)) +" milliseconds",1000);

        cmd="audio_delay "+QString::number(delay)+" 0\n";
        mProcess->write(cmd.toAscii()) ;
    }

}
void  mplayerfe::setvideoproperty(QString property, int value)
{

    cmd=QString("pausing_keep "+ property +" " +QString::number(value) + " 1\n");
    mProcess->write(cmd.toAscii());
    emit show_message( property +" "+QString::number(value),1000);
}
void mplayerfe::setequalizerbandvalue(QString bandvalues)
{eqbandval=bandvalues;

    equlizerstr=QString("equalizer=")+bandvalues+",volume";
    cmd=QString("af_cmdline equalizer "+bandvalues+"\n");
    qDebug()<<cmd;
    emit  settingChanged ("Audio","Eq",bandvalues);
    mProcess->write(cmd.toAscii());
    //qDebug()<<"equlizerstr"<<equlizerstr ;
}
void mplayerfe::takescreenshot(int type)
{
    cmd=QString("screenshot "+QString::number(type)+"\n");
    mProcess->write(cmd.toAscii());
}
void mplayerfe::loadsubtitles(QString subfile)
{
    subfile = shortPathName(subfile);
    // For some reason it seems it's necessary to change the path separator to unix style
    // otherwise mplayer fails to load it
    subfile = subfile.replace("\\","/");
    cmd="sub_load \""+ subfile+"\"\n";
    arguments<<"-sub"<<subfile;
    restart();
    // mProcess->write(cmd.toAscii());
    // cmd="sub_select 0\n";
    //mProcess->write(cmd.toAscii());
}

// This function has been copied (and modified a little bit) from Scribus (program under GPL license):
// http://docs.scribus.net/devel/util_8cpp-source.html#l00112
QString mplayerfe::shortPathName(QString long_path) {
#ifdef Q_OS_WIN
    if ((QSysInfo::WindowsVersion >= QSysInfo::WV_NT) && (QFile::exists(long_path))) {
        QString short_path = long_path;

        const int max_path = 4096;
        WCHAR shortName[max_path];

        QString nativePath = QDir::convertSeparators(long_path);
        int ret = GetShortPathNameW((LPCWSTR) nativePath.utf16(), shortName, max_path);
        if (ret != ERROR_INVALID_PARAMETER && ret < MAX_PATH)
            short_path = QString::fromUtf16((const ushort*) shortName);

        return short_path;
    } else {
        return long_path;
    }
#endif
     return long_path;
}

void mplayerfe::toggle_subtitle_visibility()
{
    bsubtvisible=! bsubtvisible;
    cmd="sub_visibility\n";
    mProcess->write(cmd.toAscii());
    if (bsubtvisible)
        emit show_message("Subtitles enabled",1000);
    else
        emit show_message("Subtitles disabled",1000);
}
void  mplayerfe::usercommand(QString user_cmd)
{
    mProcess->write(user_cmd.toAscii()+"\n");
}
void  mplayerfe::switchAudio(int id)
{
    int ind=arguments.indexOf("-nosound");
    if (ind>0)
    {
        arguments.removeAt(ind);
        restart();
    }
    if( id==-1)
    {arguments<<"-nosound";
        restart();
    }
    else
    { //cmd="switch_audio "+QString::number(id);
        //mProcess->write(cmd.toAscii()+"\n");
        arguments<<"-aid"<<QString::number(id);
        restart();
    }
}
void  mplayerfe::switchVideo(int id)
{
    int ind=arguments.indexOf("-novideo");
    if (ind>0)
    {
        arguments.removeAt(ind);
        restart();
    }
    if( id==-1)
    {arguments<<"-novideo";
        restart();
    }
    else
    { cmd="switch_video "+QString::number(id);
        mProcess->write(cmd.toAscii()+"\n");
    }
}
void  mplayerfe::fastRestart(QStringList extraOption)
{

    int ind=arguments.indexOf("-ss");
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }
    ind=arguments.indexOf(extraOption.at(0));
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }
    arguments<<extraOption;
    arguments<<"-ss"<<QString::number(_curpos);
    mProcess->close();
    startMplayer();

}
///////////////////////////////////////////////////////////////'
void mplayerfe::removeOption(QString option, bool addseek)
{
    int ind=arguments.indexOf(option);

    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }
}
void mplayerfe::restart()
{
    foundsub=true;
    internalrestart=true;
    int ind=arguments.indexOf("-volume");
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }
    ind=arguments.indexOf("-ss");
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }

    if(bmute)
        arguments<<"-volume"<<QString::number(0);
    else
        arguments<<"-volume"<<QString::number(_curvolume);


    arguments<<"-ss"<<QString::number(_curpos);
    init();
    _isRestarting=true;
    emit restarting();
    stop();

    mProcess->close();
    for (int i=0;i<arguments.count();i++)
    {QString str;
        str=arguments.at(i);
        if( str.contains("equalizer="))
        {
            arguments.removeAt(i);
            arguments.insert(i,equlizerstr);
            break;
        }
    }
    int ep=arguments.indexOf(QRegExp("(equalizer=*)"));

    //removeFilter(equlizerstr);
    // equlizerstr=QString("equalizer=")+val+",volume";

    //arguments <<"-af-add"<<equlizerstr;
    startMplayer();
    qDebug()<<_curvolume;
    qDebug()<<"restart"<<arguments;
    if(!bsubtvisible)
    {cmd="sub_visibility\n";
        mProcess->write(cmd.toAscii());
    }
    //setequalizerbandvalue(this->equlizerstr);
}
void mplayerfe::loadExternalFile(QString File)
{   audioFile=File;
    removeOption("-audiofile",false);
    arguments<<"-audiofile"<< shortPathName(File);

    int ind=arguments.indexOf("-volume");
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }
    ind=arguments.indexOf("-ss");
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }
    arguments<<"-ss"<<QString::number(0);
    arguments<<"-volume"<<QString::number(_curvolume);
    init();
    _isRestarting=true;
    emit restarting();
    stop();
    mProcess->close();

    startMplayer();
    qDebug()<<arguments;
    emit show_message("Loading external Audio file",2000);
}
void mplayerfe::setAudioChannels(int ch)
{
    removeOption("-channels",true);
    if (ch==0||ch==1||ch==2||ch==3)
    {switch(ch)
        {
        case 0 :arguments<<"-channels"<<QString::number(2);
            emit show_message("Changing Audio Channels to :"+QString::number(2),2000);
            break;
        case 1 :arguments<<"-channels"<<QString::number(4);
            emit show_message("Changing Audio Channels to :"+QString::number(4),2000);
            break;
        case 2 :arguments<<"-channels"<<QString::number(6);
            emit show_message("Changing Audio Channels to :"+QString::number(6),2000);
            break;
        case 3 :arguments<<"-channels"<<QString::number(8);
            emit show_message("Changing Audio Channels to :"+QString::number(8),2000);
            break;
        }
    }
    restart();

}
void mplayerfe::addAudioFilterKaraoke(bool enable)
{  if(enable)
    { removeFilter("karaoke");
        arguments<<"-af-add"<< "karaoke";
        restart();
        emit show_message("Adding filter karaoke",1000);
    }
    else
    {
        removeFilter("karaoke");
        restart();
    }
}
void mplayerfe::addAudioFilterResample(int fre)
{
    removeFilter(resamplestr);
    resamplestr="resample="+QString::number(fre)+":0:0";
    arguments<<"-af-add"<< resamplestr;
    restart();
    emit show_message("Adding filter Resample",1000);


}
void mplayerfe::addAudioFilterSurround(int val, QWidget *parent)
{
    dlg=new  QDialog(parent);
    sb = new QSpinBox(dlg);

    QGridLayout *lay = new QGridLayout(dlg);

    QLabel *del = new QLabel(QObject::tr("Delay :"));

    QPushButton *btn = new QPushButton(QIcon(":/images/ok.png"),QObject::tr("&Ok"),
                                       dlg);
    QPushButton *btnReset = new QPushButton(QIcon(":/images/reset.png"),QObject::tr("&Reset"),
                                            dlg);
    QPushButton *btnCancel = new QPushButton(QIcon(":/images/cancel.png"),QObject::tr("&Cancel"),
                                             dlg);
    QPushButton *btnDisable = new QPushButton(QObject::tr("&Disable"),
                                              dlg);

    QObject::connect(btnDisable, SIGNAL(clicked()),
                     dlg, SLOT(close()));
    QObject::connect(btnDisable, SIGNAL(clicked()),
                     this, SLOT(disableFilter()));
    lay->addWidget(btnDisable,1,1,Qt::AlignRight);
    btnReset->setToolTip(tr("Click to disable this filter"));
    disablefilterstr=surroundstr;
    int ind=arguments.indexOf(surroundstr);
    (ind>0)?btnDisable->setEnabled(true):btnDisable->setEnabled(false);

    dlg->setAttribute(Qt::WA_DeleteOnClose);
    sb->setMaximum(1000);
    sb->setSuffix(" ms");
    lay->addWidget(del,0,0,0);
    lay->addWidget(sb,0,2,0);
    lay->addWidget(btnReset,0,3,Qt::AlignRight);

    lay->addWidget(btn,1,2,Qt::AlignRight);
    lay->addWidget(btnCancel,1,3,Qt::AlignRight);
    sb->setWhatsThis(tr("Delay time in ms for the rear speakers (0 to 1000) (default: 20) This delay should be set as follows: If d1 is the distance from the listening position to the front speakers and d2 is the distance from the listening position to the rear speakers, then the delay should be set to 15ms if d1 <= d2 and to 15 + 5*(d1-d2) if d1 > d2"));
    del->setWhatsThis(tr("Decoder for matrix encoded surround sound like Dolby Surround. Many files with 2 channel audio actually contain matrixed surround sound. Requires a sound card supporting at least 4 channels."));

    QObject::connect(btnCancel, SIGNAL(clicked()),
                     dlg, SLOT(close()));

    QObject::connect(btnReset, SIGNAL(pressed()),
                     this, SLOT(resetSurround()));

    QObject::connect(btn, SIGNAL(clicked()),
                     this, SLOT(setSurround()));

    sb->setValue(val);
    dlg->setTabOrder(sb,btnReset);
    dlg->setTabOrder(btnReset,btn);
    btn->setDefault(true);
    dlg->exec();

}

void mplayerfe::removeFilter(QString filter)
{
    int ind=arguments.indexOf(filter);
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind-1);
    }
    disablefilterstr=QString();
}
void mplayerfe::setSurround()
{
    removeFilter(surroundstr);
    surroundstr="surround="+QString::number(sb->value());
    arguments<<"-af-add"<<  surroundstr;
    restart();
    emit show_message("Adding filter Surround",1000);

    emit settingChanged("Audio","Surround",QString::number(sb->value()));
    delete  dlg;

}
void mplayerfe::resetSurround()
{

    emit settingChanged("Audio","Surround","20");
    sb->setValue(20);

}
void mplayerfe::addAudioFilterExStereo(int val, QWidget *parent)
{

    dlg=new  QDialog(parent)  ;
    sliderExstereo = new QSlider(Qt::Horizontal,dlg);

    QGridLayout *lay = new QGridLayout(dlg);
    QLabel *del = new QLabel(QObject::tr("ExtraStereo Level :"));
    QLabel *vlab = new QLabel(QString::number(val));
    QPushButton *btn = new QPushButton(QIcon(":/images/ok.png"),QObject::tr("&Ok"),
                                       dlg);
    QPushButton *btnReset = new QPushButton(QIcon(":/images/reset.png"),QObject::tr("&Reset"),
                                            dlg);
    QPushButton *btnCancel = new QPushButton(QIcon(":/images/cancel.png"),QObject::tr("&Cancel"),
                                             dlg);
    QPushButton *btnDisable = new QPushButton(QObject::tr("&Disable"),
                                              dlg);

    QObject::connect(btnDisable, SIGNAL(clicked()),
                     dlg, SLOT(close()));
    QObject::connect(btnDisable, SIGNAL(clicked()),
                     this, SLOT(disableFilter()));
    lay->addWidget(btnDisable,1,1,Qt::AlignRight);
    btnReset->setToolTip(tr("Click to disable this filter"));
    disablefilterstr=exstereostr;
    int ind=arguments.indexOf(exstereostr);
    (ind>0)?btnDisable->setEnabled(true):btnDisable->setEnabled(false);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    sliderExstereo->setValue(val);

    lay->addWidget(del,0,0,0);
    lay->addWidget(sliderExstereo,0,1,0);
    lay->addWidget(vlab,0,2,Qt::AlignHCenter);
    lay->addWidget(btnReset,0,3,0);
    lay->addWidget(btn,1,2,Qt::AlignRight );
    lay->addWidget(btnCancel,1,3,Qt::AlignHCenter);

    del->setWhatsThis(tr("(Linearly) increases the difference between left and right channels which adds some sort of \"live\" effect to playback."));

    QObject::connect(btnCancel, SIGNAL(clicked()),
                     dlg, SLOT(close()));

    QObject::connect(btnReset, SIGNAL(pressed()),
                     this, SLOT(resetExStereo()));

    QObject::connect(btn, SIGNAL(clicked()),
                     this, SLOT(setExStereo()));
    QObject::connect( sliderExstereo, SIGNAL(valueChanged(int)),
                     vlab, SLOT(setNum(int)));

    dlg->setTabOrder(sliderExstereo,btnReset);
    dlg->setTabOrder(btnReset,btn);
    btn->setDefault(true);

    dlg->exec();
}
void mplayerfe::setExStereo()
{
    removeFilter(exstereostr);
    exstereostr="extrastereo="+QString::number((float)sliderExstereo->value()/10);
    arguments<<"-af-add"<< exstereostr ;
    restart();
    emit show_message("Adding filter ExtraStereo",1000);
    emit settingChanged("Audio","ExtraStereo",QString::number(sliderExstereo->value()));
    delete  dlg;
}

void mplayerfe::resetExStereo()
{
    emit settingChanged("Audio","ExtraStereo","25");
    sliderExstereo->setValue(25);
}
void mplayerfe::addAudioFilterScaleTempo(int val, QWidget *parent)
{

    dlg=new  QDialog(parent);

    sliderScaleTempo = new QSlider(Qt::Horizontal,dlg);

    QGridLayout *lay = new QGridLayout(dlg);
    QLabel *del = new QLabel(QObject::tr("ScaleTempo :"));
    QLabel *vlab = new QLabel(QString::number(val));

    QPushButton *btn = new QPushButton(QIcon(":/images/ok.png"),QObject::tr("&Ok"),
                                       dlg);
    QPushButton *btnReset = new QPushButton(QIcon(":/images/reset.png"),QObject::tr("&Reset"),
                                            dlg);
    QPushButton *btnCancel = new QPushButton(QIcon(":/images/cancel.png"),QObject::tr("&Cancel"),
                                             dlg);
    QPushButton *btnDisable = new QPushButton(QObject::tr("&Disable"),
                                              dlg);

    QObject::connect(btnDisable, SIGNAL(clicked()),
                     dlg, SLOT(close()));
    QObject::connect(btnDisable, SIGNAL(clicked()),
                     this, SLOT(disableFilter()));
    lay->addWidget(btnDisable,1,1,Qt::AlignHCenter);
    btnReset->setToolTip(tr("Click to disable this filter"));
    disablefilterstr=scaletempostr;
    int ind=arguments.indexOf(scaletempostr);
    (ind>0)?btnDisable->setEnabled(true):btnDisable->setEnabled(false);

    dlg->setAttribute(Qt::WA_DeleteOnClose);
    sliderScaleTempo->setValue(val);
    sliderScaleTempo->setMaximum(50);
    sliderScaleTempo->setMinimum(1);
    sliderScaleTempo->setPageStep(1);
    lay->addWidget(del,0,0,0);
    lay->addWidget(sliderScaleTempo,0,1,0);
    lay->addWidget(vlab,0,2,Qt::AlignHCenter);
    lay->addWidget(btnReset,0,3,0);
    lay->addWidget(btn,1,2,Qt::AlignRight );
    lay->addWidget(btnCancel,1,3,Qt::AlignHCenter);

    del->setWhatsThis(tr("Scales audio tempo without altering pitch"));

    QObject::connect(btnCancel, SIGNAL(clicked()),
                     dlg, SLOT(close()));

    QObject::connect(btnReset, SIGNAL(pressed()),
                     this, SLOT(resetScaleTempo()));

    QObject::connect(btn, SIGNAL(clicked()),
                     this, SLOT(setScaleTempo()));

    QObject::connect(sliderScaleTempo, SIGNAL(valueChanged(int)),
                     vlab, SLOT(setNum(int)));

    dlg->setTabOrder(sliderScaleTempo,btnReset);
    dlg->setTabOrder(btnReset,btn);
    btn->setDefault(true);

    dlg->exec();
}
void mplayerfe::setScaleTempo()
{
    removeFilter(scaletempostr);
    scaletempostr=QString("scaletempo=scale=%1:speed=both").arg((float)sliderScaleTempo->value()/10);
    arguments<<"-af-add"<<scaletempostr  ;
    restart();
    emit show_message("Adding filter ScaleTempo",1000);
    emit settingChanged("Audio","ScaleTempo",QString::number(sliderScaleTempo->value()));
    delete  dlg;

}
void mplayerfe::resetScaleTempo()
{
    emit settingChanged("Audio","ScaleTempo","12");
    sliderScaleTempo->setValue(12);
}

void mplayerfe::disableFilter()
{
    removeFilter(disablefilterstr);
    restart();
}
void mplayerfe::resetDelay()
{
    emit settingChanged("Audio","DelayLeft","100");
    emit settingChanged("Audio","DelayRight","0");
    sliderDelaych1->setValue(100);
    sliderDelaych2->setValue(0);
}
void mplayerfe::setDelay()
{
    removeFilter( chdelaystr);

    chdelaystr=QString("delay=%1:%2").arg(sliderDelaych1->value()).arg(sliderDelaych2->value());

    arguments<<"-af-add"<<chdelaystr  ;
    restart();
    emit show_message("Adding filter delay",1000);

    emit settingChanged("Audio","DelayLeft",QString::number(sliderDelaych1->value()));
    emit settingChanged("Audio","DelayRight",QString::number(sliderDelaych2->value()));

    delete  dlg;
}
void mplayerfe::addAudioFilterDelay(int ch1, int ch2, QWidget *parent)
{
    dlg=new  QDialog(parent);

    sliderDelaych1 = new QSlider(Qt::Horizontal,dlg);
    sliderDelaych2=new QSlider(Qt::Horizontal,dlg);

    QGridLayout *lay = new QGridLayout(dlg);
    QLabel *del1 = new QLabel(QObject::tr("Left channel delay :"));
    QLabel *del2 = new QLabel(QObject::tr("Right channel delay :"));
    vlab1 = new QLabel(QString::number(ch1)+" ms",dlg);
    vlab2 = new QLabel(QString::number(ch2)+" ms",dlg);

    QPushButton *btn = new QPushButton(QIcon(":/images/ok.png"),QObject::tr("&Ok"),
                                       dlg);
    QPushButton *btnReset = new QPushButton(QIcon(":/images/reset.png"),QObject::tr("&Reset"),
                                            dlg);
    QPushButton *btnCancel = new QPushButton(QIcon(":/images/cancel.png"),QObject::tr("&Cancel"),
                                             dlg);
    QPushButton *btnDisable = new QPushButton(QObject::tr("&Disable"),
                                              dlg);

    QObject::connect(btnDisable, SIGNAL(clicked()),
                     dlg, SLOT(close()));
    QObject::connect(btnDisable, SIGNAL(clicked()),
                     this, SLOT(disableFilter()));
    lay->addWidget(btnDisable,2,1,Qt::AlignRight);
    btnReset->setToolTip(tr("Click to disable this filter"));
    disablefilterstr=chdelaystr;
    int ind=arguments.indexOf(chdelaystr);
    (ind>0)?btnDisable->setEnabled(true):btnDisable->setEnabled(false);

    dlg->setAttribute(Qt::WA_DeleteOnClose);
    sliderDelaych1->setMaximum(1000);
    sliderDelaych2->setMaximum(1000);
    sliderDelaych1->setValue(ch1);
    sliderDelaych2->setValue(ch2);

    lay->addWidget(del1,0,0,0);
    lay->addWidget( sliderDelaych1,0,1,0);
    lay->addWidget(vlab1,0,2,Qt::AlignHCenter);
    lay->addWidget(btnReset,0,3,0);

    lay->addWidget(del2,1,0,0);
    lay->addWidget( sliderDelaych2,1,1,0);
    lay->addWidget(vlab2,1,2,Qt::AlignHCenter);

    lay->addWidget(btn,2,2,Qt::AlignRight );
    lay->addWidget(btnCancel,2,3,Qt::AlignRight);


    QObject::connect(btnCancel, SIGNAL(clicked()),
                     dlg, SLOT(close()));

    QObject::connect(btnReset, SIGNAL(pressed()),
                     this, SLOT(resetDelay()));

    QObject::connect(btn, SIGNAL(clicked()),
                     this, SLOT(setDelay()));

    QObject::connect(sliderDelaych1, SIGNAL(valueChanged(int)),
                     this, SLOT(setch1Text(int)));

    QObject::connect(sliderDelaych2, SIGNAL(valueChanged(int)),
                     this, SLOT(setch2Text(int)));


    btn->setDefault(true);

    dlg->exec();
}
void mplayerfe::setch1Text(int val)
{
    vlab1->setText(QString::number(val)+" ms");
}
void mplayerfe::setch2Text(int val)
{
    vlab2->setText(QString::number(val)+" ms");
}
void mplayerfe::setStereoMode(int mode)
{
    removeOption("-stereo",true);
    arguments<<"-stereo"<< QString::number(mode);
    restart();

}
void  mplayerfe::removeLogo(QRect *rect,bool enable )
{if (enable)
    {
        removeFilter(delogostr);
        delogostr=QString("delogo=%1:%2:%3:%4:1").arg(rect->x()).arg(rect->y()).arg(rect->width()).arg(rect->height());
        arguments<<"-vf-add"<< delogostr  ;
        emit show_message("Adding filter remove logo",1000);
        restart();
    }
    else
    {
        removeFilter(delogostr);
        restart();
    }
}
void  mplayerfe::tile(bool enable)
{if (enable)
    {//tilestr
        removeFilter(tilestr);
        tilestr=QString("scale,tile");
        arguments <<"-vf-add"<< tilestr<<"-vo"<<"directx:noaccel" ;
        emit show_message("Adding filter tile",1000);
        restart();

    }
    else
    {
        rmoveSubfilter("-vo");
        removeFilter(tilestr);
        restart();

    }
}
void  mplayerfe::flip(bool enable)
{if (enable)
    {
        removeFilter(flipstr);
        flipstr=QString("flip");
        arguments <<"-vf-add"<<flipstr ;
        emit show_message("Adding filter flip",1000);
        restart();
    }
    else
    {
        removeFilter(flipstr);
        restart();
    }
}
void  mplayerfe::mirror(bool enable)
{if (enable)
    {
        removeFilter(mirrorstr);
        mirrorstr=QString("mirror");
        arguments <<"-vf-add"<<mirrorstr ;
        emit show_message("Adding filter mirror",1000);
        restart();
    }
    else
    {
        removeFilter(mirrorstr);
        restart();
    }
}

void  mplayerfe::halfvideo(bool enable)
{if (enable)
    {
        removeFilter(halfvideostr);
        halfvideostr=QString("down3dright");
        arguments <<"-vf-add"<<halfvideostr ;
        emit show_message("Adding filter 50:50",1000);
        restart();
    }
    else
    {
        removeFilter(halfvideostr);
        restart();
    }
}
void  mplayerfe::rotate(int val)
{
    if (val!=-1)
    {
        removeFilter(rotatestr);
        rotatestr=QString("rotate=%1").arg(val);
        arguments <<"-vf-add"<<rotatestr ;
        restart();
        emit show_message("Adding filter rotate",1000);
    }
    else
    {
        removeFilter(rotatestr);
        restart();
    }
}
void  mplayerfe::swapuv(bool enable)
{if (enable)
    {
        removeFilter(swapuvstr);
        swapuvstr=QString("swapuv");
        arguments <<"-vf-add"<< swapuvstr;
        emit show_message("Adding filter swap U& V",1000);
        restart();
    }
    else
    {
        removeFilter(swapuvstr);
        restart();
    }
}
void  mplayerfe::onebpp(bool enable)
{if (enable)
    {
        removeFilter(onebppstr);
        onebppstr=QString("scale,1bpp");
        arguments <<"-vf-add"<<onebppstr;
        emit show_message("Adding filter 1bpp",1000);
        restart();
    }
    else
    {
        removeFilter(onebppstr);
        restart();
    }
}

void painting(bool enable);

void  mplayerfe::painting(bool enable)
{if (enable)
    {
        removeFilter(paintingstr);
        paintingstr=QString("noise=80");
        arguments <<"-vf-add"<<paintingstr;
        emit show_message("Adding filter painting",1000);
        restart();
    }
    else
    {
        removeFilter(paintingstr);
        restart();
    }
}
void  mplayerfe::noise(bool enable)
{if (enable)
    {
        removeFilter(noisestr);
        noisestr=QString("noise=100[t]");
        arguments <<"-vf-add"<<noisestr;
        emit show_message("Adding filter noise",1000);
        restart();
    }
    else
    {
        removeFilter(noisestr);
        restart();
    }
}
void blur(bool enable);
void  mplayerfe:: blur(bool enable)
{if (enable)
    {
        removeFilter( blurstr);
        blurstr=QString("scale");
        arguments <<"-vf-add"<< blurstr<<"-ssf"<<"lgb=3.0";
        emit show_message("Adding filter blur",1000);
        restart();
    }
    else
    {rmoveSubfilter("-ssf");
        removeFilter(blurstr);
        restart();
    }
}
void  mplayerfe::rmoveSubfilter(QString filter)
{int ind=arguments.indexOf(filter);
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }
}
void mplayerfe::matrixview(bool enable)
{if ( enable)
    { removeOption("-vo",true);
        arguments<<"-vo"<<"matrixview"<<"-nokeepaspect";
    }
    else
    {int ind=arguments.indexOf("-nokeepaspect");
        if (ind>0)
            arguments.removeAt(ind);
        removeOption("-vo",true);

    }
    restart();
}
void mplayerfe::visualizeMV(bool enable)
{if ( enable)
    { removeOption("-lavdopts",true);
        arguments<<"-lavdopts"<<"vismv=7";
        emit show_message("Visalizing motion vectors",1000);
    }
    else
        removeOption("-lavdopts",true);

    restart();

}

void  mplayerfe:: palette(bool enable)
{if (enable)
    {
        removeFilter(palettestr);
        palettestr=QString("spp,palette");
        arguments <<"-vf-add"<< palettestr;
        emit show_message("Adding filter palette",1000);

    }
    else
    {
        removeFilter(palettestr);
    }
    restart();
}
void mplayerfe::negative(bool enable)
{if (enable)
    {
        removeFilter( negativestr);
        negativestr=QString("eq2=1.0:-0.8");
        arguments <<"-vf-add"<< negativestr;
        emit show_message("Adding filter negative",1000);

    }
    else
    {
        removeFilter(negativestr);
    }
    restart();

}

void mplayerfe::markEDL(QWidget *parent)
{
    bedlstart=!bedlstart;
    //QDataStream out(edlfile);


    if(bedlstart)
    { edlline=QString::number(_curpos);
        qDebug()<< edlline;
    }
    else
    {
        if (!edlfile->isOpen())
            edlfile->open(QIODevice::WriteOnly);

        dlg=new  QDialog(parent);
        rbskip = new QRadioButton("Skip",dlg);
        rbmute= new QRadioButton("Mute",dlg);
        rbskip->setChecked(true);
        QString li;
        QTime ti;
        li="What do you want with the selected portion:["+ti.addSecs(edlline.toFloat()).toString() +"->"+ _tcurpos.toString()+"] ?";
        QLabel *del = new QLabel(dlg);
        del->setText(li);
        edlline=edlline + " " +QString::number(_curpos);
        QPushButton *btn = new QPushButton(QIcon(":/images/ok.png"),QObject::tr("&Ok"),
                                           dlg);
        QGridLayout *lay = new QGridLayout(dlg);
        lay->addWidget(del,0,0,0);
        lay->addWidget(rbskip,1,1,0);
        lay->addWidget(rbmute,1,2,0);
        lay->addWidget(btn,2,3,0);
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        QObject::connect(btn, SIGNAL(clicked()),
                         this, SLOT(writeEDLline()));
        dlg->exec();
    }
    if(bedlstart)
        emit show_message("Marking start position",1000);
    else
        emit show_message("Marking end position",1000);

}
void mplayerfe::startFamilyFriendlymode()
{

    removeOption("-edlout",false);
    arguments<<"-edl"<<edl;
    _curpos=0;
    restart();


}
void mplayerfe::writeEDLline()
{if (rbskip->isChecked())
        edlline=edlline.append((" 0\n"));
    else
        edlline=edlline.append((" 1\n"));
    qDebug()<<edlline;
    QTextStream out(edlfile);   // we will serialize the data into the file
    out << edlline;
    dlg->close();

}
void mplayerfe::setAspectRatio(float val)
{
    int ind=arguments.indexOf("-nokeepaspect");
    if (ind>0)
    {
        arguments.removeAt(ind);
        restart();
    }
    if( val==0)
    {arguments<<"-nokeepaspect";
        restart();
    }
    else
    {
        cmd=QString("switch_ratio %1\n").arg(val);
        mProcess->write(cmd.toAscii());
        emit show_message("Changing aspectratio to "+QString::number(val),1000);
    }
}
void mplayerfe::crop(QRect *rect,bool enable )
{if (enable)
    {
        removeFilter(cropstr);
        cropstr=QString("scale,crop=%1:%2:%3:%4").arg(abs(rect->width())).arg(rect->height()).arg(rect->x()).arg(rect->y());
        arguments<<"-vf-add"<<cropstr ;
        emit show_message("Adding crop filter",1000);
        restart();
    }
    else
    {
        removeFilter(cropstr);
        emit show_message("Removing crop filter",1000);
        restart();
    }
}

void mplayerfe::switchSubtitle(int id)
{
    //cmd=QString("sub_vob %1").arg(QString(listSubtitleTrack.at(id)).toInt());
    arguments<<"-sid"<<QString::number(QString(listSubtitleTrack.at(id)).toInt());
    restart();
    qDebug()<<listSubtitleTrack;
    //mProcess->write(cmd.toAscii()+"\n");
}
void mplayerfe::setSubAlignment(int align)
{
    cmd=QString("sub_alignment %1").arg(align);
    mProcess->write(cmd.toAscii()+"\n");
    switch(align)
    {case 0:emit show_message("Setting Alignment to top",1000);
        break;
    case 1:emit show_message("Setting Alignment to center",1000);
        break;
    case 2:emit show_message("Setting Alignment to bottom",1000);
        break;

    }
}
void mplayerfe::scaleSubFont(int typ)        
{if( typ==0)
        cmd=QString("sub_scale 0.1 0");
    else
        cmd=QString("sub_scale -0.1 0");

    mProcess->write(cmd.toAscii()+"\n");
    qDebug()<<cmd;
}
void mplayerfe::setSubPos(int typ)       
{
    if (typ==0)
    {_subpos--;
        if(_subpos<0)
            _subpos= 0;

    }
    else
    {_subpos++;
        if(_subpos>100)
            _subpos= 100;
    }
    cmd=QString("sub_pos %1 1").arg(_subpos);
    mProcess->write(cmd.toAscii()+"\n");

}
void mplayerfe::setSubDelay(int typ,QWidget* par)
{
    if (typ==-1)
    {bool ok;
        int i ;

        i= QInputDialog::getInteger(par, tr("Set subtitle delay"), tr("Delay:(in milliseconds)"),100, -1000000, 1000000, 1, &ok);

        if(ok)
            cmd=QString("sub_delay %1 1").arg((float)i/1000);
    }
    else if (typ==0)
        cmd=QString("sub_delay 0.1 0");
    else
        cmd=QString("sub_delay -0.1 0");

    mProcess->write(cmd.toAscii()+"\n");

}
void mplayerfe::addAudioFilterWinampDsp()
{
    wdlg->show();
}
void mplayerfe::enableWinampPlugin(bool enable,QString path)
{   path = path.replace("/","\\\\");
    //qDebug()<<"[ath"<<path;
    if (enable)
    {
        bwinampdsp=true;
        removeFilter(equlizerstr);
        removeFilter( winampdspstr);
        winampdspstr=QString("wadsp=")+path+QString(":cfg=0")+",volume";
        arguments <<"-af-add"<<winampdspstr;
        emit show_message("Adding filter winamp dsp",1000);

    }
    else
    {
        bwinampdsp=false;
        arguments <<"-af-add"<<equlizerstr;
        removeFilter(winampdspstr);

    }
    restart();

}
void mplayerfe::enableEqualizer(QString val)
{//qDebug()<<"suck";
    removeFilter(equlizerstr);
    equlizerstr=QString("equalizer=")+val+",volume";

    arguments <<"-af-add"<<equlizerstr;
    //emit show_message("Adding filter Equalizer",1000);

}
void  mplayerfe::mpsettingChanged(QString s,QString k,QString v)
{
    emit settingChanged(s,k,v);

}
void mplayerfe::wmpsettings(QSettings *se)
{//qDebug()<<""<<se->value("Audio/Wadsp_rootdir","C:\Program Files\Winamp\Plugins\\").toString();

    wdlg->dlgsettings(se);

}
void mplayerfe::setaudiodriver(int devnum)
{
    if (devnum==1)
        argao<<"-ao"<<"win32";
    else if (devnum>1)
        argao<<"-ao"<<"dsound:device="+QString::number(devnum-2);


}
void mplayerfe::setCacheSize(long cs)
{
   argDemuxerOpt <<"-cache"<<QString::number(cs)<<"-cache-seek-min"<<QString::number(0)<<"-cache-min"<<QString::number(50);
}
void mplayerfe::removeDemuxlavf()
{
    uselavf=false;
}
void  mplayerfe::enableClosedCaption(bool en)
{
    if(en)
        arguments<<"-subcc"<<QString::number(1);
    else
        this->removeOption("-subcc",true);


    if (_started)
        restart();
}
void  mplayerfe::addAudioFilterVolnorm(bool en)
{
    if (en)
    {
        removeFilter("volnorm");
        arguments<<"-af-add"<< "volnorm";
        restart();
        emit show_message("Adding filter volnorm",1000);

    }
    else
    {
        removeFilter("volnorm");
        restart();
    }

}
void mplayerfe::unloadsub()
{

    int ind=arguments.indexOf("-sub");
    if (ind>0)
    {arguments.removeAt(ind);
        arguments.removeAt(ind);
    }

    restart();
}
void mplayerfe::enableEq(bool en)
{
    if (en)
    {//usercommand("af_add equalizer="+eqbandval);
        //usercommand("af_add volume");
        removeFilter(equlizerstr);
        enableEqualizer(eqbandval);
        if (_started)
            restart();
    }
    else
    {removeFilter(equlizerstr);
        //usercommand("af_del equalizer");
        //usercommand("af_del volume");
        if (_started)
            restart();
    }

}
void mplayerfe::setStartStop(float st,float stop)
{
    arguments<<"-ss"<<QString::number(st)<<"-endpos"<<QString::number(stop);


}
void  mplayerfe::forceidx()
{
    argVideoOpt<<"-forceidx";
}
void  mplayerfe::twins(bool enable)
{if (enable)
    {//tilestr
        removeFilter(twinstr);
        twinstr=QString("scale,tile=2:1");
        arguments <<"-vf-add"<< twinstr;//<<"-vo"<<"directx:noaccel" ;
        emit show_message("Adding filter twins",1000);
        restart();

    }
    else
    {
        //rmoveSubfilter("-vo");
        removeFilter(twinstr);
        restart();

    }
}
void  mplayerfe::sideview(bool enable)
{if (enable)
    {//tilestr
        removeFilter(svstr);

        svstr=QString("perspective=0:0:" +QString::number(this->videowidth())+":0:0:50:"+ QString::number(this->videowidth())+":"+ QString::number(this->videoheight())+":0");
        arguments <<"-vf-add"<< svstr;//<<"-vo"<<"directx:noaccel" ;
        emit show_message("Adding filter perspective",1000);
        restart();

    }
    else
    {
        //rmoveSubfilter("-vo");
        removeFilter(svstr);
        restart();

    }
}
void mplayerfe::smoothSeek()
{  if(this->curpos()>1)

    { if(!isnet)
        { if (this->_started)
            {if (!this->bmute)
                { if (!this->hasvideo())
                    {if (mutelock)
                        {this->mProcess->write("mute\n");
                            mutelock=false;


                        }
                    }

                }
            }
        }
    }

}
void mplayerfe::initMediaInfo()
{
    myLib0=new QLibrary(qApp->applicationDirPath()+"/MediaInfo.dll");



    f1 openMediaInfo = (f1) myLib0->resolve("MediaInfo_New");
    f2 readFile = (f2) myLib0->resolve("MediaInfo_Open");
    f4 closeMediaInfo =(f4) myLib0->resolve("MediaInfo_Close");
    f4  MediaInfo_Delete=(f4) myLib0->resolve("MediaInfo_Delete");
    f5  MediaInfo_Option=(f5) myLib0->resolve("MediaInfo_Option");
    f6  MediaInfo_Inform=(f6) myLib0->resolve(" MediaInfo_Inform");

    if (openMediaInfo>0)
    {
        mh=openMediaInfo();
        if (readFile>0)
        {wchar_t *prop=L"Duration";

            //QString to wchar_t*
            /////////////////////////////////////////////////////////////////
            const char *string=this->filepath().toAscii().constData();

            size_t size = strlen (string) + 1;
            wchar_t *buf = (wchar_t *)malloc (size * sizeof (wchar_t));

            size = mbstowcs (buf, string, size);
            if (size != (size_t) -1)
            {
                buf =  (wchar_t *)realloc (buf, (size + 1) * sizeof (wchar_t));

                qDebug()<<"file:"<<QString::fromWCharArray(buf );

            }
            /////////////////////////////////////////////////////////////////

            readFile(mh,buf);
            free(buf);
        }
    }

}
float mplayerfe::getStreamingDuration()
{float pos;
    f3 readInfo=(f3) myLib0->resolve("MediaInfo_Get");

    if (readInfo>0)
    {wchar_t *prop=L"Duration";
        wchar_t *result;
        result=readInfo(mh,0,0,prop,1,0);

        QString re= QString::fromWCharArray(result);
        qDebug()<<re;
        pos=re.toFloat()/1000.0;

    }
    return pos;
}
void  mplayerfe::fspp(bool enable)
{if (enable)
    {
        int ind=arguments.indexOf("screenshot");
        if (ind>0)
        {arguments.removeAt(ind);
            arguments.removeAt(ind-1);
        }

        removeFilter(fsppstr);
        fsppstr=QString("fspp=5:0:0:0");
        arguments <<"-vf-add"<<fsppstr ;
        emit show_message("Adding filter mirror",1000);
        restart();
    }
    else
    {
        removeFilter(fsppstr);
        arguments <<"-vf-add"<<"screenshot" ;
        restart();
    }
}
void mplayerfe::setfps(double fps)
{
    if (fps==0)
    {
        int ind=arguments.indexOf("-fps");
        if (ind>0)
        {arguments.removeAt(ind);
            arguments.removeAt(ind);
        }
        restart();
    }
    else
    {   removeFilter(fpsstr);
        fpsstr=QString::number(fps);
        arguments <<"-fps"<<fpsstr ;
        restart();
    }
}
QString mplayerfe::colorToRGB(unsigned int color) {
    QColor c;
    c.setRgb( color );

    QString s;
    return s.sprintf("0x%02x%02x%02x", c.blue(), c.green(), c.red() );
}
void mplayerfe::setInitSeekPos(double pos)
{
    argfrontEnd<<"-ss"<<QString::number(pos);
}
void  mplayerfe::startMplayer()
{
    QString strArgument;
    mProcess->clearArguments();
    mProcess->addArgument(mPath);
    commandLine ="";
    commandLine.append(mPath);
    commandLine.append(" ");

    foreach (strArgument, arguments) {
        commandLine+=strArgument+" ";
        mProcess->addArgument(strArgument);
    }

    qDebug()<<commandLine;
    mProcess->start();
}
void mplayerfe::mplayerConsole(QByteArray ba)
{

    QString mplayerOutputLine(ba);

    if(!_started){
     if (!_isRestarting){
        //ExMplayer log
        emit lineavailable (mplayerOutputLine);
        }

    //Network playback
    if( mplayerOutputLine.contains("Connecting to server")){

        isnet=true;
        _state=CONNECTING;
        emit show_message(QString("Connecting to server..."),2000) ;

    }
    else if( mplayerOutputLine.contains("Resolving")){
        _state=RESOLVING;
        emit show_message(QString("Resolving"),2000) ;
    }
    else if( mplayerOutputLine.contains("Cache fill")){

        if(rx_bufferfill.indexIn(mplayerOutputLine)>-1){

            _bufferfill=(int)rx_bufferfill.cap(1).toFloat();
            qDebug()<<"Buffering "<<_bufferfill;
        }
        _state=BUFFERING;
        emit show_message(QString("Buffering"),2000) ;

    }

    //Scanning font files
    if( mplayerOutputLine.contains("Scanning file")){
        if(!_hideFontDlg){

            if (!fldDlg){

                fldDlg=new fontLoadDialog(_wparent);
                fldDlg->setModal(true);
                fldDlg->setGeometry(_wparent->width()/2-fldDlg->width()/2,_wparent->height()/2-fldDlg->height()/2,fldDlg->width(),fldDlg->height());
                fldDlg->show();
                emit show_message("Please wait...Scanning font files...",4000) ;

            }
        }
    }
    if(!_isRestarting){


    //Check for Generating Index
    if (rx_gin.indexIn(mplayerOutputLine) >-1 ){

    if( rx_gin.cap(1).toInt()>1)
            emit showpg();
        emit show_message("Generating Index: "+QString::number(rx_gin.cap(1).toInt())+"%",2000);
    }

    //ID list
    if(mplayerOutputLine.contains("ID_")){

        idlist<<mplayerOutputLine;
        qDebug()<<mplayerOutputLine;
    }

    //Check for ac3
    if (mplayerOutputLine.contains("ac3"))
        emit foundac3();


    //Stream duration
    if(mplayerOutputLine.contains("ID_LENGTH",Qt::CaseInsensitive)){

        tmpstr=parsevalue("ID_LENGTH=","=",mplayerOutputLine);
        _duration=tmpstr.toFloat();
        emit gotduration(_duration);
        _tduration=  _tduration.addSecs(_duration);
        if (isurl)
            emit streamingDuration(_duration);

        qDebug()<<ba;

    }

    //Stream duration-a recheck
    if(mplayerOutputLine.contains("ANS_LENGTH",Qt::CaseInsensitive)){

        tmpstr=parsevalue("ANS_LENGTH=","=",mplayerOutputLine);
        _duration=tmpstr.toFloat();
        _tduration=QTime();
        _tduration=  _tduration.addSecs(_duration);
        emit lengthChanged();

        qDebug()<<ba;

    }



    //Check for subtitles
    if (!internalrestart){
        if(mplayerOutputLine.contains("ID_SUBTITLE_ID",Qt::CaseInsensitive))
            listSubtitleTrack<< parsevalue("ID_SUBTITLE_ID","=",mplayerOutputLine);
    }

    //Check for Audio Tracks
    if(mplayerOutputLine.contains("ID_AUDIO_ID",Qt::CaseInsensitive)){
        listAudioTrack<< parsevalue("ID_AUDIO_ID","=",mplayerOutputLine);
    }

    //Check for Video Tracks
    if(mplayerOutputLine.contains("ID_VIDEO_ID",Qt::CaseInsensitive)){
        listVideoTrack<< parsevalue("ID_VIDEO_ID","=",mplayerOutputLine);
    }

    //Check for audio codec used
    if(mplayerOutputLine.contains("Selected audio codec:",Qt::CaseInsensitive)){
        mapCodecs["audio"] =parsevalue("Selected audio codec",":",mplayerOutputLine) ;
    }

    //Check for video codec  used
    if(mplayerOutputLine.contains("Selected video codec",Qt::CaseInsensitive)){
        mapCodecs["video"] =parsevalue("Selected video codec",":",mplayerOutputLine) ;
    }

    //Check for audio device used
    if(mplayerOutputLine.contains("AO:",Qt::CaseInsensitive)){
        mapDevices["audio"] =parsevalue("AO",":",mplayerOutputLine) ;
    }

    //Check for Audio
    if(mplayerOutputLine.contains("ID_AUDIO_ID")){
        show_message("Found audio stream",1000);
    }

    //Check for Video
    if(mplayerOutputLine.contains("ID_VIDEO_ID")){
        show_message("Found video stream",1000);
    }

    //Check for no video
    if(mplayerOutputLine.contains("Video: no video")){
        _hasvideo=false;
    }

    //Emit video,audio found
    if  ( _hasvideo&& _hasaudio){
        emit foundAudioandVideo();
    }

    //Check for Seekable
    if(mplayerOutputLine.contains("ID_SEEKABLE")){
        tmpstr= parsevalue("ID_SEEKABLE","=",mplayerOutputLine);
        _isseekable =(bool)tmpstr.toInt();
        qDebug()<<"Seekable :"<<_isseekable;
    }

    //*******************************************************************
    //Title
    if(mplayerOutputLine.contains("Title:"))
        mapMetaInfo["title"]=parsevalue("Title",":",mplayerOutputLine) ;
    //Artist
    if(mplayerOutputLine.contains("Artist:"))
        mapMetaInfo["artist"]=parsevalue("Artist",":",mplayerOutputLine) ;
    //Album
    if(mplayerOutputLine.contains("Album:"))
        mapMetaInfo["album"]=parsevalue("Album",":",mplayerOutputLine) ;
    //Year
    if(mplayerOutputLine.contains("Year:"))
        mapMetaInfo["year"]=parsevalue("Year",":",mplayerOutputLine) ;
    //Comment
    if(mplayerOutputLine.contains("Comment:"))
        mapMetaInfo["comment"]=parsevalue("Comment",":",mplayerOutputLine) ;
    //Track
    if(mplayerOutputLine.contains("Track:"))
        mapMetaInfo["track"]=parsevalue("Track",":",mplayerOutputLine) ;
    //Track
    if(mplayerOutputLine.contains("Genre:"))
        mapMetaInfo["genre"]=parsevalue("Genre",":",mplayerOutputLine) ;

    //*******************************************************************

    //MetaInfo count
    if(mplayerOutputLine.contains("ID_CLIP_INFO_N=",Qt::CaseInsensitive))
        _metainfocount=parsevalue("ID_CLIP_INFO_N=","=",mplayerOutputLine).toInt();
  }

    //Check for Video Width

    if(mplayerOutputLine.contains("ID_VIDEO_WIDTH")){

        QString tmpstr= parsevalue("ID_VIDEO_WIDTH","=",mplayerOutputLine);

        _videowidth=tmpstr.toInt();
        _video_width=QString::number(tmpstr.toInt());

        if (_videowidth>0){

            _hasvideo=true;
            _bgotdimension=true;
            emit showvideoui();
            emit hidepg();

            show_message("Found video stream",1000);
            qDebug()<<"Got Video width:"<<_video_width;
        }

    }

    //Check for Video Height

    if(mplayerOutputLine.contains("ID_VIDEO_HEIGHT")){

        tmpstr= parsevalue("ID_VIDEO_HEIGHT","=",mplayerOutputLine);
        _videoheight=tmpstr.toInt();
        _video_height=QString::number(tmpstr.toInt());

        qDebug()<<"Got Video height:"<<_video_height;

    }

    //Audio Properties
    if(rx_audioinfo.indexIn(mplayerOutputLine) >-1){

        _audio_rate=QString::number(rx_audioinfo.cap(1).toInt()/1000);
        _audio_nch=rx_audioinfo.cap(2);
        _audio_bitrate=rx_audioinfo.cap(4);

        qDebug()<<"Audio rate:"<<_audio_rate;
        qDebug()<<"Audio nch:"<<_audio_nch;
        qDebug()<<"Audio bitrate:"<<_audio_bitrate;

        _hasaudio=true;

    }
    if(mplayerOutputLine.contains("Starting playback",Qt::CaseInsensitive)){

  qDebug()<<"IS RESTART"<<_hasvideo;
        QString fn;

        QFileInfo fi(this->filepath());
        fn = fi.baseName();
        QString title=mapMetaInfo["title"];
        QString artist=mapMetaInfo["artist"];
        if( artist!="")
                _friendlyTitle=artist+" - "+title;
        else
            _friendlyTitle=title;
        if(artist==""&&title=="")
         _friendlyTitle=fn;



        qDebug()<<"<---- emit startingplayback() ----->";

        if  (_hasvideo)
            qDebug()<<"Video Width :"<<_video_width<<"Video Height :"<<_videoheight;

        if(_bgotdimension && _hasvideo)
            emit startingplayback();
        if  (_hasaudio &&!_hasvideo)
            emit startingplayback();

        _started=true;

        if(!_isRestarting){
            //Show file name at startup
         this->usercommand("osd_show_text \""+ fn+"\" 2000 1");
         idlist.removeDuplicates();

        metainfoname=idlist.filter("ID_CLIP_INFO_NAME");
        metainfovalue=idlist.filter("ID_CLIP_INFO_VALUE");

        if(metainfoname.count()==metainfovalue.count()){
        for(int i=0;i<metainfoname.count();i++)
                metainfo<< parsevalue("ID_CLIP_INFO_NAME","=",metainfoname.at(i))+" : "+  parsevalue("ID_CLIP_INFO_VALUE","=",metainfovalue.at(i));
        }

        //Recheck length
        cmd=QString("get_time_length\n");
        mProcess->write(cmd.toAscii());

        //Resize video
        if (_video_width>0 && _video_height>0){
            emit resizeVideoWindow(_videowidth,_videoheight);
        }

        if(fldDlg){
            fldDlg->close();
        }

        }

        qDebug()<<"==================================================";
        qDebug()<<"Meta Info"<< mapMetaInfo;
        qDebug()<<"===================================================";
        qDebug()<<"Audio tracks:" << listAudioTrack;
        qDebug()<<"===================================================";
        qDebug()<<"Video tracks:" << listVideoTrack;
        qDebug()<<"===================================================";
        qDebug()<<"Subtitle tracks:"<< listSubtitleTrack;
        qDebug()<<"===================================================";
        qDebug()<<"Codec(s) used:"<< mapCodecs;
        qDebug()<<"===================================================";
        qDebug()<<"Device(s) used:"<< mapDevices;
        qDebug()<<"===================================================";



    }

  }
 else{
    //************************************************************************
      //Check for video device used
      if(mplayerOutputLine.contains("VO:",Qt::CaseInsensitive)){
            mapDevices["video"] =parsevalue("VO",":",mplayerOutputLine) ;
      }
    //Check for Cache filling
    if ( mplayerOutputLine.contains("Cache not",Qt::CaseInsensitive)){

        cachefill=true;
        qDebug()<<mplayerOutputLine;
    }

    //Mute while seeking
    if (mplayerOutputLine.contains("Position",Qt::CaseInsensitive)){

        if (!this->bmute){

            if(!mutelock){
                this->mProcess->write("mute\n");
                mutelock=true;

            }
        }

    }

    //Check the state of mplayer
    if(mplayerOutputLine.contains("A:",Qt::CaseInsensitive)){

        //Playing >
        _state=PLAYING;
        if (!bstop)
            emit playing();
        _isRestarting=false;


    }
    else{

        if( !_isRestarting){
        //ExMplayer log
        emit lineavailable (mplayerOutputLine);
        }

        //Paused ||
        if(mplayerOutputLine.contains("ID_PAUSED",Qt::CaseInsensitive)){

            _state=PAUSED;
            emit paused();

        }
    }

    //Get status of MPlayer parameters

    //Screenshot
    if(rx_screenshot.indexIn(mplayerOutputLine)>-1){
           this->usercommand("osd_show_text \"Screenshot is saved as " + rx_screenshot.cap(1) + "\" 2000 1");
    }

    //Position
    if(rx_pos.indexIn(mplayerOutputLine)>-1){

        _curpos=rx_pos.cap(1).toFloat();
        _tcurpos=QTime();
        _tcurpos=_tcurpos.addSecs(_curpos);


    }

    //Playback speed
    if(rx_speed.indexIn(mplayerOutputLine)>-1)
        _currentspeed =rx_speed.cap(1);
    else
        _currentspeed="1.00x";

    //Audio cpu usage
    if(rx_audiocpu_usage0.indexIn(mplayerOutputLine)>-1)
        _audio_cpu_usage= rx_audiocpu_usage0.cap(1);

    if(_hasvideo){

        //Audio cpu usage
        if(rx_audiocpu_usage1.indexIn(mplayerOutputLine)>-1)
         _audio_cpu_usage= rx_audiocpu_usage1.cap(1);

        //Video cpu usage
        if(rx_videocpu_usage.indexIn(mplayerOutputLine)>-1)
            _video_cpu_usage=rx_videocpu_usage.cap(1);

        //Frames decoded
        if(rx_frame.indexIn(mplayerOutputLine)>-1)
            _framecount=rx_frame.cap(1);

        //A-V delay
        if(rx_delay.indexIn(mplayerOutputLine)>-1)
            _avdelay=rx_delay.cap(1);
    }

    //Subtitles
    if(_started){

        if(_hasvideo){

            if (!_isRestarting){

                if (mplayerOutputLine.contains("ID_SUBTITLE_ID")){

                    if (!internalrestart){

                        listSubtitleTrack<< parsevalue("ID_SUBTITLE_ID","=",mplayerOutputLine);
                        listSubtitleTrack.removeDuplicates();
                        // listSubtitleTrack.clear();
                        emit foundSubtitletrack(listSubtitleTrack);

                    }

                    qDebug()<<"Subtitles " <<listSubtitleTrack;

                }
            }

        }


        if (!(mplayerOutputLine.contains(QLatin1String("A:"))||mplayerOutputLine.contains("V:"))){

            if (this->mutelock){
                if (!this->bmute){
                    if(!mutelock){
                        this->mProcess->write("mute\n");
                        mutelock=true;

                    }
                }
            }
        }


    }
   }

    if (mplayerOutputLine.contains("MPlayer crashed",Qt::CaseInsensitive))
       { _state=CRASHED;
        qDebug()<<"MPlayer crashed!!!";
        }
    if(! _isRestarting)
   {
    //************************************************************************
    //SIGNAL 11

    if ( mplayerOutputLine.contains("ID_SIGNAL=11",Qt::CaseInsensitive)){

        //- avi Index rebuild
        if (_filepath.contains("avi",Qt::CaseInsensitive)){
            emit useidx();
        }
        else{
            //MPlayer crashed
            if (mplayerOutputLine.contains("MPlayer crashed",Qt::CaseInsensitive))
               { _state=CRASHED;
                qDebug()<<"MPlayer crashed";
                }
        }

    }

    //Handle Quit message

    if ( mplayerOutputLine.contains("ID_EXIT=QUIT",Qt::CaseInsensitive))
    {

        //Stopped []
        bstop=true;
        _state=STOPPED;
        bstopping=true;
        emit stopping();

        qDebug()<<"stopped......";
    }

    //Handle EOF
    if ( mplayerOutputLine.contains("ID_EXIT=EOF",Qt::CaseInsensitive)){

        if (!_hasvideo&&!_hasaudio){

            _isRestarting=false;

            if (_filepath.contains("mp3",Qt::CaseInsensitive)){

                if (uselavf)
                    emit removelavf();
                else{
                    _state=STOPPED;
                    emit showerrortext("Oops!!!! No audio,Video.");
                }
            }
            else
                emit showerrortext("Oops!!!! No audio,Video.");

        }
        emit eof();
        emit this->show_endmessage("End of playback(EOF)");

        qDebug()<<"End of playback(EOF)";
    }
    }

}
