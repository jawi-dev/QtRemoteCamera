import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

Window {
    id: mainWindow
    objectName: "mainWindow"
    visible: true
    width: 640
    height: 480
    title: qsTr("RemoteCamera")

    StackView {
        id: stackView
        initialItem: "SelectView.qml"
        anchors.fill: parent
        SelectView{}
    }
}
