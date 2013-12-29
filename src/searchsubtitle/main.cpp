#include <QtGui/QApplication>
#include "searchsubtitle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchSubtitle w;
    w.show();
    
    return a.exec();
}
