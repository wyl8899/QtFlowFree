#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "common.h"
#include "GameConfig.h"
#include "Grid.h"
#include "Puzzle.h"
#include "MouseDragCircle.h"
#include "View.h"
#include "FlowFreeWindowBase.h"
#include <QObject>

class GameWindow : public QObject, public FlowFreeWindowBase, private LocatorRegister<GameWindow> {
    Q_OBJECT
public:
    explicit GameWindow(GameConfig config, QObject* parent = 0) : QObject(parent) {
        auto view = Locator<View>();
        auto gridSize = std::min(view->width(), view->height());
        grid = new Grid(gridSize, config.size, this);
        puzzle = new Puzzle(config, this);
        mouseDragCircle = new MouseDragCircle(this);
    }

    ~GameWindow(){
        delete mouseDragCircle;
        delete puzzle;
        delete grid;
    }

    Mode mode() {
        return common::GameWindow;
    }

private:
    Puzzle* puzzle;
    Grid* grid;
    MouseDragCircle* mouseDragCircle;
};

#endif // GAMEWINDOW_H
