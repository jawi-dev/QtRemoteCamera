#ifndef TRANSFILTER_H
#define TRANSFILTER_H

#include <QAbstractVideoFilter>
#include <QOpenGLContext>

class TransFilter : public QAbstractVideoFilter
{
    Q_OBJECT
public:
    explicit TransFilter(QObject *parent = nullptr);
    QVideoFilterRunnable *createFilterRunnable();

signals:
    void finished(QImage image);

public slots:
private:
    QImage mImage;
};

class TransFilterRunnable : public QVideoFilterRunnable
{
public:
    TransFilterRunnable(TransFilter *filter) : mFilter(filter) {}
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

private:
    TransFilter *mFilter;
    QImage mLastFrame;
};

#endif // TRANSFILTER_H
