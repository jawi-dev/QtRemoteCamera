#include "server.h"
#include <QtNetwork>

Server::Server(QObject *parent) : QObject(parent)
{
    statusLabel = "Uninitialized";

    server = new QTcpServer(this);
    if (!server->listen())
    {
        qDebug()<<"Unable to start server: "<<server->errorString();
        return;
    }

    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);

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

    statusLabel = QString("Listening on %1:%2").arg(address).arg(server->serverPort());
    qDebug()<<statusLabel;
}

void Server::newConnection()
{
    connection = server->nextPendingConnection();
    statusLabel = "Connected to client";
}

void Server::sendImage(QImage image)
{
    qDebug()<<"Sending frame...";

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << image.bits();

    connection->write(block);
    connection->flush();
}
