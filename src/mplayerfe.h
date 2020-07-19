/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2011-2013 Rupesh Sreeraman

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
#ifndef MPLAYERFE_H
#define MPLAYERFE_H
#include <QtCore>
#include <QtWidgets>
#include <QDebug>
#include "winampdspdialog.h"
#include <QActionGroup>
#include <QMessageBox>
#include <fontloaddialog.h>
#include <QPointer>
#include <myprocess.h>
#include <assstyles.h>
#ifdef Q_OS_WIN
#include <windows.h>
#endif

typedef long (*f1) ();
typedef long (*f2) (long,wchar_t *);
typedef wchar_t* (*f3) (long,int,int, wchar_t *,int,int);
typedef void (*f4) (long );
typedef long (*f5) (long,const char *,const char *);
typedef const char* (*f6) (long,long);

class mplayerfe : public QObject
{
 Q_OBJECT

public:
    mplayerfe(QObject *parent = 0,QWidget* wparent=0);
   ~mplayerfe();

    enum State{
        CONNECTING=0,
        RESOLVING,
        BUFFERING,
        PLAYING,
        PAUSED,
        STOPPED,
        CRASHED
       };

    QStringList idlist;
    QStringList metainfo;
    QStringList arguments;
    QStringList argaudiofilters;
    QStringList argvideofilters;
    QStringList argao;
    QStringList argSubOpt;
    QString mPath;
    MyProcess *mProcess;
    QTimer *timer;
    QString tmpstr;
    QString audioFile;
    bool bstop;
    QString commandLine;


    //---------------------------------------------
    QStringList listTemp;
    QStringList listVideoTrack;
    QStringList listAudioTrack;
    QStringList listSubtitleTrack;
    QStringList listAudioRepeat;

    QMap<QString, QString> mapCodecs;
    QMap<QString, QString> mapDevices;
    QMap<QString, QString> mapMetaInfo;
    QMap<QString, QString> mapFileSubtitles;

