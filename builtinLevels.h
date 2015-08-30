#ifndef BUILTINLEVELS_H
#define BUILTINLEVELS_H

#include "GameConfig.h"

namespace builtinLevels {
    extern const int NumOfBuiltinLevels;
    extern const char* builtinLevels[];

    GameConfig getBuiltinLevel(int levelID);
}

#endif // BUILTINLEVELS_H

