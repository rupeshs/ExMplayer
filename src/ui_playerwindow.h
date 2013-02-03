/********************************************************************************
** Form generated from reading UI file 'playerwindow.ui'
**
** Created: Sat Feb 2 15:05:08 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERWINDOW_H
#define UI_PLAYERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "dockplaylist.h"
#include "rphlabelex.h"
#include "rphslider.h"

QT_BEGIN_NAMESPACE

class Ui_PlayerWindow
{
public:
    QAction *action_Exit;
    QAction *action_Play_Pause;
    QAction *action_Stop;
    QAction *action_File;
    QAction *actionMute;
    QAction *actionForward_10_seconds;
    QAction *actionRewind_10_seconds;
    QAction *actionForward_1_minute;
    QAction *actionRewind_1_minute;
    QAction *actionForward_10_minutes;
    QAction *actionRewind_10_minutes;
    QAction *actionNormal_Speed;
    QAction *actionIncrease_10;
    QAction *actionDecrease_10;
    QAction *actionDouble_speed;
    QAction *actionHalve_speed;
    QAction *action_Increase_volume;
    QAction *action_Decrease_volume;
    QAction *actionIncrease_Delay;
    QAction *actionDecrease_Delay;
    QAction *actionAudioDisable;
    QAction *actionLoad_external_file;
    QAction *actionStereo;
    QAction *actionSurround;
    QAction *actionFull_5_1;
    QAction *action_Karaoke;
    QAction *action8000;
    QAction *action11025;
    QAction *action12000;
    QAction *action16000;
    QAction *action22100;
    QAction *action24000;
    QAction *action32000;
    QAction *action44100;
    QAction *action48000;
    QAction *action96000;
    QAction *action192000;
    QAction *actionSurroundAf;
    QAction *action_ExtraStereo;
    QAction *actionScale_Tempo;
    QAction *action_Delay;
    QAction *actionStereomode;
    QAction *actionLeft_channel;
    QAction *actionRight_channel;
    QAction *action_Remove_logo;
    QAction *action_Tile;
    QAction *action_flip;
    QAction *action_Mirror;
    QAction *action50_50;
    QAction *actionRotate_0;
    QAction *actionRotate_1;
    QAction *actionRotate_2;
    QAction *actionRotate_3;
    QAction *action_RotateDisable;
    QAction *actionSwap_U_and_V;
    QAction *actionOld_Black_and_white;
    QAction *actionPainting;
    QAction *actionAdd_noise;
    QAction *action_Blur;
    QAction *actionMatrixview;
    QAction *actionVisualize_motion_vectors;
    QAction *action_Palette;
    QAction *actionStep1_fm;
    QAction *actionStep2_fm;
    QAction *action_ar_Auto;
    QAction *action1_1;
    QAction *action4_3;
    QAction *action16_9;
    QAction *action16_10;
    QAction *action2_21_1;
    QAction *action5_4;
    QAction *action_ar_Custom;
    QAction *action_ar_Disable;
    QAction *action3_2;
    QAction *action14_9;
    QAction *action14_10;
    QAction *action_Crop;
    QAction *actionVideoDisable;
    QAction *action_osd0;
    QAction *action_osd1;
    QAction *action_osd2;
    QAction *action_osd3;
    QAction *actionToggle_OSD;
    QAction *action_fd_Disable;
    QAction *actionSoft;
    QAction *actionHard;
    QAction *actionToggle_Frame_drop;
    QAction *actionStay_on_top;
    QAction *actionScreen_shot;
    QAction *actionStart_stop_Screenshot;
    QAction *action_Open_Screenshot_folder;
    QAction *actionFrame_step;
    QAction *action_About;
    QAction *action_Load_st;
    QAction *actionToggle_subtitle_visibility;
    QAction *action_Equalizer;
    QAction *actionVideoEqualizer;
    QAction *actionStNone;
    QAction *actionStUnload;
    QAction *actionSize_Increase;
    QAction *actionSize_Decrease;
    QAction *action_sa_Top;
    QAction *action_sa_Center;
    QAction *action_sa_Bottom;
    QAction *action_st_Move_Up;
    QAction *action_st_Move_Down;
    QAction *actionDelay_Increaser;
    QAction *actionDelay_Decrease;
    QAction *action_st_Set_Delay;
    QAction *action_AV_Set_Delay;
    QAction *actionFullscreen;
    QAction *actionAdd_file;
    QAction *actionAdd_Folder;
    QAction *actionSelected_item_s;
    QAction *actionRemove_all;
    QAction *action_Load_pl;
    QAction *action_Save_as_playlist;
    QAction *action_Media_Info;
    QAction *action_Options;
    QAction *actionVolume_Normalization;
    QAction *actionNegative;
    QAction *actionWinamp_Dsp;
    QAction *actionURL;
    QAction *actionPlay_Next_File;
    QAction *actionPlay_Previous_File;
    QAction *actionOpen_containing_folder;
    QAction *actionEnable_Closed_Captions;
    QAction *actionMedia_cutter;
    QAction *actionShowpl;
    QAction *actionFull_7_1;
    QAction *action_Help;
    QAction *actionAbout_Qt;
    QAction *actionMix_and_save;
    QAction *actionFolder;
    QAction *actionSave_cover_art;
    QAction *actionEdit_Playlist;
    QAction *actionAdd_File_to_pl;
    QAction *actionAdd_Folder_to_pl;
    QAction *actionTwins;
    QAction *actionSide_view;
    QAction *actionAudio_extrctor;
    QAction *actionIncrease_Zoom;
    QAction *actionDecrease_Zoom;
    QAction *actionMove_Left;
    QAction *actionMove_Right;
    QAction *actionMove_Up;
    QAction *actionMove_Down;
    QAction *actionIncrease_Video_quality;
    QAction *actionChange_framerate;
    QAction *actionDefault;
    QAction *actionDefault_zoom;
    QAction *actionAudio_Converter;
    QAction *actionSmallmode;
    QAction *actionCopy_Audio_CD;
    QAction *actionInternet_Radio;
    QWidget *centralWidget;
    QLCDNumber *lcdCurPos;
    QLCDNumber *lcdDuration;
    QProgressBar *progressBarBusy;
    QLabel *labelStatus;
    QLabel *labelSpeed;
    QLabel *labelCpuAudio;
    QLabel *labelFrameCount;
    QLabel *labelAVdelay;
    QLabel *labelCpuVideo;
    rphSlider *sliderSeek;
    rphSlider *sliderVolume;
    QToolButton *toolButtonRewind;
    QToolButton *toolButtonForward;
    QToolButton *toolButtonVolume;
    rphLabelEx *label_display;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QFrame *page_ve;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    rphSlider *gamma;
    rphSlider *contrast;
    rphSlider *brightness;
    rphSlider *Hue;
    rphSlider *Saturation;
    QLabel *label_3;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *btnVEReset;
    QWidget *tabWidgetPage2;
    QFrame *page_ae;
    QPushButton *btnAEReset;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    rphSlider *eq0;
    rphSlider *eq1;
    rphSlider *eq2;
    rphSlider *eq3;
    rphSlider *eq4;
    rphSlider *eq5;
    rphSlider *eq6;
    rphSlider *eq7;
    rphSlider *eq8;
    rphSlider *eq9;
    QComboBox *comboBox;
    QCheckBox *cbEnableAEq;
    QToolButton *toolButtonfs;
    QToolButton *toolButtonLpl;
    QToolButton *toolButtonAdd;
    QToolButton *toolButtonRemove;
    QToolButton *toolButton_loop;
    QToolButton *toolButton_shuffle;
    QToolButton *toolButton_playpre;
    QToolButton *toolButton_playnext;
    QToolButton *toolButtonSpeed;
    QToolButton *toolButtonplaylist;
    QLabel *labToolbarSpace;
    QLabel *labVD;
    QLabel *labAD;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu_Open;
    QMenu *menuPlay;
    QMenu *menuSpeed;
    QMenu *menuFa_mily_Friendly_mode;
    QMenu *menu_Audio;
    QMenu *menuAudio_Track;
    QMenu *menuC_hannels;
    QMenu *menu_Filters;
    QMenu *menu_Resample;
    QMenu *menu_Video;
    QMenu *menu_Filters_2;
    QMenu *menu_Rotate;
    QMenu *menuA_spect_ratio;
    QMenu *menuVideo_Track;
    QMenu *menuOSD;
    QMenu *menuFrame_drop;
    QMenu *menuZoom;
    QMenu *menuFrame_rate_fps;
    QMenu *menu_Subtitles;
    QMenu *menuSelect;
    QMenu *menu_Help;
    QMenu *menuPlaylist;
    QMenu *menuAdd;
    QMenu *menu_Remove;
    QMenu *menu_Tools;
    QMenu *menu_View;
    QDockWidget *dockBrowser;
    QWidget *dockWidgetContents_3;
    dockPlayList *dock_Playlist;
    QWidget *dockWidgetContents_4;
    QFrame *frame_playlist;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QToolBar *toolBarPlaylist;
    QDockWidget *dock_Filter;
    QWidget *dockWidgetContents_2;
    QToolBar *toolBarStatus;
    QToolBar *toolBarSeek;
    QToolBar *toolBarSeekBar;
    QDockWidget *dock_log;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QFrame *frame_log;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTextEdit *mpconsole;
    QLineEdit *cmdLine;
    QToolButton *btnSaveLog;

    void setupUi(QMainWindow *PlayerWindow)
    {
        if (PlayerWindow->objectName().isEmpty())
            PlayerWindow->setObjectName(QString::fromUtf8("PlayerWindow"));
        PlayerWindow->resize(813, 609);
        PlayerWindow->setMinimumSize(QSize(450, 145));
        PlayerWindow->setMouseTracking(true);
        PlayerWindow->setFocusPolicy(Qt::StrongFocus);
        PlayerWindow->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/ExMplayer.png"), QSize(), QIcon::Normal, QIcon::Off);
        PlayerWindow->setWindowIcon(icon);
        PlayerWindow->setWindowOpacity(1);
        PlayerWindow->setStyleSheet(QString::fromUtf8(""));
        PlayerWindow->setAnimated(true);
        PlayerWindow->setDocumentMode(false);
        PlayerWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        action_Exit = new QAction(PlayerWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Exit->setIcon(icon1);
        action_Play_Pause = new QAction(PlayerWindow);
        action_Play_Pause->setObjectName(QString::fromUtf8("action_Play_Pause"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Play_Pause->setIcon(icon2);
        action_Stop = new QAction(PlayerWindow);
        action_Stop->setObjectName(QString::fromUtf8("action_Stop"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Stop->setIcon(icon3);
        action_File = new QAction(PlayerWindow);
        action_File->setObjectName(QString::fromUtf8("action_File"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/audiofile.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_File->setIcon(icon4);
        action_File->setPriority(QAction::HighPriority);
        actionMute = new QAction(PlayerWindow);
        actionMute->setObjectName(QString::fromUtf8("actionMute"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/mute.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMute->setIcon(icon5);
        actionForward_10_seconds = new QAction(PlayerWindow);
        actionForward_10_seconds->setObjectName(QString::fromUtf8("actionForward_10_seconds"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/f10s.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionForward_10_seconds->setIcon(icon6);
        actionRewind_10_seconds = new QAction(PlayerWindow);
        actionRewind_10_seconds->setObjectName(QString::fromUtf8("actionRewind_10_seconds"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/r10s.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRewind_10_seconds->setIcon(icon7);
        actionForward_1_minute = new QAction(PlayerWindow);
        actionForward_1_minute->setObjectName(QString::fromUtf8("actionForward_1_minute"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/f1m.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionForward_1_minute->setIcon(icon8);
        actionRewind_1_minute = new QAction(PlayerWindow);
        actionRewind_1_minute->setObjectName(QString::fromUtf8("actionRewind_1_minute"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/r1min.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRewind_1_minute->setIcon(icon9);
        actionForward_10_minutes = new QAction(PlayerWindow);
        actionForward_10_minutes->setObjectName(QString::fromUtf8("actionForward_10_minutes"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/f10m.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionForward_10_minutes->setIcon(icon10);
        actionRewind_10_minutes = new QAction(PlayerWindow);
        actionRewind_10_minutes->setObjectName(QString::fromUtf8("actionRewind_10_minutes"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/r10m.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRewind_10_minutes->setIcon(icon11);
        actionNormal_Speed = new QAction(PlayerWindow);
        actionNormal_Speed->setObjectName(QString::fromUtf8("actionNormal_Speed"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/images/normalspeed.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNormal_Speed->setIcon(icon12);
        actionIncrease_10 = new QAction(PlayerWindow);
        actionIncrease_10->setObjectName(QString::fromUtf8("actionIncrease_10"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/images/addfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionIncrease_10->setIcon(icon13);
        actionDecrease_10 = new QAction(PlayerWindow);
        actionDecrease_10->setObjectName(QString::fromUtf8("actionDecrease_10"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/images/removefile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDecrease_10->setIcon(icon14);
        actionDouble_speed = new QAction(PlayerWindow);
        actionDouble_speed->setObjectName(QString::fromUtf8("actionDouble_speed"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/images/doublespeed.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDouble_speed->setIcon(icon15);
        actionHalve_speed = new QAction(PlayerWindow);
        actionHalve_speed->setObjectName(QString::fromUtf8("actionHalve_speed"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/images/halfspeed.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHalve_speed->setIcon(icon16);
        action_Increase_volume = new QAction(PlayerWindow);
        action_Increase_volume->setObjectName(QString::fromUtf8("action_Increase_volume"));
        action_Increase_volume->setIcon(icon13);
        action_Decrease_volume = new QAction(PlayerWindow);
        action_Decrease_volume->setObjectName(QString::fromUtf8("action_Decrease_volume"));
        action_Decrease_volume->setIcon(icon14);
        actionIncrease_Delay = new QAction(PlayerWindow);
        actionIncrease_Delay->setObjectName(QString::fromUtf8("actionIncrease_Delay"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/images/ad_up.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionIncrease_Delay->setIcon(icon17);
        actionDecrease_Delay = new QAction(PlayerWindow);
        actionDecrease_Delay->setObjectName(QString::fromUtf8("actionDecrease_Delay"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/images/ad_down.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDecrease_Delay->setIcon(icon18);
        actionAudioDisable = new QAction(PlayerWindow);
        actionAudioDisable->setObjectName(QString::fromUtf8("actionAudioDisable"));
        actionAudioDisable->setCheckable(true);
        actionLoad_external_file = new QAction(PlayerWindow);
        actionLoad_external_file->setObjectName(QString::fromUtf8("actionLoad_external_file"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/images/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_external_file->setIcon(icon19);
        actionStereo = new QAction(PlayerWindow);
        actionStereo->setObjectName(QString::fromUtf8("actionStereo"));
        actionStereo->setCheckable(true);
        actionSurround = new QAction(PlayerWindow);
        actionSurround->setObjectName(QString::fromUtf8("actionSurround"));
        actionSurround->setCheckable(true);
        actionFull_5_1 = new QAction(PlayerWindow);
        actionFull_5_1->setObjectName(QString::fromUtf8("actionFull_5_1"));
        actionFull_5_1->setCheckable(true);
        action_Karaoke = new QAction(PlayerWindow);
        action_Karaoke->setObjectName(QString::fromUtf8("action_Karaoke"));
        action_Karaoke->setCheckable(true);
        action8000 = new QAction(PlayerWindow);
        action8000->setObjectName(QString::fromUtf8("action8000"));
        action8000->setCheckable(true);
        action11025 = new QAction(PlayerWindow);
        action11025->setObjectName(QString::fromUtf8("action11025"));
        action11025->setCheckable(true);
        action12000 = new QAction(PlayerWindow);
        action12000->setObjectName(QString::fromUtf8("action12000"));
        action12000->setCheckable(true);
        action16000 = new QAction(PlayerWindow);
        action16000->setObjectName(QString::fromUtf8("action16000"));
        action16000->setCheckable(true);
        action22100 = new QAction(PlayerWindow);
        action22100->setObjectName(QString::fromUtf8("action22100"));
        action22100->setCheckable(true);
        action24000 = new QAction(PlayerWindow);
        action24000->setObjectName(QString::fromUtf8("action24000"));
        action24000->setCheckable(true);
        action32000 = new QAction(PlayerWindow);
        action32000->setObjectName(QString::fromUtf8("action32000"));
        action32000->setCheckable(true);
        action44100 = new QAction(PlayerWindow);
        action44100->setObjectName(QString::fromUtf8("action44100"));
        action44100->setCheckable(true);
        action48000 = new QAction(PlayerWindow);
        action48000->setObjectName(QString::fromUtf8("action48000"));
        action48000->setCheckable(true);
        action96000 = new QAction(PlayerWindow);
        action96000->setObjectName(QString::fromUtf8("action96000"));
        action96000->setCheckable(true);
        action192000 = new QAction(PlayerWindow);
        action192000->setObjectName(QString::fromUtf8("action192000"));
        action192000->setCheckable(true);
        actionSurroundAf = new QAction(PlayerWindow);
        actionSurroundAf->setObjectName(QString::fromUtf8("actionSurroundAf"));
        action_ExtraStereo = new QAction(PlayerWindow);
        action_ExtraStereo->setObjectName(QString::fromUtf8("action_ExtraStereo"));
        actionScale_Tempo = new QAction(PlayerWindow);
        actionScale_Tempo->setObjectName(QString::fromUtf8("actionScale_Tempo"));
        action_Delay = new QAction(PlayerWindow);
        action_Delay->setObjectName(QString::fromUtf8("action_Delay"));
        actionStereomode = new QAction(PlayerWindow);
        actionStereomode->setObjectName(QString::fromUtf8("actionStereomode"));
        actionStereomode->setCheckable(true);
        actionLeft_channel = new QAction(PlayerWindow);
        actionLeft_channel->setObjectName(QString::fromUtf8("actionLeft_channel"));
        actionLeft_channel->setCheckable(true);
        actionRight_channel = new QAction(PlayerWindow);
        actionRight_channel->setObjectName(QString::fromUtf8("actionRight_channel"));
        actionRight_channel->setCheckable(true);
        action_Remove_logo = new QAction(PlayerWindow);
        action_Remove_logo->setObjectName(QString::fromUtf8("action_Remove_logo"));
        action_Remove_logo->setCheckable(true);
        action_Tile = new QAction(PlayerWindow);
        action_Tile->setObjectName(QString::fromUtf8("action_Tile"));
        action_Tile->setCheckable(true);
        action_flip = new QAction(PlayerWindow);
        action_flip->setObjectName(QString::fromUtf8("action_flip"));
        action_flip->setCheckable(true);
        action_Mirror = new QAction(PlayerWindow);
        action_Mirror->setObjectName(QString::fromUtf8("action_Mirror"));
        action_Mirror->setCheckable(true);
        action50_50 = new QAction(PlayerWindow);
        action50_50->setObjectName(QString::fromUtf8("action50_50"));
        action50_50->setCheckable(true);
        actionRotate_0 = new QAction(PlayerWindow);
        actionRotate_0->setObjectName(QString::fromUtf8("actionRotate_0"));
        actionRotate_0->setCheckable(true);
        actionRotate_1 = new QAction(PlayerWindow);
        actionRotate_1->setObjectName(QString::fromUtf8("actionRotate_1"));
        actionRotate_1->setCheckable(true);
        actionRotate_2 = new QAction(PlayerWindow);
        actionRotate_2->setObjectName(QString::fromUtf8("actionRotate_2"));
        actionRotate_2->setCheckable(true);
        actionRotate_3 = new QAction(PlayerWindow);
        actionRotate_3->setObjectName(QString::fromUtf8("actionRotate_3"));
        actionRotate_3->setCheckable(true);
        action_RotateDisable = new QAction(PlayerWindow);
        action_RotateDisable->setObjectName(QString::fromUtf8("action_RotateDisable"));
        action_RotateDisable->setCheckable(true);
        actionSwap_U_and_V = new QAction(PlayerWindow);
        actionSwap_U_and_V->setObjectName(QString::fromUtf8("actionSwap_U_and_V"));
        actionSwap_U_and_V->setCheckable(true);
        actionOld_Black_and_white = new QAction(PlayerWindow);
        actionOld_Black_and_white->setObjectName(QString::fromUtf8("actionOld_Black_and_white"));
        actionOld_Black_and_white->setCheckable(true);
        actionPainting = new QAction(PlayerWindow);
        actionPainting->setObjectName(QString::fromUtf8("actionPainting"));
        actionPainting->setCheckable(true);
        actionAdd_noise = new QAction(PlayerWindow);
        actionAdd_noise->setObjectName(QString::fromUtf8("actionAdd_noise"));
        actionAdd_noise->setCheckable(true);
        action_Blur = new QAction(PlayerWindow);
        action_Blur->setObjectName(QString::fromUtf8("action_Blur"));
        action_Blur->setCheckable(true);
        actionMatrixview = new QAction(PlayerWindow);
        actionMatrixview->setObjectName(QString::fromUtf8("actionMatrixview"));
        actionMatrixview->setCheckable(true);
        actionVisualize_motion_vectors = new QAction(PlayerWindow);
        actionVisualize_motion_vectors->setObjectName(QString::fromUtf8("actionVisualize_motion_vectors"));
        actionVisualize_motion_vectors->setCheckable(true);
        action_Palette = new QAction(PlayerWindow);
        action_Palette->setObjectName(QString::fromUtf8("action_Palette"));
        action_Palette->setCheckable(true);
        actionStep1_fm = new QAction(PlayerWindow);
        actionStep1_fm->setObjectName(QString::fromUtf8("actionStep1_fm"));
        actionStep2_fm = new QAction(PlayerWindow);
        actionStep2_fm->setObjectName(QString::fromUtf8("actionStep2_fm"));
        action_ar_Auto = new QAction(PlayerWindow);
        action_ar_Auto->setObjectName(QString::fromUtf8("action_ar_Auto"));
        action_ar_Auto->setCheckable(true);
        action1_1 = new QAction(PlayerWindow);
        action1_1->setObjectName(QString::fromUtf8("action1_1"));
        action1_1->setCheckable(true);
        action4_3 = new QAction(PlayerWindow);
        action4_3->setObjectName(QString::fromUtf8("action4_3"));
        action4_3->setCheckable(true);
        action16_9 = new QAction(PlayerWindow);
        action16_9->setObjectName(QString::fromUtf8("action16_9"));
        action16_9->setCheckable(true);
        action16_10 = new QAction(PlayerWindow);
        action16_10->setObjectName(QString::fromUtf8("action16_10"));
        action16_10->setCheckable(true);
        action2_21_1 = new QAction(PlayerWindow);
        action2_21_1->setObjectName(QString::fromUtf8("action2_21_1"));
        action2_21_1->setCheckable(true);
        action5_4 = new QAction(PlayerWindow);
        action5_4->setObjectName(QString::fromUtf8("action5_4"));
        action5_4->setCheckable(true);
        action_ar_Custom = new QAction(PlayerWindow);
        action_ar_Custom->setObjectName(QString::fromUtf8("action_ar_Custom"));
        action_ar_Custom->setCheckable(true);
        action_ar_Disable = new QAction(PlayerWindow);
        action_ar_Disable->setObjectName(QString::fromUtf8("action_ar_Disable"));
        action_ar_Disable->setCheckable(true);
        action3_2 = new QAction(PlayerWindow);
        action3_2->setObjectName(QString::fromUtf8("action3_2"));
        action3_2->setCheckable(true);
        action14_9 = new QAction(PlayerWindow);
        action14_9->setObjectName(QString::fromUtf8("action14_9"));
        action14_9->setCheckable(true);
        action14_10 = new QAction(PlayerWindow);
        action14_10->setObjectName(QString::fromUtf8("action14_10"));
        action14_10->setCheckable(true);
        action_Crop = new QAction(PlayerWindow);
        action_Crop->setObjectName(QString::fromUtf8("action_Crop"));
        action_Crop->setCheckable(true);
        actionVideoDisable = new QAction(PlayerWindow);
        actionVideoDisable->setObjectName(QString::fromUtf8("actionVideoDisable"));
        actionVideoDisable->setCheckable(true);
        action_osd0 = new QAction(PlayerWindow);
        action_osd0->setObjectName(QString::fromUtf8("action_osd0"));
        action_osd0->setCheckable(true);
        action_osd1 = new QAction(PlayerWindow);
        action_osd1->setObjectName(QString::fromUtf8("action_osd1"));
        action_osd1->setCheckable(true);
        action_osd2 = new QAction(PlayerWindow);
        action_osd2->setObjectName(QString::fromUtf8("action_osd2"));
        action_osd2->setCheckable(true);
        action_osd3 = new QAction(PlayerWindow);
        action_osd3->setObjectName(QString::fromUtf8("action_osd3"));
        action_osd3->setCheckable(true);
        actionToggle_OSD = new QAction(PlayerWindow);
        actionToggle_OSD->setObjectName(QString::fromUtf8("actionToggle_OSD"));
        action_fd_Disable = new QAction(PlayerWindow);
        action_fd_Disable->setObjectName(QString::fromUtf8("action_fd_Disable"));
        action_fd_Disable->setCheckable(true);
        action_fd_Disable->setChecked(true);
        actionSoft = new QAction(PlayerWindow);
        actionSoft->setObjectName(QString::fromUtf8("actionSoft"));
        actionSoft->setCheckable(true);
        actionHard = new QAction(PlayerWindow);
        actionHard->setObjectName(QString::fromUtf8("actionHard"));
        actionHard->setCheckable(true);
        actionToggle_Frame_drop = new QAction(PlayerWindow);
        actionToggle_Frame_drop->setObjectName(QString::fromUtf8("actionToggle_Frame_drop"));
        actionStay_on_top = new QAction(PlayerWindow);
        actionStay_on_top->setObjectName(QString::fromUtf8("actionStay_on_top"));
        actionStay_on_top->setCheckable(true);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/images/top.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStay_on_top->setIcon(icon20);
        actionScreen_shot = new QAction(PlayerWindow);
        actionScreen_shot->setObjectName(QString::fromUtf8("actionScreen_shot"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/images/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScreen_shot->setIcon(icon21);
        actionStart_stop_Screenshot = new QAction(PlayerWindow);
        actionStart_stop_Screenshot->setObjectName(QString::fromUtf8("actionStart_stop_Screenshot"));
        actionStart_stop_Screenshot->setIcon(icon21);
        action_Open_Screenshot_folder = new QAction(PlayerWindow);
        action_Open_Screenshot_folder->setObjectName(QString::fromUtf8("action_Open_Screenshot_folder"));
        action_Open_Screenshot_folder->setIcon(icon19);
        action_Open_Screenshot_folder->setShortcutContext(Qt::WidgetShortcut);
        action_Open_Screenshot_folder->setMenuRole(QAction::TextHeuristicRole);
        actionFrame_step = new QAction(PlayerWindow);
        actionFrame_step->setObjectName(QString::fromUtf8("actionFrame_step"));
        action_About = new QAction(PlayerWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_About->setIcon(icon);
        action_Load_st = new QAction(PlayerWindow);
        action_Load_st->setObjectName(QString::fromUtf8("action_Load_st"));
        action_Load_st->setIcon(icon19);
        actionToggle_subtitle_visibility = new QAction(PlayerWindow);
        actionToggle_subtitle_visibility->setObjectName(QString::fromUtf8("actionToggle_subtitle_visibility"));
        actionToggle_subtitle_visibility->setCheckable(true);
        action_Equalizer = new QAction(PlayerWindow);
        action_Equalizer->setObjectName(QString::fromUtf8("action_Equalizer"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/images/equalizer.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Equalizer->setIcon(icon22);
        actionVideoEqualizer = new QAction(PlayerWindow);
        actionVideoEqualizer->setObjectName(QString::fromUtf8("actionVideoEqualizer"));
        actionStNone = new QAction(PlayerWindow);
        actionStNone->setObjectName(QString::fromUtf8("actionStNone"));
        actionStNone->setCheckable(true);
        actionStUnload = new QAction(PlayerWindow);
        actionStUnload->setObjectName(QString::fromUtf8("actionStUnload"));
        actionSize_Increase = new QAction(PlayerWindow);
        actionSize_Increase->setObjectName(QString::fromUtf8("actionSize_Increase"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/images/sub_zoom in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSize_Increase->setIcon(icon23);
        actionSize_Decrease = new QAction(PlayerWindow);
        actionSize_Decrease->setObjectName(QString::fromUtf8("actionSize_Decrease"));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/images/sub_zoom out.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSize_Decrease->setIcon(icon24);
        action_sa_Top = new QAction(PlayerWindow);
        action_sa_Top->setObjectName(QString::fromUtf8("action_sa_Top"));
        action_sa_Top->setCheckable(true);
        action_sa_Center = new QAction(PlayerWindow);
        action_sa_Center->setObjectName(QString::fromUtf8("action_sa_Center"));
        action_sa_Center->setCheckable(true);
        action_sa_Bottom = new QAction(PlayerWindow);
        action_sa_Bottom->setObjectName(QString::fromUtf8("action_sa_Bottom"));
        action_sa_Bottom->setCheckable(true);
        action_st_Move_Up = new QAction(PlayerWindow);
        action_st_Move_Up->setObjectName(QString::fromUtf8("action_st_Move_Up"));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/images/sub_up.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_st_Move_Up->setIcon(icon25);
        action_st_Move_Down = new QAction(PlayerWindow);
        action_st_Move_Down->setObjectName(QString::fromUtf8("action_st_Move_Down"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/images/sub_down.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_st_Move_Down->setIcon(icon26);
        actionDelay_Increaser = new QAction(PlayerWindow);
        actionDelay_Increaser->setObjectName(QString::fromUtf8("actionDelay_Increaser"));
        actionDelay_Increaser->setIcon(icon13);
        actionDelay_Decrease = new QAction(PlayerWindow);
        actionDelay_Decrease->setObjectName(QString::fromUtf8("actionDelay_Decrease"));
        actionDelay_Decrease->setIcon(icon14);
        action_st_Set_Delay = new QAction(PlayerWindow);
        action_st_Set_Delay->setObjectName(QString::fromUtf8("action_st_Set_Delay"));
        action_AV_Set_Delay = new QAction(PlayerWindow);
        action_AV_Set_Delay->setObjectName(QString::fromUtf8("action_AV_Set_Delay"));
        actionFullscreen = new QAction(PlayerWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/images/fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFullscreen->setIcon(icon27);
        actionAdd_file = new QAction(PlayerWindow);
        actionAdd_file->setObjectName(QString::fromUtf8("actionAdd_file"));
        actionAdd_file->setIcon(icon4);
        actionAdd_Folder = new QAction(PlayerWindow);
        actionAdd_Folder->setObjectName(QString::fromUtf8("actionAdd_Folder"));
        actionAdd_Folder->setIcon(icon19);
        actionSelected_item_s = new QAction(PlayerWindow);
        actionSelected_item_s->setObjectName(QString::fromUtf8("actionSelected_item_s"));
        actionRemove_all = new QAction(PlayerWindow);
        actionRemove_all->setObjectName(QString::fromUtf8("actionRemove_all"));
        action_Load_pl = new QAction(PlayerWindow);
        action_Load_pl->setObjectName(QString::fromUtf8("action_Load_pl"));
        action_Load_pl->setIcon(icon19);
        action_Save_as_playlist = new QAction(PlayerWindow);
        action_Save_as_playlist->setObjectName(QString::fromUtf8("action_Save_as_playlist"));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/images/filesave .png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Save_as_playlist->setIcon(icon28);
        action_Media_Info = new QAction(PlayerWindow);
        action_Media_Info->setObjectName(QString::fromUtf8("action_Media_Info"));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/images/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Media_Info->setIcon(icon29);
        action_Options = new QAction(PlayerWindow);
        action_Options->setObjectName(QString::fromUtf8("action_Options"));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/images/options.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Options->setIcon(icon30);
        actionVolume_Normalization = new QAction(PlayerWindow);
        actionVolume_Normalization->setObjectName(QString::fromUtf8("actionVolume_Normalization"));
        actionVolume_Normalization->setCheckable(true);
        actionNegative = new QAction(PlayerWindow);
        actionNegative->setObjectName(QString::fromUtf8("actionNegative"));
        actionNegative->setCheckable(true);
        actionWinamp_Dsp = new QAction(PlayerWindow);
        actionWinamp_Dsp->setObjectName(QString::fromUtf8("actionWinamp_Dsp"));
        actionURL = new QAction(PlayerWindow);
        actionURL->setObjectName(QString::fromUtf8("actionURL"));
        QIcon icon31;
        icon31.addFile(QString::fromUtf8(":/images/net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionURL->setIcon(icon31);
        actionPlay_Next_File = new QAction(PlayerWindow);
        actionPlay_Next_File->setObjectName(QString::fromUtf8("actionPlay_Next_File"));
        QIcon icon32;
        icon32.addFile(QString::fromUtf8(":/images/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlay_Next_File->setIcon(icon32);
        actionPlay_Previous_File = new QAction(PlayerWindow);
        actionPlay_Previous_File->setObjectName(QString::fromUtf8("actionPlay_Previous_File"));
        QIcon icon33;
        icon33.addFile(QString::fromUtf8(":/images/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlay_Previous_File->setIcon(icon33);
        actionOpen_containing_folder = new QAction(PlayerWindow);
        actionOpen_containing_folder->setObjectName(QString::fromUtf8("actionOpen_containing_folder"));
        actionOpen_containing_folder->setIcon(icon19);
        actionEnable_Closed_Captions = new QAction(PlayerWindow);
        actionEnable_Closed_Captions->setObjectName(QString::fromUtf8("actionEnable_Closed_Captions"));
        actionEnable_Closed_Captions->setCheckable(true);
        actionMedia_cutter = new QAction(PlayerWindow);
        actionMedia_cutter->setObjectName(QString::fromUtf8("actionMedia_cutter"));
        QIcon icon34;
        icon34.addFile(QString::fromUtf8(":/images/mediacutter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMedia_cutter->setIcon(icon34);
        actionShowpl = new QAction(PlayerWindow);
        actionShowpl->setObjectName(QString::fromUtf8("actionShowpl"));
        QIcon icon35;
        icon35.addFile(QString::fromUtf8(":/images/playlist.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowpl->setIcon(icon35);
        actionFull_7_1 = new QAction(PlayerWindow);
        actionFull_7_1->setObjectName(QString::fromUtf8("actionFull_7_1"));
        actionFull_7_1->setCheckable(true);
        action_Help = new QAction(PlayerWindow);
        action_Help->setObjectName(QString::fromUtf8("action_Help"));
        QIcon icon36;
        icon36.addFile(QString::fromUtf8(":/images/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Help->setIcon(icon36);
        actionAbout_Qt = new QAction(PlayerWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        QIcon icon37;
        icon37.addFile(QString::fromUtf8(":/images/qt_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_Qt->setIcon(icon37);
        actionMix_and_save = new QAction(PlayerWindow);
        actionMix_and_save->setObjectName(QString::fromUtf8("actionMix_and_save"));
        actionFolder = new QAction(PlayerWindow);
        actionFolder->setObjectName(QString::fromUtf8("actionFolder"));
        actionFolder->setIcon(icon19);
        actionSave_cover_art = new QAction(PlayerWindow);
        actionSave_cover_art->setObjectName(QString::fromUtf8("actionSave_cover_art"));
        actionSave_cover_art->setIcon(icon28);
        actionEdit_Playlist = new QAction(PlayerWindow);
        actionEdit_Playlist->setObjectName(QString::fromUtf8("actionEdit_Playlist"));
        actionEdit_Playlist->setIcon(icon35);
        actionAdd_File_to_pl = new QAction(PlayerWindow);
        actionAdd_File_to_pl->setObjectName(QString::fromUtf8("actionAdd_File_to_pl"));
        actionAdd_File_to_pl->setIcon(icon4);
        actionAdd_Folder_to_pl = new QAction(PlayerWindow);
        actionAdd_Folder_to_pl->setObjectName(QString::fromUtf8("actionAdd_Folder_to_pl"));
        actionAdd_Folder_to_pl->setIcon(icon19);
        actionTwins = new QAction(PlayerWindow);
        actionTwins->setObjectName(QString::fromUtf8("actionTwins"));
        actionTwins->setCheckable(true);
        actionSide_view = new QAction(PlayerWindow);
        actionSide_view->setObjectName(QString::fromUtf8("actionSide_view"));
        actionSide_view->setCheckable(true);
        actionAudio_extrctor = new QAction(PlayerWindow);
        actionAudio_extrctor->setObjectName(QString::fromUtf8("actionAudio_extrctor"));
        actionIncrease_Zoom = new QAction(PlayerWindow);
        actionIncrease_Zoom->setObjectName(QString::fromUtf8("actionIncrease_Zoom"));
        QIcon icon38;
        icon38.addFile(QString::fromUtf8(":/images/zoom_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionIncrease_Zoom->setIcon(icon38);
        actionDecrease_Zoom = new QAction(PlayerWindow);
        actionDecrease_Zoom->setObjectName(QString::fromUtf8("actionDecrease_Zoom"));
        QIcon icon39;
        icon39.addFile(QString::fromUtf8(":/images/zoom_out.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDecrease_Zoom->setIcon(icon39);
        actionMove_Left = new QAction(PlayerWindow);
        actionMove_Left->setObjectName(QString::fromUtf8("actionMove_Left"));
        actionMove_Right = new QAction(PlayerWindow);
        actionMove_Right->setObjectName(QString::fromUtf8("actionMove_Right"));
        actionMove_Up = new QAction(PlayerWindow);
        actionMove_Up->setObjectName(QString::fromUtf8("actionMove_Up"));
        actionMove_Down = new QAction(PlayerWindow);
        actionMove_Down->setObjectName(QString::fromUtf8("actionMove_Down"));
        actionIncrease_Video_quality = new QAction(PlayerWindow);
        actionIncrease_Video_quality->setObjectName(QString::fromUtf8("actionIncrease_Video_quality"));
        actionIncrease_Video_quality->setCheckable(true);
        actionChange_framerate = new QAction(PlayerWindow);
        actionChange_framerate->setObjectName(QString::fromUtf8("actionChange_framerate"));
        actionDefault = new QAction(PlayerWindow);
        actionDefault->setObjectName(QString::fromUtf8("actionDefault"));
        actionDefault_zoom = new QAction(PlayerWindow);
        actionDefault_zoom->setObjectName(QString::fromUtf8("actionDefault_zoom"));
        actionAudio_Converter = new QAction(PlayerWindow);
        actionAudio_Converter->setObjectName(QString::fromUtf8("actionAudio_Converter"));
        actionSmallmode = new QAction(PlayerWindow);
        actionSmallmode->setObjectName(QString::fromUtf8("actionSmallmode"));
        actionSmallmode->setVisible(false);
        actionCopy_Audio_CD = new QAction(PlayerWindow);
        actionCopy_Audio_CD->setObjectName(QString::fromUtf8("actionCopy_Audio_CD"));
        actionInternet_Radio = new QAction(PlayerWindow);
        actionInternet_Radio->setObjectName(QString::fromUtf8("actionInternet_Radio"));
        centralWidget = new QWidget(PlayerWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMouseTracking(true);
        lcdCurPos = new QLCDNumber(centralWidget);
        lcdCurPos->setObjectName(QString::fromUtf8("lcdCurPos"));
        lcdCurPos->setGeometry(QRect(360, 240, 71, 21));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lcdCurPos->sizePolicy().hasHeightForWidth());
        lcdCurPos->setSizePolicy(sizePolicy);
        lcdCurPos->setMaximumSize(QSize(71, 21));
        lcdCurPos->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        lcdCurPos->setFrameShape(QFrame::Box);
        lcdCurPos->setFrameShadow(QFrame::Plain);
        lcdCurPos->setLineWidth(0);
        lcdCurPos->setMidLineWidth(0);
        lcdCurPos->setSmallDecimalPoint(true);
        lcdCurPos->setNumDigits(8);
        lcdCurPos->setSegmentStyle(QLCDNumber::Flat);
        lcdDuration = new QLCDNumber(centralWidget);
        lcdDuration->setObjectName(QString::fromUtf8("lcdDuration"));
        lcdDuration->setGeometry(QRect(440, 240, 71, 21));
        sizePolicy.setHeightForWidth(lcdDuration->sizePolicy().hasHeightForWidth());
        lcdDuration->setSizePolicy(sizePolicy);
        lcdDuration->setMaximumSize(QSize(71, 21));
        lcdDuration->setStyleSheet(QString::fromUtf8("color: rgb(79, 111, 255);"));
        lcdDuration->setFrameShape(QFrame::Box);
        lcdDuration->setFrameShadow(QFrame::Plain);
        lcdDuration->setLineWidth(0);
        lcdDuration->setMidLineWidth(3);
        lcdDuration->setSmallDecimalPoint(true);
        lcdDuration->setNumDigits(8);
        lcdDuration->setMode(QLCDNumber::Dec);
        lcdDuration->setSegmentStyle(QLCDNumber::Flat);
        progressBarBusy = new QProgressBar(centralWidget);
        progressBarBusy->setObjectName(QString::fromUtf8("progressBarBusy"));
        progressBarBusy->setGeometry(QRect(200, 240, 81, 16));
        sizePolicy.setHeightForWidth(progressBarBusy->sizePolicy().hasHeightForWidth());
        progressBarBusy->setSizePolicy(sizePolicy);
        progressBarBusy->setMinimumSize(QSize(81, 16));
        progressBarBusy->setMaximumSize(QSize(81, 16));
        progressBarBusy->setStyleSheet(QString::fromUtf8("QProgressBar { \n"
"border: 2px solid lightblue;\n"
"border-radius: 5px;\n"
"\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"background-color:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 150), stop:1 rgba(255, 255, 255, 100));\n"
"width: 20px;\n"
"}"));
        progressBarBusy->setValue(0);
        progressBarBusy->setTextVisible(false);
        labelStatus = new QLabel(centralWidget);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setGeometry(QRect(10, 240, 31, 16));
        labelSpeed = new QLabel(centralWidget);
        labelSpeed->setObjectName(QString::fromUtf8("labelSpeed"));
        labelSpeed->setGeometry(QRect(160, 240, 28, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelSpeed->sizePolicy().hasHeightForWidth());
        labelSpeed->setSizePolicy(sizePolicy1);
        labelSpeed->setStyleSheet(QString::fromUtf8("color: grey;"));
        labelCpuAudio = new QLabel(centralWidget);
        labelCpuAudio->setObjectName(QString::fromUtf8("labelCpuAudio"));
        labelCpuAudio->setGeometry(QRect(130, 240, 17, 16));
        labelCpuAudio->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        labelFrameCount = new QLabel(centralWidget);
        labelFrameCount->setObjectName(QString::fromUtf8("labelFrameCount"));
        labelFrameCount->setGeometry(QRect(58, 240, 16, 16));
        labelFrameCount->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);\n"
""));
        labelAVdelay = new QLabel(centralWidget);
        labelAVdelay->setObjectName(QString::fromUtf8("labelAVdelay"));
        labelAVdelay->setGeometry(QRect(80, 240, 16, 21));
        labelAVdelay->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        labelCpuVideo = new QLabel(centralWidget);
        labelCpuVideo->setObjectName(QString::fromUtf8("labelCpuVideo"));
        labelCpuVideo->setGeometry(QRect(100, 240, 17, 16));
        labelCpuVideo->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        sliderSeek = new rphSlider(centralWidget);
        sliderSeek->setObjectName(QString::fromUtf8("sliderSeek"));
        sliderSeek->setGeometry(QRect(90, 210, 84, 21));
        sliderSeek->setCursor(QCursor(Qt::ArrowCursor));
        sliderSeek->setMouseTracking(true);
        sliderSeek->setStyleSheet(QString::fromUtf8(""));
        sliderSeek->setMinimum(0);
        sliderSeek->setMaximum(100);
        sliderSeek->setOrientation(Qt::Horizontal);
        sliderVolume = new rphSlider(centralWidget);
        sliderVolume->setObjectName(QString::fromUtf8("sliderVolume"));
        sliderVolume->setGeometry(QRect(0, 210, 84, 21));
        sizePolicy.setHeightForWidth(sliderVolume->sizePolicy().hasHeightForWidth());
        sliderVolume->setSizePolicy(sizePolicy);
        sliderVolume->setMaximumSize(QSize(91, 16777215));
        sliderVolume->setCursor(QCursor(Qt::ArrowCursor));
        sliderVolume->setMouseTracking(true);
        sliderVolume->setStyleSheet(QString::fromUtf8(""));
        sliderVolume->setMinimum(0);
        sliderVolume->setMaximum(100);
        sliderVolume->setOrientation(Qt::Horizontal);
        toolButtonRewind = new QToolButton(centralWidget);
        toolButtonRewind->setObjectName(QString::fromUtf8("toolButtonRewind"));
        toolButtonRewind->setGeometry(QRect(120, 60, 41, 31));
        QIcon icon40;
        icon40.addFile(QString::fromUtf8(":/images/slower.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRewind->setIcon(icon40);
        toolButtonRewind->setPopupMode(QToolButton::MenuButtonPopup);
        toolButtonForward = new QToolButton(centralWidget);
        toolButtonForward->setObjectName(QString::fromUtf8("toolButtonForward"));
        toolButtonForward->setGeometry(QRect(160, 60, 41, 31));
        QIcon icon41;
        icon41.addFile(QString::fromUtf8(":/images/faster.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonForward->setIcon(icon41);
        toolButtonForward->setPopupMode(QToolButton::MenuButtonPopup);
        toolButtonVolume = new QToolButton(centralWidget);
        toolButtonVolume->setObjectName(QString::fromUtf8("toolButtonVolume"));
        toolButtonVolume->setGeometry(QRect(90, 60, 31, 31));
        QIcon icon42;
        icon42.addFile(QString::fromUtf8(":/vol100"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonVolume->setIcon(icon42);
        toolButtonVolume->setCheckable(false);
        label_display = new rphLabelEx(centralWidget);
        label_display->setObjectName(QString::fromUtf8("label_display"));
        label_display->setGeometry(QRect(9, 112, 43, 21));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_display->sizePolicy().hasHeightForWidth());
        label_display->setSizePolicy(sizePolicy2);
        label_display->setMinimumSize(QSize(0, 21));
        label_display->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_display->setScaledContents(false);
        label_display->setWordWrap(true);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(390, 0, 191, 31));
        tabWidget->setMouseTracking(true);
        tabWidget->setStyleSheet(QString::fromUtf8("/* Style the tab using the tab sub-control. Note that\n"
"     it reads QTabBar _not_ QTabWidget */\n"
"\n"
" QTabBar::tab {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                 stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"     border: 2px solid #C4C4C3;\n"
"     border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"     border-top-left-radius: 4px;\n"
"     border-top-right-radius: 4px;\n"
"     min-width: 8ex;\n"
"     padding: 2px;\n"
" }\n"
"\n"
" QTabBar::tab:selected, QTabBar::tab:hover {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"                                 stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
" }\n"
"\n"
" QTabBar::tab:selected {\n"
"     border-color: lightblue;\n"
"     border-bottom-color: #C2C7CB; /* same as pane color */\n"
" }\n"
"\n"
" QTabBar::tab:!selected {\n"
""
                        "     margin-top: 2px; /* make non-selected tabs look smaller */\n"
