/*  umplayer, GUI front-end for mplayer.
    Copyright (C) 2010 Ori Rejwan

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

#include "scdataapi.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDomElement>
#include <QUrl>

SCDataAPI::SCDataAPI(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotReply(QNetworkReply*)));
}

void SCDataAPI::getTop500()
{
    QNetworkRequest req(QString("http://api.shoutcast.com/legacy/Top500?k=sh1N7oyXzUvT8TRK"));
    manager->get(req);
}

void SCDataAPI::getSearchResult(QString searchTerm)
{
    QByteArray term = searchTerm.toUtf8();
    QNetworkRequest req("http://api.shoutcast.com/legacy/stationsearch?k=sh1N7oyXzUvT8TRK&search=" + QString::fromUtf8(term.toPercentEncoding().constData()));
    manager->get(req);
}

void SCDataAPI::reset()
{
    manager->deleteLater();
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotReply(QNetworkReply*)));
}

void SCDataAPI::gotReply(QNetworkReply *reply)
{
    SCReply formattedReply;
    if(reply->error() != QNetworkReply::NoError)
    {
        formattedReply.errorString = reply->errorString();
    }
    QByteArray xml = reply->readAll();
    parseXMLReply(xml, formattedReply);
    emit finalResult(formattedReply);
}

void SCDataAPI::parseXMLReply(QString xml, SCReply &formattedReply)
{
    QDomDocument doc;
    doc.setContent(xml, false);
    QDomNodeList stationNodeList = doc.elementsByTagName("station");
    formattedReply.totalResultCount = stationNodeList.count();
    for(int i=0; i < stationNodeList.count(); ++i)
    {
        QDomElement station = stationNodeList.at(i).toElement();
        SingleSCResult ssr;
        ssr.name = station.attribute("name");
        QString mime = station.attribute("mt");
        if(mime.contains("mpeg"))
            ssr.format = "mp3";
        else if(mime.contains("aacp"))
            ssr.format = "aacp";
        ssr.id = station.attribute("id");
        ssr.bitrate = station.attribute("br");
        ssr.genre = station.attribute("genre");
        ssr.song = station.attribute("ct");
        ssr.listeners = station.attribute("lc");
        formattedReply.results.append(ssr);
    }    
}


QString SCDataAPI::unescape(QString html)
{
    html.replace("&amp;", "&");
    html.replace("&lt;", "<");
    return html.replace("&gt;", ">");
}
