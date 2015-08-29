#ifndef COLOR_H
#define COLOR_H

#include "common.h"
#include <QColor>

namespace common {
    enum {
        NoIndex = -1
    };

    enum {
        NumOfPredefinedColors = 11
    };

    extern const char* predefinedColors[NumOfPredefinedColors];

    QColor getColor(common::VisibleItemID item, int subIndex = NoIndex);
}

#endif // COLOR_H
