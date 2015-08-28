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
        Locator<Puzzle>()->startDraw(pos);
        Locator<MouseDragCircle>()->move(rawPos);
    }

    void mouseMoveEvent(QMouseEvent* event) {
        QPoint rawPos = event->pos();
        if (!Locator<Grid>()->isInside(rawPos))
            return;
        Point pos = Locator<Grid>()->locate(rawPos);
        Locator<Puzzle>()->extendDraw(pos);
        Locator<MouseDragCircle>()->move(rawPos);
    }

    void mouseReleaseEvent(QMouseEvent* event) {
        Q_UNUSED(event);
        Locator<Puzzle>()->finishDraw();
        Locator<MouseDragCircle>()->hide();
    }
};

#endif // VIEW_H

