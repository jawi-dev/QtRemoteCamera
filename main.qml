import QtQuick 2.6
import QtQuick.Window 2.2
import QtMultimedia 5.9
import CameraSurface 1.0
import CameraView 1.0

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

    /* Camera {
        objectName: "camera"
        id: camera
        // You can adjust various settings in here
    }*/

    Rectangle {
        x: 100
        y: 100
        width: 300
        height: 300
        color: "blue"

        /*VideoOutput {
            objectName: "videoOutput"
            source: cameraSurface
            anchors.fill: parent
        }*/

    }

    CameraView {
        objectName: "cameraView"
        x: 0
        y: 0
        width: 300
        height: 300
    }
}
