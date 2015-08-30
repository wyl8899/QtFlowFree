#include "Strategy.h"
#include "ClickableText.h"


Strategy::Strategy(int numOfColors, QObject *parent) : QObject(parent) {
    pipes.resize(numOfColors);
    current = NoCurrentColor;
}

Strategy::~Strategy() {
}

void Strategy::paint() {
    for (auto &i : pipes) {
        if (i != nullptr)
            i->paint();
    }
}

QString Strategy::inspect() {
    QStringList list;
    for (int i = 0; i < numOfColors(); ++i) {
        Pipe* pipe = pipes[i];
        QString pipeStr = pipe == nullptr ? QString("No pipe") : pipe->inspect();
        list << QString("[%1%2]%3").arg(i).arg(i==current?"*":"").arg(pipeStr);
    }
    return QString("Strategy: [%1]").arg(list.join(", "));
}

bool Strategy::tryStartDraw(Point point) {
    if (tryStartDrawingAtStart(point))
        return true;
    if (tryStartDrawingAtMiddle(point))
        return true;
    // Not starting point nor occupied by existing pipes.
    // Fail.
    return false;
}

bool Strategy::isTemporarilyOccupied(Point point) {
    if (isDrawing()) {
        return currentPipe()->contains(point);
    } else {
        return false;
    }
}

void Strategy::startDraw(Point point) {
    if (tryStartDraw(point)) {
        paint();
    }
}

bool Strategy::shouldExtend(Point point) {
    if (Locator<Board>()->isStart(point) && Locator<Board>()->getIndex(point) != current)
        return false;
    else
        return true;
}

void Strategy::extendDraw(Point point) {
    if (isDrawing() && shouldExtend(point)) {
        currentPipe()->extend(point);
        paint();
    }
}

void Strategy::finishDraw() {
    if (!isDrawing())
        return;
    const std::vector<Point>& currentPoints = currentPipe()->points();
    currentPipe()->finish();
    for (auto point : currentPoints) {
        for (int i = 0; i < numOfColors(); ++i)
            if (i != current) {
                Pipe* pipe = pipes[i];
                if (pipe != nullptr)
                    pipe->intercept(point);
            }
    }
    current = NoCurrentColor;
    paint();

    checkWinningConditions();
}

void Strategy::startDrawAtStart(int color, Point point) {
    current = color;
    Pipe* &pipe = pipes[color];
    delete pipe;
    pipe = new Pipe(this, color, point, Locator<Board>()->getTheOther(color, point));
    pipe->setParent(this);
}

void Strategy::startDrawAtMiddle(int color, Point point) {
    current = color;
    currentPipe()->start(point);
}

bool Strategy::tryStartDrawingAtStart(Point point) {
    for (int i = 0; i < numOfColors(); ++i) {
        if (Locator<Board>()->isStart(point)) {
            startDrawAtStart(Locator<Board>()->getIndex(point), point);
            return true;
        }
    }
    return false;
}

bool Strategy::tryStartDrawingAtMiddle(Point point) {
    for (int i = 0; i < numOfColors(); ++i) {
        Pipe* pipe = pipes[i];
        if (pipe != nullptr && pipe->contains(point)) {
            startDrawAtMiddle(i, point);
            return true;
        }
    }
    return false;
}



void Strategy::checkWinningConditions() {
    for (int i = 0; i < numOfColors(); ++i) {
        Pipe* pipe = pipes[i];
        if (pipe == nullptr)
            return;
        if (!pipe->isConnected())
            return;
    }
    if (isFulfilled()) {
        notifyWin();
    } else {
        notifyHalfwayDone();
    }
}

bool Strategy::isFulfilled() {
    int total = 0;
    for (int i = 0; i < numOfColors(); ++i) {
        Pipe* pipe = pipes[i];
        total += pipe->points().size();
    }
    int boardSize = Locator<Board>()->getSize();
    return total == boardSize * boardSize;
}

void Strategy::notifyHalfwayDone() {
    drawNotifyRect("Halfway Done. Go on to fill the board!");
}

void Strategy::notifyWin() {
    drawNotifyRect("Good job!");
}

void Strategy::drawNotifyRect(QString _message) {
    auto itemList = new ItemList(this);

    auto rect = new QGraphicsRectItem;
    rect->setPen(QPen(QColor("white")));
    rect->setBrush(QBrush(QColor("black")));
    rect->setZValue(common::VisibleItemID::DialogRect);
    auto gridRect = Locator<Grid>()->getWholeGridRect();
    gridRect->setEnabled(false);

    auto text = new ClickableText();
    text->setHtml(R"(<p style="font-family:Arial;font-size:27px;color:white">Continue</p>)");
    Scene::setAlignHCenter(text);
    connect(text, &ClickableText::released, [itemList, gridRect](){
        itemList->clear();
        gridRect->setEnabled(true);
    });

    auto message = new ClickableText();
    message->setHtml(QString(R"(<p style="font-family:Arial;font-size:24px;color:white">%1</p>)").arg(_message));
    Scene::setAlignHCenter(message);

    int rectWidth = std::max(text->boundingRect().width() + 20, message->boundingRect().width());
    int rectHeight = 95;
    int textVMargin = 10;
    rect->setRect(0, 0, rectWidth, rectHeight);
    Scene::setAlignHCenter(rect);
    Scene::setAlignVCenter(rect);
    itemList->addItem(rect);

    text->setX(rect->mapFromScene(text->pos()).x());
    text->setY(rectHeight - textVMargin - text->boundingRect().height());

    message->setX(rect->mapFromScene(message->pos()).x());
    message->setY(textVMargin);
    message->setParentItem(rect);

    auto textRect = new QGraphicsRectItem(text->mapRectToParent(text->boundingRect()));
    textRect->setPen(QPen(QColor("white")));
    textRect->setBrush(QBrush(QColor("black")));
    textRect->setParentItem(rect);

    text->setPos(textRect->mapFromParent(text->pos()));
    text->setParentItem(textRect);
}
