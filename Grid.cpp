#include "Grid.h"
#include "Puzzle.h"
#include "MouseDragCircle.h"

Grid::Grid(int _pixelSize, int _size, QObject *parent) : QObject(parent) {
    pixelSize = _pixelSize;
    size = _size;
    init();
    paint();
}

Grid::~Grid() {
}

void Grid::init() {
    gridSize = (double)pixelSize / size;
    for (int i = 0; i <= size; ++i) {
        line.push_back((int)round(gridSize * i));
    }
}

void Grid::paintLine(int x1, int y1, int x2, int y2) {
    auto line = new QGraphicsLineItem(x1, y1, x2, y2);
    auto itemID = common::VisibleItemID::GridLine;
    QColor color = common::getColor(itemID);
    line->setPen(QPen(color));
    line->setParentItem(gridRect);
}

qreal Grid::getGridSize() {
    return gridSize;
}

GridRect *Grid::getWholeGridRect() {
    return gridRect;
}

void Grid::paint() {
    itemList = new ItemList(this);

    gridRect = new GridRect(QRect(0, 0, pixelSize, pixelSize));
    gridRect->setZValue(common::VisibleItemID::GridLine);
    gridRect->setFlag(QGraphicsItem::ItemHasNoContents);
    Scene::setAlignHCenter(gridRect);
    gridRect->setY(common::predefinedSize::SceneHeight * 0.1);
    itemList->addItem(gridRect);

    for (int i = 0; i <= size; ++i) {
        int pos = line[i];
        paintLine(0, pos, pixelSize, pos);
        paintLine(pos, 0, pos, pixelSize);
    }
}

bool Grid::isInside(QPointF point) {
    return isInside(point.x()) && isInside(point.y());
}

Point Grid::locate(QPointF point) {
    return Point(locate(point.x()), locate(point.y()));
}

QRectF Grid::getGridRect(Point point) {
    int x = point.x, y = point.y;
    auto localLeftTop = QPoint(line[x], line[y]);
    auto localRightBottom = QPoint(line[x+1], line[y+1]);
    auto sceneLeftTop = gridRect->mapToScene(localLeftTop);
    auto sceneRightBottom = gridRect->mapToScene(localRightBottom);
    return QRectF(sceneLeftTop, sceneRightBottom);
}

bool Grid::isInside(qreal x) {
    return x >= 0 && x <= pixelSize;
}

int Grid::locate(qreal x) {
    assert(isInside(x));
    for (int i = 0; i < size; ++i) {
        if (x <= line[i + 1])
            return i;
    }
    assert(false);
    return 0;
}


void GridRect::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    if (Locator<Grid>()->isInside(pos)) {
        Point point = Locator<Grid>()->locate(pos);
        Locator<Puzzle>()->startDraw(point);
        QPointF scenePos = mapToScene(pos);
        Locator<MouseDragCircle>()->move(scenePos);
    }
}

void GridRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    if (Locator<Grid>()->isInside(pos)) {
        Point point = Locator<Grid>()->locate(pos);
        Locator<Puzzle>()->extendDraw(point);
        QPointF scenePos = mapToScene(pos);
        Locator<MouseDragCircle>()->move(scenePos);
    }
}

void GridRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    Locator<Puzzle>()->finishDraw();
    Locator<MouseDragCircle>()->hide();
}
