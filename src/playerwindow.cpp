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

#include "playerwindow.h"
#include "ui_playerwindow.h"
#include "paths.h"
#include <QDesktopWidget>

QDesktopWidget *desktop;
QDesktopServices *mycomputer;
//extern "C" __declspec(dllimport) double AddNumbers(double a, double b);

PlayerWindow::PlayerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayerWindow)
{

    QCoreApplication::addLibraryPath(qApp->applicationDirPath()+"/imageformats");
    starting=true;
    mp=new mplayerfe(this,this);
    QString cmd;
    ui->setupUi(this);



    this->disableStylesheet();
    qDebug()<< "Config path :"<<Paths::configPath();
    settings=new QSettings(Paths::configPath()+"/ExMplayer.ini",QSettings::IniFormat,this);

    if (settings->value("Skin/style","aqua").toString()=="wood")
        QApplication::setStyle(new NorwegianWoodStyle);
    else if(settings->value("Skin/style","aqua").toString()=="aqua")
        emit setAqua();
    else
        qApp->setStyle(settings->value("Skin/style","aqua").toString());

    if (settings->value("Skin/style","aqua").toString()!="windowsxp"&&settings->value("Skin/style","aqua").toString()!="aqua")
        QApplication::setPalette(QApplication::style()->standardPalette());
    QPalette p = qApp->palette();

    p.setColor(QPalette::Window, QColor(0,0,255));
    //qApp->setStyle(new glassstyle);

    //Loading config
    settings=new QSettings(Paths::configPath()+"/ExMplayer.ini",QSettings::IniFormat,this);
    myconfig=new config();
    desktop=qApp->desktop();

    this->ui->dockBrowser->setVisible(false);
    //shortcuts
    createShortcuts();

    //play list
    myplaylist=new playList(this);
    setupPlaylistWindow();


    QString picfolder=mycomputer->storageLocation(QDesktopServices::PicturesLocation);
    myconfig->set_screenshotfolder(settings->value("Video/CaptureDir",picfolder).toString());

    //log window
    setupLogWindow();

    //file
    bstop=true;
    fileType=0;
    lavf=true;
    useidx=false;
    bfbvis=true;
    bplvis=false;
    usingfidx=false;

    //Setting ui
    setupMyUi();

    brotate=false;
    starting=false;


    if (qApp->arguments().count()>1)
    {cmd=qApp->arguments().at(1);

        if (!cmd.isEmpty()){
            if(cmd.contains("add-to-playlist",Qt::CaseInsensitive)){
                myplaylist->addFile(qApp->arguments().at(2));

            }
            else{
                myplaylist->addFile(cmd);
                myplaylist->playFirstFile();
            }
        }
    }
    readSettingsGeo();


}

PlayerWindow::~PlayerWindow()
{ 

    delete mp;
    delete myplaylist;
    delete ui;
#ifdef Q_OS_WIN
    delete winscreensaver;
#endif

}

void PlayerWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void PlayerWindow::on_btnSaveLog_clicked()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save as"),
                                                    "",
                                                    tr("Log File (*.log);;Text File (*.txt)"),
                                                    &selectedFilter,
                                                    options);
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);   // we will serialize the data into the file
        out << ui->mpconsole->toPlainText();
    }
}
void PlayerWindow::setupLogWindow()
{
    ui->dock_log->setWidget(ui->frame_log);
    QObject::connect(ui->cmdLine,SIGNAL(returnPressed()),ui->cmdLine,SLOT(clear()));
    QStringList wordList;
    wordList << "get_audio_bitrate"
             << "get_audio_codec"
             << "get_audio_samples"
             << "get_file_name"
             << "get_meta_album"
             << "get_meta_artist"
             << "get_meta_comment"
             << "get_meta_genre"
             << "get_meta_title"
             << "get_meta_track"
             << "get_meta_year"
             << "get_percent_pos"
             << "get_property "
             << "get_sub_visibility"
             << "get_time_length"
             << "get_time_pos"
             << "get_vo_fullscreen"
             << "get_video_bitrate"
             << "get_video_codec"
             << "get_video_resolution"
             << "osd_show_text"
             << "get_time_pos"
             << "get_vo_fullscreen"
             << "get_video_bitrate"
             << "get_video_codec";
    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->cmdLine->setCompleter(completer);
    ui->dock_log->hide();
    ui->dock_log->setFloating(true);

}

void PlayerWindow::on_cmdLine_returnPressed()
{
    mp->usercommand(ui->cmdLine->text());
}

void PlayerWindow::initMPlayer(QString file,int type)
{

    QMutex mutex;
    mutex.lock();
    ui->mpconsole->clear();
    videoWin->mplayerlayer->hide();
    windowTimer->setInterval(1);
    windowTimer->start();
    artisttext="";
    albumtext="";
    yeartext="";
    movie->stop();
    zoomfact=1.0;
    usingfidx=false;

    if (picflow>0)
    {
        picflow->close() ;
        delete  picflow;
    }
    videoWin->showErrorText("");
    videoWin->showeof(false);

    mp=new mplayerfe(this,this);
    if(currentFilePos!=0)
    {
        if (currentFilePos>0)
        {
            mp->setInitSeekPos(currentFilePos);
        }

        currentFilePos=0;

    }
    QString picfolder=mycomputer->storageLocation(QDesktopServices::PicturesLocation);
    myconfig->set_screenshotfolder(settings->value("Video/CaptureDir",picfolder).toString());
    loadMPlayerConfig();
    mp->mProcess->setWorkingDirectory(myconfig->screenshotfolder);
    videoWin->setColorKey(QColor(0,0,0));
    mp->setColorkey(5);
    mp->setVideoWinid((long int)videoWin->videoLayer()->winId());
    mp->wmpsettings(settings);
#ifdef Q_OS_WIN
    mp->setaudiodriver(settings->value("Audio/DevNo","0").toInt());
#endif

    QObject::connect(mp,SIGNAL(streamingDuration(float)),this,SLOT(streamingDuration(float)));
    QObject::connect(mp,SIGNAL(download()),this,SLOT(wgetDownload()));
    QObject::connect(mp,SIGNAL(progressiveStreaming()),this,SLOT(startProgressiveStreaming()));
    QObject::connect(mp,SIGNAL(gotduration(float)),myplaylist,SLOT(setDuration(float)));
    QObject::connect(mp,SIGNAL(starting()),ui->mpconsole,SLOT(clear()));
    QObject::connect(mp,SIGNAL(lineavailable(QString)),ui->mpconsole,SLOT(append(QString)));
    QObject::connect(mp,SIGNAL(startingplayback()),this,SLOT(startingPlayback()));
    //QObject::connect(mp,SIGNAL(show_message(QString,int)),ui->statusBar,SLOT(showMessage(QString,int)));
    //QObject::connect(mp,SIGNAL(restarting()),ui->mpconsole,SLOT(clear()));
    QObject::connect(mp,SIGNAL(settingChanged(QString,QString,QString)),this,SLOT(settingChanged(QString,QString,QString)));
    QObject::connect(mp,SIGNAL(lengthChanged()),this,SLOT(lengthChanged()));
    QObject::connect(mp,SIGNAL(foundSubtitletrack(QStringList)),this,SLOT(foundSubtitletrack(QStringList)));
    QObject::connect(mp,SIGNAL(show_endmessage(QString)),ui->labelStatus,SLOT(setText(QString)));
    QObject::connect(mp,SIGNAL(paused()),this,SLOT(paused()));
    QObject::connect(mp,SIGNAL(playing()),this,SLOT(playing()));
    QObject::connect(mp,SIGNAL(stopping()),this,SLOT(stopping()));
    QObject::connect(mp,SIGNAL(eof()),this,SLOT(hidebusypg()));
    QObject::connect(mp,SIGNAL(removelavf()),this,SLOT(removelavf()));
    QObject::connect(mp,SIGNAL(foundac3()),this,SLOT(enableChannels()));
    QObject::connect(mp,SIGNAL(processFinished(int,bool)),this,SLOT(playNextAfterFinish(int,bool)));
    QObject::connect(mp,SIGNAL(useidx()),this,SLOT(useidxnplay()));
    QObject::connect(mp,SIGNAL(showpg()),this,SLOT(showpg()));
    QObject::connect(mp,SIGNAL(hidepg()),pi,SLOT(hide()));
    QObject::connect(mp,SIGNAL(hidepg()),piv,SLOT(hide()));
    QObject::connect(mp,SIGNAL(hidepg()),pi,SLOT(stopAnimation()));
    QObject::connect(mp,SIGNAL(hidepg()),piv,SLOT(stopAnimation()));
    QObject::connect(mp,SIGNAL(showerrortext(QString)),this,SLOT(showerror(QString)));
    QObject::connect(mp,SIGNAL(showvideoui()),videoWin->mplayerlayer,SLOT(show()));
    //QObject::connect(mp,SIGNAL(resizeVideoWindow(int,int)),this,SLOT(resizeVideoWindow(int,int)));
    //QObject::connect(mp,SIGNAL(eof()),this,SLOT(resetUi()));
    //QObject::connect(mp,SIGNAL(showmsgBox(QString)),this,SLOT(showMsgBox(QString)));


    isstreaming=false;
    ui->actionStep1_fm->setEnabled(true);
    ui->actionStep2_fm->setEnabled(true);

    if( cdlg)
        cdlg->setMp(mp);

    mp->enableClosedCaption(true);
    ui->actionEnable_Closed_Captions->setChecked(true);

    if(!lavf)
    {
        mp->removeDemuxlavf();
        lavf=true;
    }
    if(useidx)
    { usingfidx=true;
        mp->forceidx();
        useidx=false;
    }
    fileType=type;

    //QObject::connect(mp,SIGNAL(playNextFile()),this,SLOT(setdurequal()));
    if (crossfade)
        QObject::connect(this,SIGNAL(sgcrossfade()),this,SLOT(crossfadePlay()));

    //QObject::connect(mp,SIGNAL(eof()),myplaylist,SLOT(playNextFile()));
    switch (type)
    {case 1:
        mp->setCacheSize(settings->value("Network/cache","320").toInt());
    }

    mp->setSilent(false);
    if (settings->value("Audio/mute","0").toInt()==1)
    {mp->play(file,0);
        mp->toggleMute();
    }
    else
        mp->play(file,ui->sliderVolume->value());

    currentFile=file;

    if (fr)
    { fr->stop();
        delete fr;
    }

    //QObject::connect(mp,SIGNAL(eof()),this->playerTimer,SLOT(stop()));
    videoWin->setPixmap(QPixmap());
    videoWin->setZoom(1.0);
    pi->show();
    pi->setAnimationDelay(30);
    pi->startAnimation();
    piv->move(videoWin->width()/2-piv->width()/2,videoWin->height()/2-piv->height()/2);
    piv->show();
    piv->setAnimationDelay(25);
    piv->startAnimation();
    // QMessageBox::critical(this,qApp->applicationName(),QString::number(videoWin->width()/2-piv->width()/2),QMessageBox::Ok,QMessageBox::Cancel);

    //ui->progressBarBusy->setMinimum(0);
    //ui->progressBarBusy->setMaximum(0);
    //ui->progressBarBusy->show();

    ui->labelStatus->setText(tr("Opening..."));



    iseof=false;
    bplay=false;
    bstop=false;
    recentFilesMenu->addRecentFile(currentFile);
    mutex.unlock();
}

