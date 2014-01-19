/*
    exmplayer, GUI front-end for mplayer.
    Copyright (C) 2011-2013 Rupesh Sreeraman

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
#include "opensubtitleclient.h"

OpenSubtitlesClient::OpenSubtitlesClient(QObject *parent) :
    QObject(parent)
{
    rpc = new MaiaXmlRpcClient(QUrl("http://api.opensubtitles.org/xml-rpc"), this);

    QSslConfiguration config = rpc->sslConfiguration();
    config.setProtocol(QSsl::AnyProtocol);
    rpc->setSslConfiguration(config);

    connect(rpc, SIGNAL(sslErrors(QNetworkReply *, const QList<QSslError> &)),
            this, SLOT(handleSslErrors(QNetworkReply *, const QList<QSslError> &)));


}
OpenSubtitlesClient::~OpenSubtitlesClient()
{
    logout();
}

void OpenSubtitlesClient::login()
{
    QVariantList args;
    args << "" << "" << "" << "ExMplayer";

    rpc->call("LogIn", args,
              this, SLOT(handleLogin(QVariant &)),
              this, SLOT(handleError(int, const QString &)));
}
void OpenSubtitlesClient::logout()
{
    QVariantList args;
    args << token ;

    rpc->call("LogOut", args,
              this, SLOT(handleLogin(QVariant &)),
              this, SLOT(handleError(int, const QString &)));
}

void OpenSubtitlesClient::handleLogin(QVariant& result)
{
    QVariantMap resultMap = result.toMap();

    if (resultMap["status"].toString() == QLatin1String("200 OK")) {
        token = resultMap["token"].toString();
        qDebug()<<"Login succesful"<<resultMap["status"].toString();
        emit readyForSearch();
        // XXX
        //search("F:/films/Despicable Me 2 (2013)/Despicable.Me.2.2013.720p.BluRay.x264.YIFY.mp4",FILEHASH);
    }
}
void OpenSubtitlesClient::handleError(int error, const QString& message)
{
    qDebug() << error << "-" << message;
    if (message.contains("not found"))
      {

        emit NetworkError("No network,please check your network connection");
      }
     else
        emit NetworkError(message);

}

void OpenSubtitlesClient::handleSslErrors(QNetworkReply *reply, const QList<QSslError>& errors)
{
    qDebug() << "SSL Error:" << errors;
    reply->ignoreSslErrors(); //Fix me
}
void OpenSubtitlesClient::search(const QString& filename,SearchMode mode)
{
    QVariantList args;
    QVariantMap params;
    QVariantMap data;

    data["token"] = token;
    if (mode==FILEHASH)
    {
        QString hash = QString::number(computeHash(filename), 16);
        qDebug()<<"Filehash :"<< hash;
        QFile file(filename);
        file.open(QFile::ReadOnly);
        data["moviehash"] =  hash;
        data["moviebytesize"] = QString::number(file.size());
    }
    else
    {
        data["query"]=filename;
    }
    params[""] = data;

    args << token << params;

    rpc->call("SearchSubtitles", args,
              this, SLOT(handleResponse(QVariant &)),
              this, SLOT(handleError(int, const QString &)));
}

uint64_t OpenSubtitlesClient::computeHash(const QString& filename)
{
    // http://trac.opensubtitles.org/projects/opensubtitles/wiki/HashSourceCodes
    FILE* handle = fopen(filename.toLocal8Bit(), "rb");

    if (!handle) {
        return -1;
    }

    uint64_t hash, size;

    fseek(handle, 0, SEEK_END);
    hash = size = ftell(handle);
    fseek(handle, 0, SEEK_SET);

    for(uint64_t tmp = 0, i = 0; i < 65536/sizeof(tmp) && fread((char*)&tmp, sizeof(tmp), 1, handle); hash += tmp, i++);
    fseek(handle, std::max((uint64_t)0, size - 65536), SEEK_SET);
    for(uint64_t tmp = 0, i = 0; i < 65536/sizeof(tmp) && fread((char*)&tmp, sizeof(tmp), 1, handle); hash += tmp, i++);
    fclose(handle);

    return hash;
}

void OpenSubtitlesClient::handleResponse(QVariant& result)
{
    QVariantMap mapResponse = result.toMap();
    QString status = mapResponse["status"].toString();

    if (status != "200 OK") {
        qDebug()<<"Search Failed!";
        emit NetworkError("Search Failed!");
        return;
    }
    QVariantList data = mapResponse["data"].toList();
    emit gotSubtitles(data);
    qDebug("Result count: %d", data.count());

    for (int n = 0; n < data.count(); n++) {
        QVariantMap mResult = data[n].toMap();
        /* qDebug()<<mResult["SubDownloadLink"].toString()<<":"
                 <<mResult["SubFormat"].toString()<<":"
                <<mResult["SubLanguageID"].toString()<<":"
                <<mResult["SubDownloadsCnt"].toString();*/



    }

}
