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
#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QDebug>
#include <QObject>
#include <QTableWidget>

class playList : public QObject
{
Q_OBJECT
public:
    explicit playList(QObject *parent = 0);
    QTableWidget *tableWidget(){return tab;};
    int listCount(){return tab->rowCount();};
    int currentIndex;
    QTableWidget *tab;

signals:
    void playThisfile(QString path);
    void clearingList();
    void showPictureFlow(QString path);
    void addingfilesg();
    void removingfilesg();
public slots:

    //Adding and removing
    void addFile(QString path);
    void addFolder(QString root,QStringList filters,QWidget *parent);
    void clearList();
    void removeSelectedFile();

    //Play
    void itemDoubleClicked( QTableWidgetItem * item );
    void playNextFile();
    void playPreviousFile();
    void playFirstFile();
    void playCurrentFile();
    //adds a file and plays that without clearing the list
    void playLastFile();

    //Query
    QString getNextFile();
    QString getFile(int index);

    //Playlist format handling

    void saveasM3u(QString file);
    void loadM3u(QString file);
    void saveasPls(QString file);
    void loadPls(QString file);

    //++++++++++++++++++++++++++++++
    void setDuration(float dur);
    void loop(bool en){_bloop=en;};
    void shuffle(bool en){_bshuffle=en;};

private:
   bool _bloop;
   bool _bshuffle;
   void drawOk(long ind);
   void drawPlay(long ind);



};

#endif // PLAYLIST_H
