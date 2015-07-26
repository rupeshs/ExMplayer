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
#include "equalizertypes.h"

EqualizerTypes::EqualizerTypes()
{
    Classical[0] = 0;
    Classical[1] = 0;
    Classical[2] = 0;
    Classical[3] = 0;
    Classical[4] = 0;
    Classical[5] = 0;
    Classical[6] = -7.4;
    Classical[7] = -7.4;
    Classical[8] = -7.4;
    Classical[9] = -9.4;

    Club[0] = 0;
    Club[1] = 0;
    Club[2] = 8;
    Club[3] = 5.6;
    Club[4] = 5.6;
    Club[5] = 5.6;
    Club[6] = 3.2;
    Club[7] = 0;
    Club[8] = 0;
    Club[9] = 0;

    Dance[0] = 9.6;
    Dance[1] = 7.2;
    Dance[2] = 2.4;
    Dance[3] = 0;
    Dance[4] = 0;
    Dance[5] = -5.4;
    Dance[6] = -7.4;
    Dance[7] = -7.4;
    Dance[8] = 0;
    Dance[9] = 0;

    Flat[0] = 0;
    Flat[1] = 0;
    Flat[2] = 0;
    Flat[3] = 0;
    Flat[4] = 0;
    Flat[5] = 0;
    Flat[6] = 0;
    Flat[7] = 0;
    Flat[8] = 0;
    Flat[9] = 0;

    Fullbass[0] = 9.6;
    Fullbass[1] = 9.6;
    Fullbass[2] = 9.6;
    Fullbass[3] = 5.6;
    Fullbass[4] = 1.6;
    Fullbass[5] = -4;
    Fullbass[6] = -8;
    Fullbass[7] = -10.4;
    Fullbass[8] = -11.4;
    Fullbass[9] = -11.4;

    FullbassTreble[0] = 7.2;
    FullbassTreble[1] = 5.6;
    FullbassTreble[2] = 0;
    FullbassTreble[3] = -7.4;
    FullbassTreble[4] = -4.4;
    FullbassTreble[5] = 1.6;
    FullbassTreble[6] = 8;
    FullbassTreble[7] = 11.2;
    FullbassTreble[8] = 12;
    FullbassTreble[9] = 12;

    Fulltreble[0] = -9.4;
    Fulltreble[1] = -9.4;
    Fulltreble[2] = -9.4;
    Fulltreble[3] = -4;
    Fulltreble[4] = 2.4;
    Fulltreble[5] = 11.2;
    Fulltreble[6] = 16;
    Fulltreble[7] = 16;
    Fulltreble[8] = 16;
    Fulltreble[9] = 16;

    Headphones[0] = 4.8;
    Headphones[1] = 11.2;
    Headphones[2] = 5.6;
    Headphones[3] = -3.4;
    Headphones[4] = -2.4;
    Headphones[5] = 1.6;
    Headphones[6] = 4.8;
    Headphones[7] = 9.6;
    Headphones[8] = 12.8;
    Headphones[9] = 14.4;

    LargeHall[0] = 10.4;
    LargeHall[1] = 10.4;
    LargeHall[2] = 5.6;
    LargeHall[3] = 5.6;
    LargeHall[4] = 0;
    LargeHall[5] = -4.4;
    LargeHall[6] = -4.4;
    LargeHall[7] = -4.4;
    LargeHall[8] = 0;
    LargeHall[9] = 0;

    Live[0] = -4.4;
    Live[1] = 0;
    Live[2] = 4;
    Live[3] = 5.6;
    Live[4] = 5.6;
    Live[5] = 5.6;
    Live[6] = 4;
    Live[7] = 2.4;
    Live[8] = 2.4;
    Live[9] = 2.4;

    Party[0] = 7.2;
    Party[1] = 7.2;
    Party[2] = 0;
    Party[3] = 0;
    Party[4] = 0;
    Party[5] = 0;
    Party[6] = 0;
    Party[7] = 0;
    Party[8] = 7.2;
    Party[9] = 7.2;

    Pop[0] = -1.4;
    Pop[1] = 4.8;
    Pop[2] = 7.2;
    Pop[3] = 8;
    Pop[4] = 5.6;
    Pop[5] = 0;
    Pop[6] = -2.4;
    Pop[7] = -2.4;
    Pop[8] = -1.4;
    Pop[9] = -1.4;

    Reggae[0] = 0;
    Reggae[1] = 0;
    Reggae[2] = 0;
    Reggae[3] = -5.4;
    Reggae[4] = 0;
    Reggae[5] = 6.4;
    Reggae[6] = 6.4;
    Reggae[7] = 0;
    Reggae[8] = 0;
    Reggae[9] = 0;

    Rock[0] = 8;
    Rock[1] = 4.8;
    Rock[2] = 5.4;
    Rock[3] = -8;
    Rock[4] = -3.4;
    Rock[5] = 4;
    Rock[6] = 8.8;
    Rock[7] = 11.2;
    Rock[8] = 11.2;
    Rock[9] = 11.2;

    Ska[0] = -2.4;
    Ska[1] = -4.4;
    Ska[2] = -4;
    Ska[3] = 0;
    Ska[4] = 4;
    Ska[5] = 5.6;
    Ska[6] = 8.8;
    Ska[7] = 9.6;
    Ska[8] = 11.2;
    Ska[9] = 9.6;

    Soft[0] = 4.8;
    Soft[1] = 1.6;
    Soft[2] = 0;
    Soft[3] = -2.4;
    Soft[4] = 0;
    Soft[5] = 4;
    Soft[6] = 8;
    Soft[7] = 9.6;
    Soft[8] = 11.2;
    Soft[9] = 12;

    SoftRock[0] = 4;
    SoftRock[1] = 4;
    SoftRock[2] = 2.4;
    SoftRock[3] = 0;
    SoftRock[4] = -4;
    SoftRock[5] = -5.4;
    SoftRock[6] = -3.4;
    SoftRock[7] = 0;
    SoftRock[8] = 2.4;
    SoftRock[9] = 8.8;

    Techno[0] = 8;
    Techno[1] = 5.6;
    Techno[2] = 0;
    Techno[3] = -5.4;
    Techno[4] = -4.4;
    Techno[5] = 0;
    Techno[6] = 8;
    Techno[7] = 9.6;
    Techno[8] = 9.6;
    Techno[9] = 8.8;

}
