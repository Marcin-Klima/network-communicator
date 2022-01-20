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
                id: statusBar
                Layout.maximumHeight: 50
                Layout.columnSpan: 3
                Layout.fillHeight: true
                Layout.fillWidth: true

                RowLayout {
                    height: parent.height
                    spacing: 0
                    Button {
                        font.pointSize: 11
                        text: qsTr("START")
                        Layout.maximumWidth: 100
                        Layout.fillHeight: true
                        palette.button: "#52cc6e"
                    }
                    Button {
                        font.pointSize: 11
                        text: qsTr("STOP")
                        Layout.maximumWidth: 100
                        Layout.fillHeight: true
                        palette.button: "#cc5262"
                    }

                    Text {
                        text: qsTr("status:")
                        font.pointSize: 11
                        Layout.leftMargin: 20
                        Layout.margins: -1
                    }
                    Text {
                        text: qsTr("shutdown")
                        font.pointSize: 11
                        Layout.leftMargin: 20
                        Layout.margins: -1
                    }
                }
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
