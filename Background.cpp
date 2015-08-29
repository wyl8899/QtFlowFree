#include "Background.h"
#include "View.h"

#include <QGraphicsLineItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QThread>
#include <QDebug>

#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

Background::Background(QObject *parent) : QObject(parent) {
    paint();

    // Initial lines
    for (int i = 0; i < 4; ++i)
        addFloatingLine();

    auto thread = new QThread(this);
    auto timer = new QTimer();
    timer->setInterval(4000);
    timer->moveToThread(thread);
    connect(thread, SIGNAL(started()), timer, SLOT(start()));
    connect(timer, SIGNAL(timeout()), this, SLOT(addFloatingLine()));
    thread->start();
}

void Background::addFloatingLine() {
    auto floatingLine = new FloatingLine;
    auto line = floatingLine->lineItem;
    const int sceneWidth = common::PredefinedSize::SceneWidth;
    const int sceneHeight = common::PredefinedSize::SceneHeight;
    const int lineLength = sceneWidth;
    const int lineWidth = line->pen().width();
    const int extendedLineLength = lineLength + lineWidth; // RoundCap taken into account


    floatingLine->setParentItem(bgRect);

    auto animation = new QPropertyAnimation();
    animation->setTargetObject(floatingLine);
    animation->setDuration(30000);
    animation->setStartValue(-extendedLineLength);

    static int orientationSwitch = 0;

    if (orientationSwitch ^= 1) {
        // horizontal
        auto y = std::uniform_int_distribution<>(0, sceneWidth)(gen);
        line->setLine(0, y, lineLength, y);
        animation->setEndValue(sceneWidth + lineWidth);
        animation->setPropertyName("x");
    } else {
        // vertical
        auto x = std::uniform_int_distribution<>(0, sceneHeight)(gen);
        line->setLine(x, 0, x, lineLength);
        animation->setEndValue(sceneHeight + lineWidth);
        animation->setPropertyName("y");
    }

    int direction = std::uniform_int_distribution<>(0, 1)(gen);
    animation->setDirection(direction ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);

    animation->start();
}

void Background::paint() {
    itemList = new ItemList(this);
    auto viewRect = Locator<View>()->rect();
    bgRect = new QGraphicsRectItem(viewRect);
    auto itemID = common::VisibleItemID::Background;
    bgRect->setZValue(itemID);
    QColor color = common::getColor(itemID);
    bgRect->setPen(Qt::NoPen);
    bgRect->setBrush(QBrush(color));
    itemList->addItem(bgRect);
}

FloatingLine::FloatingLine(QGraphicsItem *parent) : QGraphicsObject(parent) {
    lineItem = new QGraphicsLineItem();
    int colorIndex = std::uniform_int_distribution<>(0, common::NumOfPredefinedColors - 1)(gen);
    auto color = QColor(common::predefinedColors[colorIndex]).darker(600);
    auto brush = QBrush(color);
    qreal width = 49;
    lineItem->setPen(QPen(brush, width, Qt::SolidLine, Qt::RoundCap));
}

QRectF FloatingLine::boundingRect() const {
    return lineItem->boundingRect();
}

void FloatingLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    lineItem->paint(painter, option, widget);
}
