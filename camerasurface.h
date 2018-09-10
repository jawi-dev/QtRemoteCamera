#ifndef CAMERASURFACE_H
#define CAMERASURFACE_H

#include <QtCore/QRect>
#include <QtGui/QImage>
#include <QtMultimedia/QAbstractVideoSurface>
#include <QtMultimedia/QVideoFrame>
#include <QQuickPaintedItem>

class CameraSurface : public QAbstractVideoSurface
 {
     Q_OBJECT
 public:
     explicit CameraSurface(QObject *parent = nullptr);

     QList<QVideoFrame::PixelFormat> supportedPixelFormats(
             QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
     bool isFormatSupported(const QVideoSurfaceFormat &format) const;

     bool start(const QVideoSurfaceFormat &format);
     void stop();

     bool present(const QVideoFrame &frame);

     QRect videoRect() const { return targetRect; }
     void updateVideoRect();

     void paint(QPainter *painter);

 private:
     QQuickPaintedItem *camView;
     QImage::Format imageFormat;
     QRect targetRect;
     QSize imageSize;
     QRect sourceRect;
     QVideoFrame currentFrame;
 };

#endif // CAMERASURFACE_H
