#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameConfig.h"
#include "Puzzle.h"
#include "Scene.h"
#include "Grid.h"
#include "Background.h"

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
};

#endif // MAINWINDOW_H
