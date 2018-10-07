#include "client.h"
#include <QtNetwork>
#include <QImage>

Client::Client(QObject *parent) : QObject(parent)
{
    mUdpSocket = new QUdpSocket(this);
    connect(mUdpSocket, SIGNAL(readyRead()), this, SLOT(readServerInfo()));

    mTcpSocket = new QTcpSocket(this);
    connect(mTcpSocket, &QAbstractSocket::connected, this, &Client::connected);
    connect(mTcpSocket, &QIODevice::readyRead, this, &Client::readFrame);
    connect(mTcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::socketError);

    mInputStream.setDevice(mTcpSocket);
    mInputStream.setVersion(QDataStream::Qt_5_10);

    mFrameSize = QSize(320, 240);
    mFrameBuf = new char[mFrameSize.width() * mFrameSize.height() * 4];
}

void Client::readServerInfo()
{
    while (mUdpSocket->state() == QUdpSocket::BoundState && mUdpSocket->hasPendingDatagrams())
    {
        QByteArray info;
        QHostAddress host;
        quint16 port;

        info.resize(static_cast<int>(mUdpSocket->pendingDatagramSize()));
        mUdpSocket->readDatagram(info.data(), info.size(), &host, &port);

        QString msg = QString(info);
        if (msg.contains("qtrcam_server"))
        {
            mUdpSocket->disconnectFromHost();
            mTcpSocket->abort();
            mTcpSocket->connectToHost(host, port, QIODevice::ReadOnly);
            QString res  = msg.split(" ")[1];
            int width = res.split("x")[0].toInt();
            int height = res.split("x")[1].toInt();
            mFrameSize = QSize(width, height);
            mFrameBuf = new char[width * height * 4];
        }
    }
}

void Client::connectToServer()
{
    QByteArray info = "qtrcam_client";
    mUdpSocket->writeDatagram(info.data(), info.size(), QHostAddress::Broadcast, 49111);
}

void Client::connected()
{
    qDebug() << "server connected";
}

void Client::readFrame()
{
    qint64 numBytes = mTcpSocket->bytesAvailable();
    mInputStream.startTransaction();
    mInputStream >> mFrameBuf;
    if (mInputStream.commitTransaction())
    {

        QByteArray uncombuf = qUncompress(reinterpret_cast<uchar*>(mFrameBuf), static_cast<int>(numBytes));
        QImage img(reinterpret_cast<uchar*>(uncombuf.data()), mFrameSize.width(), mFrameSize.height(), QImage::Format_RGBA8888);
        emit imageReady(img.rgbSwapped());
    }
}

void Client::socketError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "Host not found";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "Connection refused";
        break;
    default:
        qDebug() << "Socket error: " << mTcpSocket->errorString();
    }
}

