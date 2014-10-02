/*
    exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2014 Rupesh Sreeraman <exmplayer.dev@gmail.com>

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

#include "inhibitor.h"

Inhibitor::Inhibitor()
{

    //Init service variables
    serviceLst.append("org.gnome.SessionManager");
    serviceLst.append("org.freedesktop.ScreenSaver");
    serviceLst.append("org.mate.SessionManager");

    servicePathLst.append("/org/gnome/SessionManager");
    servicePathLst.append("/ScreenSaver");
    servicePathLst.append("/org/mate/SessionManager");

    serviceInterfaceLst.append("org.gnome.SessionManager");
    serviceInterfaceLst.append("org.freedesktop.ScreenSaver");
    serviceInterfaceLst.append("org.mate.SessionManager");

    _inhibitCookie=0;
    _systemType=-1;//We don't know current system
    _dpmsEnabled=checkDpms();
    _screenSvrEnabled=checkScreenSvr();;
    dectectSystem();

}
void Inhibitor::dectectSystem()
{

    QStringList servicsLst= QDBusConnection::sessionBus().interface()->registeredServiceNames().value();

    //Check for Gnome
    int pos=servicsLst.indexOf("org.gnome.SessionManager");
    int pid=checkProcess("gnome-screensaver");
    if (pos>-1 && pid>-1)
    {
        qDebug()<<"GNOME detected";
        _systemType=GNOME;
        return;
    }

    //Check for KDE

    pos=servicsLst.indexOf("org.freedesktop.ScreenSaver");
    int ppos=servicsLst.indexOf("org.freedesktop.PowerManagement.Inhibit");
    if (pos>-1 && ppos>-1)
    {
        qDebug()<<"KDE detected";
        _systemType=KDE;
        return;
    }


    //Check for MATE
    pos=servicsLst.indexOf("org.mate.SessionManager");

    if (pos>-1 )
    {
        qDebug()<<"MATE detected";
        _systemType=MATE;
        return;
    }




}
//CheckProcess returns processid
int Inhibitor::checkProcess(const char* name)
{
    QProcess p;
    QString cmd="pidof -x ";

    p.start(cmd+QString::fromAscii(name));
    p.waitForFinished(1000);
    QString p_stdout = p.readAllStandardOutput();
    int pid=p_stdout.toInt();
    if(pid>0)
        return pid;
    else
        return -1;

}

//Check if DMPS is enabled
bool Inhibitor::checkDpms()
{
    QProcess p;
    p.start("xset q");
    p.waitForFinished(1000);
    QString p_stdout = p.readAllStandardOutput().simplified();
    if ( p_stdout.contains("DPMS is Enabled", Qt::CaseInsensitive) )
        return true;
    else
        return false;
}

//Check if screensaver is enabled
bool Inhibitor::checkScreenSvr()
{
    QProcess p;
    p.start("xset q");
    p.waitForFinished(1000);
    QString p_stdout = p.readAllStandardOutput().simplified();
    if ( p_stdout.contains("timeout: 0", Qt::CaseInsensitive) )
        return false;
    else
        return true;
}

//This will disable screensaver/powersaving
bool Inhibitor::activateInhibit()
{
    if (_systemType!=KDE) //Fix me KDE avoid segmentation fault
    {
        qDebug()<<"System Type" <<QString::number(_systemType);
        if (  _systemType>-1&& _systemType<serviceInterfaceLst.count())
        {
            system("xset -dpms");
            system("xset s off");

            QDBusConnection bus = QDBusConnection::sessionBus();

            interfaceScreenSvr= new QDBusInterface(serviceLst.at(_systemType),
                                                   servicePathLst.at(_systemType),
                                                   serviceInterfaceLst.at(_systemType),
                                                   bus,
                                                   0);

            QList<QVariant> args;
            uint inhibitCookie;
            args.append("ExMplayer");
            args.append((uint)0);
            args.append("Playing a media file");
            args.append((uint)8|4);

            if(interfaceScreenSvr)
            {
                QDBusReply<uint> reply = interfaceScreenSvr->callWithArgumentList(QDBus::BlockWithGui	,"Inhibit", args);

                if (reply.isValid())

                {
                    _inhibitCookie=reply.value();
                    qDebug()<<"Inhibit :OK "<<QString::number(_inhibitCookie);
                    return true;

                }
                else
                    qDebug()<< reply.error();
            }
        }

    }


    return false;
}

//This will enable screensaver/powersaving
bool  Inhibitor::deactivateInhibit()
{


    if (_systemType>-1&& _systemType<serviceInterfaceLst.count())
    {
        if ( _dpmsEnabled )
            system("xset +dpms");
        if ( _screenSvrEnabled )
            system("xset s on");

        QList<QVariant> args;
        args.append((uint)8|4);
        if(interfaceScreenSvr)
        {

            QDBusReply<bool> re = interfaceScreenSvr->callWithArgumentList(QDBus::BlockWithGui	,"IsInhibited", args);

            if(re)
            {
                qDebug()<<"Uninhibiting...";
                args.clear();
                args.append((uint)_inhibitCookie);
                interfaceScreenSvr->callWithArgumentList(QDBus::BlockWithGui	,"Uninhibit", args);

                QDBusReply<bool> re = interfaceScreenSvr->callWithArgumentList(QDBus::BlockWithGui	,"IsInhibited", args);

                qDebug()<< re;

                return true;

            }
        }
    }
    return false;
}
