/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2014 Rupesh Sreeraman

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

#include "updatecheck.h"

UpdateCheck::UpdateCheck(QObject *parent) :
    QObject(parent)
{

    manager= new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileIsReady(QNetworkReply*)) );

}
void UpdateCheck::fileIsReady( QNetworkReply * reply)
{

    reply->deleteLater();

    if(reply->error() == QNetworkReply::NoError) {
        // Get the http status code
        int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        // Here we got the final reply
        QByteArray replyXml = reply->readAll();
        qDebug()<<replyXml;

        QXmlStreamReader reader(replyXml);
        QString os;
        QString version;
        while (!reader.atEnd()) {

            reader.readNext();
            if (reader.isStartElement()) {
                if (reader.name() == "OperatingSystem")
                {
                    os=reader.readElementText();
                    //qDebug()<<p;
                }
                if (reader.name() == "StableVersion")
                {
                    version=reader.readElementText();

                }
                if (reader.name() == "ReleaseNotes")
                {
                    QString relNotes=reader.readElementText();
                    QStringList vList;
                    vList.append(version);
                    vList.append(relNotes);
                    mapVersions.insert(os,vList);
                }
            }

        }
    }
    else
    {
        // Error
        qDebug()<<reply->errorString();
        if (reply->errorString()=="Host  not found")
            emit NetworkError("Host  not found");


    }

    reply->manager()->deleteLater();


#ifdef Q_OS_WIN
    QString latestVersion;
    QString myVersion=Version::stable();
    if (mapVersions["Windows"].count()>0)
        latestVersion= mapVersions["Windows"].at(0);
    bool bUpdateAvail=isUpdated(latestVersion,myVersion);
    if(mapVersions["Windows"].count()>1)
        emit gotUpdateChkResponse(bUpdateAvail,mapVersions["Windows"].at(0),mapVersions["Windows"].at(1));

#endif
#ifdef Q_OS_LINUX
    QString latestVersion;
    QString myVersion=Version::stable();
    if (mapVersions["Linux"].count()>0)
        latestVersion= mapVersions["Linux"].at(0);
    bool bUpdateAvail=isUpdated(latestVersion,myVersion);

    if(mapVersions["Linux"].count()>1)
        emit gotUpdateChkResponse(bUpdateAvail,mapVersions["Linux"].at(0),mapVersions["Linux"].at(1));

# endif

    if( bUpdateAvail)
            _stableVersion=latestVersion;

}
void UpdateCheck::Check()
{

    QNetworkRequest request(QUrl("http://exmplayer.sourceforge.net/update.xml"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 Gecko/20100101 Firefox/18.0");
    manager->get(request);
}
bool UpdateCheck::isUpdated(QString currentVersion,QString myVersion)
{

    QStringList cVl=  currentVersion.split(".");
    QStringList myVl=  myVersion.split(".");

    if (cVl.count()==3 && myVl.count()==3)
    {
        if(cVl.at(0).toInt()>myVl.at(0).toInt())
        { //Major update found
            return true;
        }
        else if (cVl.at(1).toInt()>myVl.at(1).toInt())
        { //Minor update found
            return true;
        }
        else if (cVl.at(2).toInt()>myVl.at(2).toInt())
        {//Revision update found
            return true;
        }


    }

    return false;
}
