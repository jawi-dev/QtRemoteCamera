#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QQuickPaintedItem>
#include <QPainter>
#include "camerasurface.h"

class CameraView : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit CameraView(QQuickPaintedItem *parent = nullptr);
    void paint(QPainter *painter);

signals:

public slots:

private:
    CameraSurface *surface;
};

#endif // CAMERAVIEW_H
