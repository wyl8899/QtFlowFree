#include "MainWindow.h"
#include "Scene.h"
#include "View.h"

#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    resize(500, 500);
    scene = new Scene(this);
    QGraphicsView* view = new View(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene->getScene());
    setCentralWidget(view);
    puzzle = nullptr;
    grid = nullptr;
    background = nullptr;
    mouseDragCircle = nullptr;
}

MainWindow::~MainWindow() {
    delete background;
    delete puzzle;
    delete grid;
    delete mouseDragCircle;
}

void MainWindow::startGame(GameConfig config) {
    grid = new Grid(this->width(), config.size, this);
    puzzle = new Puzzle(config, this);
    background = new Background(this);
    mouseDragCircle = new MouseDragCircle(this);
}
