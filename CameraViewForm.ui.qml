import QtQuick 2.6
import QtQuick.Controls 2.2
import ImageItem 1.0
import QtMultimedia 5.9
import TransFilter 1.0
import Server 1.0

Item {
    id: item1
    anchors.fill: parent
    property alias statusLabel: statusLabel

    Rectangle {
        id: rectangle
        color: "#8d8892"
        anchors.fill: parent
    }

    Camera {
        id: camera
        objectName: "camera"
        viewfinder.resolution: "640x480"
    }

    ImageItem {
        id: cameraImage
        height: 100
        z: 1
        fillColor: "#000000"
        width: 100
        x: 0
        y: 0
    }

    Text {
        id: statusLabel
        //        text: server.status
        font.family: "Helvetica"
        font.pointSize: 14
        color: "red"
        anchors.right: parent.right
    }

    VideoOutput {
        id: output
        anchors.leftMargin: 40
        anchors.topMargin: 246
        anchors.rightMargin: 227
        anchors.bottomMargin: 50
        source: camera
        filters: [transfilter]
        anchors.fill: parent
        autoOrientation: true
    }

    TransFilter {
        id: transfilter
        onFinished: cameraImage.image = image
    }

    Server {
        id: server
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:30;anchors_height:200;anchors_width:200;anchors_x:53;anchors_y:108}
D{i:21;anchors_height:100;anchors_width:100;anchors_x:0;anchors_y:0}
}
 ##^##*/
