#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include "Locator.h"

namespace common {
    enum VisibleItemID {
        Background,
        GridBgColor,
        GridLine,
        Circle,
        PipeLine,
        MouseDragCircle
    };

    namespace PredefinedSize {
        const int SceneWidth = 500;
        const int SceneHeight = 650;
        const qreal PipeWidthOverGridSize = 0.35;
        const qreal CircleSizeOverGridSize = 0.85;
        const int MouseDragCircleSize = 156;
    }

    enum WindowMode {
        MainMenuWindow,
        GameWindow
    };
}

#endif // COMMON_H
