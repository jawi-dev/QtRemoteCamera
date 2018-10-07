#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QUdpSocket>
#include <QImage>

class Server : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QSize frameRes READ frameRes WRITE setFrameRes)

public:
    explicit Server(QObject *parent = nullptr);
    QString status() const { return mStatusLabel; }
    QSize frameRes() const { return mFrameRes; }
    void setFrameRes(QSize size) { mFrameRes = size; }
    Q_INVOKABLE void sendFrame(QImage image);

signals:
    void statusChanged(const QString &status);

private slots:
    void newConnection();
    void readClientInfo();

private:
    QTcpServer *mServer = nullptr;
    QTcpSocket *mSocket = nullptr;
    QUdpSocket *mUdpSocket;
    QString mStatusLabel;
    qint64 mFrameTime;
    QSize mFrameRes;
};

#endif
