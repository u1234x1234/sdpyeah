import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width: 400
    height: 400

    TextEdit {
        id: textField
        //        text:
    }

    Rectangle {
        id: rectangle1
        x: 0
        y: 0
        width: 400
        height: 99
        color: "#00ffff"

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: ac.func(5)
        }

        TextInput {
            id: textInput1
            x: 160
            y: 40
            width: 80
            height: 20
            text: qsTr("ls")
            font.pixelSize: 12
        }
    }
}