" }\n"
""));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QString::fromUtf8("tabWidgetPage1"));
        page_ve = new QFrame(tabWidgetPage1);
        page_ve->setObjectName(QString::fromUtf8("page_ve"));
        page_ve->setGeometry(QRect(10, 10, 421, 171));
        page_ve->setStyleSheet(QString::fromUtf8("QFrame{background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 0), stop:1 rgba(255, 255, 255, 0))}"));
        gridLayoutWidget = new QWidget(page_ve);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 291, 121));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gamma = new rphSlider(gridLayoutWidget);
        gamma->setObjectName(QString::fromUtf8("gamma"));
        gamma->setStyleSheet(QString::fromUtf8(""));
        gamma->setMinimum(-100);
        gamma->setMaximum(100);
        gamma->setOrientation(Qt::Vertical);
        gamma->setTickPosition(QSlider::TicksBelow);

        gridLayout_3->addWidget(gamma, 1, 4, 1, 1);

        contrast = new rphSlider(gridLayoutWidget);
        contrast->setObjectName(QString::fromUtf8("contrast"));
        contrast->setStyleSheet(QString::fromUtf8(""));
        contrast->setMinimum(-100);
        contrast->setMaximum(100);
        contrast->setOrientation(Qt::Vertical);
        contrast->setTickPosition(QSlider::TicksBelow);

        gridLayout_3->addWidget(contrast, 1, 0, 1, 1);

        brightness = new rphSlider(gridLayoutWidget);
        brightness->setObjectName(QString::fromUtf8("brightness"));
        brightness->setStyleSheet(QString::fromUtf8(""));
        brightness->setMinimum(-100);
        brightness->setMaximum(100);
        brightness->setOrientation(Qt::Vertical);
        brightness->setTickPosition(QSlider::TicksBelow);

        gridLayout_3->addWidget(brightness, 1, 1, 1, 1);

        Hue = new rphSlider(gridLayoutWidget);
        Hue->setObjectName(QString::fromUtf8("Hue"));
        Hue->setStyleSheet(QString::fromUtf8(""));
        Hue->setMinimum(-100);
        Hue->setMaximum(100);
        Hue->setOrientation(Qt::Vertical);
        Hue->setTickPosition(QSlider::TicksBelow);

        gridLayout_3->addWidget(Hue, 1, 2, 1, 1);

        Saturation = new rphSlider(gridLayoutWidget);
        Saturation->setObjectName(QString::fromUtf8("Saturation"));
        Saturation->setStyleSheet(QString::fromUtf8(""));
        Saturation->setMinimum(-100);
        Saturation->setMaximum(100);
        Saturation->setOrientation(Qt::Vertical);
        Saturation->setTickPosition(QSlider::TicksBelow);

        gridLayout_3->addWidget(Saturation, 1, 3, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setFrameShadow(QFrame::Plain);
        label_3->setScaledContents(true);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFrameShape(QFrame::NoFrame);
        label_8->setFrameShadow(QFrame::Plain);
        label_8->setScaledContents(true);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_8, 0, 2, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFrameShape(QFrame::NoFrame);
        label_9->setFrameShadow(QFrame::Plain);
        label_9->setScaledContents(true);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_9, 0, 3, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFrameShape(QFrame::NoFrame);
        label_10->setFrameShadow(QFrame::Plain);
        label_10->setScaledContents(true);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_10, 0, 4, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFrameShape(QFrame::NoFrame);
        label_7->setFrameShadow(QFrame::Plain);
        label_7->setScaledContents(true);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_7, 0, 1, 1, 1);

        label = new QLabel(page_ve);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 140, 42, 13));
        label->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(page_ve);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 140, 50, 13));
        label_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_6 = new QLabel(page_ve);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(150, 140, 21, 13));
        label_6->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_6->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(page_ve);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(200, 140, 50, 13));
        label_4->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_4->setTextFormat(Qt::AutoText);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(page_ve);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(260, 140, 35, 13));
        label_5->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_5->setAlignment(Qt::AlignCenter);
        btnVEReset = new QPushButton(page_ve);
        btnVEReset->setObjectName(QString::fromUtf8("btnVEReset"));
        btnVEReset->setGeometry(QRect(320, 80, 84, 21));
        btnVEReset->setStyleSheet(QString::fromUtf8(""));
        tabWidget->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName(QString::fromUtf8("tabWidgetPage2"));
        page_ae = new QFrame(tabWidgetPage2);
        page_ae->setObjectName(QString::fromUtf8("page_ae"));
        page_ae->setGeometry(QRect(10, 10, 521, 171));
        page_ae->setStyleSheet(QString::fromUtf8(""));
        page_ae->setFrameShape(QFrame::StyledPanel);
        page_ae->setFrameShadow(QFrame::Raised);
        btnAEReset = new QPushButton(page_ae);
        btnAEReset->setObjectName(QString::fromUtf8("btnAEReset"));
        btnAEReset->setGeometry(QRect(390, 70, 84, 21));
        btnAEReset->setStyleSheet(QString::fromUtf8(""));
        gridLayoutWidget_2 = new QWidget(page_ae);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 10, 384, 141));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font;
        font.setPointSize(8);
        label_11->setFont(font);
        label_11->setFrameShape(QFrame::NoFrame);
        label_11->setFrameShadow(QFrame::Plain);
        label_11->setScaledContents(true);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_11, 0, 0, 1, 1);

        label_12 = new QLabel(gridLayoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFrameShape(QFrame::NoFrame);
        label_12->setFrameShadow(QFrame::Plain);
        label_12->setScaledContents(true);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_12, 0, 2, 1, 1);

        label_13 = new QLabel(gridLayoutWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFrameShape(QFrame::NoFrame);
        label_13->setFrameShadow(QFrame::Plain);
        label_13->setScaledContents(true);
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_13, 0, 3, 1, 1);

        label_14 = new QLabel(gridLayoutWidget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFrameShape(QFrame::NoFrame);
        label_14->setFrameShadow(QFrame::Plain);
        label_14->setScaledContents(true);
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_14, 0, 4, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFrameShape(QFrame::NoFrame);
        label_15->setFrameShadow(QFrame::Plain);
        label_15->setScaledContents(true);
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_15, 0, 1, 1, 1);

        label_16 = new QLabel(gridLayoutWidget_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFrameShape(QFrame::NoFrame);
        label_16->setFrameShadow(QFrame::Plain);
        label_16->setScaledContents(true);
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_16, 0, 5, 1, 1);

        label_17 = new QLabel(gridLayoutWidget_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFrameShape(QFrame::NoFrame);
        label_17->setFrameShadow(QFrame::Plain);
        label_17->setScaledContents(true);
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_17, 0, 6, 1, 1);

        label_18 = new QLabel(gridLayoutWidget_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFrameShape(QFrame::NoFrame);
        label_18->setFrameShadow(QFrame::Plain);
        label_18->setScaledContents(true);
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_18, 0, 7, 1, 1);

        label_19 = new QLabel(gridLayoutWidget_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFrameShape(QFrame::NoFrame);
        label_19->setFrameShadow(QFrame::Plain);
        label_19->setScaledContents(true);
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_19, 0, 8, 1, 1);

        label_20 = new QLabel(gridLayoutWidget_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_20->setFrameShape(QFrame::NoFrame);
        label_20->setFrameShadow(QFrame::Plain);
        label_20->setScaledContents(true);
        label_20->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_20, 2, 0, 1, 1);

        label_21 = new QLabel(gridLayoutWidget_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_21->setFrameShape(QFrame::NoFrame);
        label_21->setFrameShadow(QFrame::Plain);
        label_21->setScaledContents(true);
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_21, 2, 1, 1, 1);

        label_22 = new QLabel(gridLayoutWidget_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_22->setFrameShape(QFrame::NoFrame);
        label_22->setFrameShadow(QFrame::Plain);
        label_22->setScaledContents(true);
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_22, 2, 2, 1, 1);

        label_23 = new QLabel(gridLayoutWidget_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_23->setFrameShape(QFrame::NoFrame);
        label_23->setFrameShadow(QFrame::Plain);
        label_23->setScaledContents(true);
        label_23->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_23, 2, 3, 1, 1);

        label_24 = new QLabel(gridLayoutWidget_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_24->setFrameShape(QFrame::NoFrame);
        label_24->setFrameShadow(QFrame::Plain);
        label_24->setScaledContents(true);
        label_24->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_24, 2, 4, 1, 1);

        label_25 = new QLabel(gridLayoutWidget_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_25->setFrameShape(QFrame::NoFrame);
        label_25->setFrameShadow(QFrame::Plain);
        label_25->setScaledContents(true);
        label_25->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_25, 2, 5, 1, 1);

        label_26 = new QLabel(gridLayoutWidget_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_26->setFrameShape(QFrame::NoFrame);
        label_26->setFrameShadow(QFrame::Plain);
        label_26->setScaledContents(true);
        label_26->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_26, 2, 6, 1, 1);

        label_27 = new QLabel(gridLayoutWidget_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_27->setFrameShape(QFrame::NoFrame);
        label_27->setFrameShadow(QFrame::Plain);
        label_27->setScaledContents(true);
        label_27->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_27, 2, 7, 1, 1);

        label_28 = new QLabel(gridLayoutWidget_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_28->setFrameShape(QFrame::NoFrame);
        label_28->setFrameShadow(QFrame::Plain);
        label_28->setScaledContents(true);
        label_28->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_28, 2, 8, 1, 1);

        label_29 = new QLabel(gridLayoutWidget_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(14, 248, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_29->setFrameShape(QFrame::NoFrame);
        label_29->setFrameShadow(QFrame::Plain);
        label_29->setScaledContents(true);
        label_29->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_29, 2, 9, 1, 1);

        label_30 = new QLabel(gridLayoutWidget_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFrameShape(QFrame::NoFrame);
        label_30->setFrameShadow(QFrame::Plain);
        label_30->setScaledContents(true);
        label_30->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_30, 0, 9, 1, 1);

        eq0 = new rphSlider(gridLayoutWidget_2);
        eq0->setObjectName(QString::fromUtf8("eq0"));
        eq0->setStyleSheet(QString::fromUtf8(""));
        eq0->setMinimum(-12);
        eq0->setMaximum(12);
        eq0->setPageStep(1);
        eq0->setOrientation(Qt::Vertical);
        eq0->setTickPosition(QSlider::TicksBelow);
        eq0->setTickInterval(2);

        gridLayout_4->addWidget(eq0, 1, 0, 1, 1);

        eq1 = new rphSlider(gridLayoutWidget_2);
        eq1->setObjectName(QString::fromUtf8("eq1"));
        eq1->setStyleSheet(QString::fromUtf8(""));
        eq1->setMinimum(-12);
        eq1->setMaximum(12);
        eq1->setPageStep(1);
        eq1->setOrientation(Qt::Vertical);
        eq1->setTickPosition(QSlider::TicksBelow);
        eq1->setTickInterval(2);

        gridLayout_4->addWidget(eq1, 1, 1, 1, 1);

        eq2 = new rphSlider(gridLayoutWidget_2);
        eq2->setObjectName(QString::fromUtf8("eq2"));
        eq2->setStyleSheet(QString::fromUtf8(""));
        eq2->setMinimum(-12);
        eq2->setMaximum(12);
        eq2->setPageStep(1);
        eq2->setOrientation(Qt::Vertical);
        eq2->setTickPosition(QSlider::TicksBelow);
        eq2->setTickInterval(2);

        gridLayout_4->addWidget(eq2, 1, 2, 1, 1);

        eq3 = new rphSlider(gridLayoutWidget_2);
        eq3->setObjectName(QString::fromUtf8("eq3"));
        eq3->setStyleSheet(QString::fromUtf8(""));
        eq3->setMinimum(-12);
        eq3->setMaximum(12);
        eq3->setPageStep(1);
        eq3->setOrientation(Qt::Vertical);
        eq3->setTickPosition(QSlider::TicksBelow);
        eq3->setTickInterval(2);

        gridLayout_4->addWidget(eq3, 1, 3, 1, 1);

        eq4 = new rphSlider(gridLayoutWidget_2);
        eq4->setObjectName(QString::fromUtf8("eq4"));
        eq4->setStyleSheet(QString::fromUtf8(""));
        eq4->setMinimum(-12);
        eq4->setMaximum(12);
        eq4->setPageStep(1);
        eq4->setOrientation(Qt::Vertical);
        eq4->setTickPosition(QSlider::TicksBelow);
        eq4->setTickInterval(2);

        gridLayout_4->addWidget(eq4, 1, 4, 1, 1);

        eq5 = new rphSlider(gridLayoutWidget_2);
        eq5->setObjectName(QString::fromUtf8("eq5"));
        eq5->setStyleSheet(QString::fromUtf8(""));
        eq5->setMinimum(-12);
        eq5->setMaximum(12);
        eq5->setPageStep(1);
        eq5->setOrientation(Qt::Vertical);
        eq5->setTickPosition(QSlider::TicksBelow);
        eq5->setTickInterval(2);

        gridLayout_4->addWidget(eq5, 1, 5, 1, 1);

        eq6 = new rphSlider(gridLayoutWidget_2);
        eq6->setObjectName(QString::fromUtf8("eq6"));
        eq6->setStyleSheet(QString::fromUtf8(""));
        eq6->setMinimum(-12);
        eq6->setMaximum(12);
        eq6->setPageStep(1);
        eq6->setOrientation(Qt::Vertical);
        eq6->setTickPosition(QSlider::TicksBelow);
        eq6->setTickInterval(2);

        gridLayout_4->addWidget(eq6, 1, 6, 1, 1);

        eq7 = new rphSlider(gridLayoutWidget_2);
        eq7->setObjectName(QString::fromUtf8("eq7"));
        eq7->setStyleSheet(QString::fromUtf8(""));
        eq7->setMinimum(-12);
        eq7->setMaximum(12);
        eq7->setPageStep(1);
        eq7->setOrientation(Qt::Vertical);
        eq7->setTickPosition(QSlider::TicksBelow);
        eq7->setTickInterval(2);

        gridLayout_4->addWidget(eq7, 1, 7, 1, 1);

        eq8 = new rphSlider(gridLayoutWidget_2);
        eq8->setObjectName(QString::fromUtf8("eq8"));
        eq8->setStyleSheet(QString::fromUtf8(""));
        eq8->setMinimum(-12);
        eq8->setMaximum(12);
        eq8->setPageStep(1);
        eq8->setOrientation(Qt::Vertical);
        eq8->setTickPosition(QSlider::TicksBelow);
        eq8->setTickInterval(2);

        gridLayout_4->addWidget(eq8, 1, 8, 1, 1);

        eq9 = new rphSlider(gridLayoutWidget_2);
        eq9->setObjectName(QString::fromUtf8("eq9"));
        eq9->setStyleSheet(QString::fromUtf8(""));
        eq9->setMinimum(-12);
        eq9->setMaximum(12);
        eq9->setPageStep(1);
        eq9->setOrientation(Qt::Vertical);
        eq9->setTickPosition(QSlider::TicksBelow);
        eq9->setTickInterval(2);

        gridLayout_4->addWidget(eq9, 1, 9, 1, 1);

        comboBox = new QComboBox(page_ae);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(390, 130, 111, 21));
        comboBox->setStyleSheet(QString::fromUtf8(""));
        cbEnableAEq = new QCheckBox(page_ae);
        cbEnableAEq->setObjectName(QString::fromUtf8("cbEnableAEq"));
        cbEnableAEq->setGeometry(QRect(390, 10, 70, 17));
        tabWidget->addTab(tabWidgetPage2, QString());
        toolButtonfs = new QToolButton(centralWidget);
        toolButtonfs->setObjectName(QString::fromUtf8("toolButtonfs"));
        toolButtonfs->setGeometry(QRect(200, 60, 41, 31));
        toolButtonfs->setStyleSheet(QString::fromUtf8(""));
        toolButtonfs->setIcon(icon27);
        toolButtonfs->setIconSize(QSize(32, 32));
        toolButtonLpl = new QToolButton(centralWidget);
        toolButtonLpl->setObjectName(QString::fromUtf8("toolButtonLpl"));
        toolButtonLpl->setGeometry(QRect(90, 20, 31, 31));
        toolButtonLpl->setIcon(icon35);
        toolButtonLpl->setIconSize(QSize(16, 16));
        toolButtonLpl->setPopupMode(QToolButton::MenuButtonPopup);
        toolButtonAdd = new QToolButton(centralWidget);
        toolButtonAdd->setObjectName(QString::fromUtf8("toolButtonAdd"));
        toolButtonAdd->setGeometry(QRect(10, 20, 41, 31));
        toolButtonAdd->setIcon(icon13);
        toolButtonAdd->setPopupMode(QToolButton::InstantPopup);
        toolButtonRemove = new QToolButton(centralWidget);
        toolButtonRemove->setObjectName(QString::fromUtf8("toolButtonRemove"));
        toolButtonRemove->setGeometry(QRect(50, 20, 41, 31));
        toolButtonRemove->setIcon(icon14);
        toolButtonRemove->setPopupMode(QToolButton::InstantPopup);
        toolButton_loop = new QToolButton(centralWidget);
        toolButton_loop->setObjectName(QString::fromUtf8("toolButton_loop"));
        toolButton_loop->setGeometry(QRect(120, 20, 31, 31));
        QIcon icon43;
        icon43.addFile(QString::fromUtf8(":/images/loop.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_loop->setIcon(icon43);
        toolButton_loop->setIconSize(QSize(16, 16));
        toolButton_loop->setCheckable(true);
        toolButton_loop->setChecked(false);
        toolButton_loop->setAutoExclusive(false);
        toolButton_loop->setPopupMode(QToolButton::InstantPopup);
        toolButton_shuffle = new QToolButton(centralWidget);
        toolButton_shuffle->setObjectName(QString::fromUtf8("toolButton_shuffle"));
        toolButton_shuffle->setGeometry(QRect(150, 20, 31, 31));
        QIcon icon44;
        icon44.addFile(QString::fromUtf8(":/images/shuffle.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_shuffle->setIcon(icon44);
        toolButton_shuffle->setIconSize(QSize(16, 16));
        toolButton_shuffle->setCheckable(true);
        toolButton_shuffle->setChecked(false);
        toolButton_shuffle->setAutoExclusive(false);
        toolButton_shuffle->setPopupMode(QToolButton::InstantPopup);
        toolButton_playpre = new QToolButton(centralWidget);
        toolButton_playpre->setObjectName(QString::fromUtf8("toolButton_playpre"));
        toolButton_playpre->setGeometry(QRect(180, 20, 31, 31));
        toolButton_playpre->setIcon(icon33);
        toolButton_playpre->setIconSize(QSize(16, 16));
        toolButton_playpre->setCheckable(false);
        toolButton_playpre->setChecked(false);
        toolButton_playpre->setAutoExclusive(false);
        toolButton_playpre->setPopupMode(QToolButton::InstantPopup);
        toolButton_playnext = new QToolButton(centralWidget);
        toolButton_playnext->setObjectName(QString::fromUtf8("toolButton_playnext"));
        toolButton_playnext->setGeometry(QRect(210, 20, 31, 31));
        toolButton_playnext->setIcon(icon32);
        toolButton_playnext->setIconSize(QSize(16, 16));
        toolButton_playnext->setCheckable(false);
        toolButton_playnext->setChecked(false);
        toolButton_playnext->setAutoExclusive(false);
        toolButton_playnext->setPopupMode(QToolButton::InstantPopup);
        toolButtonSpeed = new QToolButton(centralWidget);
        toolButtonSpeed->setObjectName(QString::fromUtf8("toolButtonSpeed"));
        toolButtonSpeed->setGeometry(QRect(10, 60, 41, 31));
        toolButtonSpeed->setIcon(icon12);
        toolButtonSpeed->setPopupMode(QToolButton::MenuButtonPopup);
        toolButtonplaylist = new QToolButton(centralWidget);
        toolButtonplaylist->setObjectName(QString::fromUtf8("toolButtonplaylist"));
        toolButtonplaylist->setGeometry(QRect(50, 60, 41, 31));
        toolButtonplaylist->setIcon(icon35);
        toolButtonplaylist->setPopupMode(QToolButton::MenuButtonPopup);
        labToolbarSpace = new QLabel(centralWidget);
        labToolbarSpace->setObjectName(QString::fromUtf8("labToolbarSpace"));
        labToolbarSpace->setGeometry(QRect(230, 210, 81, 31));
        labVD = new QLabel(centralWidget);
        labVD->setObjectName(QString::fromUtf8("labVD"));
        labVD->setGeometry(QRect(290, 240, 21, 16));
        labVD->setStyleSheet(QString::fromUtf8("color: grey;"));
        labAD = new QLabel(centralWidget);
        labAD->setObjectName(QString::fromUtf8("labAD"));
        labAD->setGeometry(QRect(320, 240, 21, 16));
        labAD->setStyleSheet(QString::fromUtf8("font: 75 7pt \"MS Shell Dlg 2\";\n"
"color: grey;"));
        PlayerWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PlayerWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy3);
        statusBar->setMouseTracking(true);
        statusBar->setAcceptDrops(true);
        PlayerWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(PlayerWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 813, 20));
        menuBar->setStyleSheet(QString::fromUtf8(""));
        menuBar->setNativeMenuBar(false);
        menu_Open = new QMenu(menuBar);
        menu_Open->setObjectName(QString::fromUtf8("menu_Open"));
        menu_Open->setSeparatorsCollapsible(false);
        menuPlay = new QMenu(menuBar);
        menuPlay->setObjectName(QString::fromUtf8("menuPlay"));
        menuSpeed = new QMenu(menuPlay);
        menuSpeed->setObjectName(QString::fromUtf8("menuSpeed"));
        menuSpeed->setTearOffEnabled(true);
        menuFa_mily_Friendly_mode = new QMenu(menuPlay);
        menuFa_mily_Friendly_mode->setObjectName(QString::fromUtf8("menuFa_mily_Friendly_mode"));
        menu_Audio = new QMenu(menuBar);
        menu_Audio->setObjectName(QString::fromUtf8("menu_Audio"));
        menuAudio_Track = new QMenu(menu_Audio);
        menuAudio_Track->setObjectName(QString::fromUtf8("menuAudio_Track"));
        menuC_hannels = new QMenu(menu_Audio);
        menuC_hannels->setObjectName(QString::fromUtf8("menuC_hannels"));
        menu_Filters = new QMenu(menu_Audio);
        menu_Filters->setObjectName(QString::fromUtf8("menu_Filters"));
        menu_Resample = new QMenu(menu_Filters);
        menu_Resample->setObjectName(QString::fromUtf8("menu_Resample"));
        menu_Resample->setTearOffEnabled(true);
        menu_Video = new QMenu(menuBar);
        menu_Video->setObjectName(QString::fromUtf8("menu_Video"));
        menu_Filters_2 = new QMenu(menu_Video);
        menu_Filters_2->setObjectName(QString::fromUtf8("menu_Filters_2"));
        menu_Filters_2->setTearOffEnabled(true);
        menu_Rotate = new QMenu(menu_Filters_2);
        menu_Rotate->setObjectName(QString::fromUtf8("menu_Rotate"));
        menuA_spect_ratio = new QMenu(menu_Video);
        menuA_spect_ratio->setObjectName(QString::fromUtf8("menuA_spect_ratio"));
        menuA_spect_ratio->setTearOffEnabled(true);
        menuVideo_Track = new QMenu(menu_Video);
        menuVideo_Track->setObjectName(QString::fromUtf8("menuVideo_Track"));
        menuOSD = new QMenu(menu_Video);
        menuOSD->setObjectName(QString::fromUtf8("menuOSD"));
        QIcon icon45;
        icon45.addFile(QString::fromUtf8(":/images/osd.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuOSD->setIcon(icon45);
        menuFrame_drop = new QMenu(menu_Video);
        menuFrame_drop->setObjectName(QString::fromUtf8("menuFrame_drop"));
        menuZoom = new QMenu(menu_Video);
        menuZoom->setObjectName(QString::fromUtf8("menuZoom"));
        QIcon icon46;
        icon46.addFile(QString::fromUtf8(":/images/zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuZoom->setIcon(icon46);
        menuFrame_rate_fps = new QMenu(menu_Video);
        menuFrame_rate_fps->setObjectName(QString::fromUtf8("menuFrame_rate_fps"));
        menu_Subtitles = new QMenu(menuBar);
        menu_Subtitles->setObjectName(QString::fromUtf8("menu_Subtitles"));
        menuSelect = new QMenu(menu_Subtitles);
        menuSelect->setObjectName(QString::fromUtf8("menuSelect"));
        menuSelect->setTearOffEnabled(true);
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menuPlaylist = new QMenu(menuBar);
        menuPlaylist->setObjectName(QString::fromUtf8("menuPlaylist"));
        menuAdd = new QMenu(menuPlaylist);
        menuAdd->setObjectName(QString::fromUtf8("menuAdd"));
        menuAdd->setIcon(icon13);
        menu_Remove = new QMenu(menuPlaylist);
        menu_Remove->setObjectName(QString::fromUtf8("menu_Remove"));
        menu_Remove->setIcon(icon14);
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        PlayerWindow->setMenuBar(menuBar);
        dockBrowser = new QDockWidget(PlayerWindow);
        dockBrowser->setObjectName(QString::fromUtf8("dockBrowser"));
        dockBrowser->setMinimumSize(QSize(79, 130));
        dockBrowser->setAcceptDrops(true);
        dockBrowser->setStyleSheet(QString::fromUtf8(""));
        dockBrowser->setFloating(false);
        dockBrowser->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::LeftDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        dockBrowser->setWidget(dockWidgetContents_3);
        PlayerWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockBrowser);
        dock_Playlist = new dockPlayList(PlayerWindow);
        dock_Playlist->setObjectName(QString::fromUtf8("dock_Playlist"));
        dock_Playlist->setMinimumSize(QSize(79, 37));
        dock_Playlist->setFocusPolicy(Qt::StrongFocus);
        dock_Playlist->setAcceptDrops(true);
        dock_Playlist->setStyleSheet(QString::fromUtf8(""));
        dock_Playlist->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        frame_playlist = new QFrame(dockWidgetContents_4);
        frame_playlist->setObjectName(QString::fromUtf8("frame_playlist"));
        frame_playlist->setGeometry(QRect(70, 40, 101, 71));
        frame_playlist->setFrameShape(QFrame::StyledPanel);
        frame_playlist->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_playlist);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));

        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        dock_Playlist->setWidget(dockWidgetContents_4);
        PlayerWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock_Playlist);
        toolBarPlaylist = new QToolBar(PlayerWindow);
        toolBarPlaylist->setObjectName(QString::fromUtf8("toolBarPlaylist"));
        toolBarPlaylist->setAcceptDrops(true);
        toolBarPlaylist->setAllowedAreas(Qt::BottomToolBarArea);
        toolBarPlaylist->setFloatable(false);
        PlayerWindow->addToolBar(Qt::BottomToolBarArea, toolBarPlaylist);
        dock_Filter = new QDockWidget(PlayerWindow);
        dock_Filter->setObjectName(QString::fromUtf8("dock_Filter"));
        dock_Filter->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        dock_Filter->setWidget(dockWidgetContents_2);
        PlayerWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dock_Filter);
        toolBarStatus = new QToolBar(PlayerWindow);
        toolBarStatus->setObjectName(QString::fromUtf8("toolBarStatus"));
        toolBarStatus->setMouseTracking(true);
        toolBarStatus->setMovable(false);
        toolBarStatus->setFloatable(false);
        PlayerWindow->addToolBar(Qt::BottomToolBarArea, toolBarStatus);
        PlayerWindow->insertToolBarBreak(toolBarStatus);
        toolBarSeek = new QToolBar(PlayerWindow);
        toolBarSeek->setObjectName(QString::fromUtf8("toolBarSeek"));
        toolBarSeek->setCursor(QCursor(Qt::ArrowCursor));
        toolBarSeek->setMouseTracking(true);
        toolBarSeek->setMovable(false);
        toolBarSeek->setIconSize(QSize(28, 28));
        toolBarSeek->setFloatable(false);
        PlayerWindow->addToolBar(Qt::BottomToolBarArea, toolBarSeek);
        PlayerWindow->insertToolBarBreak(toolBarSeek);
        toolBarSeekBar = new QToolBar(PlayerWindow);
        toolBarSeekBar->setObjectName(QString::fromUtf8("toolBarSeekBar"));
        toolBarSeekBar->setCursor(QCursor(Qt::ArrowCursor));
        toolBarSeekBar->setMouseTracking(true);
        toolBarSeekBar->setMovable(false);
        toolBarSeekBar->setFloatable(false);
        PlayerWindow->addToolBar(Qt::BottomToolBarArea, toolBarSeekBar);
        PlayerWindow->insertToolBarBreak(toolBarSeekBar);
        dock_log = new QDockWidget(PlayerWindow);
        dock_log->setObjectName(QString::fromUtf8("dock_log"));
        dock_log->setMinimumSize(QSize(289, 400));
        dock_log->setFloating(false);
        dock_log->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_log = new QFrame(dockWidgetContents);
        frame_log->setObjectName(QString::fromUtf8("frame_log"));
        sizePolicy3.setHeightForWidth(frame_log->sizePolicy().hasHeightForWidth());
        frame_log->setSizePolicy(sizePolicy3);
        frame_log->setFrameShape(QFrame::StyledPanel);
        frame_log->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_log);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        mpconsole = new QTextEdit(frame_log);
        mpconsole->setObjectName(QString::fromUtf8("mpconsole"));
        mpconsole->setReadOnly(true);

        gridLayout_2->addWidget(mpconsole, 1, 0, 2, 2);

        cmdLine = new QLineEdit(frame_log);
        cmdLine->setObjectName(QString::fromUtf8("cmdLine"));
        cmdLine->setMaxLength(32766);

        gridLayout_2->addWidget(cmdLine, 3, 0, 1, 1);

        btnSaveLog = new QToolButton(frame_log);
        btnSaveLog->setObjectName(QString::fromUtf8("btnSaveLog"));

        gridLayout_2->addWidget(btnSaveLog, 3, 1, 1, 1);


        verticalLayout->addWidget(frame_log);

        dock_log->setWidget(dockWidgetContents);
        PlayerWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock_log);

        menuBar->addAction(menu_Open->menuAction());
        menuBar->addAction(menuPlay->menuAction());
        menuBar->addAction(menu_Audio->menuAction());
        menuBar->addAction(menu_Video->menuAction());
        menuBar->addAction(menu_Subtitles->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menuBar->addAction(menuPlaylist->menuAction());
        menuBar->addAction(menu_Tools->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_Open->addAction(action_File);
        menu_Open->addAction(actionFolder);
        menu_Open->addAction(actionInternet_Radio);
        menu_Open->addAction(actionURL);
        menu_Open->addSeparator();
        menu_Open->addAction(actionAdd_File_to_pl);
        menu_Open->addAction(actionAdd_Folder_to_pl);
        menu_Open->addAction(actionEdit_Playlist);
        menu_Open->addSeparator();
        menu_Open->addAction(actionOpen_containing_folder);
        menu_Open->addSeparator();
        menu_Open->addAction(actionSave_cover_art);
        menu_Open->addSeparator();
        menu_Open->addAction(action_Exit);
        menuPlay->addAction(action_Play_Pause);
        menuPlay->addAction(action_Stop);
        menuPlay->addSeparator();
        menuPlay->addAction(actionForward_10_seconds);
        menuPlay->addAction(actionRewind_10_seconds);
        menuPlay->addAction(actionForward_1_minute);
        menuPlay->addAction(actionRewind_1_minute);
        menuPlay->addAction(actionForward_10_minutes);
        menuPlay->addAction(actionRewind_10_minutes);
        menuPlay->addSeparator();
        menuPlay->addAction(actionPlay_Next_File);
        menuPlay->addAction(actionPlay_Previous_File);
        menuPlay->addSeparator();
        menuPlay->addAction(menuSpeed->menuAction());
        menuPlay->addAction(menuFa_mily_Friendly_mode->menuAction());
        menuSpeed->addAction(actionNormal_Speed);
        menuSpeed->addSeparator();
        menuSpeed->addAction(actionIncrease_10);
        menuSpeed->addAction(actionDecrease_10);
        menuSpeed->addSeparator();
        menuSpeed->addAction(actionDouble_speed);
        menuSpeed->addAction(actionHalve_speed);
        menuFa_mily_Friendly_mode->addAction(actionStep1_fm);
        menuFa_mily_Friendly_mode->addAction(actionStep2_fm);
        menu_Audio->addAction(menuAudio_Track->menuAction());
        menu_Audio->addSeparator();
        menu_Audio->addAction(actionLoad_external_file);
        menu_Audio->addAction(actionMix_and_save);
        menu_Audio->addSeparator();
        menu_Audio->addAction(menuC_hannels->menuAction());
        menu_Audio->addAction(menu_Filters->menuAction());
        menu_Audio->addAction(action_Equalizer);
        menu_Audio->addSeparator();
        menu_Audio->addAction(action_Increase_volume);
        menu_Audio->addAction(action_Decrease_volume);
        menu_Audio->addSeparator();
        menu_Audio->addAction(actionMute);
        menu_Audio->addSeparator();
        menu_Audio->addAction(actionIncrease_Delay);
        menu_Audio->addAction(actionDecrease_Delay);
        menu_Audio->addAction(action_AV_Set_Delay);
        menuAudio_Track->addAction(actionAudioDisable);
        menuC_hannels->addAction(actionStereo);
        menuC_hannels->addAction(actionSurround);
        menuC_hannels->addAction(actionFull_5_1);
        menuC_hannels->addAction(actionFull_7_1);
        menu_Filters->addAction(action_Delay);
        menu_Filters->addAction(action_ExtraStereo);
        menu_Filters->addAction(action_Karaoke);
        menu_Filters->addAction(menu_Resample->menuAction());
        menu_Filters->addAction(actionScale_Tempo);
        menu_Filters->addAction(actionSurroundAf);
        menu_Filters->addAction(actionVolume_Normalization);
        menu_Filters->addAction(actionWinamp_Dsp);
        menu_Resample->addAction(action8000);
        menu_Resample->addAction(action11025);
        menu_Resample->addAction(action12000);
        menu_Resample->addAction(action16000);
        menu_Resample->addAction(action22100);
        menu_Resample->addAction(action24000);
        menu_Resample->addAction(action32000);
        menu_Resample->addAction(action44100);
        menu_Resample->addAction(action48000);
        menu_Resample->addAction(action96000);
        menu_Resample->addAction(action192000);
        menu_Video->addAction(menuVideo_Track->menuAction());
        menu_Video->addSeparator();
        menu_Video->addAction(menu_Filters_2->menuAction());
        menu_Video->addAction(action_Crop);
        menu_Video->addAction(menuA_spect_ratio->menuAction());
        menu_Video->addAction(menuZoom->menuAction());
        menu_Video->addAction(actionVideoEqualizer);
        menu_Video->addAction(actionIncrease_Video_quality);
        menu_Video->addAction(menuFrame_rate_fps->menuAction());
        menu_Video->addSeparator();
        menu_Video->addAction(menuOSD->menuAction());
        menu_Video->addAction(actionToggle_OSD);
        menu_Video->addSeparator();
        menu_Video->addAction(menuFrame_drop->menuAction());
        menu_Video->addAction(actionToggle_Frame_drop);
        menu_Video->addSeparator();
        menu_Video->addAction(actionStay_on_top);
        menu_Video->addSeparator();
        menu_Video->addAction(actionFrame_step);
        menu_Video->addSeparator();
        menu_Video->addAction(actionScreen_shot);
        menu_Video->addAction(actionStart_stop_Screenshot);
        menu_Video->addAction(action_Open_Screenshot_folder);
        menu_Video->addSeparator();
        menu_Video->addAction(actionFullscreen);
        menu_Filters_2->addAction(action_Remove_logo);
        menu_Filters_2->addAction(action_Tile);
        menu_Filters_2->addAction(action_flip);
        menu_Filters_2->addAction(action_Mirror);
        menu_Filters_2->addAction(action50_50);
        menu_Filters_2->addAction(menu_Rotate->menuAction());
        menu_Filters_2->addAction(actionSwap_U_and_V);
        menu_Filters_2->addAction(actionOld_Black_and_white);
        menu_Filters_2->addAction(actionPainting);
        menu_Filters_2->addAction(actionAdd_noise);
        menu_Filters_2->addAction(action_Blur);
        menu_Filters_2->addAction(actionMatrixview);
        menu_Filters_2->addAction(actionVisualize_motion_vectors);
        menu_Filters_2->addAction(action_Palette);
        menu_Filters_2->addAction(actionNegative);
        menu_Filters_2->addAction(actionTwins);
        menu_Filters_2->addAction(actionSide_view);
        menu_Rotate->addAction(action_RotateDisable);
        menu_Rotate->addAction(actionRotate_0);
        menu_Rotate->addAction(actionRotate_1);
        menu_Rotate->addAction(actionRotate_2);
        menu_Rotate->addAction(actionRotate_3);
        menuA_spect_ratio->addAction(action_ar_Auto);
        menuA_spect_ratio->addAction(action1_1);
        menuA_spect_ratio->addAction(action2_21_1);
        menuA_spect_ratio->addAction(action3_2);
        menuA_spect_ratio->addAction(action4_3);
        menuA_spect_ratio->addAction(action5_4);
        menuA_spect_ratio->addAction(action14_9);
        menuA_spect_ratio->addAction(action14_10);
        menuA_spect_ratio->addAction(action16_9);
        menuA_spect_ratio->addAction(action16_10);
        menuA_spect_ratio->addAction(action_ar_Custom);
        menuA_spect_ratio->addSeparator();
        menuA_spect_ratio->addAction(action_ar_Disable);
        menuVideo_Track->addAction(actionVideoDisable);
        menuOSD->addAction(action_osd0);
        menuOSD->addAction(action_osd1);
        menuOSD->addAction(action_osd2);
        menuOSD->addAction(action_osd3);
        menuFrame_drop->addAction(action_fd_Disable);
        menuFrame_drop->addAction(actionSoft);
        menuFrame_drop->addAction(actionHard);
        menuZoom->addAction(actionIncrease_Zoom);
        menuZoom->addAction(actionDecrease_Zoom);
        menuZoom->addAction(actionDefault_zoom);
        menuZoom->addSeparator();
        menuZoom->addAction(actionMove_Left);
        menuZoom->addAction(actionMove_Right);
        menuZoom->addAction(actionMove_Up);
        menuZoom->addAction(actionMove_Down);
        menuFrame_rate_fps->addAction(actionChange_framerate);
        menuFrame_rate_fps->addAction(actionDefault);
        menu_Subtitles->addAction(menuSelect->menuAction());
        menu_Subtitles->addSeparator();
        menu_Subtitles->addAction(action_Load_st);
        menu_Subtitles->addAction(actionStUnload);
        menu_Subtitles->addSeparator();
        menu_Subtitles->addAction(actionToggle_subtitle_visibility);
        menu_Subtitles->addSeparator();
        menu_Subtitles->addAction(action_st_Move_Up);
        menu_Subtitles->addAction(action_st_Move_Down);
        menu_Subtitles->addSeparator();
        menu_Subtitles->addAction(actionSize_Increase);
        menu_Subtitles->addAction(actionSize_Decrease);
        menu_Subtitles->addSeparator();
        menu_Subtitles->addAction(actionDelay_Increaser);
        menu_Subtitles->addAction(actionDelay_Decrease);
        menu_Subtitles->addAction(action_st_Set_Delay);
        menu_Subtitles->addSeparator();
        menu_Subtitles->addAction(actionEnable_Closed_Captions);
        menuSelect->addAction(actionStNone);
        menu_Help->addAction(action_Help);
        menu_Help->addSeparator();
        menu_Help->addAction(actionAbout_Qt);
        menu_Help->addAction(action_About);
        menuPlaylist->addAction(menuAdd->menuAction());
        menuPlaylist->addAction(menu_Remove->menuAction());
        menuPlaylist->addAction(action_Load_pl);
        menuPlaylist->addAction(action_Save_as_playlist);
        menuPlaylist->addAction(actionShowpl);
        menuAdd->addAction(actionAdd_file);
        menuAdd->addAction(actionAdd_Folder);
        menu_Remove->addAction(actionSelected_item_s);
        menu_Remove->addAction(actionRemove_all);
        menu_Tools->addAction(action_Options);
        menu_Tools->addAction(actionMedia_cutter);
        menu_Tools->addAction(actionAudio_extrctor);
        menu_Tools->addAction(actionAudio_Converter);
        menu_Tools->addAction(actionCopy_Audio_CD);
        menu_View->addAction(action_Media_Info);
        menu_View->addAction(actionSmallmode);

        retranslateUi(PlayerWindow);
        QObject::connect(eq0, SIGNAL(valueChanged(int)), label_11, SLOT(setNum(int)));
        QObject::connect(eq8, SIGNAL(valueChanged(int)), label_19, SLOT(setNum(int)));
        QObject::connect(eq1, SIGNAL(valueChanged(int)), label_15, SLOT(setNum(int)));
        QObject::connect(eq2, SIGNAL(valueChanged(int)), label_12, SLOT(setNum(int)));
        QObject::connect(eq3, SIGNAL(valueChanged(int)), label_13, SLOT(setNum(int)));
        QObject::connect(eq9, SIGNAL(valueChanged(int)), label_30, SLOT(setNum(int)));
        QObject::connect(eq7, SIGNAL(valueChanged(int)), label_18, SLOT(setNum(int)));
        QObject::connect(eq6, SIGNAL(valueChanged(int)), label_17, SLOT(setNum(int)));
        QObject::connect(eq5, SIGNAL(valueChanged(int)), label_16, SLOT(setNum(int)));
        QObject::connect(brightness, SIGNAL(valueChanged(int)), label_7, SLOT(setNum(int)));
        QObject::connect(Hue, SIGNAL(valueChanged(int)), label_8, SLOT(setNum(int)));
        QObject::connect(eq4, SIGNAL(valueChanged(int)), label_14, SLOT(setNum(int)));
        QObject::connect(contrast, SIGNAL(valueChanged(int)), label_3, SLOT(setNum(int)));
        QObject::connect(Saturation, SIGNAL(valueChanged(int)), label_9, SLOT(setNum(int)));
        QObject::connect(gamma, SIGNAL(valueChanged(int)), label_10, SLOT(setNum(int)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PlayerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlayerWindow)
    {
        PlayerWindow->setWindowTitle(QApplication::translate("PlayerWindow", "ExMplayer", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("PlayerWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        action_Play_Pause->setText(QApplication::translate("PlayerWindow", "P&lay/Pause", 0, QApplication::UnicodeUTF8));
        action_Stop->setText(QApplication::translate("PlayerWindow", "&Stop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Stop->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Stop</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_File->setText(QApplication::translate("PlayerWindow", "&File...", 0, QApplication::UnicodeUTF8));
        actionMute->setText(QApplication::translate("PlayerWindow", "&Mute", 0, QApplication::UnicodeUTF8));
        actionMute->setShortcut(QApplication::translate("PlayerWindow", "M", 0, QApplication::UnicodeUTF8));
        actionForward_10_seconds->setText(QApplication::translate("PlayerWindow", "&Forward 10 seconds", 0, QApplication::UnicodeUTF8));
        actionRewind_10_seconds->setText(QApplication::translate("PlayerWindow", "&Rewind 10 seconds", 0, QApplication::UnicodeUTF8));
        actionRewind_10_seconds->setShortcut(QApplication::translate("PlayerWindow", "Left", 0, QApplication::UnicodeUTF8));
        actionForward_1_minute->setText(QApplication::translate("PlayerWindow", "F&orward 1 minute", 0, QApplication::UnicodeUTF8));
        actionForward_1_minute->setShortcut(QApplication::translate("PlayerWindow", "Up", 0, QApplication::UnicodeUTF8));
        actionRewind_1_minute->setText(QApplication::translate("PlayerWindow", "R&ewind 1 minute", 0, QApplication::UnicodeUTF8));
        actionRewind_1_minute->setShortcut(QApplication::translate("PlayerWindow", "Down", 0, QApplication::UnicodeUTF8));
        actionForward_10_minutes->setText(QApplication::translate("PlayerWindow", "Fo&rward 10 minutes", 0, QApplication::UnicodeUTF8));
        actionForward_10_minutes->setShortcut(QApplication::translate("PlayerWindow", "PgUp", 0, QApplication::UnicodeUTF8));
        actionRewind_10_minutes->setText(QApplication::translate("PlayerWindow", "Re&wind 10 minutes", 0, QApplication::UnicodeUTF8));
        actionRewind_10_minutes->setShortcut(QApplication::translate("PlayerWindow", "PgDown", 0, QApplication::UnicodeUTF8));
        actionNormal_Speed->setText(QApplication::translate("PlayerWindow", "&Normal Speed", 0, QApplication::UnicodeUTF8));
        actionNormal_Speed->setShortcut(QApplication::translate("PlayerWindow", "Backspace", 0, QApplication::UnicodeUTF8));
        actionIncrease_10->setText(QApplication::translate("PlayerWindow", "&Increase 10%", 0, QApplication::UnicodeUTF8));
        actionIncrease_10->setShortcut(QApplication::translate("PlayerWindow", "]", 0, QApplication::UnicodeUTF8));
        actionDecrease_10->setText(QApplication::translate("PlayerWindow", "&Decrease 10%", 0, QApplication::UnicodeUTF8));
        actionDecrease_10->setShortcut(QApplication::translate("PlayerWindow", "[", 0, QApplication::UnicodeUTF8));
        actionDouble_speed->setText(QApplication::translate("PlayerWindow", "D&ouble speed", 0, QApplication::UnicodeUTF8));
        actionDouble_speed->setShortcut(QApplication::translate("PlayerWindow", "}", 0, QApplication::UnicodeUTF8));
        actionHalve_speed->setText(QApplication::translate("PlayerWindow", "&Halve speed", 0, QApplication::UnicodeUTF8));
        actionHalve_speed->setShortcut(QApplication::translate("PlayerWindow", "{", 0, QApplication::UnicodeUTF8));
        action_Increase_volume->setText(QApplication::translate("PlayerWindow", "&Increase volume", 0, QApplication::UnicodeUTF8));
        action_Increase_volume->setShortcut(QApplication::translate("PlayerWindow", "+", 0, QApplication::UnicodeUTF8));
        action_Decrease_volume->setText(QApplication::translate("PlayerWindow", "&Decrease volume", 0, QApplication::UnicodeUTF8));
        action_Decrease_volume->setShortcut(QApplication::translate("PlayerWindow", "-", 0, QApplication::UnicodeUTF8));
        actionIncrease_Delay->setText(QApplication::translate("PlayerWindow", "Increase D&elay", 0, QApplication::UnicodeUTF8));
        actionIncrease_Delay->setShortcut(QApplication::translate("PlayerWindow", "*", 0, QApplication::UnicodeUTF8));
        actionDecrease_Delay->setText(QApplication::translate("PlayerWindow", "Decrease De&lay", 0, QApplication::UnicodeUTF8));
        actionDecrease_Delay->setShortcut(QApplication::translate("PlayerWindow", "/", 0, QApplication::UnicodeUTF8));
        actionAudioDisable->setText(QApplication::translate("PlayerWindow", "D&isable", 0, QApplication::UnicodeUTF8));
        actionLoad_external_file->setText(QApplication::translate("PlayerWindow", "&Load a external audio file", 0, QApplication::UnicodeUTF8));
        actionStereo->setText(QApplication::translate("PlayerWindow", "S&tereo", 0, QApplication::UnicodeUTF8));
        actionSurround->setText(QApplication::translate("PlayerWindow", "S&urround", 0, QApplication::UnicodeUTF8));
        actionFull_5_1->setText(QApplication::translate("PlayerWindow", " 5.1Su&rround", 0, QApplication::UnicodeUTF8));
        action_Karaoke->setText(QApplication::translate("PlayerWindow", "&Karaoke", 0, QApplication::UnicodeUTF8));
        action8000->setText(QApplication::translate("PlayerWindow", "8000", 0, QApplication::UnicodeUTF8));
        action11025->setText(QApplication::translate("PlayerWindow", "11025", 0, QApplication::UnicodeUTF8));
        action12000->setText(QApplication::translate("PlayerWindow", "12000", 0, QApplication::UnicodeUTF8));
        action16000->setText(QApplication::translate("PlayerWindow", "16000", 0, QApplication::UnicodeUTF8));
        action22100->setText(QApplication::translate("PlayerWindow", "22100", 0, QApplication::UnicodeUTF8));
        action24000->setText(QApplication::translate("PlayerWindow", "24000", 0, QApplication::UnicodeUTF8));
        action32000->setText(QApplication::translate("PlayerWindow", "32000", 0, QApplication::UnicodeUTF8));
        action44100->setText(QApplication::translate("PlayerWindow", "44100", 0, QApplication::UnicodeUTF8));
        action48000->setText(QApplication::translate("PlayerWindow", "48000", 0, QApplication::UnicodeUTF8));
        action96000->setText(QApplication::translate("PlayerWindow", "96000", 0, QApplication::UnicodeUTF8));
        action192000->setText(QApplication::translate("PlayerWindow", "192000", 0, QApplication::UnicodeUTF8));
        actionSurroundAf->setText(QApplication::translate("PlayerWindow", "&Surround", 0, QApplication::UnicodeUTF8));
        action_ExtraStereo->setText(QApplication::translate("PlayerWindow", "&ExtraStereo", 0, QApplication::UnicodeUTF8));
        actionScale_Tempo->setText(QApplication::translate("PlayerWindow", "Scale&Tempo", 0, QApplication::UnicodeUTF8));
        action_Delay->setText(QApplication::translate("PlayerWindow", "&Delay", 0, QApplication::UnicodeUTF8));
        actionStereomode->setText(QApplication::translate("PlayerWindow", "S&tereo", 0, QApplication::UnicodeUTF8));
        actionLeft_channel->setText(QApplication::translate("PlayerWindow", "&Left channel", 0, QApplication::UnicodeUTF8));
        actionRight_channel->setText(QApplication::translate("PlayerWindow", "&Right channel", 0, QApplication::UnicodeUTF8));
        action_Remove_logo->setText(QApplication::translate("PlayerWindow", "Remove &logo", 0, QApplication::UnicodeUTF8));
        action_Tile->setText(QApplication::translate("PlayerWindow", "T&ile", 0, QApplication::UnicodeUTF8));
        action_flip->setText(QApplication::translate("PlayerWindow", "&Flip", 0, QApplication::UnicodeUTF8));
        action_Mirror->setText(QApplication::translate("PlayerWindow", "&Mirror", 0, QApplication::UnicodeUTF8));
        action50_50->setText(QApplication::translate("PlayerWindow", "50:50", 0, QApplication::UnicodeUTF8));
        actionRotate_0->setText(QApplication::translate("PlayerWindow", "Rotate by 90 degrees &clockwise and flip", 0, QApplication::UnicodeUTF8));
        actionRotate_1->setText(QApplication::translate("PlayerWindow", "Rotate by 90 degrees c&lockwise", 0, QApplication::UnicodeUTF8));
        actionRotate_2->setText(QApplication::translate("PlayerWindow", "Rotate by 90 degrees c&ounterclockwise", 0, QApplication::UnicodeUTF8));
        actionRotate_3->setText(QApplication::translate("PlayerWindow", "Rotate by 90 degrees co&unterclockwise and flip", 0, QApplication::UnicodeUTF8));
        action_RotateDisable->setText(QApplication::translate("PlayerWindow", "&Disable", 0, QApplication::UnicodeUTF8));
        actionSwap_U_and_V->setText(QApplication::translate("PlayerWindow", "S&wap U and V", 0, QApplication::UnicodeUTF8));
        actionOld_Black_and_white->setText(QApplication::translate("PlayerWindow", "&Black and white with noise", 0, QApplication::UnicodeUTF8));
        actionPainting->setText(QApplication::translate("PlayerWindow", "P&ortrait", 0, QApplication::UnicodeUTF8));
        actionAdd_noise->setText(QApplication::translate("PlayerWindow", "Add &Noise", 0, QApplication::UnicodeUTF8));
        action_Blur->setText(QApplication::translate("PlayerWindow", "&Blur", 0, QApplication::UnicodeUTF8));
        actionMatrixview->setText(QApplication::translate("PlayerWindow", "Matrix Vi&ew", 0, QApplication::UnicodeUTF8));
        actionVisualize_motion_vectors->setText(QApplication::translate("PlayerWindow", "Visualize motion &vectors", 0, QApplication::UnicodeUTF8));
        action_Palette->setText(QApplication::translate("PlayerWindow", "&Palette", 0, QApplication::UnicodeUTF8));
        actionStep1_fm->setText(QApplication::translate("PlayerWindow", "Step1:Mar&k positions", 0, QApplication::UnicodeUTF8));
        actionStep2_fm->setText(QApplication::translate("PlayerWindow", "Step2:S&tart Family-Friendly mode", 0, QApplication::UnicodeUTF8));
        action_ar_Auto->setText(QApplication::translate("PlayerWindow", "A&uto", 0, QApplication::UnicodeUTF8));
        action1_1->setText(QApplication::translate("PlayerWindow", "&1:1", 0, QApplication::UnicodeUTF8));
        action4_3->setText(QApplication::translate("PlayerWindow", "&4:3", 0, QApplication::UnicodeUTF8));
        action16_9->setText(QApplication::translate("PlayerWindow", "16:&9", 0, QApplication::UnicodeUTF8));
        action16_10->setText(QApplication::translate("PlayerWindow", "1&6:10", 0, QApplication::UnicodeUTF8));
        action2_21_1->setText(QApplication::translate("PlayerWindow", "&2.35:1", 0, QApplication::UnicodeUTF8));
        action5_4->setText(QApplication::translate("PlayerWindow", "&5:4", 0, QApplication::UnicodeUTF8));
        action_ar_Custom->setText(QApplication::translate("PlayerWindow", "&Custom", 0, QApplication::UnicodeUTF8));
        action_ar_Disable->setText(QApplication::translate("PlayerWindow", "&Disable", 0, QApplication::UnicodeUTF8));
        action3_2->setText(QApplication::translate("PlayerWindow", "&3:2", 0, QApplication::UnicodeUTF8));
        action14_9->setText(QApplication::translate("PlayerWindow", "14:9", 0, QApplication::UnicodeUTF8));
        action14_10->setText(QApplication::translate("PlayerWindow", "14:10", 0, QApplication::UnicodeUTF8));
        action_Crop->setText(QApplication::translate("PlayerWindow", "&Crop", 0, QApplication::UnicodeUTF8));
        actionVideoDisable->setText(QApplication::translate("PlayerWindow", "Disable", 0, QApplication::UnicodeUTF8));
        action_osd0->setText(QApplication::translate("PlayerWindow", "&Disable", 0, QApplication::UnicodeUTF8));
        action_osd1->setText(QApplication::translate("PlayerWindow", "Volume + &Seek", 0, QApplication::UnicodeUTF8));
        action_osd2->setText(QApplication::translate("PlayerWindow", "Volume + Seek+&Timer", 0, QApplication::UnicodeUTF8));
        action_osd3->setText(QApplication::translate("PlayerWindow", "Volume + Seek+Timer+Tota&l time", 0, QApplication::UnicodeUTF8));
        actionToggle_OSD->setText(QApplication::translate("PlayerWindow", "Toggle O&SD", 0, QApplication::UnicodeUTF8));
        actionToggle_OSD->setShortcut(QApplication::translate("PlayerWindow", "O", 0, QApplication::UnicodeUTF8));
        action_fd_Disable->setText(QApplication::translate("PlayerWindow", "&Disable", 0, QApplication::UnicodeUTF8));
        actionSoft->setText(QApplication::translate("PlayerWindow", "&Soft", 0, QApplication::UnicodeUTF8));
        actionHard->setText(QApplication::translate("PlayerWindow", "&Hard", 0, QApplication::UnicodeUTF8));
        actionToggle_Frame_drop->setText(QApplication::translate("PlayerWindow", "Toggle Frame drop", 0, QApplication::UnicodeUTF8));
        actionToggle_Frame_drop->setShortcut(QApplication::translate("PlayerWindow", "D", 0, QApplication::UnicodeUTF8));
        actionStay_on_top->setText(QApplication::translate("PlayerWindow", "Stay on &top ", 0, QApplication::UnicodeUTF8));
        actionStay_on_top->setShortcut(QApplication::translate("PlayerWindow", "T", 0, QApplication::UnicodeUTF8));
        actionScreen_shot->setText(QApplication::translate("PlayerWindow", "Screen&shot", 0, QApplication::UnicodeUTF8));
        actionScreen_shot->setShortcut(QApplication::translate("PlayerWindow", "C", 0, QApplication::UnicodeUTF8));
        actionStart_stop_Screenshot->setText(QApplication::translate("PlayerWindow", "St&art/stop Screenshot", 0, QApplication::UnicodeUTF8));
        actionStart_stop_Screenshot->setShortcut(QApplication::translate("PlayerWindow", "Shift+C", 0, QApplication::UnicodeUTF8));
        action_Open_Screenshot_folder->setText(QApplication::translate("PlayerWindow", "&Open Screenshot folder", 0, QApplication::UnicodeUTF8));
        action_Open_Screenshot_folder->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionFrame_step->setText(QApplication::translate("PlayerWindow", "Frame ste&p", 0, QApplication::UnicodeUTF8));
        actionFrame_step->setShortcut(QApplication::translate("PlayerWindow", "S", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("PlayerWindow", "&About", 0, QApplication::UnicodeUTF8));
        action_Load_st->setText(QApplication::translate("PlayerWindow", "&Load", 0, QApplication::UnicodeUTF8));
        actionToggle_subtitle_visibility->setText(QApplication::translate("PlayerWindow", "Toggle subtitle &visibility", 0, QApplication::UnicodeUTF8));
        action_Equalizer->setText(QApplication::translate("PlayerWindow", "&Equalizer", 0, QApplication::UnicodeUTF8));
        action_Equalizer->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+E", 0, QApplication::UnicodeUTF8));
        actionVideoEqualizer->setText(QApplication::translate("PlayerWindow", "&Equalizer", 0, QApplication::UnicodeUTF8));
        actionVideoEqualizer->setShortcut(QApplication::translate("PlayerWindow", "Shift+E", 0, QApplication::UnicodeUTF8));
        actionStNone->setText(QApplication::translate("PlayerWindow", "Disable", 0, QApplication::UnicodeUTF8));
        actionStUnload->setText(QApplication::translate("PlayerWindow", "&Unload", 0, QApplication::UnicodeUTF8));
        actionSize_Increase->setText(QApplication::translate("PlayerWindow", "Size &Increase", 0, QApplication::UnicodeUTF8));
        actionSize_Increase->setShortcut(QApplication::translate("PlayerWindow", "Ctrl++", 0, QApplication::UnicodeUTF8));
        actionSize_Decrease->setText(QApplication::translate("PlayerWindow", "Size &Decrease", 0, QApplication::UnicodeUTF8));
        actionSize_Decrease->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+-", 0, QApplication::UnicodeUTF8));
        action_sa_Top->setText(QApplication::translate("PlayerWindow", " &Top ", 0, QApplication::UnicodeUTF8));
        action_sa_Center->setText(QApplication::translate("PlayerWindow", "&Center", 0, QApplication::UnicodeUTF8));
        action_sa_Bottom->setText(QApplication::translate("PlayerWindow", "&Bottom", 0, QApplication::UnicodeUTF8));
        action_st_Move_Up->setText(QApplication::translate("PlayerWindow", "Move &Up", 0, QApplication::UnicodeUTF8));
        action_st_Move_Up->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+Up", 0, QApplication::UnicodeUTF8));
        action_st_Move_Down->setText(QApplication::translate("PlayerWindow", "Move &Down", 0, QApplication::UnicodeUTF8));
        action_st_Move_Down->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+Down", 0, QApplication::UnicodeUTF8));
        actionDelay_Increaser->setText(QApplication::translate("PlayerWindow", "D&elay Increase", 0, QApplication::UnicodeUTF8));
        actionDelay_Increaser->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+*", 0, QApplication::UnicodeUTF8));
        actionDelay_Decrease->setText(QApplication::translate("PlayerWindow", "De&lay Decrease", 0, QApplication::UnicodeUTF8));
        actionDelay_Decrease->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+/", 0, QApplication::UnicodeUTF8));
        action_st_Set_Delay->setText(QApplication::translate("PlayerWindow", "Set &Delay", 0, QApplication::UnicodeUTF8));
        action_AV_Set_Delay->setText(QApplication::translate("PlayerWindow", "Set &Delay", 0, QApplication::UnicodeUTF8));
        actionFullscreen->setText(QApplication::translate("PlayerWindow", "Fullscreen", 0, QApplication::UnicodeUTF8));
        actionFullscreen->setShortcut(QApplication::translate("PlayerWindow", "F", 0, QApplication::UnicodeUTF8));
        actionAdd_file->setText(QApplication::translate("PlayerWindow", "Add file", 0, QApplication::UnicodeUTF8));
        actionAdd_Folder->setText(QApplication::translate("PlayerWindow", "Add Folder", 0, QApplication::UnicodeUTF8));
        actionSelected_item_s->setText(QApplication::translate("PlayerWindow", "RemoveSelected item(s)", 0, QApplication::UnicodeUTF8));
        actionRemove_all->setText(QApplication::translate("PlayerWindow", "Remove all", 0, QApplication::UnicodeUTF8));
        action_Load_pl->setText(QApplication::translate("PlayerWindow", "&Load playlist...", 0, QApplication::UnicodeUTF8));
        action_Save_as_playlist->setText(QApplication::translate("PlayerWindow", "&Save as playlist", 0, QApplication::UnicodeUTF8));
        action_Media_Info->setText(QApplication::translate("PlayerWindow", "&Media Info..", 0, QApplication::UnicodeUTF8));
        action_Media_Info->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        action_Options->setText(QApplication::translate("PlayerWindow", "&Options", 0, QApplication::UnicodeUTF8));
        action_Options->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionVolume_Normalization->setText(QApplication::translate("PlayerWindow", "Volume Normalization", 0, QApplication::UnicodeUTF8));
        actionNegative->setText(QApplication::translate("PlayerWindow", "&Negative", 0, QApplication::UnicodeUTF8));
        actionWinamp_Dsp->setText(QApplication::translate("PlayerWindow", "Winamp Dsp", 0, QApplication::UnicodeUTF8));
        actionURL->setText(QApplication::translate("PlayerWindow", "&URL..", 0, QApplication::UnicodeUTF8));
        actionPlay_Next_File->setText(QApplication::translate("PlayerWindow", "Play Next File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPlay_Next_File->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Play</span><span style=\" font-size:8pt; font-weight:600;\"> Next</span><span style=\" font-size:8pt;\"> File</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPlay_Next_File->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionPlay_Next_File->setShortcut(QApplication::translate("PlayerWindow", "N", 0, QApplication::UnicodeUTF8));
        actionPlay_Previous_File->setText(QApplication::translate("PlayerWindow", "Play Previous File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPlay_Previous_File->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Play</span><span style=\" font-size:8pt; font-weight:600;\"> Previous</span><span style=\" font-size:8pt;\"> File</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPlay_Previous_File->setShortcut(QApplication::translate("PlayerWindow", "P", 0, QApplication::UnicodeUTF8));
        actionOpen_containing_folder->setText(QApplication::translate("PlayerWindow", "Open containing folder...", 0, QApplication::UnicodeUTF8));
        actionOpen_containing_folder->setShortcut(QApplication::translate("PlayerWindow", "Alt+C", 0, QApplication::UnicodeUTF8));
        actionEnable_Closed_Captions->setText(QApplication::translate("PlayerWindow", "Enable Closed Captions", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionEnable_Closed_Captions->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Display DVD Closed Caption (CC) subtitles.Closed captions are special ASCII subtitles for the hearing impaired encoded in the VOB userdata.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMedia_cutter->setText(QApplication::translate("PlayerWindow", "Media cutter", 0, QApplication::UnicodeUTF8));
        actionShowpl->setText(QApplication::translate("PlayerWindow", "Show/hide", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShowpl->setToolTip(QApplication::translate("PlayerWindow", "Show/hide Playlist", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionShowpl->setShortcut(QApplication::translate("PlayerWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));
        actionFull_7_1->setText(QApplication::translate("PlayerWindow", "7.1Surround", 0, QApplication::UnicodeUTF8));
        action_Help->setText(QApplication::translate("PlayerWindow", "&Help", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("PlayerWindow", "About Qt", 0, QApplication::UnicodeUTF8));
        actionMix_and_save->setText(QApplication::translate("PlayerWindow", "Mix and save", 0, QApplication::UnicodeUTF8));
        actionFolder->setText(QApplication::translate("PlayerWindow", "Folde&r...", 0, QApplication::UnicodeUTF8));
        actionSave_cover_art->setText(QApplication::translate("PlayerWindow", "Save cover art...", 0, QApplication::UnicodeUTF8));
        actionEdit_Playlist->setText(QApplication::translate("PlayerWindow", "&Edit Playlist...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionEdit_Playlist->setToolTip(QApplication::translate("PlayerWindow", "E&dit Playlist", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAdd_File_to_pl->setText(QApplication::translate("PlayerWindow", "Add F&ile(s) to playlist...", 0, QApplication::UnicodeUTF8));
        actionAdd_Folder_to_pl->setText(QApplication::translate("PlayerWindow", "Add F&older to playlist...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAdd_Folder_to_pl->setToolTip(QApplication::translate("PlayerWindow", "Add Folder", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionTwins->setText(QApplication::translate("PlayerWindow", "Twins", 0, QApplication::UnicodeUTF8));
        actionSide_view->setText(QApplication::translate("PlayerWindow", "Side view", 0, QApplication::UnicodeUTF8));
        actionAudio_extrctor->setText(QApplication::translate("PlayerWindow", "Audio Extractor", 0, QApplication::UnicodeUTF8));
        actionIncrease_Zoom->setText(QApplication::translate("PlayerWindow", "Increase Zoom", 0, QApplication::UnicodeUTF8));
        actionDecrease_Zoom->setText(QApplication::translate("PlayerWindow", "Decrease Zoom", 0, QApplication::UnicodeUTF8));
        actionMove_Left->setText(QApplication::translate("PlayerWindow", "Move Left", 0, QApplication::UnicodeUTF8));
        actionMove_Right->setText(QApplication::translate("PlayerWindow", "Move Right", 0, QApplication::UnicodeUTF8));
        actionMove_Up->setText(QApplication::translate("PlayerWindow", "Move Up", 0, QApplication::UnicodeUTF8));
        actionMove_Down->setText(QApplication::translate("PlayerWindow", "Move Down", 0, QApplication::UnicodeUTF8));
        actionIncrease_Video_quality->setText(QApplication::translate("PlayerWindow", "Increase Video quality", 0, QApplication::UnicodeUTF8));
        actionChange_framerate->setText(QApplication::translate("PlayerWindow", "Change frame rate", 0, QApplication::UnicodeUTF8));
        actionDefault->setText(QApplication::translate("PlayerWindow", "Default", 0, QApplication::UnicodeUTF8));
        actionDefault_zoom->setText(QApplication::translate("PlayerWindow", "Default", 0, QApplication::UnicodeUTF8));
        actionAudio_Converter->setText(QApplication::translate("PlayerWindow", "Audio Converter", 0, QApplication::UnicodeUTF8));
        actionSmallmode->setText(QApplication::translate("PlayerWindow", "Small Mode", 0, QApplication::UnicodeUTF8));
        actionCopy_Audio_CD->setText(QApplication::translate("PlayerWindow", "Copy Audio CD", 0, QApplication::UnicodeUTF8));
        actionInternet_Radio->setText(QApplication::translate("PlayerWindow", "Internet Radio", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdCurPos->setToolTip(QApplication::translate("PlayerWindow", "Current position ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lcdDuration->setToolTip(QApplication::translate("PlayerWindow", "Duration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        progressBarBusy->setFormat(QString());
        labelStatus->setText(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Ready</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSpeed->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Playback speed as a factor of original speed</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSpeed->setText(QApplication::translate("PlayerWindow", "1.00x", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelCpuAudio->setToolTip(QApplication::translate("PlayerWindow", "Audio codec CPU usage in percent", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelCpuAudio->setText(QApplication::translate("PlayerWindow", "0%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelFrameCount->setToolTip(QApplication::translate("PlayerWindow", "Frames played/decoded", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelFrameCount->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelAVdelay->setToolTip(QApplication::translate("PlayerWindow", " Audio-Video(A-V) difference in seconds (delay)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelAVdelay->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelCpuVideo->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Video codec CPU usage in percent</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelCpuVideo->setText(QApplication::translate("PlayerWindow", "0%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderVolume->setToolTip(QApplication::translate("PlayerWindow", "Volume", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        toolButtonRewind->setToolTip(QApplication::translate("PlayerWindow", "Rewind", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonRewind->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButtonForward->setToolTip(QApplication::translate("PlayerWindow", "Forward", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonForward->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButtonVolume->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Mute </span><span style=\" font-size:8pt; font-weight:600;\">On\\Off</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonVolume->setText(QString());
        label_display->setText(QString());
        label_3->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlayerWindow", "Contrast", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlayerWindow", "Brightness", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("PlayerWindow", "Hue", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PlayerWindow", "Saturation", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PlayerWindow", "Gamma", 0, QApplication::UnicodeUTF8));
        btnVEReset->setText(QApplication::translate("PlayerWindow", "Reset", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QApplication::translate("PlayerWindow", "Video equalizer", 0, QApplication::UnicodeUTF8));
        btnAEReset->setText(QApplication::translate("PlayerWindow", "Reset", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("PlayerWindow", "31Hz", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("PlayerWindow", "62Hz", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("PlayerWindow", "125Hz", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("PlayerWindow", "250Hz", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("PlayerWindow", "500Hz", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("PlayerWindow", "1KHz", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("PlayerWindow", "2KHz", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("PlayerWindow", "4KHz", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("PlayerWindow", "8KHz", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("PlayerWindow", "16KHz", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("PlayerWindow", "0", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("PlayerWindow", "Classical", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Club", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Dance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Flat", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Fullbass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "FullbassTreble", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Fulltreble", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Headphones", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "LargeHall", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Live", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Party", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Pop", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Reggae", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Rock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Ska", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Soft", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "SoftRock", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Techno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlayerWindow", "Custom", 0, QApplication::UnicodeUTF8)
        );
        cbEnableAEq->setText(QApplication::translate("PlayerWindow", "Enable", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage2), QApplication::translate("PlayerWindow", "Audio equalizer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonfs->setToolTip(QApplication::translate("PlayerWindow", "Fullscreen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonfs->setText(QApplication::translate("PlayerWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonLpl->setToolTip(QApplication::translate("PlayerWindow", "Load/save playlist", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonLpl->setText(QApplication::translate("PlayerWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonAdd->setToolTip(QApplication::translate("PlayerWindow", "Add files to playlist", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonAdd->setText(QApplication::translate("PlayerWindow", "+", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonRemove->setToolTip(QApplication::translate("PlayerWindow", "Remove files", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonRemove->setText(QApplication::translate("PlayerWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_loop->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Loop playlist</span><span style=\" font-size:8pt; font-weight:600;\"> On/Off</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_loop->setText(QApplication::translate("PlayerWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_shuffle->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Shuffle </span><span style=\" font-size:8pt; font-weight:600;\">On/Off</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_shuffle->setText(QApplication::translate("PlayerWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_playpre->setToolTip(QApplication::translate("PlayerWindow", "Play previous file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_playpre->setText(QApplication::translate("PlayerWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_playnext->setToolTip(QApplication::translate("PlayerWindow", "Play next file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_playnext->setText(QApplication::translate("PlayerWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonSpeed->setToolTip(QApplication::translate("PlayerWindow", "Normal speed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonSpeed->setText(QApplication::translate("PlayerWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonplaylist->setToolTip(QApplication::translate("PlayerWindow", "Playlist", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonplaylist->setText(QApplication::translate("PlayerWindow", "...", 0, QApplication::UnicodeUTF8));
        labToolbarSpace->setText(QString());
#ifndef QT_NO_TOOLTIP
        labVD->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Width x Height</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labVD->setText(QApplication::translate("PlayerWindow", "wxh", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labAD->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Sample Frequency Mono/Stereo</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Audio bitrate</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labAD->setText(QApplication::translate("PlayerWindow", "wxh", 0, QApplication::UnicodeUTF8));
        menu_Open->setTitle(QApplication::translate("PlayerWindow", "&Open", 0, QApplication::UnicodeUTF8));
        menuPlay->setTitle(QApplication::translate("PlayerWindow", "&Playback", 0, QApplication::UnicodeUTF8));
        menuSpeed->setTitle(QApplication::translate("PlayerWindow", "S&peed", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        menuFa_mily_Friendly_mode->setToolTip(QApplication::translate("PlayerWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">You can cut out any violence, profanity, Jar-Jar Binks .. from a movie  according to your own personal preferences.Aside from this, there are  other uses, like automatically skipping over commercials in video files you watch.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuFa_mily_Friendly_mode->setTitle(QApplication::translate("PlayerWindow", "Fa&mily-Friendly mode", 0, QApplication::UnicodeUTF8));
        menu_Audio->setTitle(QApplication::translate("PlayerWindow", "&Audio", 0, QApplication::UnicodeUTF8));
        menuAudio_Track->setTitle(QApplication::translate("PlayerWindow", "Audio &Track", 0, QApplication::UnicodeUTF8));
        menuC_hannels->setTitle(QApplication::translate("PlayerWindow", "C&hannels", 0, QApplication::UnicodeUTF8));
        menu_Filters->setTitle(QApplication::translate("PlayerWindow", "&Filters", 0, QApplication::UnicodeUTF8));
        menu_Resample->setTitle(QApplication::translate("PlayerWindow", "&Resample", 0, QApplication::UnicodeUTF8));
        menu_Video->setTitle(QApplication::translate("PlayerWindow", "&Video", 0, QApplication::UnicodeUTF8));
        menu_Filters_2->setTitle(QApplication::translate("PlayerWindow", "&Filters", 0, QApplication::UnicodeUTF8));
        menu_Rotate->setTitle(QApplication::translate("PlayerWindow", "&Rotate", 0, QApplication::UnicodeUTF8));
        menuA_spect_ratio->setTitle(QApplication::translate("PlayerWindow", "Aspect &ratio", 0, QApplication::UnicodeUTF8));
        menuVideo_Track->setTitle(QApplication::translate("PlayerWindow", "Video & Track", 0, QApplication::UnicodeUTF8));
        menuOSD->setTitle(QApplication::translate("PlayerWindow", "&OSD", 0, QApplication::UnicodeUTF8));
        menuFrame_drop->setTitle(QApplication::translate("PlayerWindow", "Frame &drop", 0, QApplication::UnicodeUTF8));
        menuZoom->setTitle(QApplication::translate("PlayerWindow", "Zoom", 0, QApplication::UnicodeUTF8));
        menuFrame_rate_fps->setTitle(QApplication::translate("PlayerWindow", "Frame rate (fps)", 0, QApplication::UnicodeUTF8));
        menu_Subtitles->setTitle(QApplication::translate("PlayerWindow", "&Subtitles", 0, QApplication::UnicodeUTF8));
        menuSelect->setTitle(QApplication::translate("PlayerWindow", "Select", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("PlayerWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuPlaylist->setTitle(QApplication::translate("PlayerWindow", "Play&list", 0, QApplication::UnicodeUTF8));
        menuAdd->setTitle(QApplication::translate("PlayerWindow", "&Add", 0, QApplication::UnicodeUTF8));
        menu_Remove->setTitle(QApplication::translate("PlayerWindow", "&Remove", 0, QApplication::UnicodeUTF8));
        menu_Tools->setTitle(QApplication::translate("PlayerWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("PlayerWindow", "V&iew", 0, QApplication::UnicodeUTF8));
        dockBrowser->setWindowTitle(QApplication::translate("PlayerWindow", "Flow Browser", 0, QApplication::UnicodeUTF8));
        dock_Playlist->setWindowTitle(QApplication::translate("PlayerWindow", "Playlist", 0, QApplication::UnicodeUTF8));
        toolBarPlaylist->setWindowTitle(QApplication::translate("PlayerWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        dock_Filter->setWindowTitle(QApplication::translate("PlayerWindow", "Equalizer", 0, QApplication::UnicodeUTF8));
        toolBarStatus->setWindowTitle(QApplication::translate("PlayerWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        toolBarSeek->setWindowTitle(QApplication::translate("PlayerWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        toolBarSeekBar->setWindowTitle(QApplication::translate("PlayerWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        dock_log->setWindowTitle(QApplication::translate("PlayerWindow", "MPlayer Log", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmdLine->setToolTip(QApplication::translate("PlayerWindow", "Enter MPlayer command", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdLine->setText(QString());
        cmdLine->setPlaceholderText(QApplication::translate("PlayerWindow", "Enter command", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        btnSaveLog->setStatusTip(QApplication::translate("PlayerWindow", "Save log to a file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        btnSaveLog->setText(QApplication::translate("PlayerWindow", "Save As...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlayerWindow: public Ui_PlayerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWINDOW_H
