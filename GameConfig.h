#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <Point.h>

#include <vector>
#include <fstream>

struct GameConfig {
    GameConfig();
    GameConfig(const char* fileName);

    inline int numOfColors() {
        return points.size();
    }

    inline void add(int stX, int stY, int edX, int edY) {
        add(Point(stX, stY), Point(edX, edY));
    }

    inline void add(Point st, Point ed) {
        points.push_back(PointPair(st, ed));
    }

    int size;
    typedef std::pair<Point, Point> PointPair;
    std::vector<PointPair> points;
};

#endif // GAMECONFIG_H
