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
#include "filefilters.h"
#include <QString>
#include <QStringList>
#include <QDesktopServices>
#include <QtCore>
#include <QDir>
#ifdef Q_OS_WIN
#include <windows.h>
#endif
fileFilters::fileFilters()
{
}
QString fileFilters::getvideofilters()
 {
    QString fpl;
    QStringList faul;
    QString fau;
    QString mul;
    faul <<"*.wav"
         <<"*.ac3"
         <<"*.flac"
         <<"*.mka"
         <<"*.mp3"
         <<"*.m4a"
         <<"*.aac"
         <<"*.mpc"
         <<"*.ogg"
         <<"*.oga"
         <<"*.ra"
         <<"*.wma"
         <<"*.spx"
         <<"*.mmf"
         <<"*.amr"
         <<"*.ape";
    for (int i=0;i<faul.count();i++)
    {if (i==faul.count())
        fau+=faul.at(i);
     else
        fau+=faul.at(i)+" ";

       mul+=faul.at(i)+" ";
    }
     fau.prepend("Audio files (");
     fau.append(");");
     QStringList fvil;
     QString fvi;
     fvil     <<"*.wmv"
              <<"*.3gp"
              <<"*.asf"
              <<"*.avi"
              <<"*.dat"
              <<"*.dv"
              <<"*.divx"
              <<"*.ext"
              <<"*.flv"
              <<"*.ifo"
              <<"*.mkv"
              <<"*.mpg"
              <<"*.mpe"
              <<"*.mov"
              <<"*.mp4"
              <<"*.ogm"
              <<"*.ogv"
              <<"*.rm"
              <<"*.rmvb"
              <<"*.nsv"
              <<"*.smk"
              <<"*.ts"
              <<"*.vob";
     for (int i=0;i<fvil.count();i++)
     {if (i==fvil.count())
         {fvi+=fvil.at(i);
          mul+=fvil.at(i);
      }
      else
         { fvi+=fvil.at(i)+" ";
         mul+=fvil.at(i)+" ";
     }
     }
      fvi.prepend("Video files (");
      fvi.append(");");
      mul.prepend("Mutimedia files (");
      mul.append(");");
      fpl="Playlists (*.m3u *.pls);;Any file (*.*)";

      return fvi;
 }
QString fileFilters::getaudiofilters()
 {
    QString fpl;
    QStringList faul;
    QString fau;
    QString mul;
    faul <<"*.wav"
         <<"*.ac3"
         <<"*.flac"
         <<"*.mka"
         <<"*.mp3"
         <<"*.m4a"
         <<"*.aac"
         <<"*.mpc"
         <<"*.ogg"
         <<"*.oga"
         <<"*.ra"
         <<"*.wma"
         <<"*.spx"
         <<"*.mmf"
         <<"*.amr"
         <<"*.ape";
    for (int i=0;i<faul.count();i++)
    {if (i==faul.count())
        fau+=faul.at(i);
     else
        fau+=faul.at(i)+" ";

       mul+=faul.at(i)+" ";
    }
     fau.prepend("Audio files (");
     fau.append(");");
     QStringList fvil;
     QString fvi;
     fvil     <<"*.wmv"
              <<"*.3gp"
              <<"*.asf"
              <<"*.avi"
              <<"*.dat"
              <<"*.dv"
              <<"*.divx"
              <<"*.ext"
              <<"*.flv"
              <<"*.ifo"
              <<"*.mkv"
              <<"*.mpg"
              <<"*.mpe"
              <<"*.mov"
              <<"*.mp4"
              <<"*.ogm"
              <<"*.ogv"
              <<"*.rm"
              <<"*.rmvb"
              <<"*.nsv"
              <<"*.smk"
              <<"*.ts"
              <<"*.vob";
     for (int i=0;i<fvil.count();i++)
     {if (i==fvil.count())
         {fvi+=fvil.at(i);
          mul+=fvil.at(i);
      }
      else
         { fvi+=fvil.at(i)+" ";
         mul+=fvil.at(i)+" ";
     }
     }
      fvi.prepend("Video files (");
      fvi.append(");");
      mul.prepend("Mutimedia files (");
      mul.append(");");
      fpl="Playlists (*.m3u *.pls);;Any file (*.*)";

      return fau;
 }

// This function has been copied (and modified a little bit) from Scribus (program under GPL license):
// http://docs.scribus.net/devel/util_8cpp-source.html#l00112
QString fileFilters::shortPathName(QString long_path) {
#ifdef Q_OS_WIN
    if ((QSysInfo::WindowsVersion >= QSysInfo::WV_NT) && (QFile::exists(long_path))) {
        QString short_path = long_path;

        const int max_path = 4096;
        WCHAR shortName[max_path];

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QString nativePath = QDir::convertSeparators(long_path);
 #else
    QString nativePath = QDir::toNativeSeparators(long_path);
 #endif
        int ret = GetShortPathNameW((LPCWSTR) nativePath.utf16(), shortName, max_path);
        if (ret != ERROR_INVALID_PARAMETER && ret < MAX_PATH)
            short_path = QString::fromUtf16((const ushort*) shortName);

        return short_path;
    } else {
        return long_path;
    }
#endif
     return long_path;
}

