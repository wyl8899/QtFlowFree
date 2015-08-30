#include "MainWindow.h"
#include "GameConfig.h"
#include "builtinLevels.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