void  PlayerWindow::setupMyUi()
{


#ifdef Q_OS_LINUX
    ui->actionWinamp_Dsp->setVisible(false);
# endif

    ui->actionInternet_Radio->setVisible(false);
    ui->actionCopy_Audio_CD->setVisible(false);

    windowTimer = new QTimer(this);
    QObject::connect(windowTimer, SIGNAL(timeout()), this,SLOT(updatevideovindow()));


    videoWin=new  MplayerWindow(this,0);
    videoWin->setAlignment(Qt::AlignCenter);
    videoWin->allowVideoMovement(true);

    videoWin->showLogo(false);

    movie = new QMovie(":/images/backanim.gif");

    this->videoWin->setMovie(movie);
    movie->start();
    //videoWin->mplayerlayer->hide();
    videoWin->showLogo(true);

    panel = new QWidget( this );
    panel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    panel->setMinimumSize( QSize(1,1) );
    panel->setFocusPolicy( Qt::StrongFocus );
    // panel
    panel->setAutoFillBackground(TRUE);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(videoWin);
    panel->setLayout(layout);

    this->setCentralWidget(panel);
    connect(this->videoWin, SIGNAL(mousewheelsg(QWheelEvent*)), this, SLOT(wheelEvent(QWheelEvent*)));
    mousewheelrole=settings->value("Mouse/Wheel","0").toInt();

    isstreaming=false;
    isdownloading=false;
    fmnu=new QMenu(this);
    fmnu->addAction(ui->actionForward_10_seconds);
    fmnu->addAction(ui->actionForward_1_minute);
    fmnu->addAction(ui->actionForward_10_minutes);
    ui->toolButtonForward->setMenu(fmnu);
    rmnu=new QMenu(this);
    rmnu->addAction(ui->actionRewind_10_seconds);
    rmnu->addAction(ui->actionRewind_1_minute);
    rmnu->addAction(ui->actionRewind_10_minutes);
    pbmnu=new QMenu(this);
    pbmnu->addAction(ui->actionAdd_File_to_pl);
    pbmnu->addAction(ui->actionAdd_Folder_to_pl);
    pbmnu->addAction(ui->action_Load_pl);
    pbmnu->addAction(ui->action_Save_as_playlist);


    ui->toolButtonplaylist->setMenu(pbmnu);
    ui->toolButtonRewind->setMenu(rmnu);
    ui->toolButtonSpeed->setMenu(ui->menuSpeed);
    ui->actionSave_cover_art->setEnabled(false);
    ui->action_Stop->setVisible(false);
    // ui->toolBarStatus->setVisible(false);
    tmpxpos=0;
    tmpypos=0;
    xpos=0;
    ypos=0;
#ifdef Q_OS_WIN
    winscreensaver =new WinScreenSaver();
    winscreensaver->disable();
#endif
    //ui->menu_Alignment->setVisible(false);
    //ui->label_11->setSuffix(" dB");
    hascover=false;
    isfullscreen=false;
    recentFilesMenu = new QRecentFilesMenu(tr("Recent Files"), ui->menu_Open);

    
    recentFilesMenu->restoreState(settings->value("History/recentFiles").toByteArray());
    connect(recentFilesMenu, SIGNAL(recentFileTriggered(const QString &)), this, SLOT(addRecentFileAndPlay(QString)));
    ui->menu_Open->insertMenu(ui->action_Exit,recentFilesMenu);

    iseof=false;
    // crossfade=true;

    //QObject::connect(this,SIGNAL(keyPress(QKeyEvent*)),ui->menuBar,SLOT(keyPressSlot(QKeyEvent*)));
    QObject::connect(ui->sliderSeek,SIGNAL(showtooltip(QPoint *)),this,SLOT(showtooltip(QPoint *)));
    QObject::connect(ui->sliderSeek,SIGNAL(hoverValue(QString,QPoint*)),this,SLOT(showSeekpos(QString,QPoint*)));


    QObject::connect(ui->dock_Playlist,SIGNAL(sgcontextMenuEvent(QContextMenuEvent*)),this,SLOT(showCtxmenuPlaylist(QContextMenuEvent*)));
    QObject::connect(ui->dock_Playlist,SIGNAL(sgdropEvent(QDropEvent*)),this,SLOT(dropEvent(QDropEvent*)));
    // QObject::connect(ui->dockBrowser,SIGNAL(visibilityChanged(bool)),this,SLOT(setfbvis(bool)));
    QObject::connect(myplaylist,SIGNAL(clearingList()),this,SLOT(clearingList()));
    QObject::connect(myplaylist,SIGNAL(showPictureFlow(QString)),this,SLOT(showPictureFlow(QString)));
    QObject::connect(myplaylist,SIGNAL(addingfilesg()),this,SLOT(addingfile()));
    QObject::connect(myplaylist,SIGNAL(removingfilesg()),this,SLOT(removingfile()));

    ui->toolButtonAdd->setMenu(ui->menuAdd);

    menuLoadSavepl=new QMenu(this);
    menuLoadSavepl->addAction(ui->action_Load_pl);
    menuLoadSavepl->addAction(ui->action_Save_as_playlist);
    ui->toolButtonLpl->setMenu(menuLoadSavepl);
    ui->toolButtonRemove->setMenu(ui->menu_Remove);
    ui->toolBarPlaylist->addWidget(ui->toolButtonAdd);
    ui->toolBarPlaylist->addWidget(ui->toolButtonRemove);
    ui->toolBarPlaylist->addWidget(ui->toolButtonLpl);
    ui->toolBarPlaylist->addWidget(ui->toolButton_loop);
    ui->toolBarPlaylist->addWidget(ui->toolButton_shuffle);
    ui->toolBarPlaylist->addWidget(ui->toolButton_playpre);
    ui->toolBarPlaylist->addWidget(ui->toolButton_playnext);

    myplaylist->loop(settings->value("Playlist/Loop","0").toBool());
    ui->toolButton_loop->setChecked( settings->value("Playlist/Loop","0").toBool());

    myplaylist->shuffle(settings->value("Playlist/Shuffle","0").toBool());
    ui->toolButton_shuffle->setChecked( settings->value("Playlist/Shuffle","0").toBool());

    QObject::connect(myplaylist,SIGNAL(playThisfile(QString)),this,SLOT(playThisfile(QString)));
    QObject::connect(ui->dock_Playlist,SIGNAL(visibilityChanged (bool)),this,SLOT(playlistVisibility(bool)));

    //qApp->setEffectEnabled(Qt::UI_AnimateMenu,true);
    //qApp->setEffectEnabled(Qt::UI_AnimateTooltip,true);
    ui->dockBrowser->resize(this->width(),500);
    w= new PictureFlow(this);
    /*labanim=new QLabel(w,0);
     QMovie *movie = new QMovie(":/images/backanimsmall.gif");

     this->labanim->setMovie(movie);
     movie->start();*/

    //w->setSlideSize(QSize(67,50));
    w->setSlideSize(QSize(4*24,3*18));
    //w->setSlideSize(QSize(100,80));
    w->setReflectionEffect(w->PlainReflection);
    w->resize(this->width(), 100);
    //w->setReflectionEffect(picflow->PlainReflection);
    w->addDrives();


    QObject::connect(w,SIGNAL(play()),myplaylist,SLOT(playLastFile()));
    QObject::connect(w,SIGNAL(filename(QString)),myplaylist,SLOT(addFile(QString)));
    QObject::connect(w,SIGNAL(addFiletoPl(QString)),myplaylist,SLOT(addFile(QString)));
    QObject::connect(w,SIGNAL(addFoldertoPl(QString)),this,SLOT(addFolderTopl(QString)));

    w->show();

    ui->dockBrowser->setWidget(w);
    w->resize(this->width(),500);
    ui->menu_View->addAction(ui->dockBrowser->toggleViewAction());
    ui->menu_View->addAction(ui->dock_log->toggleViewAction());
    ui->menu_View->addAction(ui->dock_Playlist->toggleViewAction());

    pi = new QProgressIndicator(this);
    pi->setColor(QColor(qRgb(0,0,255) ));
    piv = new QProgressIndicator(videoWin);


    //testlab =new QLabel(videoWin,0);
    //testlab->setText("ffffffffffffffffff");
    //testlab->show();
    //videoWin->setAspect(1.0);
    //videoWin->showLogo(false);

    piv->setColor(QColor(qRgb(255,255,255) ));
    piv->resize(32,32);
    ui->dock_log->setVisible(false);
    ///////////////////////////////////////////////////////////////////
    //statusbar
    ui->statusBar->addWidget(ui->labelStatus);

    ui->statusBar->addPermanentWidget(pi);

    ui->statusBar->addPermanentWidget(ui->labAD);
    ui->statusBar->addPermanentWidget(ui->lcdCurPos);
    ui->statusBar->addPermanentWidget(ui->lcdDuration);
    ///////////////////////////////////////////////////////////////////
    //metainfodisnplay-toolbar

    ui->labelCpuAudio->setVisible(false);
    ui->labelCpuVideo->setVisible(false);
    ui->labelAVdelay->setVisible(false);
    ui->labelFrameCount->setVisible(false);
    //ui->toolBarStatus->addWidget(youtubeBox);

    ui->toolBarStatus->addWidget(ui->label_display);
    //ui->toolBarStatus->addSeparator();
    ui->toolBarStatus->addWidget(ui->labelFrameCount);
    //ui->toolBarStatus->addSeparator();
    ui->toolBarStatus->addWidget(ui->labelAVdelay);
    // ui->toolBarStatus->addSeparator();
    ui->toolBarStatus->addWidget(ui->labelCpuVideo);
    // ui->toolBarStatus->addSeparator();
    ui->toolBarStatus->addWidget(ui->labelCpuAudio);
    // ui->toolBarStatus->addSeparator();
    ui->toolBarStatus->addWidget(ui->labVD);
    ui->toolBarStatus->addWidget(ui->labelSpeed);


    ///////////////////////////////////////////////////////////////////
    //seekbar-toolbar

    //ui->toolBarSeekBar->addSeparator();
    ui->toolBarSeekBar->addWidget(ui->toolButtonRewind);
    //ui->toolBarSeekBar->addSeparator();
    //ui->toolBarSeekBar->addAction(ui->actionRewind_10_seconds);
    ui->toolBarSeekBar->addWidget(ui->sliderSeek);
    // ui->toolBarSeekBar->addAction(ui->actionForward_10_seconds);
    // ui->toolBarSeekBar->addSeparator();
    toolButtonForwardAction=ui->toolBarSeekBar->addWidget(ui->toolButtonForward);
    //ui->toolBarSeekBar->addSeparator();
    ui->toolBarSeekBar->addAction(ui->actionFullscreen);
    //ui->toolBarSeekBar->addSeparator();
    //////////////////////////////////////////////////////////////////
    //btns-toolbar
    //ui->toolBarSeek->addSeparator();
    ui->toolBarSeek->addAction(ui->action_Play_Pause);

    ui->toolBarSeek->addAction(ui->action_Stop);
    //ui->toolBarSeek->addSeparator();
    ui->toolBarSeek->addAction(ui->actionPlay_Previous_File);

    ui->toolBarSeek->addAction(ui->actionPlay_Next_File);

    ui->toolBarSeek->addWidget(ui->toolButtonVolume);
    ui->toolBarSeek->addWidget(ui->sliderVolume);

    //ui->toolBarSeek->addSeparator();

    ui->toolBarSeek->addAction(ui->action_Equalizer);
    //ui->toolBarSeek->addSeparator();
    ui->toolBarSeek->addWidget(ui->toolButtonplaylist);
    //ui->toolBarSeek->addSeparator();
    ui->toolBarSeek->addWidget(ui->toolButtonFblike);

    // ui->toolBarSeek->addWidget(youtubeBox);
    ui->actionPlay_Previous_File->setVisible(false);
    ui->actionPlay_Next_File->setVisible(false);
    //version 2
    //ui->toolBarSeek->addAction(ui->actionMedia_cutter);
    ui->toolButtonfs->hide();
    // ui->toolBarSeek->addSeparator();
    //ui->toolBarSeek->addAction(ui->actionScreen_shot);
    ui->toolBarSeek->addWidget(ui->labToolbarSpace);
    ui->labToolbarSpace->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Fixed);

    //ui->toolBarSeek->addSeparator();
    //ui->toolBarSeek->addWidget(ui->toolButtonSpeed);
    //ui->toolBarSeek->addSeparator();



    //////////////////////////////////////////////////////////////////
    setMutebtnIcon(ui->sliderVolume->value());
    actiongroupChannels=new QActionGroup(this);
    actiongroupChannels->addAction(ui->actionStereo);
    actiongroupChannels->addAction(ui->actionSurround);
    actiongroupChannels->addAction(ui->actionFull_5_1);
    actiongroupChannels->addAction(ui->actionFull_7_1);
    QObject::connect(actiongroupChannels, SIGNAL(triggered(QAction*)), this,SLOT(changeChannel(QAction*)));

    actiongroupResample=new QActionGroup(this);
    actiongroupResample->addAction(ui->action11025);
    actiongroupResample->addAction(ui->action12000);
    actiongroupResample->addAction(ui->action16000);
    actiongroupResample->addAction(ui->action192000);
    actiongroupResample->addAction(ui->action22100);
    actiongroupResample->addAction(ui->action24000);
    actiongroupResample->addAction(ui->action32000);
    actiongroupResample->addAction(ui->action44100);
    actiongroupResample->addAction(ui->action48000);
    actiongroupResample->addAction(ui->action8000);
    actiongroupResample->addAction(ui->action96000);
    QObject::connect(actiongroupResample, SIGNAL(triggered(QAction*)), this,SLOT(changeSamplingFrequency(QAction*)));

    actiongroupStereoMode=new QActionGroup(this);
    actiongroupStereoMode->addAction(ui->actionStereomode);
    actiongroupStereoMode->addAction(ui->actionLeft_channel);
    actiongroupStereoMode->addAction(ui->actionRight_channel);
    QObject::connect(actiongroupStereoMode, SIGNAL(triggered(QAction*)), this,SLOT(changeStereoMode(QAction*)));

    actiongroupRotate=new QActionGroup(this);
    actiongroupRotate->addAction(ui->action_RotateDisable);
    actiongroupRotate->addAction(ui->actionRotate_0);
    actiongroupRotate->addAction(ui->actionRotate_1);
    actiongroupRotate->addAction(ui->actionRotate_2);
    actiongroupRotate->addAction(ui->actionRotate_3);
    QObject::connect(actiongroupRotate, SIGNAL(triggered(QAction*)), this,SLOT(changeRotation(QAction*)));

    actiongroupAspectRatio=new QActionGroup(this);
    actiongroupAspectRatio->addAction(ui->action_ar_Auto);
    actiongroupAspectRatio->addAction(ui->action1_1);
    actiongroupAspectRatio->addAction(ui->action2_21_1);
    actiongroupAspectRatio->addAction(ui->action3_2);
    actiongroupAspectRatio->addAction(ui->action4_3);
    actiongroupAspectRatio->addAction(ui->action5_4);
    actiongroupAspectRatio->addAction(ui->action14_9);
    actiongroupAspectRatio->addAction(ui->action14_10);
    actiongroupAspectRatio->addAction(ui->action16_9);
    actiongroupAspectRatio->addAction(ui->action16_10);
    actiongroupAspectRatio->addAction(ui->action_ar_Custom);
    actiongroupAspectRatio->addAction(ui->action_ar_Disable);
    QObject::connect(actiongroupAspectRatio, SIGNAL(triggered(QAction*)), this,SLOT(changeAspectRatio(QAction*)));

    actiongroupSubtitleAlignment= new QActionGroup(this);
    actiongroupSubtitleAlignment->addAction(ui->action_sa_Top);
    actiongroupSubtitleAlignment->addAction(ui->action_sa_Center);
    actiongroupSubtitleAlignment->addAction(ui->action_sa_Bottom);
    QObject::connect(actiongroupSubtitleAlignment, SIGNAL(triggered(QAction*)), this,SLOT(changesubAlignment(QAction*)));

    osdGroup = new QActionGroup(this);
    osdGroup->addAction(ui->action_osd0);
    osdGroup->addAction(ui->action_osd1);
    osdGroup->addAction(ui->action_osd2);
    osdGroup->addAction(ui->action_osd3);
    QObject::connect(osdGroup,SIGNAL(triggered(QAction*)),this,SLOT(change_osd(QAction*)));
    ui->action_osd1->setChecked(true);
    ui->action_Palette->setVisible(false);

    framedropGroup = new QActionGroup(this);
    framedropGroup->addAction(ui->action_fd_Disable);
    framedropGroup->addAction(ui->actionSoft);
    framedropGroup->addAction(ui->actionHard);
    QObject::connect(framedropGroup,SIGNAL(triggered(QAction*)),this,SLOT(change_framedrop(QAction*)));
    ui->action_fd_Disable->setCheckable(true);

    QObject::connect(ui->eq0,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq1,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq2,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq3,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq4,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq5,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq6,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq7,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq8,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));
    QObject::connect(ui->eq9,SIGNAL(valueChanged(int)),this,SLOT(setequlizerbandvalue(int)));

    QObject::connect(ui->eq0,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq1,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq2,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq3,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq4,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq5,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq6,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq7,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq8,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));
    QObject::connect(ui->eq9,SIGNAL(sliderReleased()),this,SLOT(setcmbIndex()));


    QObject::connect(videoWin, SIGNAL(doubleClicked()), this,SLOT(toggleFullscreen()));
    QObject::connect(videoWin, SIGNAL(mouseMoveEventsg(QMouseEvent*)), this,SLOT(mouseMoveEvent(QMouseEvent*)));

    QObject::connect(videoWin, SIGNAL(rectRubberBand(QRect*)), this,SLOT(rubberBandval(QRect*)));
    QObject::connect(videoWin, SIGNAL(resizeVideo(int,int)), this,SLOT(resizeVideo(int,int)));

    QObject::connect(qApp, SIGNAL(aboutToQuit()), this,SLOT(cleanMp()));

    ui->dock_Filter->setWidget(ui->tabWidget);
    ui->dock_Filter->hide();
    // this->setCentralWidget(videoWin);

    coreTimer = new QTimer(this);
    QObject::connect(coreTimer, SIGNAL(timeout()), this,SLOT(checkForNextPlayback()));
    coreTimer->start(500);

    resetUi();

    if(settings->value("Playlist/Visible","0").toBool())
        ui->actionShowpl->trigger();
    else
        ui->dock_Playlist->hide();
    //qDebug()<<settings->value("Audio/Volume","50").toInt();
    ui->sliderVolume->setValue(settings->value("Audio/Volume","50").toInt());

    mpseekView=new SeekView(this);
    mpseekView->hide();



    long height=ui->menuBar->height()+ui->toolBarSeek->height()+ui->toolBarStatus->height()+ui->toolBarSeekBar->height();
    qDebug()<<height;

    this->setMinimumHeight(height);


}
void PlayerWindow::resetUi()
{
    ui->labVD->setText("");
    ui->labAD->setText("");
    ui->action_Stop->setVisible(false);
    if( mp)
    {  if(playerTimer)
            this->playerTimer->stop();
        if(frameTimer)
            this->frameTimer->stop();

        //myplaylist->playNextFile();
    }
    //ui->progressBarBusy->setMaximum(1);
    // ui->progressBarBusy->hide();
    pi->hide();
    pi->stopAnimation();
    piv->hide();
    piv->stopAnimation();
    ui->cmdLine->setEnabled(false);
    if(mp)
        ui->btnSaveLog->setEnabled(true);
    else
    { ui->btnSaveLog->setEnabled(false);
        ui->dock_log->hide();
    }
    ui->toolButtonForward->setEnabled(false);
    ui->toolButtonRewind->setEnabled(false);
    ui->action_Stop->setEnabled(false);
    ui->sliderSeek->setValue(0);
    //ui->sliderSeekFullScreen->setValue(0);
    ui->actionSave_cover_art->setEnabled(false);
    ui->sliderSeek->setEnabled(  false);
    if(sliderSeekFullSc){
        sliderSeekFullSc->setEnabled(false);
        sliderSeekFullSc->setValue(0);
    }
    // ui->sliderSeekFullScreen->setEnabled(false);
    ui->labelAVdelay->setText("--");
    ui->labelCpuAudio->setText("--");
    ui->labelCpuVideo->setText("--");
    ui->labelFrameCount->setText("--");
    ui->labelSpeed->setText("--");
    ui->lcdDuration->display("--:--:--");
    ui->lcdCurPos->display("--:--:--");

    if(sliderSeekFullSc)
        sliderSeekFullSc->setEnabled(false);
    ui->labelSpeed->hide();
    ui->labelCpuAudio->hide();
    ui->labelCpuVideo->hide();
    ui->labelFrameCount->hide();
    ui->action_RotateDisable->setChecked(true);
    ui->labelAVdelay->hide();
    ui->action_Play_Pause->setIcon(QIcon(":/images/play.png"));
    ui->action_Play_Pause->setToolTip(tr("Play"));
    if  (ui->dock_log->isHidden())
        ui->dock_log->hide();
    ui->actionLoad_external_file->setDisabled(true);
    ui->actionMix_and_save->setDisabled(true);
    ui->actionIncrease_Video_quality->setChecked(false);
    //ui->menuPlay->setDisabled(true);
    //ui->menu_Audio->setDisabled(true);
    //ui->menu_Video->setDisabled(true);
    // ui->menu_Subtitles->setDisabled(true);
    ui->action_Crop->setChecked(false);
    ui->action_Crop->setEnabled(true);
    ui->action_Remove_logo->setEnabled(true);
    ui->action_Remove_logo->setChecked(false);
    //////////////////////////////////////////
    ui->action_Karaoke->setChecked(false);
    ui->actionVolume_Normalization->setChecked(false);
    for (int i=0;i<ui->menu_Filters_2->actions().count();i++)
    {
        ui->menu_Filters_2->actions().at(i)->setChecked(false);
    }
    for (int i=0;i<ui->menu_Resample->actions().count();i++)
    {
        ui->menu_Resample->actions().at(i)->setChecked(false);
    }
    ui->action_fd_Disable->setChecked(true);

    //if (iseof){
    //myplaylist->playNextFile();

    //}
    ///////////////////////////////////////////////////////////

}
void PlayerWindow::startingPlayback()
{



    QMutex mutex;
    mutex.lock();
    videoWin->showLogo(false);

    basicmetainfo.clear();
    qDebug()<<"Audio :"<<mp->hasaudio()<<"Video :"<<mp->hasvideo();

    bstop=false;
    ui->menuPlay->setDisabled(false);
    //youtubeBox->lineEdit->setFocus();

    if(mp->isRestarting()==false)
    {
        this->setWindowTitle( mp->getMediaTitle()+" - ExMplayer");
        //hide progress indicator
        pi->stopAnimation();
        pi->hide();
        piv->stopAnimation();
        piv->hide();

        //clear video window
        videoWin->clearText();
        videoWin->setPixmap(QPixmap());


        ui->action_Stop->setEnabled(true);
        //setup seek slider
        if (mp->isseekable())
        {  ui->sliderSeek->setEnabled(true);
            if(sliderSeekFullSc)
                sliderSeekFullSc->setEnabled(true);

            //setup toolbar buttons
            ui->toolButtonForward->setEnabled(true);
            ui->toolButtonRewind->setEnabled(true);
        }

        //Enable Console
        ui->cmdLine->setEnabled(true);
        ui->btnSaveLog->setEnabled(true);

        //setup volume
        //setup Timers

        playerTimer = new QTimer(this);
        QObject::connect(playerTimer, SIGNAL(timeout()), this,SLOT(updateSeekbar()));

        frameTimer = new QTimer(this);
        QObject::connect(frameTimer, SIGNAL(timeout()), this,SLOT(updateFrameDisplay()));

        //starting timers
        coreTimer->start();
        frameTimer->start(1);

        if  (!ui->action_Stop->isVisible()){
            ui->action_Stop->setVisible(true);
        }
        //show status
        ui->lcdCurPos->display("00:00:00");
        ui->labelStatus->setText(tr("Playing"));
        //videoWin->mplayerlayer->show();
        //video stream
        if( mp->hasvideo()){
            //set up width and height

            qDebug()<<"Resizing video window...."<<mp->videowidth()<<" "<<mp->videoheight();

            videoWin->mplayerlayer->show();

            videoWin->setAspect((float)mp->videowidth()/mp->videoheight());
            int eh;
            ui->dock_Filter->setFloating(true);
            //videoWin->setShowVideo(true);
            //videoWin->setShowText(false);
            //dock browser
            eh=getEh();

            //if (ui->dockBrowser->)

            if(isfullscreen){
                mp->togglefullscreen();
            }
            else{
                this->resize(mp->videowidth(),eh);
            }

            ui->actionLoad_external_file->setDisabled(false);
            ui->actionMix_and_save->setDisabled(false);

        }

        //Only Audio stream
        if(mp->hasaudio()&&!mp->hasvideo())
        {
            if(isfullscreen){
                mp->togglefullscreen();
            }
        }
        QString astr;



        astr=QString(mp->getAudioRate()+" Khz ");

        if (mp->getAudioNch().toInt()==1)
            astr+="M \n";
        else if (mp->getAudioNch().toInt()==2)
            astr+="S \n";
        else
            astr=mp->getAudioNch();

        if (mp->getAudioBitrate().toInt()==0)
        {astr+=QString("VBR");
        }
        else
        {

            astr+=QString(mp->getAudioBitrate()+" Kbps");
        }
        ui->labAD->setText(astr);

        //Audio stream
        if( mp->hasaudio())
        {

            actiongroupAudioTrack=new QActionGroup(this);
            actiongroupAudioTrack->addAction(ui->actionAudioDisable);

            ui->menu_Audio->setDisabled(false);

            for(int i=0;i<mp->listAudioTrack.count();i++)
            {
                actiongroupAudioTrack->addAction(ui->menuAudio_Track->addAction("Track "+QString::number(i+1)));
                actiongroupAudioTrack->actions().at(i+1)->setCheckable(true);

            }
            if (actiongroupAudioTrack->actions().count()>1){

                actiongroupAudioTrack->actions().at(1)->setChecked(true);

            }
            QObject::connect(actiongroupAudioTrack,SIGNAL(triggered(QAction*)),this,SLOT(changeAudioTrack(QAction*)));
        }
        bool ft=false;
        //Video stream
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        if( mp->hasvideo())
        {ui->labVD->setText(QString(mp->getVideoWidth() +" x " +mp->getVideoHeight()+" "));
            if (!ui->dock_Playlist->isFloating())
            {

                //ui->dock_Playlist->move(this->x()+this->width(),this->y());
                ui->dock_Playlist->resize(300,400);
                ui->dock_Playlist->setFloating(true);

            }


            ui->menu_Video->setDisabled(false);
            ui->menu_Subtitles->setDisabled(false);
            actiongroupSubtitleTrack=new QActionGroup(this);
            actiongroupSubtitleTrack->addAction(ui->actionStNone);
            actiongroupVideoTrack=new QActionGroup(this);
            QObject::connect(actiongroupSubtitleTrack,SIGNAL(triggered(QAction*)),this,SLOT(changeSubTitles(QAction*)));

            if( mp->listSubtitleTrack.count()>0)
            {for (int i=0;i<mp->listSubtitleTrack.count();i++)
                {actiongroupSubtitleTrack->addAction( ui->menuSelect->addAction("Track "+QString::number(mp->listSubtitleTrack.count())));
                    actiongroupSubtitleTrack->actions().last()->setCheckable(true);
                }
            }
            if(mp->listSubtitleTrack.count()==0)
            {
                actiongroupSubtitleTrack->actions().last()->setEnabled(false);

            }
            actiongroupVideoTrack->addAction(ui->actionVideoDisable);

            for(int i=0;i<mp->listVideoTrack.count();i++)
            {actiongroupVideoTrack->addAction( ui->menuVideo_Track->addAction("Track "+QString::number(i+1)));
                actiongroupVideoTrack->actions().at(i+1)->setCheckable(true);
            }
            if (actiongroupVideoTrack->actions().count()>1){
                actiongroupVideoTrack->actions().at(1)->setChecked(true);
            }
            QObject::connect(actiongroupVideoTrack,SIGNAL(triggered(QAction*)),this,SLOT(changeVideoTrack(QAction*)));
        }

        ui->lcdDuration->display(mp->tduration().toString());
        ui->action_Play_Pause->setIcon(QIcon(":/images/pause.png"));
        ui->action_Play_Pause->setToolTip(tr("Pause"));

        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //Audio Only...
        if( mp->hasvideo()&&mp->hasaudio())
        {
            ui->actionAudioDisable->setEnabled(true);

        }
        if( !mp->hasvideo()&&mp->hasaudio()){
            if (this->width()>450 ||this->height()>145)
            {
                this->resize(450,145);
                qDebug()<<"Offset height -"<<(ui->menuBar->height()+ui->menuBar->y())-ui->toolBarSeekBar->y();
                this->resize(450,this->height()+(ui->menuBar->height()+ui->menuBar->y())-ui->toolBarSeekBar->y());
                qDebug()<<"Adjusted offset -"<<(ui->menuBar->height()+ui->menuBar->y())-ui->toolBarSeekBar->y();

            }

            //#ifdef Q_OS_WIN
            //this->resize(450,145);
            ui->actionAudioDisable->setEnabled(false);
            //this->resize(450,145);
            // videoWin->setPixmap(QPixmap(":/af").scaled(64,64,Qt::IgnoreAspectRatio, Qt::FastTransformation));
            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            QLibrary myLib(qApp->applicationDirPath()+"/TagReader.dll");

            typedef unsigned char* (*fn) (const char* fn,int* size);
            typedef long (*fn1) ();

            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            fn getcover = (fn) myLib.resolve("GetCoverEx");
            fn1 terminate = (fn1) myLib.resolve("TagReader_TerminateEx");

            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if (getcover)
            {
                const char* ch=currentFile.toAscii().constData();

                int size=0;
                const uchar* data=0;
                data=getcover(ch,&size);
                //QMessageBox::critical(this,qApp->applicationName(),QString::number(size),QMessageBox::Ok,QMessageBox::Cancel);
                //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                if(size>0)
                {
                    QImage img=QImage::fromData(data,size,0);
                    //QMessageBox::critical(this,qApp->applicationName(),QString::number(img.width()),QMessageBox::Ok,QMessageBox::Cancel);

                    cover = new QPixmap(QPixmap::fromImage(img,Qt::AutoColor));

                    videoWin->setPixmap(QPixmap::fromImage(img,Qt::AutoColor).scaled(170,128,Qt::IgnoreAspectRatio, Qt::FastTransformation));
                    hascover=true;
                    cover->save(qApp->applicationDirPath()+"/"+"mcover.jpeg",0,-1);
                    ui->actionSave_cover_art->setEnabled(true);
                }
            }
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if (terminate)
                terminate();

            //#endif

            //if (!hascover)
            //   videoWin->setPixmap(QPixmap(":/images/audiofile.png").scaled(64,64,Qt::IgnoreAspectRatio, Qt::FastTransformation));

            //Drawing metainfo to videowindow
            QString val;

            for (int i=0;i<mp->metainfo.count();i++)
            {
                val=mp->metainfo.at(i);
                QStringList list;
                list = val.split(":",QString::SkipEmptyParts);

                if(val.contains("Artist",Qt::CaseInsensitive))
                {if (list.count()>1)
                        artisttext="Artist :"+list.at(1);
                    //videoWin->drawArtistName(val);
                    basicmetainfo<<artisttext;
                }

                if(val.contains("Title",Qt::CaseInsensitive))
                {

                    if (list.count()>1)
                        val="Title :"+list.at(1);


                    if (val.length()!=8)
                    {
                        ft=true;
                    }

                    videoWin->drawTitle(val);
                    basicmetainfo<<val;
                    Title=val;
                    Title=Title.mid(Title.indexOf(":")+1);

                }

                if(val.contains(QRegExp("\\b(Album|album)\\b")))
                {if (list.count()>1)
                        albumtext="Album :"+list.at(1);
                    // videoWin->drawAlbumString(val);
                    basicmetainfo<<albumtext;

                }

                if(val.contains("TYER",Qt::CaseInsensitive)||val.contains("YEAR",Qt::CaseInsensitive))
                {if (list.count()>1)
                        yeartext="Year :"+list.at(1);
                    // videoWin->drawYearString(val);
                    basicmetainfo<< yeartext;

                }
            }


            if (!ft)
            {QFileInfo info(mp->filepath());
                videoWin->drawTitle("Title : "+info.baseName());
            }
            if  (albumtext=="Album :" )
            {
            }

            videoWin->drawArtistName(artisttext);
            videoWin->drawAlbumString(albumtext);
            videoWin->drawYearString(yeartext);
            videoWin->forcedraw();
            //show meta_info

        }

        if (mp->metainfo.count())
        {
            disptimer = new QTimer(this);
            connect(disptimer, SIGNAL(timeout()), this, SLOT(updatemetadisp()));
            disptimer->start(5000);
            metadispcount=-1;
        }
        //Only video stream no audio
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        if( mp->hasvideo()&&!mp->hasaudio()){
            ui->actionVideoDisable->setEnabled(false);

        }
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        ui->action_sa_Bottom->setChecked(true);
        ui->actionStUnload->setEnabled(false);
        ui->actionToggle_subtitle_visibility->setChecked(true);
        if (mp->hasvideo())
        {
            QFileInfo fi(currentFile);
            Title=fi.baseName();
            QString val;

            for (int i=0;i<mp->metainfo.count();i++)
            {
                val=mp->metainfo.at(i);
                QStringList list;
                list = val.split(":",QString::SkipEmptyParts);


                if(val.contains("Title",Qt::CaseInsensitive))
                {
                    if (list.count()>1)
                        val="Title :"+list.at(1);

                    Title=val;
                    Title=Title.mid(Title.indexOf(":")+1);


                }
            }


        }
        if ( Title=="")
        {
            QFileInfo fi(currentFile);
            Title=fi.baseName();
        }
        ui->label_display->drawCustomText( Title,9);

    }
    else
    {
        if (brotate)
        {int eh;
            eh=videoHeight+ui->toolBarSeek->height()+ ui->statusBar->height()+ui->menuBar->height()+ui->toolBarSeekBar->height()+ui->toolBarStatus->height();
            if( !mp->isfullscreen())
                this->resize(videoWidth,eh);
            brotate=false;
        }
    }

    //qDebug()<<"-------Audio :"<<mp->hasaudio()<<"Video :"<<mp->hasvideo();
    playerTimer->start(1000);
    mutex.unlock();
    //youtubeBox->lineEdit->setText("");
    // youtubeBox->lineEdit->setText(Title);
}
void PlayerWindow::updateSeekbar()
{
    /* if (mp->hasaudio()&&!mp->hasvideo())
    {// qDebug()<<"chk;";
        if(this->videoWin->mplayerlayer->isVisible())
         this->videoWin->mplayerlayer->hide();
    }*/
    if (windowTimer->isActive())
    {
        windowTimer->stop();
    }
    if(!ui->sliderSeek->isEnabled())
    {if (mp->isseekable()){
            ui->sliderSeek->setEnabled(true);
            if(sliderSeekFullSc)
                sliderSeekFullSc->setEnabled(true);
        }


    }
    if (!ui->menu_Audio->isEnabled())
    {if (mp->hasaudio())
        {
            ui->menu_Audio->setEnabled(true);
        }

    }
    if (!ui->menu_Video->isEnabled())
    {if (mp->hasvideo())
        {
            ui->menu_Video->setEnabled(true);
        }

    }
    if(mp)
    {
        if( mp->isstarted()){
            ui->sliderSeek->setValue((mp->curpos()/mp->duration())*100);
            if(sliderSeekFullSc)
                sliderSeekFullSc->setValue((mp->curpos()/mp->duration())*100);
            ui->lcdCurPos->display(mp->tcurpos().toString());
            if (isfullscreen){
                lcdCurPosFullSc->display(mp->tcurpos().toString());
                lcdDurationFullSc->display(mp->tduration().toString());
            }


        }

    }

    if (mp->state()==mp->PLAYING)
    {/*if(ui->labelStatus->text()=="Playing")
      ui->labelStatus->setText("Playing.");
     else if(ui->labelStatus->text()=="Playing.")
       ui->labelStatus->setText("Playing..");
     else if(ui->labelStatus->text()=="Playing..")
       ui->labelStatus->setText("Playing...");
     else if(ui->labelStatus->text()=="Playing...")
       ui->labelStatus->setText("Playing");*/
        ui->labelStatus->setText("Playing...");
    }
    if (mp->state()==mp->PAUSED)
        ui->labelStatus->setText("Paused.");



}
void PlayerWindow::updateFrameDisplay()
{
    ui->labelSpeed->setText(mp->currentspeed());
    ui->labelCpuAudio->setText(mp->audio_cpu_usage());

    if(!mp->hasvideo())
    {ui->labelAVdelay->setText("--");
        ui->labelCpuVideo->setText("--");
    }
    else
    {ui->labelAVdelay->setText(mp->avdelay());
        ui->labelCpuVideo->setText(mp->video_cpu_usage());
    }
    if (mp->framecount().toInt()==0)
        ui->labelFrameCount->setText("--") ;
    else
        ui->labelFrameCount->setText(mp->framecount());
}

