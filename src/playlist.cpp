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
#include "playlist.h"
#include "QtCore"
#include "QDir"
#include "QProgressDialog"
#include "QSettings"
#include "QTime"
#include <QMessageBox>
#include <QTableWidgetItem>
playList::playList(QObject *parent) :
    QObject(parent)
{

    _bloop=false;
    _bshuffle=false;
    tab=new QTableWidget();
    tab->setColumnCount(4);
    tab->setAcceptDrops(true);
    QStringList headerLabels;
    headerLabels << "Title" << "Duration"<<"";
    tab->setHorizontalHeaderLabels(headerLabels);
    tab->setSelectionBehavior(QAbstractItemView::SelectRows);
    tab->setColumnWidth(0,170);
    //tab->setDragEnabled(true);
    tab->setDropIndicatorShown(true);
    //tab->viewport()->setAcceptDrops(true);
    tab->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QObject::connect(tab,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));
    currentIndex=-2;
    tab->setColumnWidth(2,0);
    tab->setColumnWidth(3,0);
}
void playList::addFile(QString path)
{
    path=path.replace("\\","/");

    if (path.contains("m3u"))
    {
        this->loadM3u(path);
    }
    else if(path.contains("pls"))
    {
        this->loadPls(path);
    }
    else
    {

        tab->setRowCount(tab->rowCount()+1);
        QTableWidgetItem *newItem = new QTableWidgetItem(QIcon(""),path.right(path.length()-path.lastIndexOf("/")-1));
        tab->setItem(tab->rowCount()-1, 0, newItem);
        QTableWidgetItem *newItem1 = new QTableWidgetItem("--:--:--");
        tab->setItem(tab->rowCount()-1, 1, newItem1);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(path);
        tab->setItem(tab->rowCount()-1, 2, newItem2);
        tab->setColumnWidth(2,0);
        tab->setColumnWidth(3,0);
        emit addingfilesg();
        tab->setRowHeight(tab->rowCount()-1,20);
        if(currentIndex==-2)
            currentIndex=-1;
    }
}
void playList::clearList()
{
    currentIndex=-2;
    tab->setRowCount(0);
    tab->clear();
    QStringList headerLabels;
    headerLabels << "Title" << "Duration"<<"";
    tab->setHorizontalHeaderLabels(headerLabels);
    emit clearingList();

}
void playList::addFolder(QString root,QStringList filters,QWidget *parent)
{
    // qDebug()<<"###########################"<<filters;
    QDir dir;
    QStringList folderlist;
    int pc=0;
    int count=0;
    int acount=0;
    QProgressDialog progress("Adding files...", "Cancel", 0, 1,parent);
    progress.setWindowModality(Qt::WindowModal);
    folderlist<<root;
    acount=1;
    while(folderlist.count())
    {   pc=folderlist.count();

        dir = QDir(folderlist.at(0));
        dir.setFilter(QDir::Hidden|QDir::Files|QDir::AllDirs | QDir::NoSymLinks | QDir::Readable|QDir::NoDotAndDotDot);
        dir.setNameFilters(filters);
        QFileInfoList list = dir.entryInfoList();


        for (int i=0;i<list.count();i++)
        {
            if (list.at(i).isDir())
                folderlist<<list.at(i).absoluteFilePath();
            else
                this->addFile(list.at(i).absoluteFilePath());
            qApp->processEvents();

        }
        pc-folderlist.count();
        acount=folderlist.count()-pc+acount;
        progress.setMaximum(acount);
        folderlist.removeFirst();
        count++;
        if (progress.wasCanceled())
            break;

        progress.setValue(count);
    }
    if (tab->rowCount()==0)
    {

        //  Format	Description	Qt's support
        //  BMP	Windows Bitmap	Read/write
        //  GIF	Graphic Interchange Format (optional)	Read
        //  JPG	Joint Photographic Experts Group	Read/write
        //  JPEG	Joint Photographic Experts Group	Read/write
        //  PNG	Portable Network Graphics	Read/write
        //  PBM	Portable Bitmap	Read
        //  PGM	Portable Graymap	Read
        //  PPM	Portable Pixmap	Read/write
        //  TIFF	Tagged Image File Format	Read/write
        //  XBM	X11 Bitmap	Read/write
        //  XPM	X11 Pixmap	Read/write

        QStringList picfilters;
        dir = QDir(root);
        picfilters<<"*.bmp"<<"*.jpg"<<"*.jpeg"<<"*.png"<<"*.pbm"<<"*.pgm"<<"*.ppm"<<"*.tiff"<<"*.gif"<<"*.xbm"<<"*.xpm";
        QFileInfoList li=dir.entryInfoList();
        dir.setNameFilters(picfilters);
        li = dir.entryInfoList();
        if (li.count()>0)
        {emit showPictureFlow(root);
            return;
        }
    }
}
void playList::itemDoubleClicked( QTableWidgetItem * item )
{QBrush brush(Qt::black);

    if (currentIndex>-1)
    {
        tab->item(currentIndex,0)->setIcon(QIcon(":/images/playok.png"));
        tab->item(currentIndex,0)->setForeground(brush);
        tab->item(currentIndex,1)->setForeground(brush);

    }
    //qDebug()<<"row doubleclicked" <<item->row();
    currentIndex=item->row();
    emit this->playThisfile(tab->item(currentIndex,2)->data(Qt::DisplayRole).toString());

    tab->item(currentIndex,0)->setIcon(QIcon(":/images/playing.png"));
    brush.setColor(Qt::blue);;
    tab->item(currentIndex,0)->setForeground(brush);
    tab->item(currentIndex,1)->setForeground(brush);

}
void  playList::playNextFile()
{

    if (tab->rowCount()>0)
    {
        drawOk(currentIndex);
        //+++++++++++++++++++++++++++++++++++++++++++++
        if(currentIndex==tab->rowCount()-1)
        { if (_bloop)
            { if (!_bshuffle)
                {if (tab->rowCount()>0)
                    {this->playFirstFile();
                        return;
                    }
                }
            }
            if (_bshuffle)
                goto shuffle;
            else
                return;
        }
        else
        {  //printf("%f",(double)currentIndex<tab->rowCount()*rand()/(RAND_MAX+1.0));
            //qDebug()<<"currentIndex"<<QString::number((double)tab->rowCount()*rand()/(RAND_MAX+1.0));

shuffle:if(_bshuffle)
                currentIndex=(int)((double)tab->rowCount()* (double)rand()/(RAND_MAX+1.0));
            else
                currentIndex++;
        }


        if(currentIndex>-1)
        {

            if (currentIndex<tab->rowCount())
                emit this->playThisfile(tab->item(currentIndex,2)->data(Qt::DisplayRole).toString());

        }
        //+++++++++++++++++++++++++++++++++++++++++++++
        drawPlay(currentIndex);

    }
}

