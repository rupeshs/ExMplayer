#-------------------------------------------------
#
# Project created by QtCreator 2013-12-08T10:45:25
#
#-------------------------------------------------

QT       += core gui network xml

TARGET = SearchSubtitle
TEMPLATE = app


SOURCES += main.cpp\
        searchsubtitle.cpp \
    opensubtitleclient.cpp \
    QProgressIndicator.cpp \
    languages.cpp \
    gzipuncompressor.cpp \
    tinfl.c

HEADERS  += searchsubtitle.h \
    opensubtitleclient.h \
    QProgressIndicator.h \
    languages.h \
    gzipuncompressor.h

INCLUDEPATH += miniz
DEPENDPATH += miniz
SOURCES += miniz.c tinfl.c

FORMS    += searchsubtitle.ui
# libMaia
include(maia/maia.pri)

