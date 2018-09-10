#include "camerasurface.h"
#include <QtMultimedia>
#include <QDebug>

 CameraSurface::CameraSurface(QObject *parent)
     : QAbstractVideoSurface(parent),
       imageFormat(QImage::Format_Invalid)
 {
     qDebug() << "CameraSurface constructor";

     this->camView = qobject_cast<QQuickPaintedItem*>(parent);
 }

 QList<QVideoFrame::PixelFormat> CameraSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
 {
     if (handleType == QAbstractVideoBuffer::NoHandle)
     {
         return QList<QVideoFrame::PixelFormat>()
                 << QVideoFrame::Format_RGB32
                 << QVideoFrame::Format_ARGB32
                 << QVideoFrame::Format_ARGB32_Premultiplied
                 << QVideoFrame::Format_RGB565
                 << QVideoFrame::Format_RGB555;
     }
     else
     {
         return QList<QVideoFrame::PixelFormat>();
     }
 }

 bool CameraSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
 {
     const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
     const QSize size = format.frameSize();

     return imageFormat != QImage::Format_Invalid
             && !size.isEmpty()
             && format.handleType() == QAbstractVideoBuffer::NoHandle;
 }

 bool CameraSurface::start(const QVideoSurfaceFormat &format)
 {
     const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
     const QSize size = format.frameSize();

     if (imageFormat != QImage::Format_Invalid && !size.isEmpty())
     {
         this->imageFormat = imageFormat;
         imageSize = size;
         sourceRect = format.viewport();

         QAbstractVideoSurface::start(format);

         updateVideoRect();

         return true;
     }
     else
     {
         return false;
     }
 }

 void CameraSurface::stop()
 {
     currentFrame = QVideoFrame();
     targetRect = QRect();
     QAbstractVideoSurface::stop();
 }

 bool CameraSurface::present(const QVideoFrame &frame)
 {
     if (surfaceFormat().pixelFormat() != frame.pixelFormat() || surfaceFormat().frameSize() != frame.size())
     {
         setError(IncorrectFormatError);
         stop();

         return false;
     }
     else
     {
         currentFrame = frame;
         camView->update();

         return true;
     }
 }

 void CameraSurface::updateVideoRect()
 {
     QSize size = surfaceFormat().sizeHint();
     size.scale(camView->size().boundedTo(size).toSize(), Qt::KeepAspectRatio);

     targetRect = QRect(QPoint(0, 0), size);
     targetRect.moveCenter(camView->contentsBoundingRect().center().toPoint());
 }

 void CameraSurface::paint(QPainter *painter)
 {
     if (currentFrame.map(QAbstractVideoBuffer::ReadOnly))
     {
         const QTransform oldTransform = painter->transform();
         painter->scale(-1, 1);
         painter->translate(-camView->width(), 0);

         QImage image(currentFrame.bits(), currentFrame.width(), currentFrame.height(), currentFrame.bytesPerLine(), imageFormat);
         painter->drawImage(targetRect, image, sourceRect);
         painter->setTransform(oldTransform);

         currentFrame.unmap();
     }
 }
