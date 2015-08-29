#ifndef VIEW_H
#define VIEW_H

#include "common.h"
#include "Grid.h"
#include "Puzzle.h"
#include "MouseDragCircle.h"

#include <QGraphicsView>
#include <QMouseEvent>

class QGraphicsScene;

class View : public QGraphicsView, private LocatorRegister<View> {
    Q_OBJECT
public:
    explicit View(QWidget* parent = 0);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
};

#endif // VIEW_H