void PlayerWindow::on_sliderSeek_actionTriggered(int action)
{
    this->playerTimer->stop();
    mp->goturl(ui->sliderSeek->value());
    this->playerTimer->start();

}
void PlayerWindow::on_toolButtonForward_clicked()
{
    ui->actionForward_10_seconds->trigger();
}
void PlayerWindow::on_toolButtonRewind_clicked()
{
    ui->actionRewind_10_seconds->trigger();
}
void PlayerWindow::on_sliderVolume_valueChanged(int value)
{
    if(mp)
        mp->setVolume(value);
    if (sliderVolumeFullSc)
        sliderVolumeFullSc->setValue(value);

    if(!starting)
    {   settings->beginGroup("Audio");
        settings->setValue("Mute",QString::number(0));
        settings->endGroup();
    }

    if (sliderVolumeFullSc)
        ui->sliderVolume->setValue(value);

    setMutebtnIcon(value);
    settings->beginGroup("Audio");
    settings->setValue("Volume",value);
    settings->endGroup();

}
void PlayerWindow::setMutebtnIcon(int value)
{ if (starting)
    { if (settings->value("Audio/mute","0").toInt()==1)
        {ui->toolButtonVolume->setIcon(QIcon(":/images/mute.png"));
            qDebug()<<"mute"<<settings->value("Audio/mute","0").toInt();
            toggleMute();
        }
        else
            goto  jmp;

        return;
    }

jmp:
    if(value<2)
        ui->toolButtonVolume->setIcon(QIcon(":/images/mute.png"));
    else if(value>2 &&value<=25)
        ui->toolButtonVolume->setIcon(QIcon(":/images/vol25.png"));
    else if(value>25 &&value<=50)
        ui->toolButtonVolume->setIcon(QIcon(":/images/vol50.png"));
    else if(value>50 &&value<=75)
        ui->toolButtonVolume->setIcon(QIcon(":/images/vol75.png"));
    else if (value>75)
        ui->toolButtonVolume->setIcon(QIcon(":/images/vol100.png"));
}
void PlayerWindow::on_toolButtonVolume_clicked()
{
    toggleMute();
}

void PlayerWindow::on_action_Play_Pause_triggered()
{
    togglePause();
}
void PlayerWindow::togglePause()
{

    if(mp)
    {


        if( mp->state()==mp->PLAYING|| mp->state()==mp->PAUSED)
        {    mp->pause();

            return;
        }

        if (myplaylist->tab->rowCount()>0)
        {
            if ( currentFile.isEmpty())
                myplaylist->playFirstFile();
            else
                this->playThisfile(currentFile);


        }
        else if(bstop)
        {



            if (myplaylist->tab->rowCount()>0)
            { bstop=false;
                if ( currentFile.isEmpty())
                    myplaylist->playFirstFile();
                else
                    this->playThisfile(currentFile);
            }

            else
            {   ui->action_File->trigger();
                qDebug()<<"open";
                return;
            }
        }
    }
    else
    {
        ui->action_File->trigger();
        qDebug()<<"open2";
    }
}

void PlayerWindow::on_actionMute_triggered()
{
    toggleMute();
}
void PlayerWindow::toggleMute()
{if( mp)
    {
        mp->toggleMute();
        if(mp->ismuted())
        {ui->toolButtonVolume->setIcon(QIcon(":/images/mute.png"));

            settings->beginGroup("Audio");
            settings->setValue("Mute",QString::number(1));
            settings->endGroup();


        }
        else
        {   setMutebtnIcon(ui->sliderVolume->value());

            settings->beginGroup("Audio");
            settings->setValue("Mute",QString::number(0));
            settings->endGroup();
            mp->setVolume(ui->sliderVolume->value());


        }
    }
}

void PlayerWindow::on_action_Exit_triggered()
{
    qApp->quit();
}

void PlayerWindow::on_action_Stop_triggered()
{ if (mp)
    { bstop=true;
        mp->stop();
        if (playerTimer)
        {this->playerTimer->stop();
            resetUi();
            ui->action_Stop->setVisible(false);
        }

    }
}

void PlayerWindow::on_action_File_triggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QStringList  fileName;
    QString filter =getFilter();
    //tr("Any File (*.*)")

    if (mp>0)
    {
        fileName = QFileDialog::getOpenFileNames(this,
                                                 tr("Open media file(s)"),
                                                 settings->value("Playlist/OpenfileDlg","").toString(),
                                                 filter ,
                                                 &selectedFilter,
                                                 options);
    }
    else
    { fileName = QFileDialog::getOpenFileNames(this,
                                               tr("Open media file(s)"),
                                               mycomputer->storageLocation( mycomputer->MoviesLocation),
                                               tr("Any File (*.*)"),
                                               &selectedFilter,
                                               options);

    }


    if(fileName.count()>0)
    {  QFileInfo fi;
        fi.setFile(fileName.at(0));
        settings->beginGroup("Playlist");
        settings->setValue("OpenfileDlg",fi.absolutePath());
        settings->endGroup();
    }
    if (fileName.count()>0)

    {
        myplaylist->clearList();
        for (int i=0;i<fileName.count();i++)
        { myplaylist->addFile(fileName.at(i));
        }

        myplaylist->playFirstFile();
    }

}

void PlayerWindow::on_actionForward_10_seconds_triggered()
{if(mp)
        mp->seeknseconds(10);
    if (picflow>  0 )
        picflow->showNext();
}

void PlayerWindow::on_actionRewind_10_seconds_triggered()
{if(mp)
        mp->seeknseconds(-10);
    if (picflow>  0 )
        picflow->showPrevious();
}

void PlayerWindow::on_actionForward_1_minute_triggered()
{if(mp)
        mp->seeknseconds(60);
}

void PlayerWindow::on_actionRewind_1_minute_triggered()
{if(mp)
        mp->seeknseconds(-60);
}

void PlayerWindow::on_actionForward_10_minutes_triggered()
{if(mp)
        mp->seeknseconds(600);
}

void PlayerWindow::on_actionRewind_10_minutes_triggered()
{if(mp)
        mp->seeknseconds(-600);
}

void PlayerWindow::on_actionNormal_Speed_triggered()
{if(mp)
        mp->setSpeed(1.0,2);
}

void PlayerWindow::on_actionDouble_speed_triggered()
{if(mp)
        mp->setSpeed(2,1);
}

void PlayerWindow::on_actionHalve_speed_triggered()
{if(mp)
        mp->setSpeed(0.5,1);
}

void PlayerWindow::on_actionIncrease_10_triggered()
{if(mp)
        mp->setSpeed(0.1,0);
}

void PlayerWindow::on_actionDecrease_10_triggered()
{if(mp)
        mp->setSpeed(-0.1,0);
}

