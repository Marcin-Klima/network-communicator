import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15

Rectangle {
    color: "#e5929f"
    Layout.maximumHeight: 70
    Layout.fillHeight: true
    Layout.fillWidth: true

    TextArea {
        id: inputTextArea
        font.pixelSize: 20
        anchors.fill: parent
        anchors.margins: 3
        color: "black"
        background: Rectangle{color:"transparent"}

        Keys.onReturnPressed: {
            if(text.length > 0) {
                server.receiveInputFromFrontend(text)
                clear()
            }
        }
        Keys.onEnterPressed: {
            console.log("DUPAAA")
        }
    }
}
