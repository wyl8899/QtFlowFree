#include "MainWindow.h"
#include "Scene.h"
#include "View.h"
#include "WindowSelector.h"
#include "MainMenuWindow.h"

#include <QGraphicsView>
#include <QDebug>
#include <QPushButton>
#include <QGraphicsProxyWidget>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setFixedWidth(common::PredefinedSize::SceneWidth);
    setFixedHeight(common::PredefinedSize::SceneHeight);

    scene = new Scene(this);

    view = new View(this);
    view->setGeometry(this->geometry());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene->getScene());
    view->setSceneRect(view->rect());

    background = new Background(this);

    auto mainMenuWindow  = new MainMenuWindow();
    WindowSelector::select(mainMenuWindow);
}

MainWindow::~MainWindow() {
    delete background;
    delete view;
}

void MainWindow::startGame(GameConfig config) {
    auto gameWindow = new GameWindow(config);
    WindowSelector::select(gameWindow);
}
