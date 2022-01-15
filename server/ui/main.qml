import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

import "./MessageHistoryBox.qml"
import "./MessageInputBox.qml"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1024
    height: 768
    title: qsTr("Server")
    color: "#000000"

    onClosing: {
        server.stopServer()
    }

    Connections {
        target: server
        onServerStarted: {
        }

        onServerStopped: {
            mainWindow.close()
        }
    }

    Rectangle {
        id: mainContainer
        color: "#000000"
        anchors.fill: parent
        anchors.margins: 5
        border.color: "#b42240"
        border.width: 3

        GridLayout {
            anchors.fill: parent
            columns: 3
            rows: 2

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.rowSpan: 2
            }


            MessageHistoryBox {
                id: messageHistoryBox
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.rowSpan: 2
            }

            MessageInputBox {
                id: messageInputBox
            }

        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
