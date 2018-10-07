#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QImage>
#include <QQuickPaintedItem>

class ImageItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

public:
    explicit ImageItem(QQuickItem *parent = nullptr) : QQuickPaintedItem(parent) {}
    QImage image() const { return mImage; }
    void setImage(const QImage &image);
    void paint(QPainter *painter);

signals:
    void imageChanged();

private:
    QImage mImage;
};

#endif
