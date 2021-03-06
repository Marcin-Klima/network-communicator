import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15

Rectangle {
    color: "#482020"
    Layout.fillHeight: true
    Layout.fillWidth: true

    function appendText(stringToAppend){
        outputTextArea.text = outputTextArea.text + stringToAppend
    }

    TextArea {
        id: outputTextArea
        anchors.fill: parent
        anchors.margins: 3
        font.pixelSize: 20
        wrapMode: Text.WordWrap
        readOnly: true
        color: "black"
        background: Rectangle{color:"transparent"}
    }
}
