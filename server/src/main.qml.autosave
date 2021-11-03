import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Minimal Qml")
    color: "#000000"

    onHeightChanged: {
        console.log("DUPA")
    }

    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            color: "#54DEFD"
            Layout.fillHeight: true
            Layout.fillWidth: true

            TextEdit {
                color: "#FFFBFA"
                anchors.fill: parent
                font.pointSize: 22
                selectionColor: "#8BD7D2"
            }
        }

        Rectangle {
            color: "#49C6E5"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
