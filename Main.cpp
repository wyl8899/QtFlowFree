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


    /*
    puzzle._startDraw(Point(1, 1));
    puzzle._extendDraw(Point(1, 0));
    puzzle._extendDraw(Point(0, 0));
    puzzle._finishDraw();
    */

    return app.exec();
}
