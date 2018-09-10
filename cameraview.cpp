#include "cameraview.h"

CameraView::CameraView(QQuickPaintedItem *parent)
    : QQuickPaintedItem(parent)
{
    qDebug() << "CameraView constructor";

    surface = new CameraSurface(this);
    surface->setObjectName("cameraSurface");
}

void CameraView::paint(QPainter *painter)
{
    surface->paint(painter);
}
