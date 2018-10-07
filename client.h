#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QImage>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);    
    Q_INVOKABLE void connectToServer();
    void connected();

private slots:
    void readFrame();
    void socketError(QAbstractSocket::SocketError socketError);
    void readServerInfo();

signals:
    void imageReady(QImage image);

private:
    QTcpSocket *mTcpSocket = nullptr;
    QUdpSocket *mUdpSocket = nullptr;
    QDataStream mInputStream;
    char* mFrameBuf = nullptr;
    QSize mFrameSize;
};

#endif