void PlayerWindow::on_actionIncrease_Delay_triggered()
{if(mp)
        mp->setaudiodelay(0.1,this);
}

void PlayerWindow::on_actionDecrease_Delay_triggered()
{if(mp)
        mp->setaudiodelay(-0.1,this);
}

void PlayerWindow::on_action_Increase_volume_triggered()
{
    ui->sliderVolume->setValue( ui->sliderVolume->value()+1);
}

void PlayerWindow::on_action_Decrease_volume_triggered()
{
    ui->sliderVolume->setValue( ui->sliderVolume->value()-1);
}
void PlayerWindow::changeAudioTrack(QAction*act)
{
    if (this->actiongroupAudioTrack->actions().indexOf(act)==0)
    {if(mp)
            mp->switchAudio(-1);
    }
    else
    {
        QString val=mp->listAudioTrack.at(this->actiongroupAudioTrack->actions().indexOf(act)-1);
        if(mp)
            mp->switchAudio(val.toInt());
    }

}

void PlayerWindow::on_actionLoad_external_file_triggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open media file"),
                                                    mp->shortPathName(mp->filepath()),
                                                    this->getaudioFilter(),
                                                    &selectedFilter,
                                                    options);
    if (!fileName.isEmpty()){
        if(mp)
            mp->loadExternalFile(fileName);

    }
}
void PlayerWindow::changeChannel(QAction *act)
{
    if(mp)
        mp->setAudioChannels(actiongroupChannels->actions().indexOf(act));
}
void PlayerWindow::settingChanged(QString group,QString key,QString value)
{
    settings->beginGroup(group);
    settings->setValue(key,value);
    settings->endGroup();
}

void PlayerWindow::on_action_Karaoke_triggered()
{if(mp)
        mp->addAudioFilterKaraoke(ui->action_Karaoke->isChecked());
}
void PlayerWindow::changeSamplingFrequency(QAction* act)
{if(mp)
        mp->addAudioFilterResample(act->text().toInt());
}
void PlayerWindow::on_actionSurroundAf_triggered()
{if(mp)
        mp->addAudioFilterSurround(settings->value("Audio/Surround","20").toInt(),this);
}
void PlayerWindow::on_action_ExtraStereo_triggered()
{if(mp)
        mp->addAudioFilterExStereo(settings->value("Audio/ExtraStereo","25").toInt(),this);
}

void PlayerWindow::on_actionScale_Tempo_triggered()
{if(mp)
        mp->addAudioFilterScaleTempo(settings->value("Audio/ScaleTempo","12").toInt(),this);

}

void PlayerWindow::on_action_Delay_triggered()
{if(mp)
        mp->addAudioFilterDelay(settings->value("Audio/DelayLeft","10").toInt(),settings->value("Audio/DelayRight","10").toInt(),this);

}
void PlayerWindow::changeStereoMode(QAction* act)
{if(mp)
        mp->setStereoMode(this->actiongroupStereoMode->actions().indexOf(act));
}
void PlayerWindow::rubberBandval(QRect *val)
{if(mp)
    {

        if (ui->action_Remove_logo->isChecked())
            mp->removeLogo(val,true);
        if( ui->action_Crop->isChecked())
            mp->crop(val,true);


        videoWin->showRubberBand(false);
    }
}

void PlayerWindow::on_action_Remove_logo_triggered()
{ if(mp)
    {if (mp->isfullscreen())
        {
            this->toggleFullscreen();
        }
        if ( ui->action_Remove_logo->isChecked())
        {
            ui->action_Crop->setEnabled(false);
            //ui->dockBrowser->hide();
            int eh;
            eh=getEh();
            this->resize(mp->videowidth(),eh);
            videoWin->showRubberBand(true);
            QMessageBox msgBox(this);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText(tr("Drag and select the portion which contains the logo"));
            msgBox.exec();
        }
        else
        { mp->removeLogo(NULL,false);
            ui->action_Crop->setEnabled(true);
        }
    }
}

void PlayerWindow::on_action_Tile_triggered()
{if(mp)
        mp->tile(ui->action_Tile->isChecked());
}

void PlayerWindow::on_action_flip_triggered()
{if(mp)
        mp->flip(ui->action_flip->isChecked());
}

void PlayerWindow::on_action_Mirror_triggered()
{if(mp)
        mp->mirror(ui->action_Mirror->isChecked());
}

void PlayerWindow::on_action50_50_triggered()
{if(mp)
        mp->halfvideo(ui->action50_50->isChecked());
}
void PlayerWindow::changeRotation(QAction *act)
{if(mp)
    { brotate=true;
        if (this->actiongroupRotate->actions().indexOf(act)!=0)
        {videoHeight=mp->videowidth();
            videoWidth=mp->videowidth();
            mp->rotate(this->actiongroupRotate->actions().indexOf(act)-1);

        }
        else
        {
            brotate=false;

            videoHeight=mp->videoheight();
            videoWidth=mp->videowidth();

            mp->rotate(-1);
            if(! mp->isfullscreen())
            {int eh;
                eh=getEh();
                this->resize(mp->videowidth(),eh);
            }
        }
    }
}

void PlayerWindow::on_actionSwap_U_and_V_triggered()
{if(mp)
        mp->swapuv(ui->actionSwap_U_and_V->isChecked());
}

void PlayerWindow::on_actionOld_Black_and_white_triggered()
{if(mp)
        mp->onebpp(ui->actionOld_Black_and_white->isChecked());
}

void PlayerWindow::on_actionPainting_triggered()
{if(mp)
        mp->painting(ui->actionPainting->isChecked());
}

void PlayerWindow::on_actionAdd_noise_triggered()
{if(mp)
        mp->noise(ui->actionAdd_noise->isChecked());
}

void PlayerWindow::on_action_Blur_triggered()
{if(mp)
        mp->blur(ui->action_Blur->isChecked());
}

void PlayerWindow::on_actionMatrixview_triggered()
{if(mp)
        mp->matrixview(ui->actionMatrixview->isChecked());
}

void PlayerWindow::on_actionVisualize_motion_vectors_triggered()
{if(mp)
        mp->visualizeMV(ui->actionVisualize_motion_vectors->isChecked());
}

void PlayerWindow::on_action_Palette_triggered()
{if(mp)
        mp->palette(ui->action_Palette->isChecked());
}

void PlayerWindow::on_actionStep1_fm_triggered()
{
    bedlenable=true;
    //ui->actionStep2_fm->setEnabled(true);
    //ui->actionStep1_fm->setEnabled(false);
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(tr("Just hit <b>key X/key x</b> to mark the beginning and end of a skip block."));
    msgBox.exec();

}
void PlayerWindow::keyPressEvent(QKeyEvent *event)
{
    //qDebug()<<event->text();

    emit this->keyPress(event);
    switch(event->key())
    {
    case Qt::Key_X:
        if(bedlenable)
        {  mp->markEDL(this);
        }
        break;
    }
    event->accept();
}

void PlayerWindow::on_actionStep2_fm_triggered()
{
    mp->startFamilyFriendlymode();
}
void PlayerWindow::changeAspectRatio(QAction*act)
{if(mp)
    {
        switch(actiongroupAspectRatio->actions().indexOf(act))
        {
        case 0:if(mp->videowidth())
                videoWin->setAspect((float)mp->videowidth()/mp->videoheight());
            break;
        case 1:videoWin->setAspect(1.0);
            break;
        case 2:videoWin->setAspect(2.35/1);
            break;
        case 3:videoWin->setAspect(3.0/2);
            break;
        case 4:videoWin->setAspect(4.0/3);
            break;
        case 5:videoWin->setAspect(5.0/4);
            break;
        case 6:videoWin->setAspect(14.0/9);
            break;
        case 7:videoWin->setAspect(14.0/10);
            break;
        case 8:videoWin->setAspect(16.0/9);
            break;
        case 9:videoWin->setAspect(16.0/10);
            break;
        case 10:
            bool ok;
            double d ;
            d= QInputDialog::getDouble(this, tr("Set Aspect ratio"), tr("Ratio:"), 1.0, 0.1, 10.0, 2, &ok);
            if(ok)
                videoWin->setAspect((float)d);
            break;
        case 11:videoWin->setAspect(0);
            break;
        }
    }
}
void  PlayerWindow::lengthChanged()
{if(mp)
        ui->lcdDuration->display(mp->tduration().toString());
}

void PlayerWindow::on_action_Crop_triggered()
{if(mp)
    {  if( ui->action_Crop->isChecked())
        {  if (mp->isfullscreen())
            {
                this->toggleFullscreen();
            }

            ui->action_Remove_logo->setEnabled(false);
            int eh;
            eh=getEh();
            this->resize(mp->videowidth(),eh);

            videoWin->showRubberBand(true);

            QMessageBox msgBox(this);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText(tr("Drag and select the portion,which you want to crop"));
            msgBox.exec();
        }
        else
        {   ui->action_Remove_logo->setEnabled(true);

            mp->crop(NULL,false);
            ui->action_Crop->setChecked(false);
        }
    }
}
void PlayerWindow::changeVideoTrack(QAction* act)
{if(mp)
    {
        if (this->actiongroupVideoTrack->actions().indexOf(act)==0)
        {
            mp->switchVideo(-1);
        }
        else
        {
            QString val=mp->listVideoTrack.at(this->actiongroupVideoTrack->actions().indexOf(act)-1);
            mp->switchVideo(val.toInt());
        }
    }
}



void PlayerWindow::on_actionStay_on_top_triggered()
{if (!mp->isfullscreen())
    {
        if(ui->actionStay_on_top->isChecked())
            this->setWindowFlags(Qt::WindowStaysOnTopHint);
        else
            this->setWindowFlags(!Qt::WindowStaysOnTopHint);
        this->showNormal();
    }

}

void PlayerWindow::on_actionFrame_step_triggered()
{if(mp)
        mp->framestep();
}
void PlayerWindow::change_osd(QAction *action)
{
    if(mp)
    {osdlevel=osdGroup->actions().indexOf(action);
        mp->setOSDlevel(osdGroup->actions().indexOf(action));
    }
}
void PlayerWindow::change_framedrop(QAction *action)
{if(mp)
    { framedroplevel=framedropGroup->actions().indexOf(action);
        mp->setframedroplevel(framedropGroup->actions().indexOf(action));
    }
}

void PlayerWindow::on_actionToggle_OSD_triggered()
{ if (mp)
    { if(++osdlevel<=3)
        {
            switch(osdlevel)
            {case 0:
                ui->action_osd0->setChecked(true);
                break;
            case 1:
                ui->action_osd1->setChecked(true);
                break;
            case 2:
                ui->action_osd2->setChecked(true);
                break;
            case 3:
                ui->action_osd3->setChecked(true);
                break;
            }
        }
        else
        {osdlevel=0 ;
            ui->action_osd0->setChecked(true);
        }


        mp->setOSDlevel(osdlevel);
    }

}
void PlayerWindow::on_actionToggle_Frame_drop_triggered()
{if (mp)
    {if(++framedroplevel<=2)
        {  switch(framedroplevel)
            {case 0:
                ui->action_fd_Disable->setChecked(true);
                break;
            case 1:
                ui->actionSoft->setChecked(true);
                break;
            case 2:
                ui->actionHard->setChecked(true);
                break;
            }
        }
        else
        {
            framedroplevel=0 ;
            ui->action_fd_Disable->setChecked(true);
        }
        mp->setframedroplevel(framedroplevel);
    }
}

void PlayerWindow::on_actionScreen_shot_triggered()
{if (mp)
        mp->takescreenshot(0);
}

void PlayerWindow::on_actionStart_stop_Screenshot_triggered()
{if (mp)
        mp->takescreenshot(1);
}

void PlayerWindow::on_action_Open_Screenshot_folder_triggered()
{
    QString arg= myconfig->screenshotfolder;
#ifdef Q_OS_WIN
    path=path.replace("/","\\");
    QProcess::execute("explorer.exe "+opt+path);
#elif defined Q_OS_LINUX
    //QString lpath = QDir::toNativeSeparators(path);
    // lpath.left(lpath.length()- lpath.lastIndexOf(QDir::separator () );
    //qDebug()<<lpath.left(lpath.length()-lpath.lastIndexOf("/")+1);
    //QDir d = QFileInfo(lpath).absoluteDir();
    QDesktopServices::openUrl(QUrl(arg));
#endif
}

void PlayerWindow::on_actionToggle_subtitle_visibility_triggered()
{if (mp)
        mp->toggle_subtitle_visibility();
}

void PlayerWindow::on_btnVEReset_clicked()
{
    QPropertyAnimation *animation[5];
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    animation[0]= new QPropertyAnimation(ui->contrast, "value");
    animation[1]= new QPropertyAnimation(ui->Hue, "value");
    animation[2]= new QPropertyAnimation(ui->Saturation, "value");
    animation[3]= new QPropertyAnimation(ui->gamma, "value");
    animation[4]= new QPropertyAnimation(ui->brightness, "value");
    for( int i=0;i<5;i++)
    {
        animation[i]->setDuration(100);
        animation[i]->setEndValue(0);
        group->addAnimation(animation[i]);
    }
    group->start();

}
void PlayerWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu rmenu(this);
    rmenu.addMenu(ui->menu_Open);
    rmenu.addMenu(ui->menuPlay);
    rmenu.addMenu(ui->menu_Audio);
    rmenu.addMenu(ui->menu_Video);
    rmenu.addMenu(ui->menu_Subtitles);
    rmenu.addMenu(ui->menuPlaylist);
    rmenu.addMenu(ui->menu_View);
    rmenu.addMenu(ui->menu_Tools);
    rmenu.addMenu(ui->menu_Help);
    rmenu.exec(event->globalPos());
    //QMainWindow::contextMenuEvent(event);


}
void PlayerWindow::animate_ae_slider(QStringList values)
{

    QPropertyAnimation *animation[10];
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    animation[0]= new QPropertyAnimation(ui->eq0, "value");
    animation[1]= new QPropertyAnimation(ui->eq1, "value");
    animation[2]= new QPropertyAnimation(ui->eq2, "value");
    animation[3]= new QPropertyAnimation(ui->eq3, "value");
    animation[4]= new QPropertyAnimation(ui->eq4, "value");
    animation[5]= new QPropertyAnimation(ui->eq5, "value");
    animation[6]= new QPropertyAnimation(ui->eq6, "value");
    animation[7]= new QPropertyAnimation(ui->eq7, "value");
    animation[8]= new QPropertyAnimation(ui->eq8, "value");
    animation[9]= new QPropertyAnimation(ui->eq9, "value");

    for( int i=0;i<10;i++)
    {
        tmp=values.at(i);
        animation[i]->setDuration(100);
        animation[i]->setEndValue(tmp.toFloat());
        group->addAnimation(animation[i]);
    }
    group->start();
}

void PlayerWindow::on_contrast_valueChanged(int value)
{if (mp)
        mp->setvideoproperty("contrast",ui->contrast->value());
}

void PlayerWindow::on_brightness_valueChanged(int value)
{if (mp)
        mp->setvideoproperty("brightness",ui->brightness->value());

}


void PlayerWindow::on_Hue_valueChanged(int value)
{if (mp)
        mp->setvideoproperty("hue",ui->Hue->value());
}


void PlayerWindow::on_Saturation_valueChanged(int value)
{if (mp)
        mp->setvideoproperty("saturation",ui->Saturation->value());
}


void PlayerWindow::on_gamma_valueChanged(int value)
{if (mp)
        mp->setvideoproperty("gamma",ui->gamma->value());
}
void PlayerWindow::setequlizerbandvalue(int bandval)
{
    if( mp)
    {QString val;

        val=QString::number((double)ui->eq0->value())+":";
        val+= QString::number((double)ui->eq1->value())+":";
        val+= QString::number((double)ui->eq2->value())+":";
        val+= QString::number((double)ui->eq3->value())+":";
        val+= QString::number((double)ui->eq4->value())+":";
        val+= QString::number((double)ui->eq5->value())+":";
        val+= QString::number((double)ui->eq6->value())+":";
        val+= QString::number((double)ui->eq7->value())+":";
        val+= QString::number((double)ui->eq8->value())+":";
        val+= QString::number((double)ui->eq9->value());

        mp->setequalizerbandvalue( val);
        mp->eqvalues(val);
    }

}

void PlayerWindow::on_btnAEReset_clicked()
{
    QStringList values;
    values.clear();
    values<<QString::number(0)<<QString::number(0);
    values<<QString::number(0)<<QString::number(0);
    values<<QString::number(0)<<QString::number(0);
    values<<QString::number(0)<<QString::number(0);
    values<<QString::number(0)<<QString::number(0);
    animate_ae_slider(values);
    ui->comboBox->setCurrentIndex(3);
}
void PlayerWindow::on_comboBox_currentIndexChanged(int index)
{   settings->setValue("Audio/EqBand",QString::number(index));

    EqualizerTypes *ebt =new EqualizerTypes();
    QStringList values;
    values.clear();
    switch(index)
    {
    case 0:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Classical[i]*0.6);
        break;
    case 1:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Club[i]*0.6);
        break;
    case 2:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Dance[i]*0.6);
        break;
    case 3:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Flat[i]*0.6);
        break;
    case 4: for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Fullbass[i]*0.6);
        break;
    case 5:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->FullbassTreble[i]*0.6);
        break;
    case 6:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Fulltreble[i]*0.6);
        break;
    case 7:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Headphones[i]*0.6);
        break;
    case 8: for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->LargeHall[i]*0.6);
        break;
    case 9:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Live[i]*0.6);
        break;
    case 10:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Party[i]*0.6);
        break;
    case 11:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Pop[i]*0.6);
        break;
    case 12:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Reggae[i]*0.6);
        break;
    case 13:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Rock[i]*0.6);
        break;
    case 14:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Ska[i]*0.6);
        break;
    case 15:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Soft[i]*0.6);
        break;
    case 16:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->SoftRock[i]*0.6);
        break;
    case 17:for(int i=0;i<10;i++)
            values<<QString::number((double)ebt->Techno[i]*0.6);
        break;
    }
    if (index!=18)
        animate_ae_slider(values);

    delete ebt;

}

