#ifndef PATHS_H
#define PATHS_H
#include <QString>

class Paths
{
public:
    Paths();
    //! Return the path where exmplayer should save its config files
    static QString configPath();
    static QString sharePath();
};

#endif // PATHS_H
