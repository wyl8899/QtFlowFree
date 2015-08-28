#include "GameConfig.h"

GameConfig::GameConfig() {
}

GameConfig::GameConfig(const char *fileName) {
    std::ifstream fin(fileName);
    int numOfColors;
    fin >> size >> numOfColors;
    for (int i = 0; i < numOfColors; ++i) {
        int x, y, s, t;
        fin >> x >> y >> s >> t;
        add(x, y, s, t);
    }
}
