#include "MainWindow.h"
#include "Scene.h"
#include "View.h"

#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    scene = new Scene(this);
    puzzle = nullptr;
    grid = nullptr;
    background = nullptr;
    mouseDragCircle = nullptr;

    ui.setupUi(this);
    view = ui.view;
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene->getScene());
}

MainWindow::~MainWindow() {
    delete background;
    delete puzzle;
    delete grid;
    delete mouseDragCircle;
}

void MainWindow::startGame(GameConfig config) {
    auto gridSize = std::min(view->width(), view->height());
    grid = new Grid(gridSize, config.size, this);
    puzzle = new Puzzle(config, this);
    background = new Background(this);
    mouseDragCircle = new MouseDragCircle(this);
}
