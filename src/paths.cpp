#include "paths.h"
#include <QLibraryInfo>
#include <QLocale>
#include <QFile>
#include <QRegExp>
#include <QDir>
#include <stdlib.h>
Paths::Paths()
{
}
QString Paths::configPath()
{

#ifdef Q_OS_WIN
    return qApp->applicationDirPath();
#else

#if !defined(Q_OS_WIN) && !defined(Q_OS_OS2)
    const char * XDG_CONFIG_HOME = getenv("XDG_CONFIG_HOME");
    if (XDG_CONFIG_HOME!=NULL) {
        /* qDebug("Paths::configPath: XDG_CONFIG_HOME: %s", XDG_CONFIG_HOME); */
        return QString(XDG_CONFIG_HOME) + "/exmplayer";
    }
    else
        return QDir::homePath() + "/.config/exmplayer";
#else
    return QDir::homePath() + "/.exmplayer";
#endif
#endif
}
QString Paths::sharePath()
 {
#ifdef Q_OS_WIN
    return qApp->applicationDirPath();
#endif

#ifdef Q_OS_LINUX
    return  QString("/usr/share/exmplayer");

#endif

 }

QString Paths::getStaticConfigPath()
{

#ifdef Q_OS_WIN
    return qApp->applicationDirPath();
#endif

#ifdef Q_OS_LINUX
    return  QString("/etc/exmplayer");

#endif
}
