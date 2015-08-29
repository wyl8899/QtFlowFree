#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameConfig.h"
#include "Puzzle.h"
#include "Scene.h"
#include "Grid.h"
#include "Background.h"
#include "MouseDragCircle.h"

#include "ui_MainWindow.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startGame(GameConfig config);
private:
    Puzzle* puzzle;
    Grid* grid;
    Scene* scene;
    Background* background;
    MouseDragCircle* mouseDragCircle;
    View* view;

    Ui_MainWindow ui;
};

#endif // MAINWINDOW_H
