#include "GameConfig.h"

#include <QDebug>

GameConfig::GameConfig() {
}

GameConfig::GameConfig(QTextStream& stream) {
    int numOfColors;
    stream >> size >> numOfColors;
    for (int i = 0; i < numOfColors; ++i) {
        int x, y, s, t;
        stream >> x >> y >> s >> t;
        add(x, y, s, t);
    }
}
