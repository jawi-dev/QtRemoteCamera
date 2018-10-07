#include "server.h"
#include <QtNetwork>

Server::Server(QObject *parent) : QObject(parent)
{
    mStatusLabel = "Uninitialized";
    mFrameTime = 0;
    mFrameRes = QSize(0, 0);

    mServer = new QTcpServer(this);
    if (!mServer->listen(QHostAddress::Any, 49111))
    {
        qDebug() << "Unable to start server: " << mServer->errorString();
        return;
    }

    connect(mServer, &QTcpServer::newConnection, this, &Server::newConnection);

    QString address;
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
    foreach (QHostAddress ip, ipList)
    {
        if (ip != QHostAddress::LocalHost && ip.toIPv4Address())
        {
            address = ip.toString();
            break;
        }
    }
    if (address.isEmpty())
        address = QHostAddress(QHostAddress::LocalHost).toString();

    mStatusLabel = QString("Listening on %1:%2").arg(address).arg(mServer->serverPort());

    mUdpSocket = new QUdpSocket(this);
    mUdpSocket->bind(mServer->serverPort(), QUdpSocket::ShareAddress);
    connect(mUdpSocket, SIGNAL(readyRead()), this, SLOT(readClientInfo()));
}

void Server::readClientInfo()
{
    while (mUdpSocket->state() == QUdpSocket::BoundState && mUdpSocket->hasPendingDatagrams())
    {
        QByteArray info;
        QHostAddress host;
        quint16 port;

        info.resize(static_cast<int>(mUdpSocket->pendingDatagramSize()));
        mUdpSocket->readDatagram(info.data(), info.size(), &host, &port);

        QString msg = QString(info);
        if (msg.contains("qtrcam_client"))
        {
            msg = QString("qtrcam_server %1x%2").arg(mFrameRes.width()).arg(mFrameRes.height());
            info.clear();
            info.append(msg);
            mUdpSocket->writeDatagram(info.data(), info.size(), host, port);
        }
    }
}

void Server::newConnection()
{
    mSocket = mServer->nextPendingConnection();
    mStatusLabel = "Connected to client";
    emit statusChanged(mStatusLabel);
}

void Server::sendFrame(QImage image)
{
    qint64 currTime = QDateTime::currentMSecsSinceEpoch();
    if (mSocket && mSocket->state() == QAbstractSocket::ConnectedState && currTime - mFrameTime > 1000/10)
    {
        QByteArray outBuf;
        QDataStream outStream(&outBuf, QIODevice::WriteOnly);
        outStream.setVersion(QDataStream::Qt_5_10);
        QByteArray comBuf = qCompress(image.bits(), static_cast<int>(image.sizeInBytes()), 5);
        outStream.writeBytes(comBuf, static_cast<uint>(comBuf.size()));
        mSocket->write(outBuf);
        mSocket->waitForBytesWritten();
        mFrameTime = currTime;
    }
}
