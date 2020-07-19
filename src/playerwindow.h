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

#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include "mplayerfe.h"
#include <QtWidgets>
#include <QSettings>
#include "config.h"
#include "equalizertypes.h"
#include "playlist.h"
#include "pictureflow.h"
#include <QCompleter>
#include "QProgressIndicator.h"
#include "preferencedialog.h"
#include "urldialog.h"
#include "QRecentFilesMenu.h"
#include "midialog.h"
#if defined(Q_OS_WIN) || defined(Q_OS_OS2)
#ifdef Q_OS_WIN
#include <Winbase.h>
#include "screensaver.h"
#ifdef TAGLIB
#include "qcoverart.h"
#endif
#endif
#endif
#include "aboutdialog.h"
#include "cutterdialog.h"
 #if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  #include "norwegianwoodstyle.h"
#endif
#include "helpdialog.h"
#include "winfileassoc.h"
#include "mixdialog.h"
#include <QMenu>
#include <qlocalsocket.h>
#include <QLocalSocket>
#include <QLocalServer>
#include "rphfile.h"
#include "audioextdialog.h"
#include "mplayerwindow.h"
#include "audioconvdialog.h"
#include "seekview.h"
#include "glassstyle.h"
#include "radiodialog.h"
#include "seekview.h"
#include "rphslider.h"
#include <QResizeEvent>
#include "advancedinfodialog.h"
#include <languages.h>

#include <QAction>
#include <stereovinputdialog.h>
#ifdef Q_OS_UNIX
#include <inhibitor.h>
#endif

#include <updatecheckdlg.h>
#include <searchsubtitle.h>
#include <socialshare.h>
#include <coverartdialog.h>
#include <videodl.h>
#include "gifpalettegenerator.h"
#include "gifgenerator.h"
#include <gifanimatordialog.h>

#define FULLSCREENCTRL_WIDTH_PERCENTAGE  .60
#define FULLSCREENCTRLHEIGHT  70
#define PLAYER_WIDTH  500

namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QMainWindow {
    Q_OBJECT

public:

    PlayerWindow(QWidget *parent = 0);
    ~PlayerWindow();
    QPointer<mplayerfe> mp;
    QPointer<mplayerfe>fr;
    QPointer<QSettings> settings;

    float mediaduration;
    float mediaposition;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
    void changeEvent(QEvent *e);
    void keyPressEvent ( QKeyEvent * e );
    void closeEvent(QCloseEvent *event);
    void showEvent ( QShowEvent * event );
#ifdef Q_OS_WIN
    /* Disable screensaver by event */
    virtual bool winEvent ( MSG * m, long * result );
#endif

private:

    Ui::PlayerWindow *ui;
    QPoint dragPosition;
    QStringList basicmetainfo;
    bool starting;
    QLocalSocket *socket;
    QString currentCmd;
    quint16 blockSize;
    QTimer *idleTimer;
    QPointer<QMenu> menuLoadSavepl;
    QPointer<mixDialog> mxdlg;
    QPointer<audioextDialog> axdlg;
    QPointer<audioconvDialog> aucdlg;
    QPointer<StereoVinputDialog> svindlg;
    #if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
     QPointer<Inhibitor> screensaverInhibit;
    #endif
    //QPointer<ripDialog> auripdlg;
    //QPointer<seekview> mpseekview;
    //QPixmap *pixCover;
#ifdef Q_OS_WIN
    WinScreenSaver* winscreensaver;
#endif
    QLabel *labstr;
    QLabel *testlab;
    QPointer<QLabel> lab;
    QPointer<PictureFlow> w;
    QPointer<PictureFlow> picflow;
    QPointer<playList> myplaylist;
    MplayerWindow *videoWin;
    config *myconfig;
    int xpos;
    int ypos;
    int tmpxpos;
    int tmpypos;
    float prevpos;
    float streamingDur;
    QTimer *clientTimer;
    QPointer<QTimer> windowTimer;
    QPointer<QTimer> coreTimer;
    QPointer<QTimer> playerTimer;
    QPointer<QTimer> frameTimer;
    QPointer<QTimer> disptimer;
    QPointer<QTimer> hidetimer;
    QPointer<QActionGroup> actiongroupSubtitleAlignment;
    QPointer<QActionGroup> actiongroupSubtitleTrack;
    QPointer<QActionGroup> actiongroupAudioTrack;
    QPointer<QActionGroup> actiongroupVideoTrack;
    QPointer<QActionGroup> actiongroupChannels;
    QPointer<QActionGroup> actiongroupResample;
    QPointer<QActionGroup> actiongroupStereoMode;
    QPointer<QActionGroup> actiongroupRotate;
    QPointer<QActionGroup> actiongroupAspectRatio;
    QPointer<QActionGroup> framedropGroup;
    QPointer<QActionGroup> osdGroup;
    QPointer<QActionGroup> actiongroupInFormatStereo;
    QPointer<QActionGroup> actiongroupOutFormatStereo;
    QPointer<QActionGroup> actiongroupShareExMplayer;
    QWidget * panel;
    MplayerWindow *mpwindow;
    bool usingfidx;
    bool forceplay;
    bool bfbvis;
    bool bplvis;
    bool blogvis;
    bool bfilvis;
    bool bplay;
    bool brotate;
    bool bedlenable;
    bool bstop;
    bool iseof;
    bool crossfade;
    bool useidx;
    int videoHeight;
    int videoWidth;
    int osdlevel;
    int framedroplevel;
    int metadispcount;
    bool bPlayListDrop;
    QString tmp;
    QString currentFile;
    QAction *actPrgsIndicator;
    QPointer<QProgressIndicator> pi;
    QPointer<QProgressIndicator> piv;
    QPointer<cutterDialog> cdlg;
    QPointer<GifAnimatorDialog> gifdlg;
    QPointer<preferenceDialog>optionDlg;
    QPointer<miDialog> midlg;
    QPointer<aboutDialog> abtDlg;
    QPointer<helpDialog> mainhlpDlg;
    QPointer<UrlDialog> urldlg;
    QPointer<RadioDialog> radiodlg;
    QPointer<QShortcut> shortcut;
    QRecentFilesMenu *recentFilesMenu;
    QPointer<updateCheckDlg> updCheckDlg;
    int mousewheelrole ;
    bool isfullscreen;
    bool hascover;
    QPixmap *cover;
    QString frpos;
    QString Title;
    bool lavf;
    int fileType;
    QSharedMemory sharedMemory;
    QMenu *fmnu;
    QMenu *rmnu;
    QMenu *pbmnu;
    QProcess *wget;
    bool isdownloading;
    bool isstreaming;
    double zoomfact;
    QMovie *movie;
    QString artisttext;
    QString albumtext;
    QString yeartext;
    QLabel *labanim;
    SeekView *mpseekView;
    double currentFilePos;

    QPointer<QToolBar>fullScreenControls;
    long leftSide;
    long fullScreenControlWidth;
    QAction *toolButtonForwardAction;
    QPointer<QLCDNumber> lcdCurPosFullSc;
    QPointer<QLCDNumber> lcdDurationFullSc;
    QPointer<rphSlider> sliderSeekFullSc;
    QPointer<rphSlider> sliderVolumeFullSc;

    QPointer<AdvancedInfoDialog> advInfoDlg;
    int curSubTitleTrack;

    QPointer<SearchSubtitle> subSearchDlg;
    QPointer<CoverArtDialog> covArtDlg;

    QPointer<Videodl> videodlDlg;

    QPointer<GifPaletteGenerator> gifPalettteGen;
    QPointer<GifGenerator> gifGene;


signals:
    void sgcrossfade();
    void keyPress(QKeyEvent * e);

private slots:
    void resizeVideoWindow(int w,int h);
    void on_actionSmallmode_triggered();
    void on_actionAudio_Converter_triggered();
    void updatevideovindow();
    void on_toolButtonplaylist_clicked();
    void on_actionDefault_zoom_triggered();
    void on_actionChange_framerate_triggered();
    void on_actionDefault_triggered();
    void on_actionIncrease_Video_quality_triggered();
    void on_actionMove_Down_triggered();
    void on_actionMove_Up_triggered();
    void on_actionMove_Right_triggered();
    void on_actionMove_Left_triggered();
    void on_actionDecrease_Zoom_triggered();
    void on_actionIncrease_Zoom_triggered();
    void on_toolButtonSpeed_clicked();
    void on_actionAudio_extrctor_triggered();
    void on_actionSide_view_triggered();
    void on_actionTwins_triggered();
    void on_actionAdd_Folder_to_pl_triggered();
    void on_actionAdd_File_to_pl_triggered();
    void on_actionEdit_Playlist_triggered();
    void on_actionSave_cover_art_triggered();
    void on_actionFolder_triggered();
    void on_toolButton_playnext_clicked();
    void on_toolButton_playpre_clicked();
    void on_toolButton_shuffle_toggled(bool checked);
    void on_toolButton_loop_toggled(bool checked);
    void on_toolButtonfs_clicked();
    void on_actionMix_and_save_triggered();
    void on_actionAbout_Qt_triggered();
    void on_action_Help_triggered();
    void on_cbEnableAEq_clicked();
    void on_actionShowpl_triggered();
    void on_actionMedia_cutter_triggered();
    void on_actionEnable_Closed_Captions_triggered();
    void on_action_About_triggered();
    void on_actionOpen_containing_folder_triggered();
    void on_action_Load_pl_triggered();
    void on_eq0_actionTriggered(int action);
    void on_actionPlay_Previous_File_triggered();
    void on_actionPlay_Next_File_triggered();
    void on_action_Save_as_playlist_triggered();
    void on_actionURL_triggered();
    void on_eq3_valueChanged(int value);
    void on_cbEnableAEq_stateChanged(int );
    void on_actionWinamp_Dsp_triggered();
    void on_actionNegative_triggered();
    void on_actionVolume_Normalization_triggered();
    void on_action_Options_triggered();
    void on_sliderSeek_valueChanged(int value);
    void on_action_Media_Info_triggered();
    void on_sliderVolume_actionTriggered(int action);
    void on_actionSelected_item_s_triggered();
    void on_actionAdd_Folder_triggered();
    void on_actionRemove_all_triggered();
    void on_actionAdd_file_triggered();
    void on_actionFullscreen_triggered();
    void on_action_AV_Set_Delay_triggered();
    void on_action_st_Set_Delay_triggered();
    void on_actionDelay_Decrease_triggered();
    void on_actionDelay_Increaser_triggered();
    void on_action_st_Move_Down_triggered();
    void on_action_st_Move_Up_triggered();
    void on_actionStUnload_triggered();
    void on_actionSize_Decrease_triggered();
    void on_actionSize_Increase_triggered();
    void on_action_Load_st_triggered();
    void on_action_Equalizer_triggered();
    void toggle_bottomdock_visibility();
    void on_actionVideoEqualizer_triggered();
    void on_comboBox_currentIndexChanged(int index);
    void on_btnAEReset_clicked();
    void setequlizerbandvalue(int bandval);
    void on_gamma_valueChanged(int value);
    void on_Saturation_valueChanged(int value);
    void on_Hue_valueChanged(int value);
    void on_brightness_valueChanged(int value);
    void on_contrast_valueChanged(int value);
    void animate_ae_slider(QStringList values);
    void contextMenuEvent(QContextMenuEvent *event);
    void on_btnVEReset_clicked();
    void on_actionToggle_subtitle_visibility_triggered();
    void on_action_Open_Screenshot_folder_triggered();
    void on_actionStart_stop_Screenshot_triggered();
    void on_actionScreen_shot_triggered();
    void on_actionToggle_Frame_drop_triggered();
    void on_actionToggle_OSD_triggered();
    void on_actionFrame_step_triggered();
    void on_actionStay_on_top_triggered();
    void on_action_Crop_triggered();
    void on_actionStep2_fm_triggered();
    void on_actionStep1_fm_triggered();
    void on_action_Palette_triggered();
    void on_actionVisualize_motion_vectors_triggered();
    void on_actionMatrixview_triggered();
    void on_action_Blur_triggered();
    void on_actionAdd_noise_triggered();
    void on_actionPainting_triggered();
    void on_actionOld_Black_and_white_triggered();
    void on_actionSwap_U_and_V_triggered();
    void on_action50_50_triggered();
    void on_action_Mirror_triggered();
    void on_action_flip_triggered();
    void on_action_Tile_triggered();
    void on_action_Remove_logo_triggered();
    void on_action_Delay_triggered();
    void on_actionScale_Tempo_triggered();
    void on_action_ExtraStereo_triggered();
    void on_actionSurroundAf_triggered();
    void on_action_Karaoke_triggered();
    void on_actionLoad_external_file_triggered();
    void on_action_Decrease_volume_triggered();
    void on_action_Increase_volume_triggered();
    void on_actionDecrease_Delay_triggered();
    void on_actionIncrease_Delay_triggered();
    void on_actionDecrease_10_triggered();
    void on_actionIncrease_10_triggered();
    void on_actionHalve_speed_triggered();
    void on_actionDouble_speed_triggered();
    void on_actionNormal_Speed_triggered();
    void on_actionRewind_10_minutes_triggered();
    void on_actionForward_10_minutes_triggered();
    void on_actionRewind_1_minute_triggered();
    void on_actionForward_1_minute_triggered();
    void on_actionRewind_10_seconds_triggered();
    void on_actionForward_10_seconds_triggered();
    void on_action_File_triggered();
    void on_action_Stop_triggered();
    void on_action_Exit_triggered();
    void on_actionMute_triggered();
    void on_action_Play_Pause_triggered();
    void on_toolButtonVolume_clicked();
    void on_sliderVolume_valueChanged(int value);
    void on_toolButtonRewind_clicked();
    void on_toolButtonForward_clicked();
    void on_sliderSeek_actionTriggered(int action);
    void on_cmdLine_returnPressed();
    void on_btnSaveLog_clicked();
    void setupLogWindow();
    void setupPlaylistWindow();
    void setupMyUi();
    void resetUi();
    void initMPlayer(QString file,int type);
    void startingPlayback();
    void updateSeekbar();
    void updateFrameDisplay();
    void setMutebtnIcon(int value);
    void togglePause();
    void toggleMute();
    void changesubAlignment(QAction *action);
    void change_framedrop(QAction *action);
    void change_osd(QAction *action);
    void changeSubTitles(QAction*);
    void changeAudioTrack(QAction*);
    void changeVideoTrack(QAction*);
    void changeChannel(QAction*);
    void changeSamplingFrequency(QAction*);
    void changeStereoMode(QAction*);
    void changeRotation(QAction*);
    void settingChanged(QString group,QString key,QString value);
    void rubberBandval(QRect *val);
    void changeAspectRatio(QAction*);
    void lengthChanged();
    void foundSubtitletrack(QStringList sl );
    void updatemetadisp();
    void mouseMoveEvent ( QMouseEvent * e );
    void hidestatus();
    void playThisfile(QString fn);
    void addfile();
    void addFolder();
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dropPlayListEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void cleanMp();
    void paused();
    void playing();
    void stopping();
    void showCtxmenuPlaylist(QContextMenuEvent *event);
    void addFolderTopl(QString fp);
    void wheelEvent ( QWheelEvent * event );
    void setEof();
    void showSeekpos(QString pos,QPoint *pt);
    void checkForNextPlayback();
    void crossfadePlay();
    void hidebusypg();
    void showtooltip(QPoint *pt);
    void hideframe();
    void loadMPlayerConfig();
    void setcmbIndex();
    void addRecentFileAndPlay(QString file);
    void playurl(QString url);
    void createShortcuts();
    //void saveActionToXml();
    void setmousewheelrole();
    void toggleFullscreen();
    void mouseDoubleClickEvent (QMouseEvent *ev);
    void saveCoverArt();
    void removelavf();
    void winExplorer(QString opt,QString path);
    void enableChannels();
    void setAqua();
    void disableStylesheet();
    int getEh();
    void readCmd();
    void connectTosever();
    void writeSettings();
    void readSettingsGeo();
    void setfbvis(bool val){bfbvis=val;}
    void  completeRestart();
    void getMessage(QString msg);
    void clearingList();
    void playNextAfterFinish(int ec,bool stop);
    void restartSeekView(int ec,bool stop);
    void pauseSeekView();
    void showMsgBox(QString msg);
    QString getFilter();
    void showPictureFlow(QString path);
    void resizeVideo(int w,int hei);
    void useidxnplay();
    QString  getaudioFilter();
    void showctxmenu(QContextMenuEvent *event);
    void pfdblClick();
    void showpg();
    void showerror(QString tex);
    void playlistVisibility(bool vis);
    void startingPlaybackframe();
    void  startProgressiveStreaming();
    void wgetDownload();
    void streamingDuration(float dur);
    void searchYT(QString searchTerm, int engine);
    void on_actionCopy_Audio_CD_triggered();
    void on_actionInternet_Radio_triggered();
    void playSCUrl(QString url,QString url2);
    void playYTUrl(const QMap<int, QString> &qualityMap, QString title);
    void addingfile();
    void removingfile();
    void ShowStop();
    void image2Pixmap(QImage &img,QPixmap &pixmap);
    void mousePressEvent(QMouseEvent *event);
    void on_toolButtonFblike_clicked();
    void on_sliderSeekFullSc_actionTriggered(int act);
    void resizeEvent ( QResizeEvent * event );
    void on_actionAdvanced_Info_triggered();
    void on_actionEnable_3D_triggered();
    void on_actionInfobar_triggered();
    void changeStereoscopicView(QAction *);
    void on_toolButtonStereoVideo_clicked();
    void on_actionWatch_as_2D_video_triggered();
    void on_actionVolume_Boost_triggered();
    void on_toolButtonVolumeBoost_clicked();
    void setStereoInputFormat(int mode);
    void hideSeek();
    bool userInactive();
    void addSubtitletrack(QStringList sl);
    void on_actionCheck_for_updates_triggered();
    void on_toolButtonVolume_pressed();
    void calculateHeight();
    void shareWithFriends(QAction *act);
    void on_actionSearch_subtitles_on_OpenSubtitles_org_triggered();
    void on_actionMini_Mode_triggered();
    void searchForSubtitle();
    void loadSubtitleOS(QString url);
    void on_actionUpload_subtitle_to_OpenSubtitles_org_triggered();
    void on_actionShare_this_playback_on_Facebook_triggered();


    void on_actionUpload_subtitle_to_OpenSubtitles_org_Advanced_triggered();
    void on_toolButtonInfo_clicked();
    void on_actionVideo_Downloader_triggered();
    void on_actionGIF_Animator_triggered();

};

#endif // PLAYERWINDOW_H
