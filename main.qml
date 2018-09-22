import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.9
import TransFilter 1.0
import ImageItem 1.0

Window {
    id: mainWindow
    objectName: "mainWindow"
    visible: true
    width: 640
    height: 480
    title: qsTr("RemoteCamera")

    Text {
        text: "CamView"
        font.family: "Helvetica"
        font.pointSize: 24
        color: "red"
    }

    Camera {
        id: camera
        objectName: "camera"
        viewfinder.resolution: "640x480"
    }

    VideoOutput {
        id: output
        source: camera
        filters: [ transfilter ]
        anchors.fill: parent
        autoOrientation: true
    }

    TransFilter {
        id: transfilter
        onFinished: { cameraImage.image = image }
    }

    ImageItem {
        id: cameraImage
        height: 100
        width: 100
        x: 0
        y: 0
    }


}
