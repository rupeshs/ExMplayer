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
#include "paths.h"
#include <QLibraryInfo>
#include <QLocale>
#include <QFile>
#include <QRegExp>
#include <QDir>
#include <stdlib.h>
#include <QApplication>

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
