#include "imageitem.h"
#include <QDebug>
#include <QPainter>

void ImageItem::setImage(const QImage &image)
{
    if (image == mImage)
        return;

    mImage = image;

    emit imageChanged();
    update();
}

void ImageItem::paint(QPainter *painter)
{
    if (mImage.isNull())
        return;

    painter->drawImage(boundingRect(), mImage, mImage.rect(), Qt::ImageConversionFlag::AutoColor);
}
