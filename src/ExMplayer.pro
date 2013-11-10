# -------------------------------------------------
# Project created by QtCreator 2010-06-10T20:36:40
# -------------------------------------------------
QT       += core gui
QT       += network xml
unix{
TARGET    = exmplayer
}
TEMPLATE  = app


SOURCES += main.cpp \
    playerwindow.cpp \
    mplayerfe.cpp \
    rphslider.cpp \
    rphalabelex.cpp \
    config.cpp \
    equalizertypes.cpp \
    pictureflow.cpp \
    playlist.cpp \
    dockplaylist.cpp \
    QProgressIndicator.cpp \
    preferencedialog.cpp \
    winampdspdialog.cpp \
    urldialog.cpp \
    QRecentFilesMenu.cpp \
    audioextdialog.cpp \
    shortcutgetter.cpp \
    midialog.cpp \
    assstyles.cpp \
    colorutils.cpp \
    aboutdialog.cpp \
    helpdialog.cpp \
    rphmpfehelp.cpp \
    cutterdialog.cpp \
    norwegianwoodstyle.cpp \
    winfileassoc.cpp \
    mixdialog.cpp \
    rphfile.cpp \
    desktopinfo.cpp \
    mplayerwindow.cpp \
    audioconvdialog.cpp \
    filefilters.cpp \
    seekview.cpp \
    myprocess.cpp \
    glassstyle.cpp \
    fontloaddialog.cpp\
    advancedinfodialog.cpp \
    paths.cpp \
    qcoverart.cpp \
    stereovinputdialog.cpp
HEADERS += playerwindow.h \
    mplayerfe.h \
    rphlabelex.h \
    rphslider.h \
    config.h \
    equalizertypes.h \
    pictureflow.h \
    playlist.h \
    dockplaylist.h \
    rphlabelex.h \
    QProgressIndicator.h \
    preferencedialog.h \
    winampdspdialog.h \
    urldialog.h \
    QRecentFilesMenu.h \
    audioextdialog.h \
    shortcutgetter.h \
    midialog.h \
    colorutils.h \
    assstyles.h \
    aboutdialog.h \
    helpdialog.h \
    rphmpfehelp.h \
    cutterdialog.h \
    norwegianwoodstyle.h \
    winfileassoc.h \
    mixdialog.h \
    rphfile.h \
    mplayerwindow.h \
    desktopinfo.h \
    audioconvdialog.h \
    filefilters.h \
    seekview.h \
    myprocess.h \
    glassstyle.h \
    fontloaddialog.h\
    advancedinfodialog.h \
    paths.h \
    qcoverart.h \
    stereovinputdialog.h
FORMS += playerwindow.ui \
    preferencedialog.ui \
    winampdspdialog.ui \
    urldialog.ui \
    audioextdialog.ui \
    midialog.ui \
    aboutdialog.ui \
    helpdialog.ui \
    cutterdialog.ui \
    mixdialog.ui \
    audioconvdialog.ui \
    seekview.ui \
    fontloaddialog.ui \
    advancedinfodialog.ui \
    stereovinputdialog.ui

INCLUDEPATH += qtsingleapplication
DEPENDPATH += qtsingleapplication
SOURCES += qtsingleapplication.cpp qtlocalpeer.cpp
HEADERS += qtsingleapplication.h qtlocalpeer.h


INCLUDEPATH +=taglib

LIBS += $$PWD\taglib\lib\libtag.a


win32 {

INCLUDEPATH += directx

HEADERS += screensaver.h
SOURCES += screensaver.cpp
LIBS += -ldsound \
    -lddraw
contains(TEMPLATE,vcapp):LIBS += ole32.lib \
    user32.lib
else:LIBS += libole32
}
RESOURCES += ExMplayer.qrc
RC_FILE = ExMplayer.rc
