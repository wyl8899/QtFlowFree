#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <Point.h>

#include <vector>
#include <fstream>

struct GameConfig {
    GameConfig() {
    }

    GameConfig(const char* fileName) {
        std::ifstream fin(fileName);
        int numOfColors;
        fin >> size >> numOfColors;
        for (int i = 0; i < numOfColors; ++i) {
            int x, y, s, t;
            fin >> x >> y >> s >> t;
            Point st(x, y), ed(s, t);
            points.push_back(PointPair(st, ed));
        }
    }

    inline int numOfColors() {
        return points.size();
    }

    int size;
    typedef std::pair<Point, Point> PointPair;
    std::vector<PointPair> points;
};

#endif // GAMECONFIG_H
