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
#include "searchsubtitle.h"
#include "ui_searchsubtitle.h"

SearchSubtitle::SearchSubtitle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchSubtitle)
{
    ui->setupUi(this);

    oSubClient=new OpenSubtitlesClient();
    QObject::connect(oSubClient,SIGNAL(readyForSearch()),this,SLOT(loginOkay()));

    oSubClient->login();
    QStringList labels;
    labels << tr("Language") << tr("Name") << tr("Download count") <<tr("Format")<< tr("Added Date")<<tr("Uploaded by")<<tr("Download link");

    table = new QStandardItemModel(this);
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels( labels );
    QObject::connect(oSubClient,SIGNAL(gotSubtitles(QVariantList)),this,SLOT(gotSubtitles(QVariantList)));
    QObject::connect(ui->comboLangFilter,SIGNAL(currentIndexChanged(QString)),this,SLOT(subLanguageChanged(QString)));
    QObject::connect(oSubClient,SIGNAL(NetworkError(QString)),this,SLOT(gotNetworkError(QString)));

    ui->tableSubtitles->setModel(table);

    proxy_model = new QSortFilterProxyModel(this);
    proxy_model->setSourceModel(table);
    proxy_model->setFilterKeyColumn(0);
    ui->tableSubtitles->setModel(proxy_model);
    ui->tableSubtitles->setSortingEnabled(true);
    ui->tableSubtitles->setAlternatingRowColors(true);
    ui->tableSubtitles->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableSubtitles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableSubtitles->setWordWrap(false);
    ui->tableSubtitles->resizeRowsToContents();
    ui->tableSubtitles->resizeColumnsToContents();

    pgIndicator=new QProgressIndicator(this);
    pgIndicator->setColor(QColor(qRgb(0,0,0) ));
    pgIndicator->show();
    ui->statusBar->addWidget(pgIndicator);
    ui->statusBar->showMessage("      Searching...");
    pgIndicator->startAnimation();
    ui->comboLangFilter->addItem("All");
    QStringList lstFilter=Languages::LangList().values();
    lstFilter.sort();
    ui->comboLangFilter->addItems( lstFilter);

    // Actions
    downloadAct = new QAction(this);
    downloadAct->setText("Download");
    connect( downloadAct, SIGNAL(triggered()), this, SLOT(on_pushButtonDwnld_clicked()) );

    copyLinkAct = new QAction(this);
    copyLinkAct->setText("Copy Link to clipboard");
    connect( copyLinkAct, SIGNAL(triggered()), this, SLOT(on_pushCopyLink_clicked()) );

    context_menu = new QMenu(this);
    context_menu->addAction(downloadAct);
    context_menu->addAction(copyLinkAct);

    disableUi();
}

