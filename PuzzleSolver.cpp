#include "PuzzleSolver.h"
#include "Point.h"
#include "Puzzle.h"
#include "GameWindow.h"
#include "Strategy.h"
#include "Pipe.h"

#include <utility>
#include <QDebug>

static const int MaxN = 10;

static int size, colors;
static int _color[MaxN][MaxN];
static Point st[MaxN], ed[MaxN];
static Point nxt[MaxN][MaxN];

static int& color(int x, int y) {
    return _color[x][y];
}
static int& color(Point p) {
    return color(p.x, p.y);
}

static bool found;

void PuzzleSolver::solve() {
    found = false;
    init();
    dfs(0);
    dumpResult();
    emit done();
}

void PuzzleSolver::init() {
    size = config.size;
    colors = config.numOfColors();
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            color(i, j) = -1;
    for (int i = 0; i < colors; ++i) {
        std::pair<Point, Point> pair = config.points[i];
        st[i] = pair.first;
        ed[i] = pair.second;
        color(st[i]) = i;
        color(ed[i]) = i;
    }
}

static const int dx[] = {1, 0, -1, 0};
static const int dy[] = {0, 1, 0, -1};

static bool inside(int x) {
    return x >= 0 && x < size;
}

static bool inside(int x, int y) {
    return inside(x) && inside(y);
}

static bool isEnd(int k, int x, int y) {
    return Point(x, y) == ed[k];
}

void PuzzleSolver::dfsPath(int k, int x, int y) {
    // qDebug() << "dfsPath:" << k << x << y;
    if (isEnd(k, x, y)) {
        dfs(k + 1);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int tx = x + dx[i], ty = y + dy[i];
        if (!inside(x, y))
            continue;
        int& tc = color(tx, ty);
        if (tc != -1 && !isEnd(k, tx, ty))
            continue;
        tc = k;
        nxt[x][y] = Point(tx, ty);
        dfsPath(k, tx, ty);
        if (found)
            break;
        tc = -1;
    }
}

void PuzzleSolver::dfs(int k) {
    if (k == colors) {
        check();
        return;
    }
    Point p = st[k];
    dfsPath(k, p.x, p.y);
}

void PuzzleSolver::check() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (color(i, j) == -1)
                return;
    found = true;
}

void PuzzleSolver::dumpResult() {
    Puzzle* puzzle = window->puzzle;
    // std::vector<Pipe*>& pipes = Locator<Strategy>()->getPipes();
    for (int i = 0; i < colors; ++i) {
        Point p = st[i];
        puzzle->startDraw(p);
        while (p != ed[i]) {
            p = nxt[p.x][p.y];
            puzzle->extendDraw(p);
        }
        puzzle->finishDraw();
        qDebug() << puzzle->inspect();
    }
}
