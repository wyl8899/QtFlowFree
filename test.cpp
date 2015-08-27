#include "test.h"

namespace test {

typedef std::pair<Point, Point> Pair;

template<class T>
void inspect(T& t) {
    qDebug() << t.inspect();
}

// Test: at most one pipe of a specific color can exist at a time.
void Test0() {
    GameConfig config;
    config.size = 5;
    auto& points = config.points;
    points.push_back(Pair(Point(0, 0), Point(1, 1)));
    Puzzle puzzle(config);
    puzzle._startDraw(Point(1, 1));
    puzzle._finishDraw();
    inspect(puzzle);

    puzzle._startDraw(Point(0, 0));
    inspect(puzzle);
    puzzle._extendDraw(Point(0, 1));
    puzzle._extendDraw(Point(0, 2));
    puzzle._extendDraw(Point(0, 3));
    puzzle._extendDraw(Point(1, 3));
    puzzle._extendDraw(Point(1, 2));
    inspect(puzzle);
    puzzle._extendDraw(Point(0, 2));
    puzzle._finishDraw();
    inspect(puzzle);
    qDebug();
}

// Test: intercept
void Test1() {
    GameConfig config;
    config.size = 5;
    auto& points = config.points;
    points.push_back(Pair(Point(0, 1), Point(2, 1)));
    points.push_back(Pair(Point(1, 0), Point(1, 2)));
    Puzzle puzzle(config);
    puzzle._startDraw(Point(0, 1));
    puzzle._extendDraw(Point(1, 1));
    puzzle._extendDraw(Point(2, 1));
    puzzle._finishDraw();
    inspect(puzzle);

    puzzle._startDraw(Point(1, 0));
    puzzle._extendDraw(Point(1, 1));
    inspect(puzzle);
    puzzle._extendDraw(Point(1, 2));
    inspect(puzzle);
    puzzle._finishDraw();
    inspect(puzzle);

    puzzle._startDraw(Point(0, 1));
    puzzle._extendDraw(Point(1, 1));
    puzzle._extendDraw(Point(0, 1));
    puzzle._extendDraw(Point(0, 2));
    puzzle._extendDraw(Point(0, 3));
    puzzle._extendDraw(Point(1, 3));
    puzzle._extendDraw(Point(2, 3));
    puzzle._extendDraw(Point(2, 2));
    puzzle._extendDraw(Point(2, 1));
    puzzle._finishDraw();
    inspect(puzzle);

    qDebug();
}

void main() {
    Test0();
    Test1();
}

}
