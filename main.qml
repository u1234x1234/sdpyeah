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
            onClicked: {
                ac.func(5)
//                textInput1.text = "qwe"
            }
        }

        Text {
            id: text1
            x: 187
            y: 42
            text: qsTr("ls")
            font.pixelSize: 12
        }
    }

    Text {
        id: textInput1
        objectName: "textInput"
        text: "qwe\nqwe"
        x: 86
        y: 162
        width: 228
        height: 143
        font.pixelSize: 12
    }
}
