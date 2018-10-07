import QtQuick 2.4
import QtQuick 2.6
import QtQuick.Controls 2.2

Item {
    id: item1
    property alias button: button
    property alias button1: button1

    Rectangle {
        id: rectangle
        x: 176
        y: 121
        width: 200
        height: 200
        color: "#1567b8"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: text1
            x: 232
            y: 152
            text: qsTr("Select role:")
            anchors.verticalCenterOffset: -80
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }

        Button {
            id: button
            x: 214
            y: 193
            text: qsTr("Camera")
            anchors.verticalCenterOffset: -27
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            id: button1
            x: 214
            y: 262
            text: qsTr("Remote")
            anchors.verticalCenterOffset: 42
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
