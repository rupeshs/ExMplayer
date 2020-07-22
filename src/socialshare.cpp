/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2020 Rupesh Sreeraman

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
#include "socialshare.h"

SocialShare::SocialShare()
{
}
QString SocialShare::makeClearInfoText(QString inf)
{
    int pos=inf.indexOf("www");
    QString str;
    if(pos>2)
    {
        str=inf.mid(0,pos);
        //qDebug()<<QString(str.at(pos-2));
        if (pos>3&str.length()>2)
        {if (QString(str.at(pos-1))==QString("-"))
                str=str.mid(0,pos-2);

            if (QString(str.at(pos-2))==QString("-"))
                str=str.mid(0,pos-3);
        }
        return str;

    }
    else
    {
        return inf;
    }
}

bool SocialShare::shareThisPlaybackOnFacebook(QWidget *parent,mplayerfe* mp)
{
    if (mp->state()==mplayerfe::PLAYING||mp->state()==mplayerfe::PAUSED)
    {

        QString sharePlayback;
        sharePlayback="https://www.facebook.com/dialog/feed?app_id=445733802216245&display=popup&caption=";
        if(mp->hasvideo())
            sharePlayback+="Watching "+mp->getMediaTitle();
        else
        {
            if (mp->mapMetaInfo["title"]!="")
            {   bool ok;
                QString userInputSongName;
                QString title=makeClearInfoText(mp->mapMetaInfo["title"]);
                if (title.contains(QRegExp("(Track)")))
                {

                    userInputSongName = QInputDialog::getText(parent, "ExMplayer",
                                                              "Song name:", QLineEdit::Normal,
                                                              "", &ok);
                    if (ok && !userInputSongName.isEmpty())
                        title=userInputSongName;
                    else
                    {
                        QMessageBox::information(parent,"ExMplayer","Please enter song name.");
                        return false;
                    }


                }


                sharePlayback =sharePlayback+"Listening to "+title;
            }
            else
            {
                int pos=mp->getMediaTitle().indexOf("www");
                if (mp->getMediaTitle().contains(QRegExp("(Track)"))||pos==0)
                {

                    bool ok=false;
                    QString title;
                    QString userInputSongName = QInputDialog::getText(parent, "ExMplayer",
                                                                      "Song name:", QLineEdit::Normal,
                                                                      "", &ok);
                    if (ok && !userInputSongName.isEmpty())
                        title=userInputSongName;
                    else
                    {
                        QMessageBox::information(parent,"ExMplayer","Please enter song name.");
                        return false;
                    }


                    sharePlayback+="Listening to "+title;
                }
                else
                    sharePlayback+="Listening to "+mp->getMediaTitle();
            }
        }

        sharePlayback+="&description=";

        if (mp->mapMetaInfo["album"]!="")
            sharePlayback+="Album - "+makeClearInfoText(mp->mapMetaInfo["album"])+" , ";
        if (mp->mapMetaInfo["artist"]!="")
            sharePlayback+="Artist - "+makeClearInfoText(mp->mapMetaInfo["artist"])+"";

        if(mp->hasvideo())
            sharePlayback+=QString::number(mp->videowidth())+"x"+QString::number(mp->videoheight())+", "+mp->getVideoFormat() ;

        sharePlayback+="&link=http://exmplayer.sourceforge.net&redirect_uri=https://apps.facebook.com/exmplayer/";
        QDesktopServices::openUrl(sharePlayback);
    }
    return true;

}
