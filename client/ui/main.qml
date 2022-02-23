import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
//import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1024
    height: 768
    title: qsTr("Client")
    color: "#000000"

    onClosing: {
        backend.stop();
    }

    Connections {
        target: backend
        onMessageReceived: {
            outputTextArea.appendText(message)
        }
    }

    Rectangle {
        id: rectangle
        color: "#000000"
        anchors.fill: parent
        anchors.margins: 5
        border.color: "#22b455"
        border.width: 3

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10


            Rectangle {
                color: "#204829"
                Layout.fillHeight: true
                Layout.fillWidth: true

                TextArea {
                    id: outputTextArea
                    anchors.fill: parent
                    anchors.margins: 3
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                    readOnly: true
                    color: "black"
                    background: Rectangle{color:"transparent"}

                    function appendText(stringToAppend){
                        outputTextArea.text = outputTextArea.text + stringToAppend
                    }
                }
            }

            Rectangle {
                color: "#92e5a1"
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
                            backend.receiveInputFromFrontend(text)
                            clear()
                        }
                    }
                    Keys.onEnterPressed: {
                    }
                }
            }

        }
    }
}