void PlayerWindow::on_actionVideoEqualizer_triggered()
{
    toggle_bottomdock_visibility();
    ui->tabWidget->setCurrentIndex(0);
}
void PlayerWindow::toggle_bottomdock_visibility()
{if(mp)
    {ui->comboBox->setCurrentIndex(settings->value("Audio/EqBand","3").toInt());

        if(mp->isfullscreen())
        {if(ui->dock_Filter->isHidden())
            {ui->dock_Filter->show();
                ui->dock_Filter->setFloating(true);
                ui->dock_Filter->setAllowedAreas(Qt::NoDockWidgetArea);
                ui->dock_Filter->resize(606,256);
            }
        }
        else
        {
            if(ui->dock_Filter->isHidden())
            {ui->dock_Filter->show();
                ui->dock_Filter->setAllowedAreas(Qt::BottomDockWidgetArea);
                ui->dock_Filter->setFloating(true);
                ui->dock_Filter->resize(606,256);

            }
        }
    }

}

void PlayerWindow::on_action_Equalizer_triggered()
{
    toggle_bottomdock_visibility();
    ui->tabWidget->setCurrentIndex(1);

}
void PlayerWindow::foundSubtitletrack(QStringList sl )
{

    if (sl.count()+1!=ui->menuSelect->actions().count())
    {if(actiongroupSubtitleTrack)
            actiongroupSubtitleTrack->addAction( ui->menuSelect->addAction("Track "+QString::number(sl.count())));
        actiongroupSubtitleTrack->actions().last()->setCheckable(true);
    }
}

void PlayerWindow::on_action_Load_st_triggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open subtitles"),
                                                    mp->filepath(),
                                                    tr("Subtitles(*.srt *.sub *.ssa *.ass *.idx *.txt *.smi *.rt *.utf *.aqt)"),
                                                    &selectedFilter,
                                                    options);
    if (!fileName.isEmpty())
    {
        mp->loadsubtitles(fileName);
        ui->actionStUnload->setEnabled(true);
    }
}
void PlayerWindow::changeSubTitles(QAction*act)
{
    if(mp)
    {if(this->actiongroupSubtitleTrack->actions().indexOf(act)-1>-1)
            mp->switchSubtitle(this->actiongroupSubtitleTrack->actions().indexOf(act)-1);
    }

}
void PlayerWindow::changesubAlignment(QAction *action)
{
    if (mp)
        mp->setSubAlignment(actiongroupSubtitleAlignment->actions().indexOf(action));

}

void PlayerWindow::on_actionSize_Increase_triggered()
{
    if (mp)
        mp->scaleSubFont(0);
}

void PlayerWindow::on_actionSize_Decrease_triggered()
{if (mp)
        mp->scaleSubFont(1);
}

void PlayerWindow::on_actionStUnload_triggered()
{
    if (mp)
    {mp->unloadsub();
        ui->actionStUnload->setEnabled(false);
    }

}

void PlayerWindow::on_action_st_Move_Up_triggered()
{if (mp)
        mp->setSubPos(0);
}

void PlayerWindow::on_action_st_Move_Down_triggered()
{if (mp)
        mp->setSubPos(1);
}

void PlayerWindow::on_actionDelay_Increaser_triggered()
{if (mp)
        mp->setSubDelay(0,this);
}

void PlayerWindow::on_actionDelay_Decrease_triggered()
{if (mp)
        mp->setSubDelay(1,this);

}

void PlayerWindow::on_action_st_Set_Delay_triggered()
{if (mp)
        mp->setSubDelay(-1,this);
}

void PlayerWindow::on_action_AV_Set_Delay_triggered()
{if (mp)
        mp->setaudiodelay(-1.0,this);
}
void  PlayerWindow::updatemetadisp()
{
    metadispcount++;

    if( basicmetainfo.count()>0)
    {//ui->label_display->drawCustomText(mp->metainfo.at(metadispcount),9);

        //qDebug()<<mp->metainfo.at(metadispcount);
        if (metadispcount <basicmetainfo.count())
        {
            ui->label_display->drawCustomText(basicmetainfo.at(metadispcount),9);

        }
        else
        {  metadispcount=0;
            // ui->label_display->setText(mp->metainfo.at(metadispcount));
            ui->label_display->drawCustomText(basicmetainfo.at(metadispcount),9);
        }
    }
}

void PlayerWindow::on_actionFullscreen_triggered()
{
    this->toggleFullscreen();

}
void PlayerWindow::mouseMoveEvent ( QMouseEvent * e )
{

    if(this->isFullScreen())
    { ypos=e->y();
        xpos=e->x();

        if(e->y()<(desktop->height() - fullScreenControls->height()))
        {
            if (!hidetimer->isActive())
                hidetimer->start();

            this->unsetCursor();
            fullScreenControls->hide();
        }
        else
        {

            this->unsetCursor();
            fullScreenControls->show();

            /*if (fullScreenControls->y()==desktop->screen()->height()){
                QPropertyAnimation *animation = new QPropertyAnimation(fullScreenControls, "geometry");
                animation->setDuration(300);
                animation->setStartValue(QRect(leftSide,desktop->screen()->height(),fullScreenControlWidth,70));
                animation->setEndValue(QRect(leftSide,desktop->screen()->height()-70,fullScreenControlWidth,70));
                animation->start();
            }*/


            hidetimer->stop();

        }
    }

    if (e->buttons() & Qt::LeftButton) {



        if (ui->action_Crop->isChecked()==false){

            if(e->y()<ui->toolBarSeekBar->y()&&e->y()>ui->menuBar->height()){
                if(!isfullscreen){
                    if (ui->action_Remove_logo->isChecked()==false)
                        move(e->globalPos() - dragPosition);
                }

            }
            qDebug()<<"checked "<<ui->action_Crop->isChecked();


            e->accept();


        }

    }

}
void PlayerWindow::hidestatus()
{


    if (ypos<desktop->height() - fullScreenControls->height())
    {
        //ui->toolBarSeekBar->hide();
        //  ui->toolBarSeek->hide();
        // ui->toolBarStatus->hide();
        //ui->statusBar->hide();
        /* QPropertyAnimation *animation = new QPropertyAnimation(fullScreenControls, "geometry");
        animation->setDuration(300);
        animation->setStartValue(QRect(leftSide,desktop->screen()->height()-70,fullScreenControlWidth,70));
        animation->setEndValue(QRect(leftSide,desktop->screen()->height(),fullScreenControlWidth,70));
        animation->start();*/
        fullScreenControls->hide();
        this->setCursor(Qt::BlankCursor);
        hidetimer->stop();
    }
    tmpxpos= xpos;
    tmpypos= ypos;
}
void PlayerWindow::playThisfile(QString fn)
{forceplay=true;
    QTimer::singleShot(2000, this, SLOT(ShowStop()));


    if( mp)
    {
        resetUi();
        if(playerTimer)
            playerTimer->stop();
        if (disptimer)
            delete disptimer;

        mp->stop();
        mp->mProcess->close();
        //delete mp;
        //}

        ui->menuAudio_Track->clear();
        ui->menuVideo_Track->clear();

        ui->menuSelect->clear();

        ui->menuAudio_Track->addAction(ui->actionAudioDisable);
        ui->menuVideo_Track->addAction(ui->actionVideoDisable);
        ui->menuSelect->addAction(ui->actionStNone);
    }
    if  (fn.contains("http",Qt::CaseInsensitive)||
         fn.contains("ftp",Qt::CaseInsensitive)||
         fn.contains("mms",Qt::CaseInsensitive)||
         fn.contains("rtsp",Qt::CaseInsensitive)||
         fn.contains("rtp",Qt::CaseInsensitive)) {
        this->initMPlayer(fn,1);
    }
    else
        this->initMPlayer(fn,0);

    forceplay=false;

}
void  PlayerWindow::setupPlaylistWindow()
{ui->gridLayout_5->addWidget(myplaylist->tableWidget(),0,0,0);

    ui->gridLayout_5->addWidget(ui->toolBarPlaylist,1,0,0);
    ui->dock_Playlist->setWidget(ui->frame_playlist);
}
void PlayerWindow::addfile()
{

    QFileDialog::Options options;
    QString selectedFilter;
    QStringList  fileName;
    QString filter =getFilter();
    fileName = QFileDialog::getOpenFileNames(this,
                                             tr("Add media file(s) to playlist"),
                                             settings->value("Playlist/OpenfileDlg","").toString(),
                                             filter ,
                                             &selectedFilter,
                                             options);

    if (fileName.count()>0)
    {
        for (int i=0;i<fileName.count();i++)
        { myplaylist->addFile(fileName.at(i));

        }
    }
    /////////////////////////////////////////////

}
void PlayerWindow::addFolder()
{
    QString root=settings->value("Playlist/LastFolder","").toString();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    root,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        myplaylist->addFolder(dir,w->filters,this);
        settings->beginGroup("Playlist");
        settings->setValue("LastFolder",dir);
        settings->endGroup();
    }
}

void PlayerWindow::on_actionAdd_file_triggered()
{
    this->addfile();
}

void PlayerWindow::on_actionRemove_all_triggered()
{
    myplaylist->clearList();
}

void PlayerWindow::on_actionAdd_Folder_triggered()
{
    this->addFolder();
}
void PlayerWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();

}
void PlayerWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urlList;

    if (event->mimeData()->hasUrls())
        urlList = event->mimeData()->urls();

    for (int i = 0; i < urlList.size() && i < 32; ++i) {
        //QString url = urlList.at(i).path();
        // url=url.right(url.length()-1);

#ifdef Q_OS_WIN
        QString url = urlList.at(i).path();
        url=url.right(url.length()-1);
#endif
#ifdef Q_OS_LINUX
        QString url = urlList.at(i).toLocalFile();
# endif
        QFileInfo fi(url);
        if(fi.isFile())
        {  if (urlList.size()==1)
                myplaylist->clearList();
            else if (urlList.size()>1 &&i==0)
                myplaylist->clearList();
            myplaylist->addFile(url);
            myplaylist->playFirstFile();
        }
        else if(fi.isDir())
        { myplaylist->clearList();
            myplaylist->addFolder(url,w->filters,this);
            myplaylist->playFirstFile();
            //this->playThisfile(myplaylist->tab->item(0,2)->data(Qt::DisplayRole).toString());
        }
    }
    event->acceptProposedAction();
}
void PlayerWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}
void PlayerWindow::on_actionSelected_item_s_triggered()
{
    myplaylist->removeSelectedFile();
}
void PlayerWindow::cleanMp()
{
#ifdef Q_OS_WIN
    winscreensaver->enable();
#endif
}
void PlayerWindow::paused()
{ui->action_Play_Pause->setIcon(QIcon(":/images/play.png"));
    ui->action_Play_Pause->setToolTip(tr("Play"));
}
void PlayerWindow::playing()
{
    ui->action_Play_Pause->setIcon(QIcon(":/images/pause.png"));
    ui->action_Play_Pause->setToolTip(tr("Pause"));

}
void PlayerWindow::stopping()
{
    ui->action_Play_Pause->setIcon(QIcon(":/images/play.png"));
    ui->action_Play_Pause->setToolTip(tr("Play"));
}
void  PlayerWindow::showCtxmenuPlaylist(QContextMenuEvent *event)
{
    QMenu rmenu(this);
    //rmenu.addMenu(ui->menuAdd);
    rmenu.addMenu(ui->menuAdd);
    rmenu.addMenu(ui->menu_Remove);
    rmenu.exec(event->globalPos());
}
void PlayerWindow::addFolderTopl(QString fp)
{
    myplaylist->addFolder(fp,w->filters,this);
}
void  PlayerWindow::wheelEvent ( QWheelEvent * event )
{
    if (mousewheelrole==0)
    {if (event->delta()>0){

            ui->sliderVolume->setValue( ui->sliderVolume->value()+5);
            if (sliderVolumeFullSc)
                sliderVolumeFullSc->setValue( ui->sliderVolume->value()+5);

        }
        else{
            ui->sliderVolume->setValue( ui->sliderVolume->value()-5);
            if (sliderVolumeFullSc)
                sliderVolumeFullSc->setValue( ui->sliderVolume->value()-5);

        }
    }
    else
    {if (ui->sliderSeek->isEnabled())
        { if (event->delta()>0){
                ui->sliderSeek->setValue( ui->sliderSeek->value()+1);
                if (playerTimer)
                { this->playerTimer->stop();
                    mp->goturl(ui->sliderSeek->value());
                    this->playerTimer->start();
                }
            }
            else{
                ui->sliderSeek->setValue( ui->sliderSeek->value()-1);
                if (playerTimer)
                {this->playerTimer->stop();
                    mp->goturl(ui->sliderSeek->value());
                    this->playerTimer->start();
                }
            }

        }
    }
}

void PlayerWindow::on_sliderVolume_actionTriggered(int action)
{

}
void PlayerWindow::setEof()
{
    iseof=true;
    //myplaylist->playNextFile();
}
void PlayerWindow::showSeekpos(QString pos, QPoint *pt)
{

    float p=(pos.toInt()/100.0)*mp->duration();
    QTime _duration(0,0,0,0);
    _duration=_duration.addSecs(p);

    if(lab)
    {if( mp->hasvideo())
        {
            mpseekView->resize(128,105);
            if(! isfullscreen)
                mpseekView->move(pt->x()-64+ui->sliderSeek->x(),ui->toolBarSeekBar->y()-105);
            else
                mpseekView->move(pt->x()-64+sliderSeekFullSc->x()+fullScreenControls->x(),fullScreenControls->y()-105);

            mpseekView->show();
        }
        else
        {
            lab->setStyleSheet("image: url(:/images/tooltip.png);"
                               "border-radius: 1px;"
                               "color:white;"
                               "font:80 8pt \"MS Shell Dlg 2\";");


            lab->setAlignment(Qt::AlignCenter);
            lab->resize(60,24);

            if(! isfullscreen)
                lab->move(pt->x()-30+ui->sliderSeek->x(),ui->toolBarSeekBar->y()-ui->toolBarSeekBar->height()/2);
            else
                lab->move(pt->x()-30+sliderSeekFullSc->x()+fullScreenControls->x(),fullScreenControls->y()-25);

            lab->show();
        }
        if (mp->hasvideo())

        {
            if (!fr)
            {

                fr=new mplayerfe(this,this);
                fr->hideFontDlg();
                if(usingfidx)
                { if(mp)
                    {if(mp->arguments.contains("-forceidx",Qt::CaseInsensitive))
                            fr->forceidx();
                    }
                }
                QObject::connect(fr,SIGNAL(startingplayback()),this,SLOT(startingPlaybackframe()));

                fr->setVideoWinid(mpseekView->getwindowID());
                fr->setColorkey(5);
                fr->setaspect(false);
                fr->play(this->currentFile,0);


                fr->setOSDlevel(0);
            }

            if(pos.toInt()<100)
            {fr->pause();
                fr->goturl(pos.toInt());
            }
        }

        if (mp->hasvideo())
        {if (fr)
            {if( fr->isstarted())
                {if (lab)
                    {lab->setText(_duration.toString());
                        mpseekView->setPosition(_duration.toString());
                        frpos=_duration.toString();
                    }
                }
                else
                {  if (lab)
                        lab->setText("Please wait...");
                    // mpseekView->setPosition("Please wait...");
                }
            }

        }
        if (!mp->hasvideo()&&mp->hasaudio())
        {if (lab)
            {
                lab->setText(_duration.toString());
                frpos=_duration.toString();
            }

        }

        // lab->move(pt->x()+10,ui->statusBar->y()-30);
    }
    else
    {
        lab=new QLabel(_duration.toString(),this);
        QPixmap pixmap(":/images/tooltip.png");
        lab->setMask(pixmap.mask());

        connect(ui->sliderSeek,SIGNAL(hidetooltip()),this,SLOT(hideframe()));

        if (mp->hasvideo())
        {
            fr=new mplayerfe(this,this);
            fr->hideFontDlg();
            QObject::connect(fr,SIGNAL(startingplayback()),this,SLOT(startingPlaybackframe()));

            if(usingfidx)
            { if(mp)
                {if(mp->arguments.contains("-forceidx",Qt::CaseInsensitive))
                        fr->forceidx();
                }
            }
            fr->setVideoWinid(mpseekView->getwindowID());
            fr->setColorkey(5);
            fr->setaspect(false);
            fr->play(this->currentFile,0);
            fr->setOSDlevel(0);

        }
        else
        {
            lab->setAlignment(Qt::AlignCenter);
            lab->resize(60,24);
            //lab->move(pt->x()+30,ui->statusBar->y()-30);
            lab->setLineWidth(2);
            //lab->setFrameShadow(QFrame::Raised);
            // lab->show();
        }
    }

}
void PlayerWindow::checkForNextPlayback()
{

    if (mp->state()==mp->BUFFERING){
        QString cacheFill="Buffering...["+QString::number(mp->getBufferFill())+"%]";
        ui->labelStatus->setText(cacheFill);
    }
    if (mp->state()==mp->CONNECTING)
        ui->labelStatus->setText("Connecting...");
    if (mp->state()==mp->RESOLVING)
        ui->labelStatus->setText("Resolving host...");
    if (mp->state()==mp->CRASHED)
        ui->labelStatus->setText("Whoops...Failed!");


}
void PlayerWindow::crossfadePlay()
{
    /*if( mp)
       {resetUi();
        if(playerTimer)
           playerTimer->stop();
        if (disptimer)
           delete disptimer;

       ui->menuAudio_Track->clear();
       ui->menuVideo_Track->clear();
       ui->menuSelect->clear();

      ui->menuAudio_Track->addAction(ui->actionAudioDisable);
      ui->menuVideo_Track->addAction(ui->actionVideoDisable);
      ui->menuSelect->addAction(ui->actionStNone);
     }
       //this->initMPlayer(myplaylist->getNextFile(),0);*/
}
void PlayerWindow::hidebusypg()
{

    pi->stopAnimation();
}

