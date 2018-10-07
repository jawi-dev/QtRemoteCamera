import QtQuick 2.6

SelectViewForm {
    button.onClicked: stackView.push("CameraView.qml")
    button1.onClicked: stackView.push("RemoteView.qml")
}
