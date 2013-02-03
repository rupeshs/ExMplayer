#ifndef RPHMENUBAR_H
#define RPHMENUBAR_H

#include <QMenuBar>
#include <QKeyEvent>
class rphMenuBar : public QMenuBar
{Q_OBJECT
public:
    rphMenuBar(QWidget *parent = 0);
signals:
    void keyPress(QKeyEvent * e);
public slots:
void keyPressSlot( QKeyEvent * e );
};

#endif // RPHMENUBAR_H
