#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QCamera>
#include <QCameraInfo>
#include "camerasurface.h"
#include "cameraview.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<CameraSurface>("CameraSurface", 1, 0, "CameraSurface");
    qmlRegisterType<CameraView>("CameraView", 1, 0, "CameraView");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *rootObject = engine.rootObjects().first();
    QObject *qmlObject = rootObject->findChild<QObject*>("cameraSurface");
    CameraSurface *surf = qobject_cast<CameraSurface*>(qmlObject);

    QCamera *camera = new QCamera(QCameraInfo::availableCameras()[0]);
    if (camera) {
        camera->setViewfinder(surf);
        camera->start();
    }

    return app.exec();
}