void  playList::playPreviousFile()
{ if (currentIndex>0)
    {drawOk(currentIndex);
        //+++++++++++++++++++++++++++++++++++++++++++++
        currentIndex--;
        //qDebug()<<"next index hreee "<<currentIndex;
        if (currentIndex>-1 )
        {emit this->playThisfile(tab->item(currentIndex,2)->data(Qt::DisplayRole).toString());
            //+++++++++++++++++++++++++++++++++++++++++++++
            drawPlay(currentIndex);
        }
    }
}
void playList::removeSelectedFile()
{
    QList<QTableWidgetItem *> ni;
    QStringList selrows;
    ni = tab->selectedItems();

    int sel=0;
    int removecount=0;
    for (int j=0;j<ni.count();j++)
    {selrows<<QString::number(ni.at(j)->row());

    }
    selrows.removeDuplicates();

    //qDebug()<<"files to remove"<<selrows.count();

    if (selrows.count())
    { sel=selrows.count();
        tab->setSortingEnabled(false);
        for (int j=0;j<selrows.count();j++)
        {
            for(int k=0;k<tab->rowCount();k++)
            {
                //if (k==currentIndex)
                //{  sel=selrows.count()-1;
                //  break;
                //}


                if( k==QString(selrows.at(j)).toInt())
                {

                    //qDebug()<<"k"<<""<<k<<"row"<<QString(selrows.at(j)).toInt();
                    if  (k<currentIndex)
                    {qDebug()<<"less"<<k<<"cr"<<currentIndex;
                        removecount++;
                        tab->item(k,2)->setData(Qt::DisplayRole,"");
                        break;

                    }
                    else if (k==currentIndex)
                    {  qDebug()<<"playfile";
                        //sel=selrows.count()-1;
                        int bt;
                        bt= QMessageBox::question (0,"ExMplayer","Do you want to remove playing file?",QMessageBox::Yes,QMessageBox::No);

                        //qDebug()<<bt<<"fgdf";
                        if(bt==QMessageBox::Yes)
                        {removecount++;
                            tab->item(k,2)->setData(Qt::DisplayRole,"");
                            emit clearingList();
                        }


                        break;
                    }
                    else
                    {//qDebug()<<"great";
                        //qDebug()<<tab->item(k,2)->data(Qt::DisplayRole).toString();
                        qDebug()<<"gr"<<k<<"cr"<<currentIndex;
                        tab->item(k,2)->setData(Qt::DisplayRole,"");
                        break;
                    }
                }
            }

        }
    }
    for (int k=0;k<sel;k++)

    { for (int j=0;j<tab->rowCount();j++)
        { qDebug()<<"count";

            if(tab->item(j,2)->data(Qt::DisplayRole).toString()=="")
            {
                tab->removeRow(j);
                emit removingfilesg();
                break;
            }
        }
    }
    currentIndex-=removecount;
}
QString playList::getNextFile()
{
    currentIndex++;

    if(currentIndex>-1)
    {
        if (currentIndex<tab->rowCount())
            return tab->item(currentIndex,2)->data(Qt::DisplayRole).toString();
    }

}
void playList::playFirstFile()
{
    drawOk(currentIndex);
    //+++++++++++++++++++++++++++++++++++++++++++++
    if(tab->rowCount()>0)
    {currentIndex=0;

        emit this->playThisfile(tab->item(0,2)->data(Qt::DisplayRole).toString());
    }
    //+++++++++++++++++++++++++++++++++++++++++++++
    drawPlay(currentIndex);

}
void  playList::playLastFile()
{

    drawOk(currentIndex);
    //+++++++++++++++++++++++++++++++++++++++++++++
    currentIndex=tab->rowCount()-1;
    if(currentIndex>-1)
    {if (currentIndex<tab->rowCount())
        { emit this->playThisfile(tab->item(currentIndex,2)->data(Qt::DisplayRole).toString());
        }
    }
    //+++++++++++++++++++++++++++++++++++++++++++++
    drawPlay(currentIndex);


}
void   playList::drawOk(long ind)
{if (ind>-1)
    {
        QBrush brush(Qt::black);
        tab->item(ind,0)->setIcon(QIcon(":/images/playok.png"));
        tab->item(ind,0)->setForeground(brush);
        tab->item(ind,1)->setForeground(brush);

    }
}
void playList::drawPlay(long ind)
{ if (ind>-1&& ind<tab->rowCount())
    {
        QBrush brush(Qt::black);
        tab->item(ind,0)->setIcon(QIcon(":/images/playing.png"));
        brush.setColor(Qt::blue);
        tab->item(ind,0)->setForeground(brush);
        tab->item(ind,1)->setForeground(brush);
    }
}

