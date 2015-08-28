#include "predefinedColor.h"
#include <QColor>

namespace common {
    QColor getIndexColor(int index) {
        static const char* colors[] = {
            "red",
            "yellow",
            "blue",
            "lightskyblue",
            "orange",
            "pink",
            "purple",
            "royalblue",
            "plum",
            "darkviolet"
        };
        static const int colorsSize = sizeof(colors) / sizeof(colors[0]);
        if (index < colorsSize) {
            return QColor(QString(colors[index]));
        } else {
            // Run out of colors, use grayscale
            return QColor(index, index, index);
        }
    }

    QColor getIndexBgColor(int index) {
        QColor color = getIndexColor(index);
        color.setAlpha(100);
        return color;
    }

    QColor getColor(VisibleItemID item, int subIndex) {
        switch (item) {
        case Background: return QColor("black");
        case GridBgColor: return getIndexBgColor(subIndex);
        case GridLine: return QColor("white");
        case Circle:
        case PipeLine: return getIndexColor(subIndex);
        case MouseDragCircle: return QColor("#80FF0000");
        }
        return QColor(0, 0, 0);
    }
}