void PlayerWindow::on_action_Media_Info_triggered()
{
    /*<TABLE BORDER=1 WIDTH=80%>
<TBODY>
<TR>
<TD>Row 1, Column 1 text.</TD>
<TD>Row 1, Column 2 text.</TD>
</TR>
</TBODY>
</TABLE>*/

    if (mp)
    {midlg=new miDialog(this);
        QObject::connect(midlg,SIGNAL(saveCoverArt()),this,SLOT(saveCoverArt()));
        QString tex,tmp,md;

        bool add=false;
        if (mp->hasvideo())
        {
            if (!Title.isEmpty() )
                tex="<p></p><center><h2>"+Title+"<h2></center>" ;
        }

        tex="<p></p><center><h2>"+Title+"<h2></center>" ;




        if (mp->idlist.count()>0)
        {//qDebug()<<"ttttttttttttttttttttttttttt"<<Title;
            //if (!Title.isEmpty() )
            //  tex+="<p></p><center><h2>"+Title+"<h2></center>" ;
            tex+="</TBODY></TABLE>";
            tex+="<p><b><h3><SPAN STYLE=\"color: blue\">Metadata</SPAN></h3></b></p>";
            tex+="<TABLE BORDER=0 WIDTH=100%> <TBODY>";

            tex+="<TR><TD bgcolor=#def1ff><b>DURATION</b></TD>";
            QTime t;
            t=t.addSecs(mp->duration());
            tex +="<TD bgcolor=#d0edff>"+ t.toString() + "</TD>";

            for (int i=0;i< mp->idlist.count();i++)
            {QStringList list;
                tmp=mp->idlist.at(i);

                if (tmp.contains("ID_CLIP_INFO_NAME"))
                { list= tmp.split("=",QString::KeepEmptyParts);

                    QString val=QString(list.at(1)).toUpper();
                    if (val.contains("TYER"))
                        val="YEAR";
                    if (val.contains("YEAR"))
                        val="YEAR";

                    tex=tex+"<TR><TD bgcolor=#def1ff><b>"+val+"</b></TD>";

                }
                if (tmp.contains("ID_CLIP_INFO_VALUE"))
                {
                    list.clear();
                    list = tmp.split("=",QString::SkipEmptyParts);
                    if(list.count()>1)
                        tex=tex+"<TD bgcolor=#d0edff>"+list.at(1)+"</TD>";
                    else
                        tex=tex+"<TD bgcolor=#d0edff></TD>";

                }
                if (i>mp->idlist.count())
                    break;

            }

            tex=tex+"</TBODY></TABLE>";
        }
        if (hascover)
        {
            tex+="</TBODY></TABLE>";
            tex+="<p><b><h3><SPAN STYLE=\"color: blue\">Cover</SPAN></h3></b></p>";
            tex+="<TABLE BORDER=0 WIDTH=100%> <TBODY>";
            //tex=tex+"img src=mcover.jpeg"+"\"</TD>";
            //QMessageBox::critical(this,qApp->applicationName(),qApp->applicationDirPath(),QMessageBox::Ok,QMessageBox::Cancel);

            tex+="</TBODY></TABLE>";
            // tex=tex+"<p>Cover</p>";
            QString path;
            QString str;
            str.resize(1);

            str[0] = QChar('"');
            //qDebug()<<str;
            path=qApp->applicationDirPath()+"/mcover.jpeg";
            path.append(str);
            path.prepend(str);
            tex+="<p><img src="+path+"</img></p>";

        }
        if (mp->hasaudio())
        {
            tex+="<p><b><h3><SPAN STYLE=\"color: blue\">Audio</SPAN></h3></b></p>";
            tex+="<TABLE BORDER=0 WIDTH=100%> <TBODY>";
            for (int i=0;i< mp->idlist.count();i++)
            {QStringList list;
                tmp=mp->idlist.at(i);

                if (tmp.contains("ID_AUDIO"))
                {
                    list.clear();
                    //#d0edff
                    list = tmp.split("=",QString::SkipEmptyParts);
                    tex+="<TR><TD bgcolor=#def1ff><b>"+QString(list.at(0)).right(QString(list.at(0)).length()-3)+"</b></TD>";
                    if(list.count()>1)
                        tex+="<TD bgcolor=#d0edff>"+list.at(1)+"</TD></TR>";
                    else
                        tex+="<TD bgcolor=#d0edff></TD></TR>";

                }
                if (i>mp->idlist.count())
                    break;

            }

            tex+="</TBODY></TABLE>";
        }
        if (mp->hasvideo())
        {
            tex+="<p><b><h3><SPAN STYLE=\"color: blue\">Video</SPAN></h3></b></p>";
            tex+="<TABLE BORDER=0 WIDTH=100%> <TBODY>";
            for (int i=0;i< mp->idlist.count();i++)
            {QStringList list;
                tmp=mp->idlist.at(i);

                if (tmp.contains("ID_VIDEO"))
                {
                    list.clear();
                    list = tmp.split("=",QString::SkipEmptyParts);
                    tex+="<TR><TD bgcolor=#def1ff><b>"+QString(list.at(0)).right(QString(list.at(0)).length()-3)+"</b></TD>";
                    if(list.count()>1)
                        tex+="<TD bgcolor=#d0edff>"+list.at(1)+"</TD></TR>";
                    else
                        tex+="<TD bgcolor=#d0edff></TD></TR>";


                }
                if (i>mp->idlist.count())
                    break;

            }


            tex+="</TBODY></TABLE>";
        }

        //mi->setText(tex);
        //mi->resize(250,300);
        //mi->show();
        midlg->setMiText(tex);
        midlg->setbtnSaveEnable(hascover);

        midlg->resize(250,0);
        if (mp->hasvideo())
        { midlg->resize(250,470);
            /*QPropertyAnimation *animation = new QPropertyAnimation(midlg, "size");
            animation->setDuration(300);
            animation->setStartValue(QSize(250, 0));
            animation->setEndValue(QSize(250, 470));

            midlg->show();
            animation->start();*/
            midlg->show();
        }
        else if (!mp->hasvideo())
        { if (!hascover)
            { midlg->resize(250,400);
                /*QPropertyAnimation *animation = new QPropertyAnimation(midlg, "size");
                animation->setDuration(300);
                animation->setStartValue(QSize(250, 0));
                animation->setEndValue(QSize(250, 400));
                //animation->setEasingCurve(QEasingCurve::InCurve);
                midlg->show();
                animation->start();*/
                midlg->show();

            }

            else
            {midlg->resize(500,550);
                /*QPropertyAnimation *animation = new QPropertyAnimation(midlg, "size");
                animation->setDuration(300);
                animation->setStartValue(QSize(500, 0));
                animation->setEndValue(QSize(500, 550));
               // animation->setEasingCurve(QEasingCurve::InCurve);
                midlg->show();
                animation->start();*/
                midlg->show();

            }
        }

    }
}
void PlayerWindow::showtooltip(QPoint *pt)
{/*if (lab)
    {QPropertyAnimation *animation = new QPropertyAnimation(lab, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(pt->x()-210, ui->statusBar->y(), 65, 25));
    animation->setEndValue(QRect(pt->x()+10, ui->statusBar->y()-25, 65, 25));
    animation->start();
}
    qDebug()<<"dsggggggggggggggggggggggggggggg";*/
}

void PlayerWindow::on_sliderSeek_valueChanged(int value)
{

}
void PlayerWindow::hideframe()
{/*QPropertyAnimation *animation = new QPropertyAnimation(lab, "geometry");
animation->setDuration(100);
animation->setEndValue(QRect(lab->x(), ui->statusBar->y()-64, 65, 0));
animation->start();*/
    videoWin->update();
    if (lab)
    {  lab->resize(1,1);
        lab->hide();

        mpseekView->resize(1,1);
        mpseekView->close();
    }
    /*if (mpseekview)
    {
        mpseekview->resize(1,1);
        mpseekview->hide();
    }*/

    //delete lab;
    videoWin->update();
}

void PlayerWindow::on_action_Options_triggered()
{
    optionDlg=new preferenceDialog(this,settings);
    QObject::connect(optionDlg,SIGNAL(settingChanged(QString,QString,QString)),this,SLOT(settingChanged(QString,QString,QString)));
    QObject::connect(optionDlg,SIGNAL(reloadshortcut()),this,SLOT(createShortcuts()));
    QObject::connect(optionDlg,SIGNAL(setmousewheelrole()),this,SLOT(setmousewheelrole()));
    QObject::connect(optionDlg,SIGNAL(disableSS()),this,SLOT(disableStylesheet()));
    QObject::connect(optionDlg,SIGNAL(setAqua()),this,SLOT(setAqua()));

    if(mp)
    {QObject::connect(optionDlg,SIGNAL(restart()),mp,SLOT(restart()));
        QObject::connect(optionDlg,SIGNAL(restartComplete()),this,SLOT(completeRestart()));
    }
    optionDlg->setSettings( settings);
    optionDlg->setSc(this);
    optionDlg->show();
}


void PlayerWindow::on_actionVolume_Normalization_triggered()
{if (mp)
        mp->addAudioFilterVolnorm(ui->actionVolume_Normalization->isChecked());

}

void PlayerWindow::on_actionNegative_triggered()
{
    mp->negative(ui->actionNegative->isChecked());

}

void PlayerWindow::on_actionWinamp_Dsp_triggered()
{
    mp->addAudioFilterWinampDsp();
}
void PlayerWindow::loadMPlayerConfig()
{
    ui->actionFull_5_1->setEnabled(false);
    ui->actionFull_7_1->setEnabled(false);
    ui->actionSurround->setEnabled(false);
    if(hascover)
        delete cover;
    Title="";
    hascover=false;
    framedroplevel=0;
    osdlevel=1;
    videoHeight=0;
    videoWidth=0;
    ui->action_fd_Disable->setCheckable(true);
    ui->action_osd1->setChecked(true);
    ui->actionStep2_fm->setEnabled(false);
    ui->actionStereo->setChecked(true);
    bedlenable=false;
    ui->action_ar_Auto->setChecked(true);
    mousewheelrole=settings->value("Mouse/Wheel","0").toInt();
    QString val;
    QString slval;
    QStringList sllst;

    slval=settings->value("Audio/Eq","0:0:0:0:0:0:0:0:0:0").toString();
    sllst=slval.split(":");
    if (sllst.count()==10)
    {
        ui->eq0->setValue(QString(sllst.at(0)).toInt());
        ui->eq1->setValue(QString(sllst.at(1)).toInt());
        ui->eq2->setValue(QString(sllst.at(2)).toInt());
        ui->eq3->setValue(QString(sllst.at(3)).toInt());
        ui->eq4->setValue(QString(sllst.at(4)).toInt());
        ui->eq5->setValue(QString(sllst.at(5)).toInt());
        ui->eq6->setValue(QString(sllst.at(6)).toInt());
        ui->eq7->setValue(QString(sllst.at(7)).toInt());
        ui->eq8->setValue(QString(sllst.at(8)).toInt());
        ui->eq9->setValue(QString(sllst.at(9)).toInt());
    }

    val=QString::number((double)ui->eq0->value())+":";
    val+= QString::number((double)ui->eq1->value())+":";
    val+= QString::number((double)ui->eq2->value())+":";
    val+= QString::number((double)ui->eq3->value())+":";
    val+= QString::number((double)ui->eq4->value())+":";
    val+= QString::number((double)ui->eq5->value())+":";
    val+= QString::number((double)ui->eq6->value())+":";
    val+= QString::number((double)ui->eq7->value())+":";
    val+= QString::number((double)ui->eq8->value())+":";
    val+= QString::number((double)ui->eq9->value());

    mp->eqvalues(val);

    if (settings->value("Audio/EnableEQ","2").toInt()==2)
    {
        ui->cbEnableAEq->setCheckState(Qt::Checked);
        mp->enableEqualizer(val);

    }
    else
        ui->cbEnableAEq->setCheckState(Qt::Unchecked);
    mp->setPriority(settings->value("General/Priority","abovenormal").toString());
    //settings->value("Audio/EnableEQ","0").toInt();



}

void PlayerWindow::on_cbEnableAEq_stateChanged(int val)
{
    settings->setValue("Audio/EnableEQ",QString::number(ui->cbEnableAEq->checkState()));
    if(val==2)
    {
        QString val;
        val=QString::number((double)ui->eq0->value())+":";
        val+= QString::number((double)ui->eq1->value())+":";
        val+= QString::number((double)ui->eq2->value())+":";
        val+= QString::number((double)ui->eq3->value())+":";
        val+= QString::number((double)ui->eq4->value())+":";
        val+= QString::number((double)ui->eq5->value())+":";
        val+= QString::number((double)ui->eq6->value())+":";
        val+= QString::number((double)ui->eq7->value())+":";
        val+= QString::number((double)ui->eq8->value())+":";
        val+= QString::number((double)ui->eq9->value());

        mp->enableEq(true);
    }
    else
    {qDebug()<<"remove";
        //mp->usercommand("af_del equalizer");
        // mp->usercommand("af_del volume");
        mp->enableEq(false);
    }


}

void PlayerWindow::on_eq3_valueChanged(int value)
{

}
void PlayerWindow::setcmbIndex()
{
    ui->comboBox->setCurrentIndex(18);
}

void PlayerWindow::on_actionURL_triggered()
{if (!urldlg)
    {
        urldlg=new UrlDialog(this);
        connect(urldlg,SIGNAL(playurl(QString)),this,SLOT(playurl(QString)));
    }

    urldlg->show();
}
void PlayerWindow::addRecentFileAndPlay(QString file)
{
    myplaylist->clearList();
    myplaylist->addFile(file);
    myplaylist->playFirstFile();
}
void PlayerWindow:: playurl(QString url)
{
    myplaylist->clearList();
    myplaylist->addFile(url);
    myplaylist->playFirstFile();
}
void PlayerWindow::createShortcuts()
{
    QString path;

    path=Paths::configPath();
    path.append("/sc_user.xml");

    QFile file(path);
    qDebug()<<"Checking for user short cut bindings..."<<file.exists();
    if(!file.exists())
    {  file.close();
        path.clear();
#ifdef Q_OS_WIN
     path=Paths::configPath();
#endif
#ifdef Q_OS_LINUX
    path=Paths::getStaticConfigPath();
# endif
        path.append("/sc_default.xml");
        qDebug()<<"Loading shortcut file :"<<path;
        file.setFileName(path);
        qDebug()<<"Checking for deault short cut bindings..."<<file.exists();

    }
    if (!file.open(QIODevice::ReadOnly)) {
        ///msgBox.setText(file.errorString());
        // msgBox.exec();
        qDebug()<<"Failed in initializing the shortcuts";
        return;
    }

    QXmlStreamReader reader(&file);
    QString p;
    while (!reader.atEnd()) {

        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == "Name")
            {
                p=reader.readElementText();
            }
            if (reader.name() == "ShortCut")
            {QString sc=reader.readElementText();

                QAction *act= this->findChild<QAction *>(p);

                act->setShortcut( QKeySequence(sc));
                //   qDebug()<<act->shortcut().toString();
                act->setShortcutContext(	Qt::WidgetShortcut);
                shortcut = new QShortcut(QKeySequence(sc),
                                         this);

                QObject::connect(shortcut,SIGNAL(activated()),act,SLOT(trigger()));

            }


        }

    }


}
void PlayerWindow::setmousewheelrole()
{
    mousewheelrole= settings->value("Mouse/Wheel","0").toInt();
}

