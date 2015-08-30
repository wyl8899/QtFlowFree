#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameConfig.h"
#include "Puzzle.h"
#include "Scene.h"
#include "Grid.h"
#include "Background.h"
#include "MouseDragCircle.h"
#include "View.h"
#include "GameWindow.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Scene* scene;
    Background* background;
    View* view;
};

#endif // MAINWINDOW_H
