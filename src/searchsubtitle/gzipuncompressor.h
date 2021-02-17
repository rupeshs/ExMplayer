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

/*
   Based on the Qt network/http example
   Data decompression is done using miniz library
   https://code.google.com/p/miniz/

*/

#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QtWidgets>
#include <QProgressDialog>
#include <QByteArray>

#ifndef TINFL_HEADER_FILE_ONLY
#define TINFL_HEADER_FILE_ONLY
#endif // TINFL_HEADER_FILE_ONLY

#include <stdexcept>
extern "C" {
#include <tinfl.c>

}

QT_BEGIN_NAMESPACE
class QFile;
class QProgressDialog;
class QPushButton;
class QSslError;
class QNetworkReply;
QT_END_NAMESPACE

class GzipUncompressor : public QProgressDialog
{
    Q_OBJECT

public:
    GzipUncompressor(QWidget *parent = 0);

    //Download and uncompress a single file
    void downloadAndUncompress(QUrl url,QString destPath);


private slots:
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
    void cancelDownload();
    bool gzUncompress(QByteArray const& data);

#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
#endif
signals:
    void uncompressFinished();
private:
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    int httpGetId;
    bool httpRequestAborted;
    QByteArray gzFileData;
    QString savePath;

};

#endif