void PlayerWindow::on_action_Save_as_playlist_triggered()
{ QFileDialog::Options options;
    QString selectedFilter;
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("Save as playlist"),
                                            "",
                                            tr("Playlist (*.m3u);;Playlist (*.pls)"),
                                            &selectedFilter,
                                            options);


    if (!fileName.isEmpty())
    { QFileInfo fi(fileName);
        QString ext = fi.suffix();  // ext = "gz"

        if (ext=="m3u")
            myplaylist->saveasM3u(fileName);
        else
            myplaylist->saveasPls(fileName);
    }

}
void PlayerWindow::toggleFullscreen()
{

    this->isFullScreen();

    if(this->isFullScreen()){
        if (mp){
            if (mp->hasvideo())
                mp->usercommand("osd_show_text \"\" 1 1");
        }

        if (!ui->actionStay_on_top->isChecked())
            this->setWindowFlags(!Qt::WindowStaysOnTopHint);

        ui->actionFullscreen->setIcon(QIcon(":/images/fullscreen.png"));
        ui->actionFullscreen->setToolTip("Show fullscreen");
        isfullscreen=false;
        hidetimer->stop();
        this->showNormal();
        ui->toolBarSeek->show();
        ui->menuBar->show();
        ui->toolBarStatus->show();
        ui->toolBarSeekBar->show();
        ui->statusBar->show();
        this->unsetCursor();

        if (bfilvis)
            ui->dock_Filter->show();
        if (blogvis)
            ui->dock_log->show();
        if (bplvis)
            ui->dock_Playlist->show();
        if (bfbvis)
            ui->dockBrowser->show();

        delete hidetimer;
    }
    else
    {
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
        qDebug()<<"Screen Height :"<<desktop->screen()->height();
        qDebug()<<"Screen Width :"<<desktop->screen()->width();

        if(fullScreenControls<=0)
        { fullScreenControls=new QToolBar(this);

            GlassStyle *st=new GlassStyle;
            fullScreenControls->setStyle(st);
            lcdCurPosFullSc=new QLCDNumber(this);

            lcdDurationFullSc=new QLCDNumber(this);
            lcdCurPosFullSc->setSegmentStyle(ui->lcdCurPos->segmentStyle());
            lcdDurationFullSc->setSegmentStyle(ui->lcdDuration->segmentStyle());
            lcdCurPosFullSc->setNumDigits(8);
            lcdDurationFullSc->setNumDigits(8);
            lcdCurPosFullSc->setMaximumSize(ui->lcdCurPos->maximumSize());
            lcdDurationFullSc->setMaximumSize(ui->lcdDuration->maximumSize());
            lcdCurPosFullSc->setFrameShape(ui->lcdCurPos->frameShape());
            lcdDurationFullSc->setFrameShape(ui->lcdDuration->frameShape());
            lcdCurPosFullSc->setLineWidth(ui->lcdCurPos->lineWidth());
            lcdDurationFullSc->setLineWidth(ui->lcdDuration->lineWidth());

            sliderVolumeFullSc=new rphSlider(this);
            sliderVolumeFullSc->setTracking(true);
            sliderVolumeFullSc->setMouseTracking(true);
            sliderVolumeFullSc->setMinimum(0);
            sliderVolumeFullSc->setMaximum(100);
            sliderVolumeFullSc->setMaximumWidth(65);
            sliderVolumeFullSc->setMaximumHeight(ui->sliderVolume->height());
            sliderVolumeFullSc->setOrientation(Qt::Horizontal);
            sliderVolumeFullSc->setStyleSheet(ui->sliderVolume->styleSheet());
            sliderVolumeFullSc->setValue(ui->sliderVolume->value());
            QObject::connect(sliderVolumeFullSc,SIGNAL(valueChanged(int)),this,SLOT(on_sliderVolume_valueChanged(int)));


            sliderSeekFullSc=new rphSlider(this);
            sliderSeekFullSc->setTracking(true);
            sliderSeekFullSc->setMouseTracking(true);
            sliderSeekFullSc->setMaximumHeight(ui->sliderSeek->height());
            sliderSeekFullSc->setOrientation(Qt::Horizontal);
            sliderSeekFullSc->setMinimum(0);
            sliderSeekFullSc->setMaximum(100);
            sliderSeekFullSc->setEnabled(ui->sliderSeek->isEnabled());
            sliderSeekFullSc->setStyleSheet(ui->sliderSeek->styleSheet());
            sliderSeekFullSc->setValue(ui->sliderSeek->value());
            QObject::connect(sliderSeekFullSc,SIGNAL(actionTriggered(int)),this,SLOT(on_sliderSeekFullSc_actionTriggered(int)));

            QObject::connect(sliderSeekFullSc,SIGNAL(showtooltip(QPoint *)),this,SLOT(showtooltip(QPoint *)));
            QObject::connect(sliderSeekFullSc,SIGNAL(hoverValue(QString,QPoint*)),this,SLOT(showSeekpos(QString,QPoint*)));

            lcdCurPosFullSc->display("00:00:00");
            lcdDurationFullSc->display("00:00:00");
            lcdCurPosFullSc->setStyleSheet(ui->lcdCurPos->styleSheet());
            lcdDurationFullSc->setStyleSheet(ui->lcdDuration->styleSheet());

            connect(sliderSeekFullSc,SIGNAL(hidetooltip()),this,SLOT(hideframe()));


        }
        fullScreenControlWidth=(long)desktop->screen()->width()*FULLSCREENCTRL_WIDTH_PERCENTAGE;

        leftSide=(desktop->screen()->width()/2)-(fullScreenControlWidth/2);
        if(fullScreenControls)
        {


            fullScreenControls->setMovable(false);
            fullScreenControls->setGeometry(leftSide,desktop->screen()->height()-FULLSCREENCTRLHEIGHT,fullScreenControlWidth,70);
            fullScreenControls->addAction(ui->action_Play_Pause);
            fullScreenControls->addAction(ui->action_Stop);
            fullScreenControls->addWidget(sliderVolumeFullSc);
            fullScreenControls->addWidget(lcdCurPosFullSc);
            fullScreenControls->addWidget(sliderSeekFullSc);
            fullScreenControls->addWidget(lcdDurationFullSc);
            fullScreenControls->addAction(ui->actionFullscreen);
            fullScreenControls->show();
            sliderSeekFullSc->setEnabled(ui->sliderSeek->isEnabled());
            sliderSeekFullSc->setValue(ui->sliderSeek->value());
            sliderVolumeFullSc->setValue(ui->sliderVolume->value());

            QPropertyAnimation *animation = new QPropertyAnimation(fullScreenControls, "geometry");
            animation->setDuration(60);
            animation->setStartValue(QRect(leftSide,desktop->screen()->height(),fullScreenControlWidth,70));
            animation->setEndValue(QRect(leftSide,desktop->screen()->height()-70,fullScreenControlWidth,70));
            animation->start();
        }

        ui->toolBarSeek->hide();
        ui->menuBar->hide();
        ui->toolBarStatus->hide();
        ui->toolBarSeekBar->hide();
        ui->statusBar->hide();
        this->showFullScreen();

        ui->actionFullscreen->setIcon(QIcon(":/images/fullscreen_exit.png"));
        ui->actionFullscreen->setToolTip("Exit fullscreen");
        if (mp)
        {if (mp->hasvideo())
            {
                mp->usercommand("osd_show_text \"Press " + ui->actionFullscreen->shortcut().toString() + " to exit fullscreen\" 2000 1");

            }
        }
        ui->menuBar->hide();
        if (!hidetimer)
        {hidetimer = new QTimer(this);
            QObject::connect(hidetimer, SIGNAL(timeout()), this, SLOT(hidestatus()));
        }

        bfilvis=ui->dock_Filter->isVisible();
        blogvis=ui->dock_log->isVisible();
        bplvis=ui->dock_Playlist->isVisible();
        bfbvis=ui->dockBrowser->isVisible();

        if (ui->dock_Playlist->isVisible())
            ui->dock_Playlist->hide();
        if (ui->dockBrowser->isVisible())
            ui->dockBrowser->hide();
        if (ui->dock_log->isVisible())
            ui->dock_log->hide();
        if (ui->dock_Filter->isVisible())
            ui->dock_Filter->hide();

        hidetimer->start(3000);
        isfullscreen=true;
    }
    mp->togglefullscreen();

}
void PlayerWindow::mouseDoubleClickEvent (QMouseEvent *ev)
{
    toggleFullscreen();
}

void PlayerWindow::on_actionPlay_Next_File_triggered()
{
    myplaylist->playNextFile();
}

void PlayerWindow::on_actionPlay_Previous_File_triggered()
{
    myplaylist->playPreviousFile();
}
void PlayerWindow::saveCoverArt()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save as"),
                                                    "",
                                                    tr("Joint Photographic Experts Group (*.jpg);;Windows Bitmap (*.bmp);;Portable Network Graphics(*.png);;X11 Bitmap(*.xbm);Portable Pixmap(*.ppm)"),
                                                    &selectedFilter,
                                                    options);
    if (!fileName.isEmpty())
    {
        if(!cover->save(fileName,0,-1))
            QMessageBox::critical(this,qApp->applicationName(),tr("An error occured while saving"),QMessageBox::Ok,QMessageBox::Cancel);

    }
}
void PlayerWindow::removelavf()
{
    lavf=false;
    this->initMPlayer(currentFile,fileType);
}

void PlayerWindow::on_eq0_actionTriggered(int action)
{

}

void PlayerWindow::on_action_Load_pl_triggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open a playlist"),
                                            "",
                                            tr("Playlists (*.m3u *.pls)"),
                                            &selectedFilter,
                                            options);


    if (!fileName.isEmpty())
    {myplaylist->addFile(fileName);
    }
}
void PlayerWindow::winExplorer(QString opt,QString path)
{
#ifdef Q_OS_WIN
    path=path.replace("/","\\");
    QProcess::execute("explorer.exe "+opt+path);
#elif defined Q_OS_LINUX
    QString lpath = QDir::toNativeSeparators(path);
    // lpath.left(lpath.length()- lpath.lastIndexOf(QDir::separator () );
    //qDebug()<<lpath.left(lpath.length()-lpath.lastIndexOf("/")+1);
    QDir d = QFileInfo(lpath).absoluteDir();
    QDesktopServices::openUrl(QUrl(d.absolutePath()));
#endif


}

void PlayerWindow::on_actionOpen_containing_folder_triggered()
{
    if (fileType!=1||fileType!=3)
    {if (currentFile!="")
            this->winExplorer(QString("/select,"),currentFile);


    }


}

void PlayerWindow::on_action_About_triggered()
{
    abtDlg=new aboutDialog(this);
    abtDlg->show();

}

void PlayerWindow::on_actionEnable_Closed_Captions_triggered()
{
    if( mp)
        mp->enableClosedCaption(ui->actionEnable_Closed_Captions->isChecked());
}

void PlayerWindow::on_actionMedia_cutter_triggered()
{
    cdlg=new cutterDialog(this,mp);
    QObject::connect(cdlg,SIGNAL(showfile(QString,QString)),this,SLOT(winExplorer(QString,QString)));
    cdlg->show();
}

void PlayerWindow::on_actionShowpl_triggered()
{


    if (!ui->dock_Playlist->isVisible())
    {
        ui->dock_Playlist->setFloating(true);

        ui->dock_Playlist->resize(310,400);
        if (desktop->width()-100>this->width()+this->x())
        {ui->dock_Playlist->move(this->width()+this->x()+8,this->y());
        }

        ui->dock_Playlist->show();
    }
    else
        ui->dock_Playlist->hide();
    /*if (mp)
   {if (mp->hasvideo())
    ui->dock_Playlist->setFloating(true);
else
   ui->dock_Playlist->setFloating(false);
}*/
}

void PlayerWindow::on_cbEnableAEq_clicked()
{

}
void PlayerWindow::enableChannels()
{
    ui->actionFull_5_1->setEnabled(true);
    ui->actionFull_7_1->setEnabled(true);
    ui->actionSurround->setEnabled(true);
}

void PlayerWindow::on_action_Help_triggered()
{
    mainhlpDlg=new helpDialog(this);
    mainhlpDlg->showContent();
    mainhlpDlg->show();
}
void PlayerWindow::setAqua()
{   //qApp->setStyle("windowsxp");
    qApp->setStyle(new GlassStyle);
    // QApplication::setPalette(QApplication::style()->standardPalette());

    ui->sliderVolume->setStyleSheet(QString::fromUtf8("QSlider::sub-page:horizontal {\n"
                                                      "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 255), stop:1 rgba(255, 255, 255, 255));    \n"
                                                      " border: 1px solid lightgray;\n"
                                                      " }\n"
                                                      " QSlider::groove:horizontal {\n"
                                                      "     height: 2px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
                                                      "     margin: 1px 0;\n"
                                                      " background: qlineargradient(x1: 1, y1:12, x1: 15, y2: 0, stop: 0 #e7effd, stop: 1 #D2E7FA); \n"
                                                      " border: 2px solid lightgray;\n"
                                                      " }\n"
                                                      "QSlider::handle::horizontal{ \n"
                                                      "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 150), stop:1 rgba(255, 255, 255, 200));\n"
                                                      "width: 14px;\n"
                                                      " border: 1px solid rgba(128, 184, 228, 150);\n"
                                                      "     margin: -8px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                      "     border-radius: 8px;\n"
                                                      "}\n"
                                                      "QSlider::handle::hover:horizontal{ \n"
                                                      "background:qlineargradient(spread:pad, x1:"
                                                      "0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 255, 0, 150), stop:1 rgba(255, 255, 255, 255));\n"
                                                      "width: 14px;\n"
                                                      " border: 1px solid lightgreen;\n"
                                                      "     margin: -8px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                      "     border-radius: 8px;\n"
                                                      "}\n"
                                                      "QSlider::handle::disabled:horizontal{ \n"
                                                      "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 205), stop:1 rgba(255, 255, 255, 200));\n"
                                                      "width: 0px;\n"
                                                      " border: 2px solid lightblue;\n"
                                                      "     margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                      "     border-radius: 2px;\n"
                                                      "}"));
    ui->sliderSeek->setStyleSheet(QString::fromUtf8("QSlider::sub-page:horizontal {\n"
                                                    "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 255), stop:1 rgba(255, 255, 255, 255));    \n"
                                                    " border: 1px solid lightgray;\n"
                                                    " }\n"
                                                    " QSlider::groove:horizontal {\n"
                                                    "     height: 2px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
                                                    "     margin: 1px 0;\n"
                                                    " background: qlineargradient(x1: 1, y1:12, x1: 15, y2: 0, stop: 0 #e7effd, stop: 1 #D2E7FA); \n"
                                                    " border: 2px solid lightgray;\n"
                                                    " }\n"
                                                    "QSlider::handle::horizontal{ \n"
                                                    "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 150), stop:1 rgba(255, 255, 255, 200));\n"
                                                    "width: 2px;\n"
                                                    " border: 1px solid rgba(128, 184, 228, 150);\n"
                                                    "     margin: -8px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                    "     border-radius: 8px;\n"
                                                    "}\n"
                                                    "QSlider::handle::hover:horizontal{ \n"
                                                    "background:qlineargradient(spread:pad, x1:"
                                                    "0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 255, 0, 150), stop:1 rgba(255, 255, 255, 255));\n"
                                                    "width: 2px;\n"

                                                    "     margin: -8px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                    "     border-radius: 8px;\n"
                                                    "}\n"
                                                    "QSlider::handle::disabled:horizontal{ \n"
                                                    "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 205), stop:1 rgba(255, 255, 255, 200));\n"
                                                    "width: 0px;\n"
                                                    " border: 2px solid lightblue;\n"
                                                    "     margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                    "     border-radius: 2px;\n"
                                                    "}"));

    // ui->sliderSeek->setStyleSheet(ui->sliderVolume->styleSheet());

    ui->toolBarSeekBar->setStyleSheet(QString::fromUtf8("background:white;"));

    //this->setStyleSheet(QString::fromUtf8());

}
void PlayerWindow::disableStylesheet()
{
    this->setStyleSheet("");
    ui->sliderSeek->setStyleSheet("");
    ui->sliderVolume->setStyleSheet("");
    ui->toolBarSeekBar->setStyleSheet("");
}

void PlayerWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void PlayerWindow::on_actionMix_and_save_triggered()
{
    if (mp)
    {if (mp->audioFile.isEmpty())
        {QMessageBox::information(this,qApp->applicationName(),tr("Please load a external audio file."),QMessageBox::Ok,QMessageBox::Cancel);
            return;
        }
    }



    QString dir = rphFile::getDir(this,"Open a Directory for output:","");




    if (!dir.isEmpty())
    {

        mxdlg=new mixDialog(this);
        QObject::connect(mxdlg,SIGNAL(showfile(QString,QString)),this,SLOT(winExplorer(QString,QString)));
        mxdlg->mix(mp->shortPathName(mp->filepath()),mp->shortPathName(mp->audioFile),dir);
        mxdlg->show();
    }

}

void PlayerWindow::on_toolButtonfs_clicked()
{
    this->toggleFullscreen();
}
int PlayerWindow::getEh()
{int eh=mp->videoheight()+ui->toolBarSeek->height()+ ui->statusBar->height()+ui->menuBar->height()+ui->toolBarSeekBar->height()+ui->toolBarStatus->height();
    if (!ui->dockBrowser->isHidden())
    {if (!ui->dockBrowser->isFloating())
        {
            eh+=ui->dockBrowser->height();
            eh+=8;

        }
    }
    if (!ui->dockBrowser->isFloating()&&!ui->dock_Filter->isHidden())
        eh=eh+ui->dock_Filter->height();
    return eh;
}


void PlayerWindow::readCmd()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (in.atEnd())
        return;

    QString nextCmd;
    in >> nextCmd;
    //QMessageBox::critical(this,qApp->applicationName(), nextCmd,QMessageBox::Ok,QMessageBox::Cancel);
    //this->setWindowTitle(nextCmd);
    if (nextCmd.contains("add-to-playlist"))
    {nextCmd=nextCmd.right(nextCmd.length()-15);
        myplaylist->addFile(nextCmd);
        this->setFocus(Qt::ActiveWindowFocusReason);
    }
    else
    {
        myplaylist->clearList();
        myplaylist->addFile(nextCmd);
        myplaylist->playFirstFile();
        this->setFocus(Qt::ActiveWindowFocusReason);
    }
    // if (nextFortune == currentFortune) {
    //     QTimer::singleShot(0, this, SLOT(requestNewFortune()));
    //     return;
    // }

    //currentFortune = nextFortune;
}

void  PlayerWindow::connectTosever()
{
    blockSize = 0;
    socket->abort();
    socket->connectToServer("ExMplayer-SERVER");


}
void PlayerWindow::writeSettings()
{if (settings)
    {
        //QSettings settings;
        qDebug()<<settings->value("General/recentFilesClear","0");

        if(settings->value("General/recentFilesClear",0).toInt()==2)
        {
            recentFilesMenu->clearMenu();
            // qDebug()<<"CLEAR HISTORY";
        }
        settings->beginGroup("History");
        settings->setValue("recentFiles", recentFilesMenu->saveState());
        settings->endGroup();

        settings->beginGroup("MainWindow");
        settings->setValue("size", size());
        settings->setValue("pos", pos());
        settings->endGroup();

    }

}
void PlayerWindow::readSettingsGeo()
{
    QSize sz;
    settings->beginGroup("MainWindow");
    sz=settings->value("size", QSize(600, 500)).toSize();
    resize(sz);

    QPoint po=settings->value("pos", QPoint((desktop->width()-this->width())/2, (desktop->height()-this->height())/2)).toPoint();
    move(settings->value("pos", QPoint((desktop->width()-this->width())/2, (desktop->height()-this->height())/2)).toPoint());

    settings->endGroup();


    /*
          QPropertyAnimation *anim1 = new QPropertyAnimation(this, "pos");
          anim1->setDuration(200);
          anim1->setStartValue(QPoint(po.x()+sz.width()/2,po.y()+sz.height()/2));
          anim1->setEasingCurve(QEasingCurve::Linear);
          anim1->setEndValue(QPoint(po.x(),po.y()));
      //anim1->start();
          QPropertyAnimation *anim2 = new QPropertyAnimation(this, "size");
          anim2->setDuration(200);
          anim2->setStartValue(QSize(0, 0));
          anim2->setEasingCurve(QEasingCurve::Linear);
          anim2->setEndValue(QSize(sz.width(),sz.height()));


          QParallelAnimationGroup *group = new QParallelAnimationGroup;
          group->addAnimation(anim1);
          group->addAnimation(anim2);

          group->start();*/
    //450/145
}
void PlayerWindow::completeRestart()
{
    if( mp->state()==mp->PLAYING)
    { prevpos=ui->sliderSeek->value();
        currentFilePos=mp->curpos();
        ui->action_Stop->trigger();
        qDebug()<<"**********************************************"<<QString::number(currentFilePos);
        myplaylist->playCurrentFile();
        //mp->goturl(prevpos);
    }

}
void PlayerWindow::getMessage(QString msg)
{
    if (msg.contains("add-to-playlist"))
    {msg=msg.right(msg.length()-15);
        myplaylist->addFile(msg);
        this->setFocus(Qt::ActiveWindowFocusReason);
    }
    else
    {
        myplaylist->clearList();
        myplaylist->addFile(msg);
        myplaylist->playFirstFile();
        this->setFocus(Qt::ActiveWindowFocusReason);
    }
    this->activateWindow();
    this->raise();

}
void PlayerWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();

}
void PlayerWindow::clearingList()
{
    currentFile="";
    ui->action_Stop->trigger();
    ui->actionPlay_Next_File->setVisible(false);
    ui->actionPlay_Previous_File->setVisible(false);

}

void PlayerWindow::on_toolButton_loop_toggled(bool checked)
{
    settings->beginGroup("Playlist");
    settings->setValue("Loop",QString::number(checked));
    settings->endGroup();
    myplaylist->loop( checked);
}



void PlayerWindow::on_toolButton_shuffle_toggled(bool checked)
{
    settings->beginGroup("Playlist");
    settings->setValue("Shuffle",QString::number(checked));
    settings->endGroup();
    myplaylist->shuffle(checked);
}

void PlayerWindow::on_toolButton_playpre_clicked()
{
    ui->actionPlay_Previous_File->trigger();
}

