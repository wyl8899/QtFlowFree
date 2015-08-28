#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "paint_common.h"
#include <QObject>

class Background : public QObject {
    Q_OBJECT
public:
    Background(QObject* parent = 0);

    void paint();
};

#endif // BACKGROUND_H
