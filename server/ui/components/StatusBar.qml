import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15

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
            id: startButton
            font.pointSize: 11
            text: qsTr("START")
            Layout.maximumWidth: 100
            Layout.fillHeight: true
            palette.button: "#52cc6e"
            onClicked: backend.startServer()
        }
        Button {
            id: stopButton
            font.pointSize: 11
            text: qsTr("STOP")
            Layout.maximumWidth: 100
            Layout.fillHeight: true
            palette.button: "#cc5262"
            onClicked: backend.stopServer()
        }
        Text {
            text: qsTr("status:")
            font.pointSize: 11
            Layout.leftMargin: 20
            Layout.margins: -1
        }
        Text {
            id: serverStatusText
            text: backendComponent.isRunning ? "running" : "shutdown"
            font.pointSize: 11
            Layout.leftMargin: 20
            Layout.margins: -1
        }
        RowLayout {
            visible: backendComponent.isRunning
            Text {
                text: qsTr("clients:")
                font.pointSize: 11
                Layout.leftMargin: 100
            }
            Text {
                font.pointSize: 11
                text: backendComponent.clientsConnected
                Layout.leftMargin: 20
                Layout.margins: -1
            }
        }
    }
}
