#ifndef COMMON_H
#define COMMON_H

#include <QObject>

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
    }
}

#endif // COMMON_H