void PlayerWindow::on_toolButton_playnext_clicked()
{
    ui->actionPlay_Next_File->trigger();

}
void PlayerWindow::playNextAfterFinish(int ec,bool stop)
{

    if(! forceplay)
    {if(mp->hasvideo())
        {
            videoWin->mplayerlayer->hide();
            videoWin->showeof(true);

            // videoWin->setShowVideo(false);
            // videoWin->setShowText(true);
        }
        if(!mp->isRestarting())
        {resetUi();
            if(!bstop)
            {myplaylist->playNextFile();
                qDebug()<<"restart"<<mp->isRestarting();
            }
        }
    }

}

void PlayerWindow::on_actionFolder_triggered()
{
    // ui->actionAdd_Folder->trigger();
    QString root=settings->value("Playlist/LastFolder","").toString();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    root,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    { myplaylist->clearList();
        myplaylist->addFolder(dir,w->filters,this);
        settings->beginGroup("Playlist");
        settings->setValue("LastFolder",dir);
        settings->endGroup();
        myplaylist->playFirstFile();
    }


}
void PlayerWindow::showMsgBox(QString msg)
{
    //ui->labelStatus->setText(ui->labelStatus->text()+" No Audio Stream No video Stream");
    //if(myplaylist->tab->rowCount()==1)
    //{qDebug()<<"++++++++++++++++++++++";
    //if(!settings->value("Playlist/Loop","0").toBool())
    // QMessageBox::information(this,qApp->applicationName(),msg,QMessageBox::Ok,QMessageBox::NoButton);
    // }
}
QString PlayerWindow::getFilter()
{
    //QString fila;
    //QString filv;
    //QString filp;
    //QString filmd;
    //QString filtermultimedia;
    //QFile file(qApp->applicationDirPath()+"/fmtsa.aud");
    //file.open(QIODevice::ReadOnly);
    //QTextStream stream(&file);
    // QString line;
    // do {line = stream.readLine();
    //     if (line=="eof")
    //        break;
    //     /*QFile file(qApp->applicationDirPath()+"/a/file."+line);
    // file.open(QIODevice::WriteOnly);
    // file.close();*/
    //     line="*."+line+" ";
    //      fila+=line;
    // } while (!line.isNull());
    // filmd=fila;
    //
    //file.close();
    //fila.append(");;");
    //fila.prepend("Audio files (");
    //QFile file1(qApp->applicationDirPath()+"/fmtsv.vid");
    //file1.open(QIODevice::ReadOnly);
    //QTextStream stream1(&file1);
    //
    // do {line = stream1.readLine();
    //     if (line=="eof")
    //        break;
    //     /*QFile file(qApp->applicationDirPath()+"/v/file."+line);
    // file.open(QIODevice::WriteOnly);
    // file.close();*/
    //     line="*."+line+" ";
    //      filv+=line;
    // } while (!line.isNull());
    //  filmd+=filv;
    //file1.close();
    //filv.append(");;");
    //filv.prepend("Video files (");
    //filp="Playlists (*.m3u *.pls);;Any file(*.*)";
    //filmd+=" *.m3u *.pls);;";
    //filmd.prepend("Media files (" );
    //qDebug()<<filmd+fila+filv+filp;
    //return filmd+fila+filv+filp;
    QString fpl;
    QStringList faul;
    QString fau;
    QString mul;
    faul <<"*.wav"
        <<"*.ac3"
       <<"*.flac"
      <<"*.mka"
     <<"*.mp3"
    <<"*.m4a"
    <<"*.aac"
    <<"*.mpc"
    <<"*.ogg"
    <<"*.oga"
    <<"*.ra"
    <<"*.wma"
    <<"*.spx"
    <<"*.mmf"
    <<"*.amr"
    <<"*.ape";
    for (int i=0;i<faul.count();i++)
    {if (i==faul.count())
            fau+=faul.at(i);
        else
            fau+=faul.at(i)+" ";

        mul+=faul.at(i)+" ";
    }
    fau.prepend("Audio files (");
    fau.append(");;");
    QStringList fvil;
    QString fvi;
    fvil     <<"*.wmv"
            <<"*.3gp"
           <<"*.asf"
          <<"*.avi"
         <<"*.dat"
        <<"*.dv"
       <<"*.divx"
      <<"*.ext"
     <<"*.flv"
    <<"*.ifo"
    <<"*.mkv"
    <<"*.mpg"
    <<"*.mpe"
    <<"*.mov"
    <<"*.mp4"
    <<"*.ogm"
    <<"*.ogv"
    <<"*.rm"
    <<"*.rmvb"
    <<"*.nsv"
    <<"*.smk"
    <<"*.ts"
    <<"*.vob";
    for (int i=0;i<fvil.count();i++)
    {if (i==fvil.count())
        {fvi+=fvil.at(i);
            mul+=fvil.at(i);
        }
        else
        { fvi+=fvil.at(i)+" ";
            mul+=fvil.at(i)+" ";
        }
    }
    fvi.prepend("Video files (");
    fvi.append(");;");
    mul.prepend("Mutimedia files (");
    mul.append(");;");
    fpl="Playlists (*.m3u *.pls);;Any file (*.*)";
    return mul+fvi+fau+fpl;
}

void PlayerWindow::showPictureFlow(QString path)
{
    if (picflow>0)
    {   picflow->close() ;

        delete  picflow;
    }
    picflow=new PictureFlow(panel);
    picflow->showPictures(true);
    //QObject::connect(picflow,SIGNAL(click ()  ),this,SLOT(toggleFullscreen()));
    QObject::connect(picflow,SIGNAL(showctxmenu(QContextMenuEvent*)  ),this,SLOT(showctxmenu(QContextMenuEvent*)));
    QObject::connect(picflow,SIGNAL(dblclick()),this,SLOT(pfdblClick() ));

    picflow->setSlideSize(QSize( 4*55,3*55));

    picflow->show();
    this->resize(900, 600);
    picflow->resize(videoWin->width(),videoWin->height());
    picflow->hideBackButton();
    //picflow->setReflectionEffect(picflow->PlainReflection);
    picflow->addPictureFolder(path);

    //PlainReflection,
    //BlurredReflection
    //ReflectionEffect eff;
    //picflow->setReflectionEffect( );
    //this->setCentralWidget(picflow);

    ui->dock_Playlist->setFloating(true);

}
void PlayerWindow::resizeVideo(int w,int hei)
{
    //mpseekView->setGeometry(QRect(0,ui->toolBarSeekBar->y()-99,128,98));

    if(picflow>0)
    {if(picflow->slideCount()>0)
            picflow->resize(w,hei);
    }
    if (piv->isVisible())
    {
        piv->move(videoWin->width()/2-piv->width()/2,videoWin->height()/2-piv->height()/2);

    }
    else
    { /*if (mp->hasaudio()&&!mp->hasvideo())
    {
     if(hei<3)
         this->videoWin->setPixmap(QPixmap());
      else
     {
       if (this->hascover)
              this->videoWin->mplayerlayer->show();
       else
            {qDebug()<<"gyfg";
           //this->videoWin->setPixmap(qApp->applicationDirPath()+"/"+"mcover.jpeg");

          }
        }

    }*/
    }

}

void PlayerWindow::on_actionSave_cover_art_triggered()
{
    this->saveCoverArt();
}
void PlayerWindow::useidxnplay()
{
    useidx=true;
    this->initMPlayer(currentFile,fileType);
}
QString PlayerWindow::getaudioFilter()
{
    QString fila;
    QFile file(qApp->applicationDirPath()+"/fmtsa.aud");

    if (file.exists())
    {file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        QString line;
        fila.prepend("Audio files (");
        do {line = stream.readLine();
            if (line=="eof")
                break;
            line=" *."+line;
            fila+=line;
        } while (!line.isNull());
        file.close();
        fila.append(")");
    }
    return fila;
}
void PlayerWindow::showctxmenu(QContextMenuEvent *event)
{
    this->contextMenuEvent(event);
}
void PlayerWindow::pfdblClick()
{
    this->toggleFullscreen();
}
void PlayerWindow::showpg()
{
    if (!pi->isVisible())
    {pi->show();
        pi->setAnimationDelay(25);
        pi->startAnimation();

    }
    if (!piv->isVisible())
    {   piv->show();
        piv->move(videoWin->width()/2-piv->width()/2,videoWin->height()/2-piv->height()/2);
        piv->setAnimationDelay(25);
        piv->startAnimation();
    }
}
void PlayerWindow::showerror(QString tex)
{
    videoWin->showErrorText("Oops!!!! No Audio,No Video!");

}
void  PlayerWindow::showEvent ( QShowEvent * event )
{
    if (piv->isVisible())
    {
        piv->move(videoWin->width()/2-piv->width()/2,videoWin->height()/2-piv->height()/2);

    }
}

void PlayerWindow::on_actionEdit_Playlist_triggered()
{
    // ui->dock_Playlist->show();
    /* ui->dock_Playlist->setFloating(true);
    ui->dock_Playlist->show();
    ui->dock_Playlist->resize(310,400);*/
    if (!ui->dock_Playlist->isVisible())
    {
        ui->dock_Playlist->setFloating(true);

        ui->dock_Playlist->resize(310,400);
        if (desktop->width()-100>this->width()+this->x())
        {ui->dock_Playlist->move(this->width()+this->x()+8,this->y());
        }

        ui->dock_Playlist->show();
    }

}

void PlayerWindow::on_actionAdd_File_to_pl_triggered()
{
    ui->actionAdd_file->trigger();
}

void PlayerWindow::on_actionAdd_Folder_to_pl_triggered()
{
    ui->actionAdd_Folder->trigger();
}
void PlayerWindow::playlistVisibility(bool vis)
{
    settings->beginGroup("Playlist");
    settings->setValue("Visible",QString::number(vis));
    settings->endGroup();
}

void PlayerWindow::on_actionTwins_triggered()
{
    if(mp)
        mp->twins(ui->actionTwins->isChecked());
}

void PlayerWindow::on_actionSide_view_triggered()
{
    if(mp)
        mp->sideview(ui->actionSide_view->isChecked());
}
void PlayerWindow::startingPlaybackframe()
{ if (fr)
    {fr->pause();
    }
    //lab->setText(frpos);
    //lab->drawTitle(frpos);


}

void PlayerWindow::on_actionAudio_extrctor_triggered()
{
    axdlg= new audioextDialog(this);
    QObject::connect(axdlg,SIGNAL(showfile(QString,QString)),this,SLOT(winExplorer(QString,QString)));
    axdlg->show();

}

void PlayerWindow::on_toolButtonSpeed_clicked()
{
    ui->actionNormal_Speed->trigger();
}
void PlayerWindow::startProgressiveStreaming()
{ /*ui->action_Stop->trigger();
    isstreaming=true;
    this->playThisfile("D:/rphMPFE(4)/rphMPFE/thetrain01(www.songs.pk).mp3");
    mp->initMediaInfo();*/
}
void PlayerWindow::wgetDownload()
{
    wget = new QProcess(this);
    QStringList arg;
    arg <<"-N"<<"-c"<<"http://link.songs.pk/song.php?songid=4746";
    wget->start(qApp->applicationDirPath()+ "/wget.exe",arg);
    isdownloading=true;
}
void PlayerWindow::streamingDuration(float dur)
{
    qDebug()<<"durrrrrrrrrrrrrrrrrr"<<dur;
    streamingDur=dur;
}

void PlayerWindow::on_actionIncrease_Zoom_triggered()
{
    if (mp)
    {
        if (zoomfact<2.0)
        {zoomfact+=0.01;
            videoWin->setZoom(zoomfact);
        }

    }
}

void PlayerWindow::on_actionDecrease_Zoom_triggered()
{
    if (mp)
    {
        if (zoomfact>0.5)
        {zoomfact-=0.01;
            videoWin->setZoom(zoomfact);
        }

    }
}

void PlayerWindow::on_actionMove_Left_triggered()
{
    videoWin->moveLeft();
}

void PlayerWindow::on_actionMove_Right_triggered()
{
    videoWin->moveRight();
}

void PlayerWindow::on_actionMove_Up_triggered()
{
    videoWin->moveUp();
}

void PlayerWindow::on_actionMove_Down_triggered()
{
    videoWin->moveDown();
}

void PlayerWindow::on_actionIncrease_Video_quality_triggered()
{
    if (mp)
    {
        mp->fspp(ui->actionIncrease_Video_quality->isChecked());
    }
}

void PlayerWindow::on_actionDefault_triggered()
{
    if (mp)
    {mp->setfps(0);
    }
}

void PlayerWindow::on_actionChange_framerate_triggered()
{
    if (mp)
    { bool ok;
        double val = QInputDialog::getDouble(this, tr("Frame rate"),
                                             tr("Enter Frame rate(1-100):"),40,1,100,1,&ok,0);


        mp->setfps(val);
    }
}


void PlayerWindow::on_actionDefault_zoom_triggered()
{
    if (mp)
    {
        this->videoWin->setZoom(1.0);
    }
}

void PlayerWindow::on_toolButtonplaylist_clicked()
{
    ui->actionShowpl->trigger();
}

void  PlayerWindow::updatevideovindow()
{
    if (mp)
    {//qDebug()<<"check";

        if (mp->hasaudio() && !mp->hasvideo())
        {
            //  this->setGeometry(this->videoWin->x(),this->videoWin->y(),450,145);

            this->videoWin->mplayerlayer->hide();
        }
        if (mp->hasvideo())
        {
            this->videoWin->mplayerlayer->show();
        }
        if (!mp->hasvideo()&&!mp->hasaudio())
        {
            this->windowTimer->stop();;
        }
        //  if (mp->videoheight()==0)
        // this->resize(450,145);
    }

}

void PlayerWindow::on_actionAudio_Converter_triggered()
{
    aucdlg= new audioconvDialog(this);
    QObject::connect(aucdlg,SIGNAL(showfile(QString,QString)),this,SLOT(winExplorer(QString,QString)));
    aucdlg->show();

}

void PlayerWindow::on_actionSmallmode_triggered()
{
    if (ui->dock_Playlist->isVisible())
        ui->dock_Playlist->hide();
    if (ui->dockBrowser->isVisible())
        ui->dockBrowser->hide();
    if (ui->dock_log->isVisible())
        ui->dock_log->hide();
    if (ui->dock_Filter->isVisible())
        ui->dock_Filter->hide();

    this->resize(450,0);

}

void PlayerWindow::on_actionCopy_Audio_CD_triggered()
{
    //auripdlg= new ripDialog(this);
    //auripdlg->show();
}
void PlayerWindow::searchYT(QString searchTerm, int engine)
{



}

void PlayerWindow::on_actionInternet_Radio_triggered()
{
    if (!radiodlg)
    {
        // radiodlg=new RadioDialog(this);
        //connect(radiodlg,SIGNAL(playurl(QString)),this,SLOT(playurl(QString)));
    }

    //radiodlg->show();
}
void PlayerWindow::playSCUrl(QString url,QString desc)
{
    myplaylist->clearList();
    myplaylist->addFile(url);
    myplaylist->playFirstFile();
}
void PlayerWindow::playYTUrl(const QMap<int, QString> &qualityMap, QString title)
{
    QString url;
    //    switch(pref->playback_quality)
    //    {
    //    case YTDialog::FullHD:
    //        url = qualityMap.value(YTDialog::FullHD, QString());
    //        if(!url.isNull()) break;
    //    case YTDialog::HD:
    //        url = qualityMap.value(YTDialog::HD, QString());
    //        if(!url.isNull()) break;
    //    case YTDialog::Normal:
    //        url = qualityMap.value(YTDialog::Normal, QString());
    //    }
    // case YTDialog::Normal:
    //url = qualityMap.value(YTDialog::LowFlv, QString());
    // qDebug()<<"you tube url"<<url;
    // myplaylist->clearList();
    //myplaylist->addFile(url);
    //myplaylist->playFirstFile();


}
void PlayerWindow::addingfile()
{
    if (!ui->actionPlay_Next_File->isVisible())
    {if (myplaylist->tab->rowCount()>1)
        {ui->actionPlay_Next_File->setVisible(true);
            ui->actionPlay_Previous_File->setVisible(true);
        }
    }

}
void PlayerWindow::removingfile()
{
    if (ui->actionPlay_Next_File->isVisible())
    {if (myplaylist->tab->rowCount()==1)
        {ui->actionPlay_Next_File->setVisible(false);
            ui->actionPlay_Previous_File->setVisible(false);
        }
    }
}
void PlayerWindow::ShowStop()
{
    ui->action_Stop->setVisible(true);
    ui->action_Stop->setEnabled(true);
}
void PlayerWindow::image2Pixmap(QImage &img,QPixmap &pixmap)
{
    // Convert the QImage to a QPixmap for display
    pixmap = QPixmap(img.size());
    QPainter painter;
    painter.begin(&pixmap);
    painter.drawImage(0,0,img);
    painter.end();
}
void PlayerWindow::resizeVideoWindow(int w,int h)
{

    videoWin->setAspect((float)w/h);
    this->resize(w,h);
}
void PlayerWindow::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {

        if(event->y()<videoWin->height()+this->menuBar()->height()){
            dragPosition = event->globalPos() - frameGeometry().topLeft();
        }
        event->accept();
    }

}

void PlayerWindow::on_toolButtonFblike_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.facebook.com/exmplayer"));
}

#ifdef Q_OS_WIN
/* Disable screensaver by event */
bool PlayerWindow::winEvent ( MSG * m, long * result ) {
    //qDebug("BaseGui::winEvent");
    if (m->message==WM_SYSCOMMAND) {
        if ((m->wParam & 0xFFF0)==SC_SCREENSAVE || (m->wParam & 0xFFF0)==SC_MONITORPOWER) {

            return true;
        } else {

            return false;
        }
    }

    return false;
}
#endif


void PlayerWindow::on_sliderSeekFullSc_actionTriggered(int action)
{

    this->playerTimer->stop();
    mp->goturl(sliderSeekFullSc->value());
    this->playerTimer->start();

}
void PlayerWindow::resizeEvent ( QResizeEvent * event )
{
    if (ui->menuBar->height()==ui->toolBarSeekBar->y()){
        if(mp){
            if(mp->hasaudio()&&!mp->hasvideo()){
                setMinimumSize(450,this->height());
                qDebug()<<"resize to 450"<<this->height();
            }
            else
            {
                setMinimumSize(450,this->height());
            }
        }
    }



}

void PlayerWindow::on_actionAdvanced_Info_triggered()
{
    advInfoDlg=new AdvancedInfoDialog(this);
    advInfoDlg->setMPlayer(mp);
    advInfoDlg->show();
}
