#ifndef VIEW_H
#define VIEW_H

#include "Grid.h"
#include "Puzzle.h"
#include "MouseDragCircle.h"

#include <QGraphicsView>
#include <QMouseEvent>

class QGraphicsScene;

class View : public QGraphicsView {
    Q_OBJECT
public:
    explicit View(QWidget* parent = 0) : QGraphicsView(parent) {
    }

    void mousePressEvent(QMouseEvent* event) {
        QPoint rawPos = event->pos();
        Point pos = Locator<Grid>()->locate(rawPos);
        Puzzle::startDraw(pos);
        MouseDragCircle::move(rawPos);
    }

    void mouseMoveEvent(QMouseEvent* event) {
        QPoint rawPos = event->pos();
        if (!Locator<Grid>()->isInside(rawPos))
            return;
        Point pos = Locator<Grid>()->locate(rawPos);
        Puzzle::extendDraw(pos);
        MouseDragCircle::move(rawPos);
    }

    void mouseReleaseEvent(QMouseEvent* event) {
        Q_UNUSED(event);
        Puzzle::finishDraw();
        MouseDragCircle::hide();
    }
};

#endif // VIEW_H