    //-----------------------------------------------
    QString getVideoFormat(){return _videoFormat;}
    QString getAudioRate(){return _audio_rate;}
    QString getAudioNch(){return _audio_nch;}
    QString getAudioBitrate(){return _audio_bitrate;}
    QString getVideoWidth(){return _video_width;}
    QString getVideoHeight(){return _video_height;}
    QString filepath(){return _filepath;}
    int  videowidth(){return _videowidth;}
    bool isRestarting(){return _isRestarting;}
    int  videoheight(){return _videoheight;}
    bool isfullscreen(){return bfullscreen;}
    bool ismuted(){return bmute;}
    bool ispaused(){return bpause;}
    void setVideoWinid(long int videowinid){ _videowinid=videowinid; }
    bool isseekable(){return _isseekable;}
    bool hasaudio(){ return _hasaudio; }
    bool hasvideo(){ return _hasvideo; }
    float  duration(){ return _duration; }
    float  starttime(){ return _starttime; }
    QTime  tduration(){ return _tduration;}
    QString getMediaTitle(){return _friendlyTitle;}
    QString currentspeed(){ return _currentspeed;}
    QString video_cpu_usage(){ return _video_cpu_usage;}
    QString audio_cpu_usage(){ return _audio_cpu_usage;}
    QString framecount(){ return _framecount;}
    QString avdelay(){return _avdelay;}
    float curpos(){ return _curpos; }
    QTime tcurpos(){ return _tcurpos;}
    int metainfocount(){ return _metainfocount;}
    State state(){return _state;}
    bool isstarted(){return _started;}
    int getBufferFill(){return _bufferfill;}
signals:
    void starting();
    void startingplayback();
    void playing();
    void paused();
    void stopping();
    void eof();
    void show_message(QString msg,int dur);
    void show_endmessage(QString msg);
    void lineavailable (QString line);
    void restarting();
    void settingChanged(QString group,QString key,QString value);
    void lengthChanged();
    void gotduration(float dur);
    void foundSubtitletrack(QStringList sl );
    void addSubtitletrack(QStringList sl );
    void playNextFile();
    void foundAudioandVideo();
    void removelavf();
    void foundac3();
    void processFinished(int ec,bool stop);
    void showmsgBox(QString msg);
    void useidx();
    void showpg();
    void hidepg();
    void showerrortext(QString tex);
    void progressiveStreaming();
    void download();
    void streamingDuration(float le);
    void showvideoui();
    void resizeVideoWindow(int wid,int height);
    void fontScanProgress(int val);
    void disableSeek();
public slots:
    void startMplayer();
    void play(QString File,int volume);
    void pause();
    void stop();
    void toggleMute();
    void togglefullscreen(){bfullscreen=!bfullscreen;}
    void setVolume(int vol);
    void seek(int pos);
    void setOSDlevel(int osdlevel);
    void setframedroplevel(int framedroplevel);
    void framestep();
    void seeknseconds(int nsec);
    void setSpeed(float speed,int type);
    //type=0 then increase/decrease by value
    //type=1 then halve/double speed
    //type=2 then reset speed,ie,1x
    void setaudiodelay(float delay,QWidget* par);
    void setvideoproperty(QString propery,int value);
    //[brightness|contrast|gamma|hue|saturation]
    void setequalizerbandvalue(QString bandval);
    void takescreenshot(int type);
    //0 Take a single screenshot.
    //1 Start/stop taking screenshot of each frame.
    void loadsubtitles(QString subfile);
     void toggle_subtitle_visibility();
     void usercommand(QString user_cmd);
     void readmpconsole();
     void switchAudio(int id);
     void fastRestart(QStringList extraoption);
     void loadExternalFile(QString File);
     void setAudioChannels(int ch);
     void addAudioFilterKaraoke(bool enable);
     void addAudioFilterResample(int fre);
     void addAudioFilterVolnorm(bool en);
     void removeFilter(QString filter);
     void addAudioFilterSurround(int val,QWidget *parent);
     void setSurround();
     void resetSurround();
     void addAudioFilterExStereo(int val,QWidget *parent);
     void setExStereo();
     void resetExStereo();
     void addAudioFilterScaleTempo(int val,QWidget *parent);
     void setScaleTempo();
     void resetScaleTempo();
     void disableFilter();
     void addAudioFilterDelay(int ch1,int ch2,QWidget *parent);
     void setDelay();
     void resetDelay();
     void setch1Text(int val);
     void setch2Text(int val);
     void setStereoMode(int mode);
     void removeLogo(QRect *rect,bool enable );
     void crop(QRect *rect,bool enable );
     void tile(bool enable);
     void flip(bool enable);
     void mirror(bool enable);
     void halfvideo(bool enable);
     void rotate(int val);// -1 to disable
     void swapuv(bool enable);
     void onebpp(bool enable);
     void painting(bool enable);
     void noise(bool enable);
     void blur(bool enable);
     void matrixview(bool enable);
     void rmoveSubfilter(QString filter);
     void visualizeMV(bool enable); 
     void palette(bool enable);
     void negative(bool enable);
     void markEDL(QWidget *parent);
     void startFamilyFriendlymode();
     void writeEDLline();
     void setAspectRatio(float val);
     void switchVideo(int id);
     void switchSubtitle(int id);
     void setSubAlignment(int align);
     void scaleSubFont(int typ);
     void setSubPos(int typ);
     void setSubDelay(int typ,QWidget *parent);
     void setColorkey(int col){ckey=colorToRGB(col);}
     void setaspect(bool val){keepaspect=val;}
     void addAudioFilterWinampDsp();
     void enableWinampPlugin(bool enable,QString path);
     void setPriority(QString val){_priority=val;}
     void enableEqualizer(QString val);
     void mpsettingChanged(QString,QString,QString);
     void wmpsettings(QSettings *se);
     void setaudiodriver(int devnum);
     void setCacheSize(long cs);
     void removeDemuxlavf();
     void restart();
     void enableClosedCaption(bool en);
     void unloadsub();
     void enableEq(bool en);
     void eqvalues(QString val){eqbandval=val;}
     void setStartStop(float st,float stop);
     int getVolume(){return _curvolume;}
     void setSilent(bool sil){_silent=sil;}
     void configureSoftEqualiser(bool _en){_useVideoSoftEq=_en;}
     void emitProcessFinished(int ec){_state=STOPPED;emit processFinished(ec,bstopping);}
     void forceidx();
     void twins(bool enable);
     void sideview(bool enable);
     void smoothSeek();
     void initMediaInfo();
     float getStreamingDuration();
     void fspp(bool enable);
     void setfps(double fps);
     void hideFontDlg(){_hideFontDlg=true;}
     void setInitSeekPos(double pos);
     QString shortPathName(QString long_path);
     void mplayerConsole(QByteArray ba);
     void Stereo3D(bool enable);
     void Stereo3D(QString inFmt,QString outFmt);
     void StartUp3D(QString inFmt,QString outFmt);
     void ConvertStereoVideoToMono(bool enable);
     void addDefaultVideoDriver();
     void addVolumeBoost(bool enable,long val);
     void setVolumeBoost(long val);
     void setSubtitleCodePage(QString cp);
    //void setcrossfading(int sec,bool enable);

