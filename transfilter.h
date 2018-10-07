#ifndef TRANSFILTER_H
#define TRANSFILTER_H

#include <QAbstractVideoFilter>

class TransFilter : public QAbstractVideoFilter
{
    Q_OBJECT

public:
    explicit TransFilter(QObject *parent = nullptr) : QAbstractVideoFilter(parent) {}
    QVideoFilterRunnable *createFilterRunnable();

signals:
    void frameReady(QImage image);
};

class TransFilterRunnable : public QVideoFilterRunnable
{
public:
    TransFilterRunnable(TransFilter *filter) : mFilter(filter) {}
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

private:
    TransFilter *mFilter;
};

#endif
