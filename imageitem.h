#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QImage>
#include <QQuickPaintedItem>

class ImageItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
public:
    ImageItem(QQuickItem *parent = nullptr);
    QImage image() const;
    void setImage(const QImage &image);

    void paint(QPainter *painter);

public slots:
    void finished(QImage image) { m_image = image; }

signals:
    void imageChanged();
private:
    QImage m_image;
};
#endif // IMAGEITEM_H
