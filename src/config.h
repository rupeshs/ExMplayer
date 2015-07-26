/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2015 Rupesh Sreeraman

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


#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QSettings>
class config
{
 public:
 QSettings _settings;
 config();
 void set_screenshotfolder(QString dir){screenshotfolder=dir;}
 void setcrossfade(bool val);
 //String processPriority(){return _settings.value("General/Priority","abovenormal").toString();};
 QString screenshotfolder;
 public slots:
 private:
 //QString _processPriority;
 bool crossfade;

};

#endif // CONFIG_H
