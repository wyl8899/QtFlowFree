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
    window.startGame(config);

    return app.exec();
}
