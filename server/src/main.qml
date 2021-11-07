import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Minimal Qml")
    color: "#000000"

    onHeightChanged: {
        console.log("DUPA")
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
                    anchors.fill: parent
                    anchors.margins: 3
                    font.pixelSize: 20
                    text: "dupa"
                    wrapMode: Text.WordWrap
                    readOnly: true
                    backgroundVisible: false
                }
            }

            Rectangle {
                color: "#92e5a1"
                Layout.fillHeight: true
                Layout.fillWidth: true

                TextArea {
                    font.pixelSize: 20
                    anchors.fill: parent
                    anchors.margins: 3
                    backgroundVisible: false
                }
            }

        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
