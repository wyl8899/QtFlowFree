#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include <Locator.h>

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
        const int SceneSize = 500;
        const qreal PipeWidthOverGridSize = 0.35;
        const qreal CircleSizeOverGridSize = 0.85;
        const int MouseDragCircleSize = 156;
    }
}

#endif // COMMON_H
