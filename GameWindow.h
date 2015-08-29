#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "paint_common.h"
#include "GameConfig.h"
#include "Grid.h"
#include "Puzzle.h"
#include "MouseDragCircle.h"
#include "View.h"
#include "FlowFreeWindowBase.h"
#include "ClickableText.h"

#include <QObject>

class GameWindow : public QObject, public FlowFreeWindowBase, private LocatorRegister<GameWindow> {
    Q_OBJECT

public:
    explicit GameWindow(GameConfig config, QObject* parent = 0);
    ~GameWindow();

    Mode mode() {
        return common::GameWindow;
    }

private:
    Puzzle* puzzle;
    Grid* grid;
    MouseDragCircle* mouseDragCircle;
    ItemList* itemList;
};

#endif // GAMEWINDOW_H
