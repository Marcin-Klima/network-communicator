import QtQuick 2.12
import QtQuick.Layouts 1.1

Rectangle {
    id: formTextInput
    width: 244
    height: 55
    color: "#cecece"
    border.color: "#1c1c1c"
    border.width: 0
    property string sampleText: ""
    property bool hideContent: false

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: rectangle2
            color: "#cccccc"
            Layout.fillHeight: true
            Layout.fillWidth: true

            TextInput {
                id: textInput
                activeFocusOnTab: true
                onActiveFocusChanged: {
                    if(activeFocus) {
                        selectAll()
                    }
                }
                text: formTextInput.sampleText
                anchors.fill: parent
                font.pixelSize: 22
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                clip: true
                echoMode: formTextInput.hideContent ? TextInput.Password : TextInput.Normal
            }
        }

        Rectangle {
            id: rectangle
            width: 200
            height: 200
            color: "#9600ae"
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: 6
        }


    }
}
