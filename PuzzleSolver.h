#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include "common.h"
#include "GameConfig.h"
#include "Pipe.h"

#include <QObject>

class GameWindow;

class PuzzleSolver : public QObject {
    Q_OBJECT
public:
    explicit PuzzleSolver(GameConfig config, GameWindow* window, QObject* parent = 0) : QObject(parent) {
        this->config = config;
        this->window = window;
    }
    std::vector<std::vector<Point>>& getPaths() {
        return paths;
    }

private:
    GameConfig config;
    GameWindow* window;
    std::vector<std::vector<Point>> paths;

    void init();
    void dfs(int currentColor);
    void dfsPath(int currentColor, int x, int y);
    void check();
    void dumpResult();

signals:
    void done();

public slots:
    void solve();
};

#endif // PUZZLESOLVER_H
