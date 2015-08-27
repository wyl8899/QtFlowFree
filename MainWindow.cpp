#include "MainWindow.h"
#include "Scene.h"
#include "QGraphicsView"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 500);
    Scene* scene = new Scene(this);
    QGraphicsView* view = new QGraphicsView(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene->getScene());
    setCentralWidget(view);

    puzzle = nullptr;
}

MainWindow::~MainWindow()
{

}
