#include "MainWindow.h"
#include "GameConfig.h"
#include "Puzzle.h"

#include <QApplication>
#include <QDebug>

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
    puzzle.startDraw(Point(1, 1));
    puzzle.finishDraw();
    inspect(puzzle);

    puzzle.startDraw(Point(0, 0));
    inspect(puzzle);
    puzzle.extendDraw(Point(0, 1));
    puzzle.extendDraw(Point(0, 2));
    puzzle.extendDraw(Point(0, 3));
    puzzle.extendDraw(Point(1, 3));
    puzzle.extendDraw(Point(1, 2));
    inspect(puzzle);
    puzzle.extendDraw(Point(0, 2));
    puzzle.finishDraw();
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
    puzzle.startDraw(Point(0, 1));
    puzzle.extendDraw(Point(1, 1));
    puzzle.extendDraw(Point(2, 1));
    puzzle.finishDraw();
    inspect(puzzle);

    puzzle.startDraw(Point(1, 0));
    puzzle.extendDraw(Point(1, 1));
    inspect(puzzle);
    puzzle.extendDraw(Point(1, 2));
    inspect(puzzle);
    puzzle.finishDraw();
    inspect(puzzle);

    puzzle.startDraw(Point(0, 1));
    puzzle.extendDraw(Point(1, 1));
    puzzle.extendDraw(Point(0, 1));
    puzzle.extendDraw(Point(0, 2));
    puzzle.extendDraw(Point(0, 3));
    puzzle.extendDraw(Point(1, 3));
    puzzle.extendDraw(Point(2, 3));
    puzzle.extendDraw(Point(2, 2));
    puzzle.extendDraw(Point(2, 1));
    puzzle.finishDraw();
    inspect(puzzle);

    qDebug();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Test0();
    Test1();
    return 0;
}
