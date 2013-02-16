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

#include "rphmpfehelp.h"

rphMPFEhelp::rphMPFEhelp()
{

 helpcutterstr=   this->addTitle("How to cut a media file") +
                  this->addHeading("Step 1:Play your file in ExMplayer then from tools menu select media cutter then press 'mark start' button to indicate the start position as shown  below.")+
                  this->addImage(":/images/sh1.png")+
                  this->addHeading("Step 2:Now press the 'markstop' button to mark the stop position as shown below.")+
                  this->addImage(":/images/sh2.png")+
                  this->addHeading("Step 3:Now press cut button to cut rhe media,browse for output folder as shown below,before cutting you can preview the media using 'preview' button.")+
                  this->addImage(":/images/sh3.png");
  playerhlpstrEx= this->addLine("")+
                  this->addLine("")+
                  this->addTitle("ExMplayer") +
                  this->addImage(":/images/rphMPFE_sh.png")+
                  this->addLine("")+
                  this->addLine("")+
                  this->addLine("              ExMplayer is a GUI front-end for MPlayer with thumbnail view.Supports audio,video,dvd files(.vob),vcd files(.mpg,.dat) and network streaming.Subtitle decoding is done by using ass library.ExMplayer has inbuilt audio and video codecs.")+
                  this->addHeading("Features")+
                  this->addLine("Using MPlayer svn r32848")+
                  this->addLine("161 audio & 357 video codecs")+
                  this->addLine("Flow browser")+
                  this->addLine("PictureFlow")+
                  this->addLine("8 Window styles")+
                  this->addLine("Configurable keyboard shortcuts and mouse")+
                  this->addLine("Subtitles")+
                  this->addLine("Media cutter")+
                  this->addLine("Media mixer")+
                  this->addLine("Audio extractor")+
                  this->addLine("Network streaming")+
                  this->addLine("Cool Seek view-you can see a frame at a partuicular postion without seeking.")+
                  this->addLine("Family friendly mode")+
                  this->addLine("10 band audio equalizer")+
                  this->addLine("video equalizer")+
                  this->addLine("Winamp dsp plugins support")+
                  this->addLine("8 Audio effect filters,17 Video effect filters")+
                  this->addHeading("Flow Browser")+
                  this->addImage(":/images/flow.png")+
                  this->addLine("        Flow browser is a browser which allows u to browse media files very easily it displays folders,drives and files that are playable by rephMPFE.It shows the first frame of videofiles.")+
                  this->addHeading("Flow Browser-how to use?")+
                  this->addLine( "You can use mouse to navigate flow browser.Just scroll the mouse wheel or click and drag to start the flow.Single click will open folder or drive and double click will play the file.")+
                  this->addHeading("Family friendly mode")+
                  this->addLine("You can cut out any violence, profanity, Jar-Jar Binks .. from a movie  according to your own personal preferences.Aside from this, there are  other uses, like automatically skipping over commercials in video files you watch.")+
                  this->addLine("First watch the movie then mark the positions then from plyback menu start family friendly mode.")+
                  this->addHeading("PictureFlow")+
                  this->addLine("Just drag and drop a folder which contains only picture files.")+
                  this->addImage(":/images/sh4.png");
  playerhlpstr=    this->addTitle("Player") +
                  this->addHeading("Priority")+
                  this->addLine("Process priority for MPlayer according to the predefined priorities available under Windows and OS/2")+
                  this->addLine("idle|belownormal|normal|abovenormal|high|realtime")+
                  this->addLine("ideal=low")+
                  this->addWarningLine("WARNING: Using realtime priority can cause system lockup.")+
                  this->addHeading("Style")+
                  this->addLine("This will set window's style.");
                  //playerhlpstrEx+=playerhlpstr;
                  audiohlpstr=this->addTitle("Audio") +
                  this->addHeading("Audio output driver")+
                  this->addLine("win32 (Windows only)-native Windows waveout audio output driver")+
                  this->addLine("dsound (Windows only)-DirectX DirectSound audio output driver")+

                  this->addHeading("Equalizer")+
                  this->addLine("10 octave band graphic equalizer, implemented using 10 IIR band pass filters. This means that it works regardless of what type of audio is being played back. The center frequencies for the 10 bands are:")+
                  this->addLine("No. frequency")+
                  this->addLine("0 31.25 Hz")+
                  this->addLine("1 62.50 Hz")+
                  this->addLine("2 125.00 Hz")+
                  this->addLine("3 250.00 Hz")+
                  this->addLine("4 500.00 Hz")+
                  this->addLine("5 1.00 kHz")+
                  this->addLine("6 2.00 kHz")+
                  this->addLine("7 4.00 kHz")+
                  this->addLine("8 8.00 kHz")+
                  this->addLine("9 16.00 kHz");

 videohlpstr=     this->addTitle("Video") +
                  this->addHeading("Video output driver")+
                  this->addLine("Video output driver is automatically selected.")+
                  this->addHeading("Screenshot output folder")+
                  this->addLine("Output folder for screen shot can be set.");

subtitlehlpstr=   this->addTitle("Subtitles") +
                  this->addHeading("Font")+
                  this->addLine("Select the font for the subtitles.")+
                  this->addHeading("Size")+
                  this->addLine("The size in pixels.")+
                  this->addHeading("Bold")+
                  this->addLine("If checked, the text will be displayed in bold.")+
                  this->addHeading("Italic")+
                  this->addLine("If checked, the text will be displayed in italic.")+
                  this->addHeading("Text color")+
                  this->addLine("Select the color for the text of the subtitles.")+
                  this->addHeading("Border color")+
                  this->addLine("Select the color for the border of the subtitles.")+
                  this->addHeading("Shadow color")+
                  this->addLine("This color will be used for the shadow of the subtitles.")+
                  this->addHeading("Horizontal alignment")+
                  this->addLine("Horizontal alignment can be left,center or right.")+
                  this->addHeading("Vertical alignment")+
                  this->addLine("Vertical alignment can be bottom,middle or top.")+
                  this->addHeading("Closed Captions")+
                  this->addLine("Display DVD Closed Caption (CC) subtitles. These are not the VOB subtitles, these are special ASCII subtitles for the hearing impaired encoded in the VOB userdata stream on most region 1 DVDs. CC subtitles have not been spotted on DVDs from other regions so far.");

internethlpstr=   this->addTitle("Network streaming") +
                  this->addHeading("Internet protocol")+
                  this->addLine("Internet protocol version 4 and 6")+
                  this->addHeading("Cache size")+
                  this->addLine("This option specifies how much memory (in kBytes) to use when precaching a URL.");

keyboardhlpstr=   this->addTitle("Keyboard")+
                  this->addHeading("Edit shortcut")+
                  this->addLine("You can edit shortcuts accoding to your preference just double click the row to edit the shortcut.A restart is necessary to initialise the new shortcuts.");

mousehlpstr=      this->addTitle("Mouse") +
                  this->addHeading("Mose wheel role")+
                  this->addLine("By scrolling mouse wheel you can change the volume or seek the media");

QRegExp sec("Section");
QRegExp head("Heading");
QRegExp lne("Line");
QRegExp warn("Warning");

QString cursec;
QFile f(qApp->applicationDirPath()+"/help.hlpx" );


if ( f.open( QIODevice::ReadOnly ) ) {

    QTextStream stream( &f );
    QString line;

    while ( !stream.atEnd() ) {
        line = stream.readLine();

        if (sec.indexIn(line)!=-1) {

            cursec=line.right(line.length()-8);



        }
        else if (head.indexIn(line)!=-1) {
          if (cursec=="Audio" )
              audiohlpstr+=this->addHeading(line.right(line.length()-8)) ;
          else if (cursec=="Video" )
             videohlpstr+=this->addHeading(line.right(line.length()-8)) ;


         }
        else if (lne.indexIn(line)!=-1) {
          if (cursec=="Audio" )
             audiohlpstr+=this->addLine(line.right(line.length()-5)) ;
          else if (cursec=="Video" )
              videohlpstr+=this->addLine(line.right(line.length()-5)) ;
         }
        else if (warn.indexIn(line)!=-1) {
          if (cursec=="Audio" )
             audiohlpstr+=this->addWarningLine(line.right(line.length()-8)) ;
          else if (cursec=="Video" )
              videohlpstr+=this->addWarningLine(line.right(line.length()-5)) ;
         }

    }
}

}
