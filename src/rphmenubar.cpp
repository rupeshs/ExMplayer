#include "rphmenubar.h"


rphMenuBar::rphMenuBar(QWidget  *parent) :
      QMenuBar (parent)
{

}
void rphMenuBar::keyPressSlot ( QKeyEvent * e )
{
    QMenuBar::keyPressEvent(e);
}
