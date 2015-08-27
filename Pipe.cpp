#include "Pipe.h"
#include "Strategy.h"

void Pipe::paintLines() {
    std::vector<QPoint> centers;
    for (auto& point : path) {
        if (isTemporarilyOccupied(point))
            break;
        centers.push_back(getCenter(point));
    }
    for (size_t i = 1; i < centers.size(); ++i) {
        QPoint& st = centers[i - 1];
        QPoint& ed = centers[i];
        paintLine(st, ed);
    }
}

bool Pipe::isTemporarilyOccupied(Point point) {
    if (state == Drawing)
        return false;
    else
        return strategy->isTemporarilyOccupied(point);
}
