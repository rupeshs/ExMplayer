# -------------------------------------------------
# Project created by QtCreator 2010-06-10T20:36:40
# -------------------------------------------------
TEMPLATE = app
QT       += core gui
QT       += network xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix{
QT       += dbus
TARGET    = exmplayer
}
#DEFINES += TAGLIB

message(Qt version: $$QT_VERSION)

lessThan(QT_MAJOR_VERSION, 5) {
message("Single instance enabled(Qt<5)")

DEFINES += SINGLE_INSTANCE
}
# qtsingleapplication
contains( DEFINES, SINGLE_INSTANCE ) {

INCLUDEPATH += qtsingleapplication
DEPENDPATH += qtsingleapplication

HEADERS += qtsingleapplication/qtsingleapplication.h qtsingleapplication/qtlocalpeer.h
SOURCES += qtsingleapplication/qtsingleapplication.cpp qtsingleapplication/qtlocalpeer.cpp

HEADERS +=norwegianwoodstyle.h
SOURCES +=norwegianwoodstyle.cpp
}

HEADERS +=  gifpalettegenerator.h \
            gifgenerator.h \
            gifanimatordialog.h

SOURCES += gifpalettegenerator.cpp \
           gifgenerator.cpp \
           gifanimatordialog.cpp

INCLUDEPATH += searchsubtitle
DEPENDPATH += searchsubtitle

INCLUDEPATH += searchsubtitle/maia
DEPENDPATH += searchsubtitle/maia

INCLUDEPATH += searchsubtitle/miniz
DEPENDPATH += searchsubtitle/miniz

HEADERS += searchsubtitle/opensubtitleclient.h searchsubtitle/gzipuncompressor.h searchsubtitle/searchsubtitle.h
SOURCES += searchsubtitle/opensubtitleclient.cpp searchsubtitle/gzipuncompressor.cpp searchsubtitle/searchsubtitle.cpp

FORMS += searchsubtitle/searchsubtitle.ui \
    coverartdialog.ui \
    gifanimatordialog.ui

#miniz library to uncompress data
SOURCES += searchsubtitle/miniz/miniz.c searchsubtitle/miniz/tinfl.c

# xmlrpc client code to connect to opensubtitles.org
HEADERS +=searchsubtitle/maia/maiaObject.h searchsubtitle/maia/maiaFault.h searchsubtitle/maia/maiaXmlRpcClient.h
SOURCES += searchsubtitle/maia/maiaObject.cpp searchsubtitle/maia/maiaFault.cpp searchsubtitle/maia/maiaXmlRpcClient.cpp

#video dl support
INCLUDEPATH += videodl
DEPENDPATH += videodl

HEADERS += videodl/youtubedlfe.h videodl/videodl.h videodl/vdlsettingsdialog.h videodl/supsitesdialog.h
SOURCES += videodl/youtubedlfe.cpp videodl/videodl.cpp videodl/vdlsettingsdialog.cpp videodl/supsitesdialog.cpp
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
    stereovinputdialog.cpp \
    languages.cpp \
    version.cpp \
    updatecheck.cpp \
    updatecheckdlg.cpp\
    socialshare.cpp \
    coverartdialog.cpp


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
    stereovinputdialog.h \
    languages.h \
    updatecheck.h \
    version.h \
    updatecheckdlg.h\
    socialshare.h \
    WinVersion.h \
    coverartdialog.h

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
    stereovinputdialog.ui \
    updatecheckdlg.ui\
    videodl/videodl.ui\
    videodl/supsitesdialog.ui \
    videodl/vdlsettingsdialog.ui
unix{
HEADERS += inhibitor.h
SOURCES += inhibitor.cpp
}
contains( DEFINES, TAGLIB ) {

win32 {
INCLUDEPATH +=taglib

LIBS += $$PWD/taglib/lib/libtag.a

HEADERS += qcoverart.h
SOURCES += qcoverart.cpp
}

}

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
