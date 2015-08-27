#include "MainWindow.h"
#include "GameConfig.h"
#include "Puzzle.h"
#include "test.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    GameConfig config;
    config.size = 5;
    window.startGame(config);

    config.add(1, 0, 1, 2);
    config.add(0, 1, 2, 1);
    Puzzle puzzle(config);

    /*
    puzzle._startDraw(Point(1, 1));
    puzzle._extendDraw(Point(1, 0));
    puzzle._extendDraw(Point(0, 0));
    puzzle._finishDraw();
    */

    return app.exec();
}
