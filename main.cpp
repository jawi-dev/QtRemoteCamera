#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QCamera>
#include <QCameraInfo>

#include "transfilter.h"
#include "imageitem.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<TransFilter>("TransFilter", 1, 0, "TransFilter");
    qmlRegisterType<ImageItem>("ImageItem", 1, 0, "ImageItem");
    qmlRegisterType<Server>("Server", 1, 0, "Server");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