void  playList::saveasM3u(QString file)
{
    /*#EXTM3U

#EXTINF:123,Sample Artist - Sample title
C:\Documents and Settings\I\My Music\Sample.mp3

#EXTINF:321,Example Artist - Example title
C:\Documents and Settings\I\My Music\Greatest Hits\Example.ogg
*/
    QFile f( file );
    if ( f.open( QIODevice::WriteOnly ) ) {
        QTextStream stream( &f );


        QString filename;

        stream << "#EXTM3U" << "\n";
        stream << "# Playlist created by ExMplayer \n";
        for (int i=0;i<tab->rowCount();i++)
        {
            stream << "#EXTINF:";
            stream << "0,";
            stream <<tab->item(i,0)->data(Qt::DisplayRole).toString()<<"\n";
            stream <<tab->item(i,2)->data(Qt::DisplayRole).toString()<<"\n";



        }


        f.close();
    }

}

void  playList::loadM3u(QString file)
{

    QRegExp m3u_id("^#EXTM3U|^#M3U");
    QRegExp info("^#EXTINF:(.*),(.*)");

    QFile f( file );
    QString playlist_path,filename ;
    if ( f.open( QIODevice::ReadOnly ) ) {
        playlist_path = QFileInfo(file).path();
        QTextStream stream( &f );

        QString line;
        while ( !stream.atEnd() ) {
            line = stream.readLine(); // line of text excluding '\n'
            // qDebug( " * line: '%s'", line.toUtf8().data() );
            if (m3u_id.indexIn(line)!=-1) {
                //#EXTM3U
                // Ignore line
            }
            else
                if (info.indexIn(line)!=-1) {
                    //duration = info.cap(1).toDouble();
                    // name = info.cap(2);
                    //qDebug(" * name: '%s', duration: %f", name.toUtf8().data(), duration );
                }
                else
                    if (line.startsWith("#")) {
                        // Comment
                        // Ignore
                    } else {
                        filename = line;
                        QFileInfo fi(filename);
                        if (fi.exists()) {
                            addFile(filename);
                            filename = fi.absoluteFilePath();

                        }
                        if (!fi.exists()) {
                            if (QFileInfo( playlist_path + "/" + filename).exists() ) {
                                filename = playlist_path + "/" + filename;
                                addFile(filename);
                            }
                        }

                        //addItem( filename, name, duration );
                        //name="";
                        // duration = 0;
                    }
        }
    }
    f.close();
}
void playList::saveasPls(QString file)
{
    /*The format is essentially that of an INI file  structured as follows:

  Header

      * [playlist] : This tag indicates that it is a Playlist File
      * NumberOfEntries : This variable indicates the number of tracks

  Track Entry
  Assuming track entry #X

      * FileX : Variable defining location of stream.
      * TitleX : Defines track title.
      * LengthX : Length in seconds of track. Value of -1 indicates indefinite.

  Footer

      * Version : Playlist version. Currently only a value of 2 is valid.

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
[playlist]

File1=http://streamexample.com:80
Title1=My Favorite Online Radio
Length1=-1

File2=http://example.com/song.mp3
Title2=Remote MP3
Length2=286

File3=/home/myaccount/album.flac
Title3=Local album
Length3=3487

NumberOfEntries=3

Version=2
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

*/
    QSettings set(file, QSettings::IniFormat);

    set.beginGroup( "playlist");

    for ( int n=0; n < tab->rowCount(); n++ ) {

        set.setValue("File"+QString::number(n+1),tab->item(n,2)->data(Qt::DisplayRole).toString());
        set.setValue("Title"+QString::number(n+1),tab->item(n,0)->data(Qt::DisplayRole).toString());
        set.setValue("Length"+QString::number(n+1),QString::number(0));

    }

    set.setValue("NumberOfEntries",QString::number(tab->rowCount()));
    set.setValue("Version", QString::number(2));
    set.endGroup();
    set.sync();

}
void playList::setDuration(float dur)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(dur));
    tab->setItem(currentIndex,3, newItem);
    QTime _tduration=QTime();
    _tduration=  _tduration.addSecs(dur);
    //qDebug()<<"fd"<<_tduration.toString();
    QTableWidgetItem *newItem1 = new QTableWidgetItem( _tduration.toString());
    tab->setItem(currentIndex,1, newItem1);
}
void playList::loadPls(QString file)
{

    QString playlist_path = QFileInfo(file).path();
    QSettings set(file, QSettings::IniFormat);

    set.beginGroup( "playlist");

    if (set.status() == QSettings::NoError) {
        //clear();
        QString filename;
        QString name;
        double duration;

        int num_items = set.value("NumberOfEntries", 0).toInt();
        //qDebug()<<"num_items"<<num_items;
        for (int n=0; n < num_items; n++) {
            filename = set.value("File"+QString::number(n+1), "").toString();
            name = set.value("Title"+QString::number(n+1), "").toString();
            duration = (double) set.value("Length"+QString::number(n+1), 0).toInt();

            QFileInfo fi(filename);
            if (fi.exists()) {
                filename = fi.absoluteFilePath();
            }
            if (!fi.exists()) {
                if (QFileInfo( playlist_path + "/" + filename).exists() ) {
                    filename = playlist_path + "/" + filename;
                }
            }
            //addItem( filename, name, duration );
            this->addFile(filename);
        }
    }

    set.endGroup();
}
QString playList::getFile(int index)
{
    if (tab->rowCount()>0)
        return tab->item(index,2)->data(Qt::DisplayRole).toString();


}
void  playList::playCurrentFile()
{
    if (tab->rowCount()>0)
        emit this->playThisfile(tab->item(currentIndex,2)->data(Qt::DisplayRole).toString());

}

