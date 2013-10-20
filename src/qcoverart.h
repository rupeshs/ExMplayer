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
