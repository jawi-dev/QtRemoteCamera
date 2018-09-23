#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QImage>

class Server : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status)

public:
    explicit Server(QObject *parent = nullptr);
    QString status() const { return statusLabel; }

private slots:
    void newConnection();

public slots:
    void sendImage(QImage image);

private:
    QTcpServer *server = nullptr;
    QTcpSocket *connection = nullptr;
    QString statusLabel;
};

#endif
