import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15

Rectangle {
    width: 458
    height: 277

    GridLayout {
        id: gridLayout
        x: 141
        y: 215
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 4
        columns: 2

        Text {
            id: text1
            text: qsTr("Username:")
            font.pixelSize: 22
            Layout.fillHeight: false
        }

        FormTextInput {
            sampleText: qsTr("Username")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: false
        }

        Text {
            id: text2
            text: qsTr("E-mail:")
            font.pixelSize: 22
            Layout.fillHeight: false
        }

        FormTextInput {
            sampleText: qsTr("E-mail")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: false
        }

        Text {
            id: text3
            text: qsTr("Password:")
            font.pixelSize: 22
            Layout.fillHeight: false
        }

        FormTextInput {
            hideContent: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: false
        }

        Text {
            id: text4
            text: qsTr("Reenter password:")
            font.pixelSize: 22
            Layout.fillHeight: false
        }

        FormTextInput {
            hideContent: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: false
        }

        RowLayout {
            id: columnLayout
            width: 100
            height: 100
            Layout.topMargin: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2

            Button {
                text: qsTr("Close")
                font.pointSize: 22
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Register")
                font.pointSize: 22
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }


}


