import QtQuick 2.4

RemoteViewForm {
    connectBtn.onClicked: client.connectToServer()
    exitBtn.onClicked: stackView.pop()
    client.onImageReady: serverImage.image = image
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
