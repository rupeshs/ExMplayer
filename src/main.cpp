/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2013 Rupesh Sreeraman

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
#include <QtGui/QApplication>
#include <QtCore>
#include "playerwindow.h"
#include "qtsingleapplication.h"


void crashingMessageHandler(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg);
        __asm("int3");
        abort();
    }
}

int main(int argc, char *argv[])
{
#ifdef Q_OS_LINUX
    qInstallMsgHandler(crashingMessageHandler);
#endif
    QtSingleApplication instance(argc, argv);
    if(instance.isRunning())
    {
        QString cmd;
        if (qApp->arguments().count()>1)
        {
            cmd=qApp->arguments().at(1);

            if (!cmd.isEmpty()){
                if(cmd.contains("add-to-playlist",Qt::CaseInsensitive))
                    cmd="add-to-playlist"+qApp->arguments().at(2);
            }
            instance.sendMessage(cmd);
        }

        return 0;
    }
    QApplication::setApplicationName("ExMplayer");
    PlayerWindow w;
    instance.setActivationWindow(&w,true);
    QObject::connect(&instance, SIGNAL(messageReceived(const QString&)),
                     &w, SLOT(getMessage(QString)));
    w.show();

    return qApp->exec();


}