SearchSubtitle::~SearchSubtitle()
{
    delete ui;
}
void SearchSubtitle::gotSubtitles(QVariantList data)
{

    /*From  http://trac.opensubtitles.org/projects/opensubtitles/wiki/XMLRPC#SearchSubtitles
                [0] => Array
                (
                    [MatchedBy] => moviehash
                    [IDSubMovieFile] => 865
                    [MovieHash] => d745cd88e9798509
                    [MovieByteSize] => 734058496
                    [MovieTimeMS] => 0
                    [IDSubtitleFile] => 1118
                    [SubFileName] => Al sur de Granada (SPA).srt
                    [SubActualCD] => 1
                    [SubSize] => 15019
                    [SubHash] => 0cb51bf4a5266a9aee42a2d8c7ab6793
                    [IDSubtitle] => 905
                    [UserID] => 0
                    [SubLanguageID] => spa
               ->   [SubFormat] => srt
                    [SubSumCD] => 1
                    [SubAuthorComment] =>
               ->   [SubAddDate] => 2005-06-15 20:05:35
                    [SubBad] => 1
                    [SubRating] => 4.5
               ->   [SubDownloadsCnt] => 216
                    [MovieReleaseName] => ss
                    [IDMovie] => 11517
                    [IDMovieImdb] => 349076
                    [MovieName] => Al sur de Granada
                    [MovieNameEng] => South from Granada
                    [MovieYear] => 2003
                    [MovieImdbRating] => 6.4
                    [SubFeatured] => 0
                    [UserNickName] =>
                    [ISO639] => es
             ->     [LanguageName] => Spanish
                    [SubComments] => 1
                    [SubHearingImpaired] => 0
                    [UserRank] =>
                    [SeriesSeason] =>
                    [SeriesEpisode] =>
                    [MovieKind] => movie
                    [QueryParameters] => Array
                        (
                            [sublanguageid] => all
                            [moviehash] => d745cd88e9798509
                            [moviebytesize] => 734058496
                        )

                    [QueryNumber] => 0
             ->     [SubDownloadLink] => http://dl.opensubtitles.org/en/download/filead/1118.gz
                    [ZipDownloadLink] => http://dl.opensubtitles.org/en/download/subad/905
                    [SubtitlesLink] => http://www.opensubtitles.org/en/subtitles/905/al-sur-de-granada-es
                )

      */
    enableUi();
    pgIndicator->hide();

    if(data.count()==0)
        ui->statusBar->showMessage(QString("%1 subtitles available.").arg(data.count()));
    else
        ui->statusBar->showMessage("Subtitles not available");

    for (int n = 0; n < data.count(); n++) {

        QVariantMap mResult = data[n].toMap();
        qDebug()<<mResult["SubDownloadLink"].toString()<<":"
                                                      <<mResult["SubFormat"].toString()<<":"
                                                      <<mResult["SubLanguageID"].toString()<<":"
                                                      <<mResult["SubDownloadsCnt"].toString();

        QString Lang=mResult["LanguageName"].toString();
        QStandardItem * itemLang = new QStandardItem(Lang);
        table->setItem(n,0,itemLang);

        QString MovieName=mResult["MovieName"].toString();
        QStandardItem *  itemMovieName = new QStandardItem(MovieName);
        table->setItem(n,1,itemMovieName);

        QString SubDownloadsCnt=mResult["SubDownloadsCnt"].toString();
        QStandardItem *  itemDownloadsCnt = new QStandardItem(SubDownloadsCnt);
        table->setItem(n,2,itemDownloadsCnt);

        QString SubFormat=mResult["SubFormat"].toString();
        QStandardItem *  itemSubFormat = new QStandardItem(SubFormat);
        table->setItem(n,3,itemSubFormat );

        QString SubAddDate=mResult["SubAddDate"].toString();
        QStandardItem *  itemSubAddDate = new QStandardItem(SubAddDate);
        table->setItem(n,4,itemSubAddDate );

        QString SubUserNickName=mResult["UserNickName"].toString();
        QStandardItem *  itemUserNickName = new QStandardItem(SubUserNickName);
        table->setItem(n,5,itemUserNickName );

        QString SubDownloadLink=mResult["SubDownloadLink"].toString();
        QStandardItem *  itemSubDownloadLink = new QStandardItem(SubDownloadLink);
        table->setItem(n,6,itemSubDownloadLink );
    }

    filterSubtitles(ui->comboLangFilter->currentText());
    subLanguageChanged(ui->comboLangFilter->currentText());
    ui->tableSubtitles->resizeRowsToContents();
    ui->tableSubtitles->resizeColumnsToContents();
}

void SearchSubtitle::on_comboLangFilter_currentIndexChanged(const QString &arg1)
{
    filterSubtitles(arg1);
}
void SearchSubtitle::filterSubtitles(QString filter)
{
    if( filter=="All")
        proxy_model->setFilterWildcard("*");
    else
        proxy_model->setFilterWildcard(filter);
    ui->tableSubtitles->resizeRowsToContents();
    proxy_model->sort(0, Qt::AscendingOrder);

}
void SearchSubtitle::subLanguageChanged(QString ln)
{
    if (ui->statusBar->currentMessage()!="      Searching...")
    {
        if (pgIndicator->isVisible())
            ui->statusBar->showMessage(QString("      Found %1 subtitles.").arg(ui->tableSubtitles->model()->rowCount()));
        else
            ui->statusBar->showMessage(QString("%1 subtitle(s) available.").arg(ui->tableSubtitles->model()->rowCount()));
        if (ui->tableSubtitles->model()->rowCount()==0)
            ui->statusBar->showMessage("Subtitles not available");
    }
}

void SearchSubtitle::on_toolButtonSearch_clicked()
{
    if (ui->lineEditSeachFilm->text()=="")
    {
        ui->statusBar->showMessage(QString("Oops...Enter a movie name."));
        return;
    }
    table->clear();
    QStringList labels;
    labels << tr("Language") << tr("Name") << tr("Download count") <<tr("Format")<< tr("Added Date")<<tr("Uploaded by")<<tr("Download link");
    table->setHorizontalHeaderLabels( labels );

    ui->statusBar->addWidget(pgIndicator);

    ui->statusBar->showMessage("      Searching...");
    pgIndicator->startAnimation();
    pgIndicator->show();
    oSubClient->search(ui->lineEditSeachFilm->text(),OpenSubtitlesClient::QUERY);
    _filePath="";
    disableUi();

}
void SearchSubtitle::disableUi()
{
    ui->toolButtonSearch->setEnabled(false);
    ui->lineEditSeachFilm->setEnabled(false);
    ui->comboLangFilter->setEnabled(false);
    ui->pushButtonDwnld->setEnabled(false);
    ui->pushCopyLink->setEnabled(false);
    copyLinkAct->setEnabled(false);
    downloadAct->setEnabled(false);
}

