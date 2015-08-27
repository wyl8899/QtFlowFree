#include "Point.h"

QDebug operator<<(QDebug debug, const Point& point) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "(" << point.x << ", " << point.y << ")";
    return debug;
}
