/*
    exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2021 Rupesh Sreeraman

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
#ifndef OPENSUBTITLECLIENT_H
#define OPENSUBTITLECLIENT_H

#include <QObject>
#include <QVariantList>
#include <QVariant>
#include <QNetworkReply>
#include "maiaXmlRpcClient.h"
#include <QList>
#include <QString>
#include <QSslConfiguration>
#include <QDebug>
#ifdef Q_OS_UNIX
#include <inttypes.h>
#endif
#if defined(Q_OS_WIN) || defined(Q_OS_OS2)
 typedef unsigned __int64 uint64_t;
#endif

class OpenSubtitlesClient : public QObject
{
    Q_OBJECT
public:
    explicit OpenSubtitlesClient(QObject *parent = 0);
    ~OpenSubtitlesClient();
    enum SearchMode{
        FILEHASH=0,
        QUERY
       };
signals:
    void gotSubtitles(QVariantList data);
    void NetworkError(QString);
    void readyForSearch();
    
public slots:
    void login();
    void logout();
    void search(const QString& filename,SearchMode mode);

private slots:
    void handleResponse(QVariant &);
    void handleLogin(QVariant& result);
    void handleError(int error, const QString &message);
    void handleSslErrors(QNetworkReply *, const QList<QSslError> &);
protected:
    uint64_t computeHash(const QString& filename);

private:
    MaiaXmlRpcClient *rpc;
    QString token;

};

#endif // OPENSUBTITLECLIENT_H
