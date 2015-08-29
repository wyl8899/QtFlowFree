#include "predefinedColor.h"
#include <QColor>

namespace common {
    QColor getIndexColor(int index) {
        static const char* colors[] = {
            "red",
            "yellow",
            "blue",
            "green",
            "orange",
            "lightskyblue",
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

    QColor getIndexGridBgColor(int index) {
        QColor color = getIndexColor(index);
        color.setAlpha(150);
        return color;
    }

    QColor getIndexMouseDragCircleColor(int index) {
        QColor color = getIndexColor(index);
        color.setAlpha(100);
        return color;
    }

    QColor getColor(VisibleItemID item, int subIndex) {
        switch (item) {
        case Background: return QColor("black");
        case Text: break;
        case GridBgColor: return getIndexGridBgColor(subIndex);
        case GridLine: return QColor("yellow").lighter();
        case Circle:
        case PipeLine: return getIndexColor(subIndex);
        case MouseDragCircle: return getIndexMouseDragCircleColor(subIndex);
        }
        return QColor(0, 0, 0);
    }
}
