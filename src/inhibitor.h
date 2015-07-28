/*
    exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2015 Rupesh Sreeraman <exmplayer.dev@gmail.com>

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

 /*
 * Based on freedesktop Power Management Specification
 * https://people.gnome.org/~mccann/gnome-session/docs/gnome-session.html#id344989
 */
#ifndef INHIBITOR_H
#define INHIBITOR_H
#include <QStringList>
#include <QtDBus>
#include <QProcess>


class Inhibitor:public QObject
{
    enum ExmInhibit
    {
        GNOME, /**< GNOME 2.26..3.4 */
        KDE,   /**< KDE >= 4 and GNOME >= 3.6 */
        MATE   /**< >= 1.0 */
    };

public:
    Inhibitor();
    bool activateInhibit();
    bool deactivateInhibit();

 private:

    int _systemType;
    bool _dpmsEnabled;
    bool _screenSvrEnabled;
    uint _inhibitCookie;
     QPointer<QDBusInterface> interfaceScreenSvr;

    QStringList serviceLst;
    QStringList servicePathLst;
    QStringList serviceInterfaceLst;

    void dectectSystem();
    int checkProcess(const char* name);
    bool checkDpms();
    bool checkScreenSvr();

};

#endif // INHIBITOR_H
