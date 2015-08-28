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
}

MainWindow::~MainWindow() {
    delete grid;
    delete background;
}
