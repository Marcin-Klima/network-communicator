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
        anchors.margins: 12

        GridLayout {
            anchors.fill: parent
            columns: 3
            rows: 2

            Rectangle {
                id: leftBox
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.rowSpan: 2

                ColumnLayout {
                    anchors.fill: parent

                    Button {
                        text: "TEST1"
                        height: 100
//                        anchors.fill: parent
                    }

                    Button {
                        text: "TEST2"
                        height: 100
//                        anchors.fill: parent
                    }
                }
            }

            MessageHistoryBox {
                id: messageHistoryBox
            }

            Rectangle {
                id: rightBox
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
