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
#ifndef QCOVERART_H
#define QCOVERART_H

#include <QString>
#include <QImage>

// TagLib
#define TAGLIB_STATIC
#include "fileref.h"
#include "apefile.h"
#include "apetag.h"
#include "asffile.h"
#include "attachedpictureframe.h"
#include "commentsframe.h"
#include "flacfile.h"
#include "id3v1genres.h"
#include "id3v2tag.h"
#include "mpcfile.h"
#include "mp4file.h"
#include "mpegfile.h"
#include "tag.h"
#include "taglib.h"
#include "textidentificationframe.h"
#include "tstring.h"
#include "vorbisfile.h"
#include "wavpackfile.h"
#include "mp4coverart.h"

class QCoverArt
{
public:
    QCoverArt();
    bool GetCover(const TagLib::FileRef& fr);
    QImage getCoverImage(){return img;}

private:
    QImage img;

    bool ExtractID3(TagLib::ID3v2::Tag* tag);
    bool ExtractASF(TagLib::ASF::File* file);
    bool ExtractAPE(TagLib::APE::Tag* tag);
    bool ExtractFLAC(TagLib::FLAC::File* file);
    bool ExtractMP4(TagLib::MP4::File* file);

};

#endif // QCOVERART_H
