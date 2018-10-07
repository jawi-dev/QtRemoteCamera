#include "transfilter.h"

#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>

extern QImage qt_imageFromVideoFrame(const QVideoFrame& f);

QVideoFilterRunnable *TransFilter::createFilterRunnable()
{
    return new TransFilterRunnable(this);
}

QVideoFrame TransFilterRunnable::run(QVideoFrame *frame, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);

    if (!frame->isValid() || (frame->handleType() != QAbstractVideoBuffer::NoHandle && frame->handleType() != QAbstractVideoBuffer::GLTextureHandle))
    {
        qDebug() << "Wrong frame=" << frame->handleType();
        return *frame;
    }

    if (frame->pixelFormat() == QVideoFrame::Format_YUV420P || frame->pixelFormat() == QVideoFrame::Format_YV12)
    {
        qDebug() << "YUV is not supported yet";
        return *frame;
    }

    QImage image;
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    if (frame->handleType() == QAbstractVideoBuffer::NoHandle)
    {
        image = qt_imageFromVideoFrame(*frame);
    }
    else if (frame->handleType() == QAbstractVideoBuffer::GLTextureHandle)
    {
        image = QImage(frame->width(), frame->height(), QImage::Format_RGBA8888);
        GLuint fbo, prevFbo;
        f->glBindTexture(GL_TEXTURE_2D, frame->handle().toUInt());
        f->glGenFramebuffers(1, &fbo);
        f->glGetIntegerv(GL_FRAMEBUFFER_BINDING, reinterpret_cast<GLint*>(&prevFbo));
        f->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame->handle().toUInt(), 0);
        f->glReadPixels(0, 0, frame->width(), frame->height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
        f->glBindFramebuffer(GL_FRAMEBUFFER, prevFbo);
#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
        image = image.rgbSwapped();
#endif
    }

    emit mFilter->frameReady(image);

    return *frame;
}
