import QtQuick 2.6

SelectViewForm {
    button.onClicked: stackView.push("CameraViewForm.ui.qml")
    button1.onClicked: stackView.push("CameraViewForm.ui.qml")
}
