#include "Board.h"

Board* Board::singleton = nullptr;

QDebug operator<<(QDebug debug, const PointPair& pair) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "[" << pair.first << ", " << pair.second << "]";
    return debug;
}
