#ifndef COLOR_H
#define COLOR_H

#include "common.h"
#include <QColor>

namespace common {
    enum {
        NoIndex = -1
    };
    QColor getColor(common::VisibleItemID item, int subIndex = NoIndex);
}

#endif // COLOR_H

