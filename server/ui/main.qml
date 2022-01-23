import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

import "components"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1024
    height: 768
    title: qsTr("Server")
    color: "#000000"

    onClosing: {
        backend.stopServer()
    }

    Backend {
        id: backendComponent
    }

    Connections {
        target: backend
        onPrintMessage: {

        }
        onServerStarted: {
            backendComponent.isRunning = true
        }
        onServerStopped: {
            backendComponent.isRunning = false
            backendComponent.clientsConnected = 0
        }
        onClientConnected: {
            backendComponent.clientsConnected++
        }
    }

    Rectangle {
        id: mainContainer
        color: "#000000"
        anchors.fill: parent
        anchors.margins: 12

        GridLayout {
            anchors.fill: parent
            columns: 3
            rows: 2

            StatusBar {
                id: statusBar
            }

            Rectangle {
                id: leftBox
                color: "#00000000"
                Layout.fillHeight: true
                Layout.minimumWidth: 200
                Layout.rowSpan: 2
            }

            MessageHistoryBox {
                id: messageHistoryBox
            }

            Rectangle {
                id: rightBox
                color: "#00000000"
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.maximumWidth: 200
                Layout.rowSpan: 2
            }

            MessageInputBox {
                id: messageInputBox
            }
        }
    }
}
