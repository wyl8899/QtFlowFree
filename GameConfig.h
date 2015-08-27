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
            add(x, y, s, t);
        }
    }

    inline int numOfColors() {
        return points.size();
    }

    void add(int stX, int stY, int edX, int edY) {
        add(Point(stX, stY), Point(edX, edY));
    }

    void add(Point st, Point ed) {
        points.push_back(PointPair(st, ed));
    }

    int size;
    typedef std::pair<Point, Point> PointPair;
    std::vector<PointPair> points;
};

#endif // GAMECONFIG_H
