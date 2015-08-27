#ifndef VIEW_H
#define VIEW_H

#include "Grid.h"
#include "Puzzle.h"

#include <QGraphicsView>
#include <QMouseEvent>

class QGraphicsScene;

class View : public QGraphicsView {
    Q_OBJECT
public:
    explicit View(QWidget* parent = 0) : QGraphicsView(parent) {
    }

    void mousePressEvent(QMouseEvent* event) {
        Point pos = Grid::locate(event->pos());
        Puzzle::startDraw(pos);
    }

    void mouseMoveEvent(QMouseEvent* event) {
        Point pos = Grid::locate(event->pos());
        Puzzle::extendDraw(pos);
    }

    void mouseReleaseEvent(QMouseEvent* event) {
        Q_UNUSED(event);
        Puzzle::finishDraw();
    }
};

#endif // VIEW_H

