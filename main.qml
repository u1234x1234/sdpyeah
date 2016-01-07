//import QtQuick 2.3
//import QtQuick.Window 2.2

//Window {
//    visible: true
//    width: 700
//    height: 700

//    TextEdit {
//        id: textField
//        //        text:
//    }

//    Rectangle {
//        id: rectangle1
//        x: 0
//        y: 0
//        width: 400
//        height: 99
//        color: "#00ffff"

//        MouseArea {
//            id: mouseArea1
//            anchors.fill: parent
//            onClicked: {
//                ac.func(5)
////                textInput1.text = "qwe"
//            }
//        }

//        Text {
//            id: text1
//            x: 187
//            y: 42
//            text: qsTr("ls")
//            font.pixelSize: 12
//        }
//    }

//    Text {
//        id: textInput1
//        objectName: "textInput"
//        text: "qwe\nqwe"
//        x: 86
//        y: 162
//        width: 228
//        height: 143
//        font.pixelSize: 12
//    }
//}

import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Window 2.2

Window {
    visible: true
    id: root
    width: 320
    height: 480

    Hosts {
        id: hosts
        width: parent.width; height: parent.height
    }

    Rectangle {
        id: commands
        property int asd: 123
        visible: false
        enabled: false
        width: parent.width; height: parent.height
        Text { text: "Commands"; font.bold: true; }
    }

}

