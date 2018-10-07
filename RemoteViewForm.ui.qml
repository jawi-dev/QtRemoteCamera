import QtQuick 2.4
import QtQuick.Controls 2.2
import Client 1.0
import ImageItem 1.0

Item {
    property alias client: client
    property alias serverImage: serverImage
    property alias connectBtn: connectBtn
    property alias exitBtn: exitBtn

    Client {
        id: client
    }

    Rectangle {
        id: background
        color: "#b0b3b8"
        anchors.fill: parent
    }

    Rectangle {
        id: cameraFrame
        color: "#d0d0d0"
        anchors.bottomMargin: 8
        anchors.right: column.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 8
        anchors.leftMargin: 8
        anchors.topMargin: 8

        ImageItem {
            id: serverImage
            anchors.fill: parent
        }
    }

    Column {
        id: column
        spacing: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottomMargin: 8
        anchors.topMargin: 8
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        Button {
            id: connectBtn
            text: qsTr("Connect")
        }

        Button {
            id: exitBtn
            text: qsTr("Exit")
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
