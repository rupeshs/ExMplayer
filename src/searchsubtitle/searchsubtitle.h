#ifndef SEARCHSUBTITLE_H
#define SEARCHSUBTITLE_H
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

#include <QMainWindow>
#include <opensubtitleclient.h>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QProgressIndicator.h>
#include <languages.h>
#include <QClipboard>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <gzipuncompressor.h>
#include <QDesktopServices>

namespace Ui {
class SearchSubtitle;
}

class SearchSubtitle : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SearchSubtitle(QWidget *parent = 0);
    ~SearchSubtitle();
protected:
    QStandardItemModel * table;

    QSortFilterProxyModel * proxy_model;
public slots:
     void gotSubtitles(QVariantList data);
     void filterSubtitles(QString filter);
     void subLanguageChanged(QString ln);
     void disableUi();
     void enableUi();



private slots:
     void on_comboLangFilter_currentIndexChanged(const QString &arg1);

     void on_toolButtonSearch_clicked();

     void on_lineEditSeachFilm_returnPressed();
     void gotNetworkError(QString);

     void on_tableSubtitles_clicked(const QModelIndex &index);

     void on_pushCopyLink_clicked();

     void on_pushButtonDwnld_clicked();

     void on_tableSubtitles_customContextMenuRequested(const QPoint &pos);

     void on_pushButtonUploadSub_clicked();

private:
    Ui::SearchSubtitle *ui;
    OpenSubtitlesClient *oSubClient;
    QProgressIndicator *pgIndicator;
    QMenu * context_menu;
    QAction * downloadAct;
    QAction * copyLinkAct;
    GzipUncompressor *gzDownloader;

};

#endif // SEARCHSUBTITLE_H
