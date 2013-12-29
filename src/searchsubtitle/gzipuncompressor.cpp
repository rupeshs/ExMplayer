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

/*
   Based on the Qt network/http example
   Data decompression is done using miniz library
   https://code.google.com/p/miniz/

*/

#include <QtNetwork>
#include <stdlib.h>
#include "gzipuncompressor.h"
#include <QDebug>

GzipUncompressor::GzipUncompressor(QWidget *parent)
    : QProgressDialog(parent)
{

#ifndef QT_NO_SSL
    connect(&qnam, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
#endif
    connect(this, SIGNAL(canceled()), this, SLOT(cancelDownload()));
    setWindowTitle(tr("Subtitle downloader"));
    setLabelText("Downloading...");

}

void GzipUncompressor::downloadAndUncompress(QUrl url,QString destPath)
{
    gzFileData.clear();
    savePath=destPath;
    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();

    setWindowTitle(tr("Subtitle downloader"));
    setLabelText(tr("Downloading %1.").arg(fileName));
    // schedule the request
    httpRequestAborted = false;

    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));

}

void GzipUncompressor::httpFinished()
{
    if (httpRequestAborted) {
        reply->deleteLater();
        return;
    }
   if (reply->error()) {
       QMessageBox::critical(this, tr("Download Error"),
                                 tr("Download failed: %1.")
                                 .arg(reply->errorString()));
    this->close();
   }
    reply->deleteLater();
    reply = 0;
    //Uncompress file
    if (gzFileData.size()>0)
       if(!gzUncompress(gzFileData))
       {
           QMessageBox::critical(this, tr("Error"),
                               tr("Error while uncompressing"));

       }


}

void GzipUncompressor::httpReadyRead()
{
    // We read all of its new data and write it into the file.
    QByteArray ba=reply->readAll();
    /*if (file)
        file->write(ba);*/
    gzFileData.append(ba);
    qDebug("%d",gzFileData.size());

}

void GzipUncompressor::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    if (httpRequestAborted)
        return;

    setMaximum(totalBytes);
    setValue(bytesRead);
    qDebug("%ld %ld",bytesRead,totalBytes);
}



#ifndef QT_NO_SSL
void GzipUncompressor::sslErrors(QNetworkReply*,const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += ", ";
        errorString += error.errorString();
    }
    
    if (QMessageBox::warning(this, tr("ExMplayer"),
                             tr("One or more SSL errors has occurred: %1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        reply->ignoreSslErrors();
    }
}
#endif

//Gzip uncompressor
bool GzipUncompressor::gzUncompress(QByteArray const& data)
{
  setLabelText("Uncompressing...");
  static tinfl_decompressor inflator;
  static QByteArray result(TINFL_LZ_DICT_SIZE, 0);
  mz_uint8 const* inPtr(reinterpret_cast<mz_uint8 const*>(data.data()) + 10);

  tinfl_init(&inflator);

  size_t inAvail(data.size());
  size_t outTotal(0);

  tinfl_status ret;

  do
  {
     if (httpRequestAborted)
          return false;
    size_t inSize(inAvail);
    size_t outSize(result.size() - outTotal);

    ret = tinfl_decompress(&inflator,
      inPtr,
      &inSize,
      reinterpret_cast<mz_uint8*>(result.data()),
      reinterpret_cast<mz_uint8*>(result.data()) + outTotal,
      &outSize,
      0
      );

    switch (ret)
    {
      case TINFL_STATUS_HAS_MORE_OUTPUT:
        inAvail -= inSize;
        inPtr += inSize;

        result.resize(2 * result.size());


      case TINFL_STATUS_DONE:
        outTotal += outSize;
        break;

      default:
        throw std::runtime_error("error decompressing gzipped content");
    }
  }
  while (TINFL_STATUS_DONE != ret);
  QFile sfile(savePath);
  if (!sfile.open(QIODevice::WriteOnly) )
  {qDebug("File open error");
  }
  sfile.write(result.data());
  sfile.close();
  emit uncompressFinished();
  return true;
}
void GzipUncompressor::cancelDownload()
{
    httpRequestAborted = true;
    reply->abort();
}
