import QtQuick 2.9
import QtMultimedia 5.9

CameraViewForm {
    exitBtn.onClicked: stackView.pop()
    server.onStatusChanged: statusLabel.text = status
    transfilter.onFrameReady: server.sendFrame(image)
    camera.onCameraStateChanged: {
        //set lowest possible resolution of camera
        if (camera.cameraState == Camera.ActiveState && server.frameRes == Qt.size(0, 0)) {
            var list = camera.supportedViewfinderResolutions()
            var i = 0;
            if (list.length > 0) {
                camera.viewfinder.resolution = Qt.size(list[i].width,
                                                       list[i].height)
                server.frameRes = camera.viewfinder.resolution
                console.log("Setup camera resolution: " + list[i].width + "x" + list[i].height)
            }
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
