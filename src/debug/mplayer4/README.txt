MPlayer/MEncoder Win32 binary Builds by Gianluigi Tiesi <sherpya@netfarm.it>

The included subfont.ttf is DejaVu Serif,
Copyright (c) 2003 by Bitstream, Inc. All Rights Reserved. Bitstream Vera is
a trademark of Bitstream, Inc.
DejaVu changes are in public domain.

Additionally were added some patches from me, and other picked around internet.
For information about included patches please look at:
http://oss.netfarm.it/mplayer-win32.php

Modified windows icons are made by using Lila SVG Icon and Theme Artwork:
http://www.lila-center.info/doku.php
Copyright 2004-2006 Lila Community
available under the GNU General Public License

-- Report bugs to sherpya@netfarm.it

--
The bottom of this file has a list of keyboard shortcuts to control MPlayer.
A complete list of command line parameters is in mplayer.html. More
documentation is in the docs/ directory. Start reading at index.html or
skip right to windows.html for Windows-specific information. Note that
while most of the documentation is written with the Unix version in mind
most things are valid for Windows as well.


The files in this package:
mplayer.exe   - the main executable
mencoder.exe  - a full-featured video encoder
vfw2menc.exe  - a tool used to configure VfW codecs, please look at
                docs/menc-feat-video-for-windows.html
mplayer.html  - usage and command line options
AUTHORS.txt   - (incomplete) authors list
Changelog.txt - a list of the most important changes between versions
Copyright.txt - copyright information for imported libraries
LICENSE.txt   - a copy of the GNU General Public License (GNU GPL)
README.txt    - this document
codecs/       - binary codecs (Real, QuickTime etc.) directory;
                You can download some codecs from our downlad page:
                http://www.mplayerhq.hu/design7/dload.html

mplayer/config      - configuration file with adjustable options
mplayer/input.conf  - keybinding configuration file

A list of Windows frontends for MPlayer can be found at
http://www.mplayerhq.hu/homepage/design7/projects.html#windows

A mailing list for Windows-related questions is at
http://lists.mplayerhq.hu/mailman/listinfo/mplayer-cygwin


KEYBOARD CONTROL

general control
  <- and ->
       Seek backward/forward 10 seconds.
  up and down
       Seek backward/forward 1 minute.
  pgup and pgdown
       Seek backward/forward 10 minutes.
  [ and ]
       Decreases/increases current playback speed by 10%.
  { and }
       Halves/doubles current playback speed.
  Backspace
       Reset playback speed to normal.
  < and >
       backward/forward in playlist
  HOME and END
       next/previous playtree entry in the parent list
  INS and DEL
       next/previous alternative source (ASX playlist only)
  p / SPACE
       Pause movie (pressing again unpauses).
  .
       Step forward.  Pressing once  will  pause  movie,  every
       consecutive  press  will play one frame and then go into
       pause mode again (any other key unpauses).
  q / ESC
       Stop playing and quit.
  + and -
       Adjust audio delay by +/- 0.1 seconds.
  / and *
       Decrease/increase volume.
  9 and 0
       Decrease/increase volume.
  m
       Mute sound.
  f
       Toggle fullscreen (also see -fs).
  T
       Toggle stay-on-top (also see -ontop).
  w and e
       Decrease/increase pan-and-scan range.
  o
       Toggle OSD states: none / seek / seek + timer /  seek  +
       timer + total time.
  d
       Toggle frame dropping states: none / skip display / skip
       decoding (see -framedrop and -hardframedrop).
  v
       Toggle subtitle visibility.
  b / j
       Cycle through the available subtitles.
  F
       Toggle displaying "forced subtitles".
  a
       Toggle subtitle aligment: top/middle/bottom.
  z and x
       Adjust subtitle delay by +/- 0.1 seconds.
  r and t
       Move subtitles up/down.
  i
       Set EDL mark.

(The following keys are valid only when using  a  hardware  accelerated
video  output  (xv,  (x)vidix,  (x)mga, etc), or the software equalizer
filter (-vf eq or -vf eq2).

  1 and 2
       Adjust contrast.
  3 and 4
       Adjust brightness.
  5 and 6
       Adjust hue.
  7 and 8
       Adjust saturation.