void SearchSubtitle::enableUi()
{
    ui->toolButtonSearch->setEnabled(true);
    ui->lineEditSeachFilm->setEnabled(true);
    ui->comboLangFilter->setEnabled(true);
    ui->pushButtonDwnld->setEnabled(true);
    ui->pushCopyLink->setEnabled(true);
    copyLinkAct->setEnabled(true);
    downloadAct->setEnabled(true);
}

void SearchSubtitle::on_lineEditSeachFilm_returnPressed()
{
    on_toolButtonSearch_clicked();
}
void SearchSubtitle::gotNetworkError(QString err)
{

    pgIndicator->startAnimation();
    ui->statusBar->showMessage(err);
}

void SearchSubtitle::on_tableSubtitles_clicked(const QModelIndex &index)
{
    QString download_link = ui->tableSubtitles->model()->index(index.row(),5).data().toString();

    qDebug()<<download_link;
}

void SearchSubtitle::on_pushCopyLink_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QModelIndexList selectedRows =ui->tableSubtitles->selectionModel()->selectedRows();
    QString originalText;
    foreach( QModelIndex index, selectedRows )
    {

        originalText = ui->tableSubtitles->model()->index(index.row(),6).data().toString();;

    }
    clipboard->setText(originalText);
}

void SearchSubtitle::on_pushButtonDwnld_clicked()
{
    bool isQury=false;
    if (!ui->lineEditSeachFilm->text().contains("."))
    {
        isQury=true;
    }
    QModelIndexList selectedRows =ui->tableSubtitles->selectionModel()->selectedRows();
    if(selectedRows.count()==0)
    {
        QMessageBox::information(this,"ExMplayer","Please select a subtitle to download.   ");
    }
    else
    {   if (_filePath=="")
        {
            isQury=true;
            QString dir = rphFile::getDir(this,"Open a Directory for output:","");

            if (!dir.isEmpty())
            {
                _filePath=dir;
            }
            else
                return;
        }
        QString subUrl;
        QString subName;
        QString subFormat;
        QString subLanguage;
        foreach( QModelIndex index, selectedRows )
        {
            subUrl = ui->tableSubtitles->model()->index(index.row(),6).data().toString();
            if (isQury)
                subName =ui->tableSubtitles->model()->index(index.row(),1).data().toString();

            subFormat = ui->tableSubtitles->model()->index(index.row(),3).data().toString();
            subLanguage= ui->tableSubtitles->model()->index(index.row(),0).data().toString();;
        }
        QFileInfo fInfo(_filePath);
        QString fileName;
        if (!isQury)
        {
            subName =fInfo.completeBaseName();
            fileName=QFileInfo(_filePath).canonicalPath()+ QString(QDir::separator())+ subName+"_"+Languages::LangList().key(subLanguage)+"."+subFormat;

        }
        else
        {
            fileName=_filePath+subName+"_"+Languages::LangList().key(subLanguage)+"."+subFormat;
            //_filePath=="";
        }
        qDebug()<<QFile::exists(fileName);
        _subfileName=fileName;

        gzDownloader=new GzipUncompressor(this);
        QObject::connect(gzDownloader,SIGNAL(uncompressFinished()),this,SLOT(downloadComplete()));
        gzDownloader->downloadAndUncompress(QUrl(subUrl),fileName);
        gzDownloader->show();
    }

}
void SearchSubtitle::on_tableSubtitles_customContextMenuRequested(const QPoint &pos)
{
    context_menu->move( ui->tableSubtitles->viewport()->mapToGlobal(pos) );
    context_menu->show();
}

void SearchSubtitle::on_pushButtonUploadSub_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.opensubtitles.org/upload"));
}

void SearchSubtitle::loginOkay()
{
    emit readyForSubSearch();
}

void  SearchSubtitle::searchSubtitleForMovie(const QString& filename)
{
    oSubClient->search(filename,OpenSubtitlesClient::FILEHASH);
    _filePath=filename;
    qDebug()<<QFileInfo(_filePath).canonicalPath();
    ui->lineEditSeachFilm->setText(QFileInfo(_filePath).fileName());

}

void SearchSubtitle::downloadComplete()
{
    emit loadSubtitle(_subfileName);
}
