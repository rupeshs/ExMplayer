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
#include "qcoverart.h"

QCoverArt::QCoverArt()
{

}

/*
** Attempts to extract cover art from audio files.
**
*/
bool QCoverArt::GetCover(const TagLib::FileRef& fr)
{
    bool found = false;

    if (TagLib::MPEG::File* file = dynamic_cast<TagLib::MPEG::File*>(fr.file()))
    {
        if (file->ID3v2Tag())
        {
            found = ExtractID3(file->ID3v2Tag());
        }
        if (!found && file->APETag())
        {
            found = ExtractAPE(file->APETag());
        }
    }
    else if (TagLib::ASF::File* file = dynamic_cast<TagLib::ASF::File*>(fr.file()))
    {
        found = ExtractASF(file);
    }
    else if (TagLib::MP4::File* file = dynamic_cast<TagLib::MP4::File*>(fr.file()))
    {
        if (file->tag())
        {
            found = ExtractMP4(file);
        }
    }
    else if (TagLib::FLAC::File* file = dynamic_cast<TagLib::FLAC::File*>(fr.file()))
    {
        found = ExtractFLAC(file);

        if (!found && file->ID3v2Tag())
        {
            found = ExtractID3(file->ID3v2Tag());
        }
    }
    else if (TagLib::APE::File* file = dynamic_cast<TagLib::APE::File*>(fr.file()))
    {
        if (file->APETag())
        {
            found = ExtractAPE(file->APETag());
        }
    }
    else if (TagLib::MPC::File* file = dynamic_cast<TagLib::MPC::File*>(fr.file()))
    {
        if (file->APETag())
        {
            found = ExtractAPE(file->APETag());
        }
    }
    else if (TagLib::WavPack::File* file = dynamic_cast<TagLib::WavPack::File*>(fr.file()))
    {
        if (file->APETag())
        {
            found = ExtractAPE(file->APETag());
        }
    }

    return found;
}

/*
** Extracts cover art embedded in APE tags.
**
*/
bool QCoverArt::ExtractAPE(TagLib::APE::Tag* tag)
{
    const TagLib::APE::ItemListMap& listMap = tag->itemListMap();

    if (listMap.contains("COVER ART (FRONT)"))
    {
        const TagLib::ByteVector nullStringTerminator(1, 0);

        TagLib::ByteVector item = listMap["COVER ART (FRONT)"].value();
        int pos = item.find(nullStringTerminator);	// Skip the filename

        if (++pos > 0)
        {
            const TagLib::ByteVector& pic = item.mid(pos);

            img.loadFromData((const unsigned char*)pic.data(), pic.size());
            return true;
        }
    }

    return false;
}

/*
** Extracts cover art embedded in ID3v2 tags.
**
*/
bool QCoverArt::ExtractID3(TagLib::ID3v2::Tag* tag)
{
    const TagLib::ID3v2::FrameList& frameList = tag->frameList("APIC");
    if (!frameList.isEmpty())
    {
        // Grab the first image
        TagLib::ID3v2::AttachedPictureFrame* frame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frameList.front());
        img.loadFromData((const unsigned char*)frame->picture().data(), (int)frame->picture().size());

        return true;
    }

    return false;
}

/*
** Extracts cover art embedded in ASF/WMA files.
**
*/
bool QCoverArt::ExtractASF(TagLib::ASF::File* file)
{
    const TagLib::ASF::AttributeListMap& attrListMap = file->tag()->attributeListMap();
    if (attrListMap.contains("WM/Picture"))
    {
        const TagLib::ASF::AttributeList& attrList = attrListMap["WM/Picture"];

        if (!attrList.isEmpty())
        {
            // Let's grab the first cover. TODO: Check/loop for correct type
            TagLib::ASF::Picture wmpic = attrList[0].toPicture();
            if (wmpic.isValid())
            {
                img.loadFromData((const unsigned char*)wmpic.picture().data(), (int)wmpic.picture().size());

                return true;
            }
        }
    }

    return false;
}

/*
** Extracts cover art embedded in FLAC files.
**
*/
bool QCoverArt::ExtractFLAC(TagLib::FLAC::File* file)
{
    const TagLib::List<TagLib::FLAC::Picture*>& picList = file->pictureList();
    if (!picList.isEmpty())
    {
        // Let's grab the first image
        TagLib::FLAC::Picture* pic = picList[0];
        img.loadFromData((const unsigned char*)pic->data().data(), (int)pic->data().size());

        return true;
    }

    return false;
}

/*
** Extracts cover art embedded in MP4-like files.
**
*/
bool QCoverArt::ExtractMP4(TagLib::MP4::File* file)
{
    TagLib::MP4::Tag* tag = file->tag();
    if (tag->itemListMap().contains("covr"))
    {
        TagLib::MP4::CoverArtList coverList = tag->itemListMap()["covr"].toCoverArtList();

        if (coverList[0].data().size() > 0)
        {
            img.loadFromData((const unsigned char*)coverList[0].data().data(), coverList[0].data().size());
            return true;
        }
    }

    return false;
}

