#include "builtinLevels.h"

#include <cassert>
#include <QString>
#include <QFile>

namespace builtinLevels {

const int NumOfBuiltinLevels = 7;

const char* builtinLevels[NumOfBuiltinLevels] = {
    "halfwayDone",
    "5a",
    "5b",
    "6a",
    "6b",
    "7a",
    "7b"
};

GameConfig getBuiltinLevel(int levelID) {
    assert(levelID >= 0);
    assert(levelID < NumOfBuiltinLevels);
    QString url = QString(":/Levels/Levels/%1.txt").arg(builtinLevels[levelID]);
    QFile file(url);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return GameConfig();
    }
    QTextStream stream(&file);
    return GameConfig(stream);
}

}