 private:
   QString parsestatusline(QString serstr,QString str);
   QString parsevalue( QString serstr,QString sep, QString str);
   QString _audio_nch;
   QString _audio_rate;
   QString _audio_bitrate;
   QString _video_width;
   QString _video_height;

   QString cmd;
   bool _started;
   float _duration;
   float _starttime;
   float _curpos;
   int _bufferfill;
   float tmpcurpos;
   QTime _tduration;
   QTime _tcurpos;
   int _metainfocount;
   bool isseeking;
   bool _hasaudio;
   bool _hasvideo;
   QString _currentspeed;
   QString _audio_cpu_usage;
   QString _video_cpu_usage;
   QString _framecount;
   QString _avdelay;
   bool _isseekable;
   State _state;
   long int  _videowinid;
   bool bpause;
   bool bmute;
   bool bfullscreen;
   bool bsubtvisible;
   int _videoheight;
   bool _isRestarting;
   int _videowidth;
   bool bedlstart;
   bool _usestereovideo;
   bool _playmonovideo;
   bool _usevolumeboost;
   bool _useVideoSoftEq;

   QString _filepath;
   QStringList metainfovalue;
   QStringList metainfoname;
   void init();
   int _curvolume;
   QDialog *dlg;
   QSpinBox *sb ;
   QLabel *vlab1;
   QLabel *vlab2;
   QSlider *sliderDelaych1;
   QSlider *sliderDelaych2;
   QSlider *sliderScaleTempo;
   QSlider *sliderExstereo;
   QString resamplestr;
   QString surroundstr;
   QString exstereostr;
   QString scaletempostr;
   QString chdelaystr;
   QString disablefilterstr;
   QString delogostr;
   QString tilestr;
   QString flipstr;
   QString mirrorstr;
   QString halfvideostr;
   QString rotatestr;
   QString swapuvstr;
   QString onebppstr;
   QString paintingstr;
   QString noisestr;
   QString blurstr;
   QString matrixstr;
   QString palettestr;
   QString negativestr;
   QString cropstr;
   QString twinstr;
   QString fsppstr;
   QString fpsstr;
   QString svstr;
   QString stereo3Dstr;
   QString volumeBoostStr;


   QFile *edlfile;
   QString edlline;
   QString winampdspstr;
   QRadioButton *rbskip;
   QRadioButton *rbmute;
   int _align;
   int _subpos;
   bool bstopping;
   QString ckey;
   bool keepaspect;
   WinampDspDialog *wdlg;
   QStringList argfrontEnd;
   QStringList argDemuxerOpt;
   QStringList argAudioOpt;
   QStringList argVideoOpt;
   QString _priority;
   QString equlizerstr;
   bool bwinampdsp;
   QWidget* _wparent;
   bool uselavf;
   bool cc;
   bool foundsub;
   bool internalrestart;
   QString eqbandval;
   bool _silent;
   QString edl;
   long volumeBoost;
   QString subTrackId;


   bool mutelock;
   long mh;
   QLibrary *myLib0;
   bool isurl;
   bool cachefill;
   bool isnet;
   QString _friendlyTitle;
   bool _hideFontDlg;
   bool _bgotdimension;
   int _osdLevel;
   QString _currentSubtitleTrack;
   QPointer<fontLoadDialog> fldDlg;
   void removeOption(QString option,bool addseek);
   QString colorToRGB(unsigned int color) ;
   QString _videoFormat;
   void writeCmd(QString str);



};

#endif // MPLAYERFE_H
