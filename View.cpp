#include "View.h"


View::View(QWidget *parent) : QGraphicsView(parent) {
}

void View::mousePressEvent(QMouseEvent *event) {
    QPointF rawPos = this->mapToScene(event->pos());
    if (Locator<Grid>()->isInside(rawPos)) {
        Point pos = Locator<Grid>()->locate(rawPos);
        Locator<Puzzle>()->startDraw(pos);
        Locator<MouseDragCircle>()->move(rawPos);
    }
}

void View::mouseMoveEvent(QMouseEvent *event) {
    QPointF rawPos = this->mapToScene(event->pos());
    if (Locator<Grid>()->isInside(rawPos)) {
        Point pos = Locator<Grid>()->locate(rawPos);
        Locator<Puzzle>()->extendDraw(pos);
        Locator<MouseDragCircle>()->move(rawPos);
    }
}

void View::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    Locator<Puzzle>()->finishDraw();
    Locator<MouseDragCircle>()->hide();
}
