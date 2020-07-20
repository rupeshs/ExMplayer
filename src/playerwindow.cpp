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

#include "playerwindow.h"
#include "ui_playerwindow.h"
#include "paths.h"
#include <QDesktopWidget>

QDesktopWidget *desktop;
QDesktopServices *mycomputer;


PlayerWindow::PlayerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayerWindow)
{

    QCoreApplication::addLibraryPath(qApp->applicationDirPath()+"/imageformats");
    starting=true;
    mp=new mplayerfe(this,this);
    QString cmd;
    ui->setupUi(this);


    qDebug()<<QDir::tempPath();
    this->disableStylesheet();
    qDebug()<< "Config path :"<<Paths::configPath();
    settings=new QSettings(Paths::configPath()+"/ExMplayer.ini",QSettings::IniFormat,this);

    if (settings->value("Skin/style","aqua").toString()=="wood")
    {
     #if QT_VERSION < 0x050000
           QApplication::setStyle(new NorwegianWoodStyle);
     #endif
    }
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



#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
     QString picfolder=mycomputer->storageLocation(QDesktopServices::PicturesLocation);
 #else
     QString picfolder=QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
 #endif
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
    bPlayListDrop=false;

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

    idleTimer = new QTimer(this);
    idleTimer->start(4000);
    installEventFilter(this);

    connect(idleTimer, SIGNAL(timeout()), this, SLOT(userInactive()));

    //Update check
    if(settings->value("Updates/Automatic","1").toInt()==1)
    {

        QDateTime curDt= QDateTime::currentDateTime();
        if(curDt.date().day()%7==0)
        {
            updCheckDlg =new updateCheckDlg(this);
        }
    }

    this->setMinimumHeight(1);
    calculateHeight();


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
    curSubTitleTrack=0;
    ui->mpconsole->clear();
    videoWin->mplayerlayer->hide();
    windowTimer->setInterval(1);
    windowTimer->start();
    artisttext="";
    albumtext="";
    yeartext="";
    //movie->stop();
    zoomfact=1.0;
    usingfidx=false;

    if (picflow>0)
    {
        picflow->close() ;
        delete  picflow;
    }
    videoWin->showErrorText("");
    videoWin->showeof(false);
    videoWin->mplayerlayer->setRepaintBackground(true);
    ui->toolButtonInfo->setIcon((QIcon(":/images/info-btn.png")));



    mp=new mplayerfe(this,this);
    if(currentFilePos!=0)
    {
        if (currentFilePos>0)
        {
            mp->setInitSeekPos(currentFilePos);
        }

        currentFilePos=0;

    }
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
     QString picfolder=mycomputer->storageLocation(QDesktopServices::PicturesLocation);
 #else
     QString picfolder=QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
 #endif
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
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
    mp->setaudiodriver(0);
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
    QObject::connect(mp,SIGNAL(addSubtitletrack(QStringList)),this,SLOT(addSubtitletrack(QStringList)));

    //QObject::connect(mp,SIGNAL(show_endmessage(QString)),ui->labelStatus,SLOT(setText(QString)));
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
    QObject::connect(mp,SIGNAL(disableSeek()),this,SLOT(hideSeek()));
    QObject::connect(mp,SIGNAL(hidepg()),pi,SLOT(stopAnimation()));
    QObject::connect(mp,SIGNAL(hidepg()),piv,SLOT(stopAnimation()));
    QObject::connect(mp,SIGNAL(showerrortext(QString)),this,SLOT(showerror(QString)));
    QObject::connect(mp,SIGNAL(showvideoui()),videoWin->mplayerlayer,SLOT(show()));
    //QObject::connect(mp,SIGNAL(resizeVideoWindow(int,int)),this,SLOT(resizeVideoWindow(int,int)));
    //QObject::connect(mp,SIGNAL(eof()),this,SLOT(resetUi()));
    //QObject::connect(mp,SIGNAL(showmsgBox(QString)),this,SLOT(showMsgBox(QString)));

    actPrgsIndicator->setVisible(true);
    isstreaming=false;
    ui->actionStep1_fm->setEnabled(true);
    ui->actionStep2_fm->setEnabled(true);

    if( cdlg)
        cdlg->setMp(mp);
    //Add subtitle code page
    if (settings->value("Subtitles/UseCodePage","0").toInt()!=0)
    {
        QString lanPg=settings->value("Subtitles/CodePage","Western European Languages").toString();
        mp->setSubtitleCodePage(Languages::encodings().key(lanPg));
    }
    mp->enableClosedCaption(true);
    qDebug()<<ui->actionEnable_3D->isChecked();
    if (ui->actionEnable_3D->isChecked())
    {
        QString inStereoFmt, outStereoFmt;
        //Get 3D input format
        foreach(QAction* sInAct, actiongroupInFormatStereo->actions())
        {
            if(sInAct->isChecked())
                inStereoFmt=sInAct->iconText();
        }

        //Get 3D output format
        foreach(QAction* sOutAct, actiongroupOutFormatStereo->actions())
        {
            if(sOutAct->isChecked())
                outStereoFmt=sOutAct->iconText();
        }

        qDebug()<<"3D in: "<<inStereoFmt <<" Out :"<<outStereoFmt;
        //Transform 3D
        if (mp)
            mp->StartUp3D(inStereoFmt,outStereoFmt);
    }
    if ((ui->actionVolume_Boost->isChecked()))
    {
        mp->setVolumeBoost(settings->value("Audio/VolumeBoost","500").toInt());
    }

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
    int enSoftEq=settings->value("Video/EnableSoftEQ","0").toInt();
    if (enSoftEq==2)
    {
        mp->configureSoftEqualiser(true);
    }
    if (settings->value("Audio/mute","0").toInt()==1)
    {
        mp->play(file,0);
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

    //ui->labelStatus->setText(tr("Opening..."));
    ui->labelCurrentPosition->setText("Opening...");



    iseof=false;
    bplay=false;
    bstop=false;
    recentFilesMenu->addRecentFile(currentFile);
    mutex.unlock();


}

void  PlayerWindow::setupMyUi()
{
    bool bMin=true;

#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
    ui->actionWinamp_Dsp->setVisible(false);
    screensaverInhibit=new Inhibitor();
    screensaverInhibit->activateInhibit();
# endif


    ui->actionInternet_Radio->setVisible(false);
    ui->actionCopy_Audio_CD->setVisible(false);

    windowTimer = new QTimer(this);
    QObject::connect(windowTimer, SIGNAL(timeout()), this,SLOT(updatevideovindow()));


    videoWin=new  MplayerWindow(this,0);
    videoWin->setAlignment(Qt::AlignCenter);
    videoWin->allowVideoMovement(true);

    videoWin->showLogo(true);


    //videoWin->mplayerlayer->hide();
    videoWin->showLogo(false);

    panel = new QWidget( this );
    panel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    panel->setMinimumSize( QSize(1,1) );
    panel->setFocusPolicy( Qt::StrongFocus );
    // panel
    panel->setAutoFillBackground(true);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(videoWin);
    videoWin->setMinimumSize( QSize(1,1) );
    panel->setLayout(layout);
    //panel->hide();
    //videoWin->hide();

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
    ui->toolBarStatus->setVisible(true);
    ui->toolButtonVolumeBoost->setToolTip("Turn <b>ON</b> volume boost");

    ui->toolButtonStereoVideo->setToolTip("Turn <b>ON</b> 3D Video");

    if (settings->value("MainWindow/InfoBar","0").toInt()==0)
    {
        ui->toolBarStatus->setVisible(false);
        ui->actionInfobar->setChecked(false);
    }
    else
    {
        ui->toolBarStatus->setVisible(true);
        ui->actionInfobar->setChecked(true);
    }
    if (settings->value("MainWindow/MiniMode","0").toInt()==0)
    {
        this->statusBar()->setVisible(true);
        ui->actionMini_Mode->setChecked(false);
    }
    else
    {
        this->statusBar()->setVisible(false);
        ui->actionMini_Mode->setChecked(true);

    }
    tmpxpos=0;
    tmpypos=0;
    xpos=0;
    ypos=0;
#ifdef Q_OS_WIN
    winscreensaver =new WinScreenSaver();
    winscreensaver->disable();

    //Prevent the sleep idle time-out.
    QLibrary library("kernel32.dll");
    if (!library.load())
        qDebug("kernel32 Library loading failed.");
    else{

        qDebug("kernel32 Library loaded");
        typedef uint (*SetThreadExecutionState)(uint esFlag);
        SetThreadExecutionState setState = (SetThreadExecutionState)library.resolve("SetThreadExecutionState");
        //flags
        //ES_CONTINUOUS
        //0x80000000
        //ES_DISPLAY_REQUIRED
        //0x00000002
        //ES_SYSTEM_REQUIRED
        //0x00000001

        setState(0x80000000|0x00000002|0x00000001);
    }

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
    QObject::connect(ui->dock_Playlist,SIGNAL(sgdropEvent(QDropEvent*)),this,SLOT(dropPlayListEvent(QDropEvent*)));
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

    /***********************************************/
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
    pi->setColor(QColor(qRgb(60,150,255) ));
    piv = new QProgressIndicator(videoWin);
    piv->ShowGif();


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
    ui->statusBar->addPermanentWidget(ui->labAD);
    ui->statusBar->addPermanentWidget(ui->lcdCurPos);
    ui->statusBar->addPermanentWidget(ui->lcdDuration);
    //ui->statusBar->addPermanentWidget(ui->lcdDuration);

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
    if (!bMin)
    {
        ui->toolBarSeekBar->addWidget(ui->toolButtonRewind);
        ui->toolBarSeekBar->addWidget(ui->sliderSeek);
        toolButtonForwardAction=ui->toolBarSeekBar->addWidget(ui->toolButtonForward);
        ui->toolBarSeekBar->addAction(ui->actionFullscreen);

        ui->toolBarSeek->addAction(ui->action_Play_Pause);
        ui->toolBarSeek->addAction(ui->action_Stop);
        ui->toolBarSeek->addAction(ui->actionPlay_Previous_File);
        ui->toolBarSeek->addAction(ui->actionPlay_Next_File);
        ui->toolBarSeek->addWidget(ui->toolButtonVolume);
        ui->toolBarSeek->addWidget(ui->sliderVolume);
        ui->toolBarSeek->addWidget(ui->toolButtonVolumeBoost);
        ui->toolBarSeek->addAction(ui->action_Equalizer);
        ui->toolBarSeek->addWidget(ui->toolButtonplaylist);
        ui->toolBarSeek->addWidget(ui->toolButtonFblike);
        ui->toolBarSeek->addWidget(ui->toolButtonSpeed);
        ui->toolBarSeek->addWidget(ui->toolButtonStereoVideo);
        ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_off.png"));
        ui->toolButtonVolumeBoost->setIcon(QIcon(":/images/volboost_off.png"));


    }
    else{

        ui->toolBarSeekBar->addAction(ui->action_Play_Pause);
        ui->toolBarSeekBar->addAction(ui->action_Stop);

        ui->toolBarSeekBar->addWidget(ui->labelCurrentPosition);

        actPrgsIndicator=ui->toolBarSeekBar->addWidget(pi);
        actPrgsIndicator->setVisible(false);

        ui->toolBarSeek->addWidget(ui->toolButtonRewind);
        ui->toolBarSeekBar->addWidget(ui->sliderSeek);
        toolButtonForwardAction=ui->toolBarSeek->addWidget(ui->toolButtonForward);


        ui->toolBarSeekBar->addWidget(ui->labelDuration);

        ui->toolBarSeekBar->addWidget(ui->toolButtonVolume);
        ui->toolBarSeekBar->addWidget(ui->sliderVolume);
        ui->toolBarSeekBar->addWidget(ui->toolButtonVolumeBoost);

        ui->toolBarSeekBar->addAction(ui->actionFullscreen);
        //this->addToolBarBreak();


        ui->toolBarSeek->addAction(ui->actionPlay_Previous_File);
        ui->toolBarSeek->addAction(ui->actionPlay_Next_File);



        ui->toolBarSeek->addAction(ui->action_Equalizer);
        ui->toolBarSeek->addWidget(ui->toolButtonplaylist);
        ui->toolBarSeek->addWidget(ui->toolButtonFblike);
        ui->toolBarSeek->addWidget(ui->toolButtonStereoVideo);
        ui->toolBarSeek->addWidget(ui->toolButtonInfo);
        ui->toolButtonInfo->setIcon(QIcon(":/images/info-btn.png"));
        ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_off.png"));
        ui->toolButtonVolumeBoost->setIcon(QIcon(":/images/volboost_off.png"));

        ui->statusBar->addWidget(ui->toolBarSeek);
        ui->lcdCurPos->setVisible(false);
        ui->lcdDuration->setVisible(false);
        ui->toolBarSeek->addWidget(ui->labelStatus);
        //ui->toolBarSeek->hide();
        //ui->statusBar->hide();
        //ui->labelStatus->hide();
    }


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

    actiongroupInFormatStereo=new QActionGroup(this);
    actiongroupInFormatStereo->addAction(ui->actionSide_by_side_left_first);
    actiongroupInFormatStereo->addAction(ui->actionSide_by_side_right_first);
    actiongroupInFormatStereo->addAction(ui->actionSide_by_side_half_width_left_first);
    actiongroupInFormatStereo->addAction(ui->actionSide_by_side_half_width_right_first);

    actiongroupInFormatStereo->addAction(ui->actionAbove_below_left_first);
    actiongroupInFormatStereo->addAction(ui->actionAbove_below_right_first);
    actiongroupInFormatStereo->addAction(ui->actionAbove_below_half_height_left_first);
    actiongroupInFormatStereo->addAction(ui->actionAbove_below_half_height_right_first);

    QObject::connect(actiongroupInFormatStereo,SIGNAL(triggered(QAction*)),this,SLOT(changeStereoscopicView(QAction*)));

    actiongroupOutFormatStereo=new QActionGroup(this);
    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_red_cyan_dubois);
    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_red_cyan_color);
    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_red_cyan_half_color);
    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_red_cyan_gray);

    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_green_magenta_color);
    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_green_magenta_half_color);
    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_green_magenta_gray);

    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_yellow_blue_color);
    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_yellow_blue_half_color);
    actiongroupOutFormatStereo->addAction(ui->actionAnaglyph_yellow_blue_gray);

    actiongroupOutFormatStereo->addAction(ui->actionInterleave_rows_left_first);
    actiongroupOutFormatStereo->addAction(ui->actionInterleave_rows_right_first);

    actiongroupOutFormatStereo->addAction(ui->actionMono_left);
    actiongroupOutFormatStereo->addAction(ui->actionMono_right);

    QObject::connect(actiongroupOutFormatStereo,SIGNAL(triggered(QAction*)),this,SLOT(changeStereoscopicView(QAction*)));


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
    //QObject::connect(videoWin, SIGNAL(resizeVideo(int,int)), this,SLOT(resizeVideo(int,int)));

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




    if (settings->value("Video/3D","0").toInt()==1)
    {
        ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_on.png"));
        ui->toolButtonStereoVideo->setToolTip("Turn <b>OFF</b> 3D video");
        ui->actionEnable_3D->setChecked(true);


    }

    if (settings->value("Audio/Boost","0").toInt()==1)
    {
        ui->toolButtonVolumeBoost->setIcon(QIcon(":/images/volboost_on.png"));
        ui->actionVolume_Boost->setChecked(true);
        ui->toolButtonVolumeBoost->setToolTip("Turn <b>OFF</b> volume boost");

    }
    ui->actionSide_by_side_left_first->setChecked(true);
    ui->actionAnaglyph_red_cyan_dubois->setChecked(true);
    ui->labelStatus->setText(tr(""));
    videoWin->showLogo(true);

    /*Easter eggs */

    QDateTime curDt= QDateTime::currentDateTime();
    /* New year greeting*/
    if(curDt.date().month()==1)
    {
        if (curDt.date().day()==1)
        {
            QString strGreeting=QString("Happy New Year! <b>")+QString::number(curDt.date().year())+QString("</b>");
            qDebug()<<"Happy New Year! ";
            //ui->labelStatus->setText(strGreeting);
            ui->labelCurrentPosition->setText(strGreeting);

        }
    }

    /* Christmas  greeting*/
    if(curDt.date().month()==12)
    {
        if (curDt.date().day()==25||curDt.date().day()==26)
        {
            //ui->labelStatus->setText("Merry Christmas!");
            ui->labelCurrentPosition->setText("Merry Christmas!");

        }
    }

    /*End of Easter egg*/

    actiongroupShareExMplayer=new QActionGroup(this);
    actiongroupShareExMplayer->addAction(ui->actionFacebook);
    actiongroupShareExMplayer->addAction(ui->actionTwitter);
    actiongroupShareExMplayer->addAction(ui->actionGmail);
    actiongroupShareExMplayer->addAction(ui->actionYahoo);
    actiongroupShareExMplayer->addAction(ui->actionHotmail);

    QObject::connect(actiongroupShareExMplayer,SIGNAL(triggered(QAction*)),this,SLOT(shareWithFriends(QAction*)));

    int w = ui->labelCurrentPosition->fontMetrics().width(ui->labelCurrentPosition->text());
    ui->labelCurrentPosition->setMinimumWidth(w/2);
    ui->labelDuration->setMinimumWidth(w/2);


}
void PlayerWindow::resetUi()
{
    ui->labVD->setText("");
    ui->labAD->setText("");
    ui->actionWatch_as_2D_video->setChecked(false);
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
    ui->labelDuration->setText("--:--");
    ui->labelCurrentPosition->setText("<b>  --:--  </b>");

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
    ui->labelCurrentPosition->setText("--:--");

    actPrgsIndicator->setVisible(false);
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
        //ui->labelStatus->hide();
        //ui->labelStatus->setText(tr("Playing"));
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
            astr+="M ";
        else if (mp->getAudioNch().toInt()==2)
            astr+="S ";
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
            if (!actiongroupSubtitleTrack)
            {
                actiongroupSubtitleTrack=new QActionGroup(this);
                actiongroupSubtitleTrack->addAction(ui->actionStNone);
            }



            actiongroupVideoTrack=new QActionGroup(this);

            QObject::connect(actiongroupSubtitleTrack,SIGNAL(triggered(QAction*)),this,SLOT(changeSubTitles(QAction*)));

            if( mp->listSubtitleTrack.count()>0)
            {   ui->actionStNone->setDisabled(false);
                ui->actionStNone->setChecked(false);
                qDebug()<<"Found "<<QString::number(mp->listSubtitleTrack.count())<<" Subtitle tracks";
                for (int i=0;i<mp->listSubtitleTrack.count();i++)
                {
                    actiongroupSubtitleTrack->addAction( ui->menuSelect->addAction("Track "+QString::number(i+1)));
                    actiongroupSubtitleTrack->actions().last()->setCheckable(true);
                }
                if(actiongroupSubtitleTrack->actions().count()>1)
                    actiongroupSubtitleTrack->actions().at(1)->setChecked(true);
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

        if (mp->duration()<3600)
            ui->labelDuration->setText("<b>  "+mp->tduration().toString("hh:mm:ss").mid(3)+"  </b>");
        else
            ui->labelDuration->setText("<b>  "+mp->tduration().toString("hh:mm:ss")+"  </b>");

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
            if (this->width()>PLAYER_WIDTH ||this->height()>145)
            {
                if (!isfullscreen)
                {this->resize(PLAYER_WIDTH,145);
                    qDebug()<<"Offset height -"<<(ui->menuBar->height()+ui->menuBar->y())-ui->toolBarSeekBar->y();
                    this->resize(PLAYER_WIDTH,this->height()+(ui->menuBar->height()+ui->menuBar->y())-ui->toolBarSeekBar->y());
                    qDebug()<<"Adjusted offset -"<<(ui->menuBar->height()+ui->menuBar->y())-ui->toolBarSeekBar->y();
                }
            }

            //#ifdef Q_OS_WIN
            ui->actionAudioDisable->setEnabled(false);
            /***********************************************************
                                Cover Art
            ************************************************************/
#ifdef Q_OS_WIN
 #ifdef TAGLIB
            TagLib::FileRef  f(currentFile.toStdString().c_str());
            QCoverArt coverArt;

            try {
                if(coverArt.GetCover(f))
                {

                    QImage img=coverArt.getCoverImage();
                    if (img.height()>0 &&img.width()>0)
                    {//QMessageBox::critical(this,qApp->applicationName(),QString::number(img.width()),QMessageBox::Ok,QMessageBox::Cancel);
                        cover = new QPixmap(QPixmap::fromImage(img,Qt::AutoColor));

                        videoWin->setPixmap(QPixmap::fromImage(img,Qt::AutoColor).scaled(170,128,Qt::IgnoreAspectRatio, Qt::FastTransformation));

                        hascover=true;
                        cover->save(QDir::tempPath()+"/"+"mcover.jpeg",0,-1);
                        ui->actionSave_cover_art->setEnabled(true);
                        QString coverPath=QDir::tempPath()+"/mcover.jpeg";
                        ui->toolButtonInfo->setIcon(QIcon(coverPath));
                    }
                    //ui->toolButtonInfo->setIconSize(QSize(60,22));


                }



            }
            catch (...)
            {
                QMessageBox::warning(0,
                                     tr("An unexpected error occurred"),
                                     tr("This is likely a bug."));

            }
#endif
#endif

            /************************************************************/

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
    //videoWin->mplayerlayer->hide();

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
            if (mp->duration()>0)
            {ui->sliderSeek->setEnabled(true);
                if(sliderSeekFullSc)
                    sliderSeekFullSc->setEnabled(true);

            }
            else
            {
                ui->sliderSeek->setEnabled(false);
                if(sliderSeekFullSc)
                    sliderSeekFullSc->setEnabled(false);

            }
        }
        else
        {

            ui->sliderSeek->setEnabled(false);
            if(sliderSeekFullSc)
                sliderSeekFullSc->setEnabled(false);

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

        if (mp->duration()>0)
        {if( mp->isstarted()){
                ui->sliderSeek->setValue((mp->curpos()/mp->duration())*100);
                if(sliderSeekFullSc)
                    sliderSeekFullSc->setValue((mp->curpos()/mp->duration())*100);
                ui->lcdCurPos->display(mp->tcurpos().toString());


                QString curtPos=mp->tcurpos().toString("hh:mm:ss");
                //qDebug()<<curtPos.mid(3);
                if (mp->duration()<3600)
                    ui->labelCurrentPosition->setText("<b>  "+curtPos.mid(3)+"  </b> ");
                else
                    ui->labelCurrentPosition->setText("<b>  "+curtPos+"  </b> ");
                if (isfullscreen){
                    lcdCurPosFullSc->display(mp->tcurpos().toString());
                    lcdDurationFullSc->display(mp->tduration().toString());
                    //qDebug()<<  mp->tduration().toString();
                }
                int w = ui->labelCurrentPosition->fontMetrics().width(ui->labelCurrentPosition->text());
                ui->labelCurrentPosition->setMinimumWidth(w/2);
                ui->labelDuration->setMinimumWidth(w/2);
                //qDebug() << Q_FUNC_INFO << w;


            }
        }
        else
        {
            ui->sliderSeek->setEnabled(false);
            if(sliderSeekFullSc)
                sliderSeekFullSc->setEnabled(false);
            ui->lcdDuration->display("--:--:--");


            ui->lcdCurPos->display(mp->tcurpos().toString());
            if (isfullscreen){
                lcdCurPosFullSc->display(mp->tcurpos().toString());
                lcdDurationFullSc->display(mp->tduration().toString());
            }


        }

    }

    /*if (mp->state()==mp->PLAYING)
    {if(ui->labelStatus->text()=="Playing")
      ui->labelStatus->setText("Playing.");
     else if(ui->labelStatus->text()=="Playing.")
       ui->labelStatus->setText("Playing..");
     else if(ui->labelStatus->text()=="Playing..")
       ui->labelStatus->setText("Playing...");
     else if(ui->labelStatus->text()=="Playing...")
       ui->labelStatus->setText("Playing");
       ui->labelStatus->setText("Playing...");
    }*/
    //if (mp->state()==mp->PAUSED)
    // ui->labelStatus->setText("Paused.");



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
    mp->seek(ui->sliderSeek->value());
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
   /*if (mp->hasvideo())
    {if (value>90)
        mp->usercommand("af_cmdline volnorm ");
    else if (value<89)
         mp->usercommand("af_cmdline volume 0,1");
    }*/

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
    /*ui->sliderVolume->setGeometry(0,0,0,20);
    QPropertyAnimation *animation = new QPropertyAnimation(ui->sliderVolume, "size");
    animation->setDuration(1000);
    animation->setEndValue(QSize(1,20));
    animation->setEndValue(QSize(70,20));
    animation->start();*/
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
        //qDebug()<<QString::number(mp->state());
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
    {
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
     QString moviefolder=mycomputer->storageLocation(QDesktopServices::MoviesLocation);

 #else
     QString moviefolder=QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
 #endif
        fileName = QFileDialog::getOpenFileNames(this,
                                               tr("Open media file(s)"),
                                               moviefolder,
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
    ui->sliderVolume->setValue( ui->sliderVolume->value()+5);
}

void PlayerWindow::on_action_Decrease_volume_triggered()
{
    ui->sliderVolume->setValue( ui->sliderVolume->value()-5);
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
    {

        if (mp->duration()<3600)
            ui->labelDuration->setText("<b>  "+mp->tduration().toString("hh:mm:ss").mid(3)+"  </b>");
        else
            ui->labelDuration->setText("<b>  "+mp->tduration().toString("hh:mm:ss")+"  </b>");

        ui->lcdDuration->display(mp->tduration().toString());

    }
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
            this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
        else
        {
            this->setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
        }
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
        {osdlevel=1 ;
            ui->action_osd1->setChecked(true);
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
    winExplorer(QString(""),arg);
#elif defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
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
    rmenu.addMenu(ui->menu3D);
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
    if (index >= 0 && index < 18)
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
    {
        if (!ui->actionStNone->isEnabled())
            ui->actionStNone->setEnabled(true);
        if(actiongroupSubtitleTrack)
        {   actiongroupSubtitleTrack->addAction( ui->menuSelect->addAction("Track "+QString::number(sl.count())));
            actiongroupSubtitleTrack->actions().last()->setCheckable(true);
        }
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
    if( this->actiongroupSubtitleTrack->actions().indexOf(act)==0)
    {
        if(mp)
            mp->switchSubtitle(-1);
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
    {//mp->unloadsub();
        ui->actionStUnload->setEnabled(false);

        completeRestart() ;
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
    {
        ypos=e->y();
        xpos=e->x();




        //Not used from v3.1
        if(e->y()<(desktop->height() - fullScreenControls->height()))
        {


            if (fullScreenControls->geometry().top()==desktop->screen()->height()-70)
            {

            }
        }
        else
        {


            if (!fullScreenControls->isVisible())
            {
                this->unsetCursor();


                fullScreenControls->show();
#ifdef Q_OS_WIN
                QPropertyAnimation *animation = new QPropertyAnimation(fullScreenControls, "geometry");
                animation->setDuration(500);
                animation->setStartValue(QRect(leftSide,desktop->screen()->height(),fullScreenControlWidth,70));
                animation->setEndValue(QRect(leftSide,desktop->screen()->height()-70,fullScreenControlWidth,70));
                animation->start();
#endif


            }
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
            // qDebug()<<"checked "<<ui->action_Crop->isChecked();


            e->accept();


        }

    }

}
void PlayerWindow::hidestatus()
{


    if (fullScreenControls->geometry().top()==desktop->screen()->height()-70)
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

    for (int i = 0; i < urlList.count(); i++) {

        QString url = urlList.at(i).toLocalFile();
        if (urlList[i].isValid())
        {
            QFileInfo fi(url);
            if(fi.isFile())
            {


                //Check dropped file is a subtitle or not
                if ( fi.suffix().toLower().contains("srt")||
                     fi.suffix().toLower().contains("sub")||
                     fi.suffix().toLower().contains("ssa")||
                     fi.suffix().toLower().contains("ass")||
                     fi.suffix().toLower().contains("idx")||
                     fi.suffix().toLower().contains("txt")||
                     fi.suffix().toLower().contains("smi")||
                     fi.suffix().toLower().contains("rt") ||
                     fi.suffix().toLower().contains("utf")||
                     fi.suffix().toLower().contains("aqt")
                     )

                {
                    if (mp->hasvideo())
                    {
                        //Video found so adding subtitle
                        mp->loadsubtitles(url);
                        ui->actionStUnload->setEnabled(true);
                    }
                }
                else
                {
                    //This is a media file add and play
                    if (urlList.size()==1)
                    {   if (!bPlayListDrop)
                        {
                            myplaylist->clearList();

                        }
                        myplaylist->addFile(url);
                        if (!bPlayListDrop)
                        {
                            myplaylist->playFirstFile();
                        }
                    }
                    else {
                        qDebug()<<QString::number(i)<<"/"<<QString::number(urlList.count())<<url;
                        myplaylist->addFile(url);
                    }


                }
            }
            else if(fi.isDir())
            {
                qDebug()<<"Add folder"<<url;
                if (!bPlayListDrop)
                {
                    myplaylist->clearList();

                }
                myplaylist->addFolder(url,w->filters,this);
                if (!bPlayListDrop)
                {
                    myplaylist->playFirstFile();
                }
                //this->playThisfile(myplaylist->tab->item(0,2)->data(Qt::DisplayRole).toString());
            }

        }
    }
    bPlayListDrop=false;
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
    QLibrary library("kernel32.dll");
    if (!library.load())
        qDebug("kernel32 Library loading failed.");
    else
    {

        qDebug("kernel32 Library loaded");

        typedef uint (*SetThreadExecutionState)(uint esFlag);
        SetThreadExecutionState setState = (SetThreadExecutionState)library.resolve("SetThreadExecutionState");
        //ES_CONTINUOUS
        //0x80000000
        //ES_DISPLAY_REQUIRED
        //0x00000002
        //ES_SYSTEM_REQUIRED
        //0x00000001
        setState(0x80000000);
    }
#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
    if (screensaverInhibit)
        screensaverInhibit->deactivateInhibit();
# endif
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
                    mp->seek(ui->sliderSeek->value());
                    this->playerTimer->start();
                }
            }
            else{
                ui->sliderSeek->setValue( ui->sliderSeek->value()-1);
                if (playerTimer)
                {this->playerTimer->stop();
                    mp->seek(ui->sliderSeek->value());
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
    QTime _duration(0,0);
    _duration=_duration.addSecs(p);

    if(lab)
    {if( mp->hasvideo())
        {
            // qDebug()<<QString::number(mp->starttime())<<"::";
            if (mp->starttime()<10)
            {mpseekView->resize(128,105);
                if(! isfullscreen)
                    mpseekView->move(pt->x()-64+ui->sliderSeek->x(),ui->toolBarSeekBar->y()-105);
                else
                    mpseekView->move(pt->x()-64+sliderSeekFullSc->x()+fullScreenControls->x(),fullScreenControls->y()-105);

                mpseekView->show();
            }
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
                QObject::connect(fr,SIGNAL(processFinished(int,bool)),this,SLOT(restartSeekView(int,bool)));
                QObject::connect(fr,SIGNAL(starting()),this,SLOT(pauseSeekView()));

                fr->setVideoWinid(mpseekView->getwindowID());
                fr->setColorkey(5);
                fr->setaspect(false);
                fr->play(this->currentFile,0);
                fr->setOSDlevel(0);


            }

            if(pos.toInt()<100)
            {
                fr->pause();
                fr->seek(pos.toInt());
            }
        }

        if (mp->hasvideo())
        {if (fr)
            {if( fr->isstarted())
                {if (lab)
                    {
                        if (mp->duration()<3600)
                            lab->setText(_duration.toString(_duration.toString("hh:mm:ss").mid(3)));
                        else
                            lab->setText(_duration.toString(_duration.toString("hh:mm:ss")));


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
                if (mp->duration()<3600)
                    lab->setText(_duration.toString(_duration.toString("hh:mm:ss").mid(3)));
                else
                    lab->setText(_duration.toString(_duration.toString("hh:mm:ss")));

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
            QObject::connect(fr,SIGNAL(processFinished(int,bool)),this,SLOT(restartSeekView(int,bool)));
            QObject::connect(fr,SIGNAL(starting()),this,SLOT(pauseSeekView()));

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
    // system("dbus-send --session --dest=org.gnome.SessionManager --type=method_call --print-reply --reply-timeout=20000 /org/gnome/SessionManager org.gnome.SessionManager.Inhibit string:\"myApp\" uint32:0 string:\"Inhibiting\" uint32:8");
    //system("dbus-send --session --dest=org.gnome.SessionManager --type=method_call --print-reply --reply-timeout=20000 /org/gnome/SessionManager org.gnome.SessionManager.IsInhibited uint32:8");

    if (mp->state()==mp->BUFFERING){
        QString cacheFill="Buffering...["+QString::number(mp->getBufferFill())+"%]";
        //ui->labelStatus->setText(cacheFill);
        ui->labelCurrentPosition->setText("Buffering...["+QString::number(mp->getBufferFill())+"%]");
    }
    if (mp->state()==mp->CONNECTING)
    {  //ui->labelStatus->setText("Connecting...");
        ui->labelCurrentPosition->setText("Connecting...");
        //ui->labelCurrentPosition->setToolTip("Connecting...");
    }

    if (mp->state()==mp->RESOLVING)
    {
        //ui->labelStatus->setText("Resolving host...");
        ui->labelCurrentPosition->setText("Resolving host...");
        //ui->labelCurrentPosition->setToolTip("Resolving host...");

    }
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
            path=QDir::tempPath()+"/mcover.jpeg";
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
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
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
                // qDebug()<<act->shortcut().toString();
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



    if(this->isFullScreen()){

        if (mp){
            if (mp->hasvideo())
                mp->usercommand("osd_show_text \"\" 1 1");
        }
#ifdef Q_OS_WIN

        if (!ui->actionStay_on_top->isChecked())
            this->setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
#endif
        ui->actionFullscreen->setIcon(QIcon(":/images/fullscreen.png"));
        ui->actionFullscreen->setToolTip("Show fullscreen");
        isfullscreen=false;
        hidetimer->stop();


        ui->toolBarSeek->show();
        ui->menuBar->show();

        if (ui->actionInfobar->isChecked())
            ui->toolBarStatus->show();
        if (!ui->actionMini_Mode->isChecked())
            this->statusBar()->show();


        ui->toolBarSeekBar->show();


        this->unsetCursor();

        if (bfilvis)
            ui->dock_Filter->show();
        if (blogvis)
            ui->dock_log->show();
        if (bplvis)
            ui->dock_Playlist->show();
        if (bfbvis)
            ui->dockBrowser->show();

        if (fullScreenControls)
            fullScreenControls->hide();

        delete hidetimer;
        this->showNormal();
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
        this->setWindowState(Qt::WindowActive);
#endif


    }
    else
    {
#ifdef Q_OS_WIN
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
#endif

        qDebug()<<"Screen Height :"<<desktop->screen()->height();
        qDebug()<<"Screen Width :"<<desktop->screen()->width();

        if(fullScreenControls<=0)
        {
            fullScreenControls=new QToolBar(this);
            fullScreenControls->setMouseTracking(true);

            GlassStyle *st=new GlassStyle;
            fullScreenControls->setStyle(st);
            lcdCurPosFullSc=new QLCDNumber(this);


            lcdDurationFullSc=new QLCDNumber(this);
            lcdCurPosFullSc->setSegmentStyle(ui->lcdCurPos->segmentStyle());
            lcdDurationFullSc->setSegmentStyle(ui->lcdDuration->segmentStyle());

#if QT_VERSION < QT_VERSION_CHECK(4,8 , 0)
            lcdCurPosFullSc->setNumDigits(8);
            lcdDurationFullSc->setNumDigits(8);
 #else
            lcdCurPosFullSc->setDigitCount(8);
            lcdDurationFullSc->setDigitCount(8);
 #endif
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

            QObject::connect(sliderSeekFullSc,SIGNAL(showtooltip(QPoint *)),this,SLOT(showtooltip(QPoint *)));
            QObject::connect(sliderSeekFullSc,SIGNAL(hoverValue(QString,QPoint*)),this,SLOT(showSeekpos(QString,QPoint*)));

            lcdCurPosFullSc->display("00:00:00");
            lcdDurationFullSc->display("00:00:00");
            lcdCurPosFullSc->setStyleSheet(ui->lcdCurPos->styleSheet());
            lcdDurationFullSc->setStyleSheet(ui->lcdDuration->styleSheet());

            connect(sliderSeekFullSc,SIGNAL(hidetooltip()),this,SLOT(hideframe()));
            QObject::connect(sliderSeekFullSc,SIGNAL(actionTriggered(int)),this,SLOT(on_sliderSeekFullSc_actionTriggered(int)));



        }
        fullScreenControlWidth=(long)desktop->screen()->width()*FULLSCREENCTRL_WIDTH_PERCENTAGE;

        leftSide=(desktop->screen()->width()/2)-(fullScreenControlWidth/2);
        if(fullScreenControls)
        {


            fullScreenControls->setMovable(false);
            fullScreenControls->setIconSize(QSize(30,30));
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
            animation->setDuration(500);
            animation->setStartValue(QRect(leftSide,desktop->screen()->height(),fullScreenControlWidth,70));
            animation->setEndValue(QRect(leftSide,desktop->screen()->height()-70,fullScreenControlWidth,70));
            //animation->blockSignals(true);
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

        //hidetimer->start(10000);
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
    {
        myplaylist->addFile(fileName);
    }
}
void PlayerWindow::winExplorer(QString opt,QString path)
{
#ifdef Q_OS_WIN
    path=path.replace("/","\\");
    QProcess::execute("explorer.exe "+opt+path);
#elif defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
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
{
    //qApp->setStyle("windowsxp");
    qApp->setStyle(new GlassStyle);

    ui->statusBar->setStyleSheet(QString::fromUtf8("background:white;"));
    // QApplication::setPalette(QApplication::style()->standardPalette());

    ui->sliderVolume->setStyleSheet(QString::fromUtf8("QSlider::sub-page:horizontal {\n"
                                                      "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 255), stop:1 rgba(255, 255, 255, 255));    \n"
                                                      " border: 1px solid rgba(100, 255, 255, 255);\n"
                                                      " }\n"
                                                      " QSlider::groove:horizontal {\n"
                                                      "     height: 3px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
                                                      "     margin: 1px 0;\n"
                                                      " background: qlineargradient(x1: 1, y1:12, x1: 15, y2: 0, stop: 0 #e7effd, stop: 1 #D2E7FA); \n"
                                                      " border: 1px solid rgba(10, 10, 10, 6);\n"
                                                      " }\n"
                                                      "QSlider::handle::horizontal{ \n"
                                                      "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 255), stop:1 rgba(255, 255, 255, 255));\n"
                                                      "width: 8px;\n"
                                                      " border: 1px solid rgba(128, 184, 228, 100);\n"
                                                      "     margin: -4px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                      "     border-radius: 4px;\n"
                                                      "}\n"
                                                      "QSlider::handle::hover:horizontal{ \n"
                                                      "background:qlineargradient(spread:pad, x1:"
                                                      "0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 255, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
                                                      "width: 8px;\n"
                                                      " border: 1px solid lightgreen;\n"
                                                      "     margin: -4px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                      "     border-radius: 4px;\n"
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
                                                    " border: 1px solid rgba(100, 255, 255, 255);\n"
                                                    " }\n"
                                                    " QSlider::groove:horizontal {\n"
                                                    "     height: 2px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
                                                    "     margin: 1px 0;\n"
                                                    " background: qlineargradient(x1: 1, y1:12, x1: 15, y2: 0, stop: 0 #e7effd, stop: 1 #D2E7FA); \n"
                                                    " border: 2px solid rgba(10, 10, 10, 6);\n"
                                                    " }\n"
                                                    "QSlider::handle::horizontal{ \n"
                                                    "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 50), stop:1 rgba(255, 255, 255, 50));\n"
                                                    "width: 0px;\n"
                                                    " border: 0px solid rgba(128, 184, 228, 100);\n"
                                                    "     margin: -8px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                    "     border-radius: 8px;\n"
                                                    "}\n"
                                                    "QSlider::handle::hover:horizontal{ \n"
                                                    "background:qlineargradient(spread:pad, x1:"
                                                    "0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 255, 0, 150), stop:1 rgba(255, 255, 255, 255));\n"
                                                    "width: 3px;\n"
                                                    " border: 1px solid lightgreen;\n"
                                                    "     margin: -8px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
                                                    "     border-radius: 8px;\n"
                                                    "}\n"
                                                    "QSlider::handle::disabled:horizontal{ \n"
                                                    "background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 0), stop:1 rgba(255, 255, 255, 0));\n"
                                                    "width: 0px;\n"
                                                    " border: 0px solid lightblue;\n"
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
{

    int eh=mp->videoheight();

    if(ui->toolBarSeek->isVisible())
        eh+=ui->toolBarSeek->height();
    if( ui->statusBar->isVisible())
        eh+=ui->statusBar->height();
    if(ui->menuBar->isVisible())
        eh+=ui->menuBar->height();
    if(ui->toolBarSeekBar->isVisible())
        eh+=ui->toolBarSeekBar->height();
    if(ui->toolBarStatus->isVisible())
        eh+= ui->toolBarStatus->height();

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
    calculateHeight();
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
           <<"*.webm"
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

    if(picflow>0)
    {
        if(picflow->slideCount()>0)
            picflow->resize(w,hei);
    }
    if (piv->isVisible())
    {
        piv->move(videoWin->width()/2-piv->width()/2,videoWin->height()/2-piv->height()/2);

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
{

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
    /* qDebug()<<"Audio :"<<mp->hasaudio()<<"Video: "<<mp->hasvideo();
    if (mp)
    {
        if (mp->hasaudio() && !mp->hasvideo())
        {
             this->videoWin->mplayerlayer->hide();
        }
        if (mp->hasvideo())
        {
            qDebug()<<"mplayerlayer->show()";
            this->videoWin->mplayerlayer->show();
        }
        if (!mp->hasvideo()&&!mp->hasaudio())
        {
            this->windowTimer->stop();;
        }
    }*/

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

    this->resize(PLAYER_WIDTH,0);

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

    // videoWin->setAspect((float)w/h);
    //this->resize(w,h);
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


void PlayerWindow::on_sliderSeekFullSc_actionTriggered(int act)
{
    this->playerTimer->stop();
    mp->seek(sliderSeekFullSc->value());
    this->playerTimer->start();

}
void PlayerWindow::resizeEvent ( QResizeEvent * event )
{
    calculateHeight();
}

void PlayerWindow::on_actionAdvanced_Info_triggered()
{
    advInfoDlg=new AdvancedInfoDialog(this);
    advInfoDlg->setMPlayer(mp);
    advInfoDlg->show();
}

void PlayerWindow::on_actionEnable_3D_triggered()
{


    emit  settingChanged ("Video","3D",QString::number(ui->actionEnable_3D->isChecked()));

    if(ui->actionEnable_3D->isChecked())
    {


        if(mp)
        {
            if (mp->hasvideo())
            {
                svindlg= new StereoVinputDialog(this);
                QObject::connect(svindlg,SIGNAL(stereoInputFormat(int)),this,SLOT(setStereoInputFormat(int)));
                svindlg->setStereo(true);
                svindlg->show();
            }
            else
            {
                ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_on.png"));
                ui->toolButtonStereoVideo->setToolTip("Turn <b>OFF</b> 3D video");
                ui->actionEnable_3D->setToolTip("");
            }
        }
    }
    else
    {
        ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_off.png"));
        ui->toolButtonStereoVideo->setToolTip("Turn <b>ON</b> 3D video");
        if(mp)
        {
            if (mp->hasvideo())
                mp->Stereo3D(ui->actionEnable_3D->isChecked());

        }
    }



}

void PlayerWindow::on_actionInfobar_triggered()
{
    ui->toolBarStatus->setVisible(ui->actionInfobar->isChecked());
    emit settingChanged ("MainWindow","InfoBar",QString::number(ui->actionInfobar->isChecked()));
    calculateHeight();

}

void PlayerWindow::changeStereoscopicView(QAction *act)
{
    QString inStereoFmt, outStereoFmt;
    //Get 3D input format
    foreach(QAction* sInAct, actiongroupInFormatStereo->actions())
    {
        if(sInAct->isChecked())
            inStereoFmt=sInAct->iconText();
    }

    //Get 3D output format
    foreach(QAction* sOutAct, actiongroupOutFormatStereo->actions())
    {
        if(sOutAct->isChecked())
            outStereoFmt=sOutAct->iconText();
    }

    qDebug()<<"3D in: "<<inStereoFmt <<" Out :"<<outStereoFmt;
    //Transform 3D
    if (mp)
    {
        if (mp->hasvideo())
            mp->Stereo3D(inStereoFmt,outStereoFmt);

    }

    ui->actionWatch_as_2D_video->setChecked(false);
    if (!ui->actionEnable_3D->isChecked())
        ui->actionEnable_3D->trigger();

    ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_on.png"));
    ui->toolButtonStereoVideo->setToolTip("Turn <b>OFF</b> 3D video");
    ui->actionWatch_as_2D_video->setChecked(false);



}

void PlayerWindow::on_toolButtonStereoVideo_clicked()
{

    ui->actionEnable_3D->trigger();
}

void PlayerWindow::on_actionWatch_as_2D_video_triggered()
{

    if (ui->actionWatch_as_2D_video->isChecked())
    {
        svindlg= new StereoVinputDialog(this);
        QObject::connect(svindlg,SIGNAL(stereoInputFormat(int)),this,SLOT(setStereoInputFormat(int)));
        svindlg->show();
    }
    else
    {
        if(mp)
        {
            mp->Stereo3D(false);
        }
    }

}

void PlayerWindow::on_actionVolume_Boost_triggered()
{

    emit  settingChanged ("Audio","Boost",QString::number(ui->actionVolume_Boost->isChecked()));
    if(mp)
        mp->addVolumeBoost(ui->actionVolume_Boost->isChecked(),settings->value("Audio/VolumeBoost","500").toInt());
    if(ui->actionVolume_Boost->isChecked())
    {
        ui->toolButtonVolumeBoost->setIcon(QIcon(":/images/volboost_on.png"));
        ui->toolButtonVolumeBoost->setToolTip("Turn <b>OFF</b> volume boost");

    }
    else
    {
        ui->toolButtonVolumeBoost->setIcon(QIcon(":/images/volboost_off.png"));
        ui->toolButtonVolumeBoost->setToolTip("Turn <b>ON</b> volume boost");
    }
}

void PlayerWindow::on_toolButtonVolumeBoost_clicked()
{
    ui->actionVolume_Boost->trigger();

}
void PlayerWindow::restartSeekView(int ec,bool stop)
{
    if (fr)
    {
        qDebug()<<"Handle !!!!";
        fr->stop();
        fr=NULL;
    }
}
void PlayerWindow::pauseSeekView()
{
    if (fr)
    {
        fr->pause();
    }
}
void PlayerWindow::setStereoInputFormat(int mode)
{

    qDebug()<<QString ::number(mode);

    if (mode==1)
        ui->actionSide_by_side_left_first->setChecked(true);
    else
        ui->actionAbove_below_left_first->setChecked(true);


    QString inStereoFmt, outStereoFmt;
    //Get 3D input format
    foreach(QAction* sInAct, actiongroupInFormatStereo->actions())
    {
        if(sInAct->isChecked())
            inStereoFmt=sInAct->iconText();
    }

    //Get 3D output format
    foreach(QAction* sOutAct, actiongroupOutFormatStereo->actions())
    {
        if(sOutAct->isChecked())
            outStereoFmt=sOutAct->iconText();
    }

    if (!svindlg->Stereo())
    {
        ui->actionEnable_3D->setChecked(false);
        if(ui->actionEnable_3D->isChecked())
        {
            ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_on.png"));
            ui->toolButtonStereoVideo->setToolTip("Turn <b>OFF</b> 3D video");

        }
        else
        {
            ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_off.png"));
            ui->toolButtonStereoVideo->setToolTip("Turn <b>ON</b> 3D video");

        }
        if(mp)
            mp->Stereo3D(inStereoFmt,"ml");
    }
    else
    {
        //Got 3D input format now transform

        //Transform 3D
        if (mp)
        {
            if (mp->hasvideo())
                mp->Stereo3D(inStereoFmt,outStereoFmt);
            ui->toolButtonStereoVideo->setIcon(QIcon(":/images/3D_on.png"));
            ui->toolButtonStereoVideo->setToolTip("Turn <b>OFF</b> 3D video");
            ui->actionWatch_as_2D_video->setChecked(false);
        }
    }

}
void PlayerWindow::hideSeek()
{

    ui->sliderSeek->setDisabled(true);
    ui->lcdDuration->display("--:--:--");
}
bool PlayerWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove || event->type() == QEvent::KeyPress ||event->type() == QEvent::Wheel||event->type() == QEvent::MouseButtonPress)
    {
        //reset timer
        idleTimer->start(5000);

    }

    return QMainWindow::eventFilter(obj, event);
}
bool PlayerWindow::userInactive()
{

    if (isfullscreen)
    {

        if(fullScreenControls)
        {qDebug()<<"User inactivity";
            if (fullScreenControls->isVisible())
            {
                // qDebug("%d %d %d",ypos,xpos,fullScreenControls->geometry().top());
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
                if (ypos<fullScreenControls->geometry().top())
                {
                    fullScreenControls->hide();
                    this->setCursor(Qt::BlankCursor);
                }
#endif

#ifdef Q_OS_WIN
                fullScreenControls->hide();
                this->setCursor(Qt::BlankCursor);
#endif

            }
        }

    }
}
void PlayerWindow::addSubtitletrack(QStringList sl )
{

    if (sl.count()+1!=ui->menuSelect->actions().count())
    {
        if (!ui->actionStNone->isEnabled())
            ui->actionStNone->setEnabled(true);
        if(actiongroupSubtitleTrack)
        {   actiongroupSubtitleTrack->addAction( ui->menuSelect->addAction("Track "+QString::number(sl.count())));
            actiongroupSubtitleTrack->actions().last()->setCheckable(true);
            actiongroupSubtitleTrack->actions().last()->setChecked(true);

        }
    }
}

void PlayerWindow::on_actionCheck_for_updates_triggered()
{
    updCheckDlg =new updateCheckDlg(this);
    updCheckDlg->show();
}

void PlayerWindow::on_toolButtonVolume_pressed()
{


}
void PlayerWindow::calculateHeight()
{
    long playerHeight=0;
    if (ui->menuBar->isVisible())
        playerHeight+=ui->menuBar->height();
    //if(ui->toolBarSeek->isVisible())
    //    playerHeight+=ui->toolBarSeek->height();
    if(ui->toolBarSeekBar->isVisible())
        playerHeight+=ui->toolBarSeekBar->height();
    if(ui->toolBarStatus->isVisible())
        playerHeight+=ui->toolBarStatus->height();
    if(ui->statusBar->isVisible())
        playerHeight+=ui->statusBar->height();
    qDebug("playerHeight :%d",playerHeight);
    this->setMinimumHeight(playerHeight);
}
void PlayerWindow::shareWithFriends(QAction *act)
{

    QString text = QString("Free media player for Windows and Linux that can all media files,featuring audio converter,audio extractor,media cutter and 3D video.").replace(" ","+");
    QString url = "http://exmplayer.sourceforge.net";

    if (act->text().toLower() == "twitter") {
        text="Free media player for Windows and Linux that can all media files,featuring audio converter,extractor ,media cutter.";
        QDesktopServices::openUrl(QUrl("http://twitter.com/intent/tweet?text=" + text + "&url=" + url));
    }
    else
        if (act->text().toLower() == "gmail") {
            QDesktopServices::openUrl(QUrl("https://mail.google.com/mail/?view=cm&fs=1&to&su=" + text + "&body=" + url + "&ui=2&tf=1&shva=1"));
        }
        else
            if (act->text().toLower() == "yahoo") {
                QDesktopServices::openUrl(QUrl("http://compose.mail.yahoo.com/?To=&Subject=" + text + "&body=" + url));
            }
            else
                if (act->text().toLower()=="hotmail") {
                    QDesktopServices::openUrl(QUrl("http://www.hotmail.msn.com/secure/start?action=compose&to=&subject=" + text + "&body=" + url));
                }
                else
                    if (act->text().toLower()=="facebook") {
                        QDesktopServices::openUrl(QUrl("http://www.facebook.com/sharer.php?u=" + url + "&t=" + text));
                    }
}

void PlayerWindow::on_actionSearch_subtitles_on_OpenSubtitles_org_triggered()
{
    subSearchDlg= new SearchSubtitle(this);
    QObject::connect(subSearchDlg,SIGNAL(readyForSubSearch()),this,SLOT(searchForSubtitle()));
    QObject::connect(subSearchDlg,SIGNAL(loadSubtitle(QString)),this,SLOT(loadSubtitleOS(QString)));

    subSearchDlg->show();
}

void PlayerWindow::on_actionMini_Mode_triggered()
{
    if (ui->actionMini_Mode->isChecked())
        this->statusBar()->setVisible(false);
    else
        this->statusBar()->setVisible(true);

    emit settingChanged ("MainWindow","MiniMode",QString::number(ui->actionMini_Mode->isChecked()));
    calculateHeight();
}
void PlayerWindow::dropPlayListEvent(QDropEvent *event)
{
    bPlayListDrop=true;
    dropEvent(event);
}

void PlayerWindow::searchForSubtitle()
{
    if (mp)
        subSearchDlg->searchSubtitleForMovie(mp->filepath());
}
void PlayerWindow::loadSubtitleOS(QString url)
{
    if (mp->hasvideo())
    {
        //Video found so adding subtitle
        mp->loadsubtitles(url);
        ui->actionStUnload->setEnabled(true);
        QMessageBox::information(this,"ExMplayer","Subtitle downloaded and loaded.");
    }
}

void PlayerWindow::on_actionUpload_subtitle_to_OpenSubtitles_org_triggered()
{
    QDesktopServices::openUrl(QUrl("http://www.opensubtitles.org/upload"));
}

void PlayerWindow::on_actionShare_this_playback_on_Facebook_triggered()
{
    if (mp)
        SocialShare::shareThisPlaybackOnFacebook(this,mp);
}

void PlayerWindow::on_actionUpload_subtitle_to_OpenSubtitles_org_Advanced_triggered()
{
    QDesktopServices::openUrl(QUrl("http://www.opensubtitles.org/en/uploadjava"));
}

void PlayerWindow::on_toolButtonInfo_clicked()
{
    if (mp)
    {
        if (hascover)
        {
            covArtDlg= new CoverArtDialog(ui->toolBarSeekBar);
            QObject::connect(covArtDlg,SIGNAL(showInfo()),this,SLOT(on_action_Media_Info_triggered()));
            covArtDlg->show();

        }
        else
        {
            ui->action_Media_Info->trigger();
        }

    }
}

void PlayerWindow::on_actionVideo_Downloader_triggered()
{
    videodlDlg= new Videodl(this,settings);
    QObject::connect(videodlDlg,SIGNAL(showfile(QString,QString)),this,SLOT(winExplorer(QString,QString)));
    videodlDlg->show();
}

void PlayerWindow::on_actionGIF_Animator_triggered()
{
   if (mp)
   {
        gifdlg=new GifAnimatorDialog(this,mp);
        QObject::connect(gifdlg,SIGNAL(showfile(QString,QString)),this,SLOT(winExplorer(QString,QString)));
        gifdlg->show();
    }



}

