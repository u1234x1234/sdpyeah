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

    ObjectModel {
        id: itemModel

        Hosts {
            width: view.width; height: view.height
        }
        Rectangle {
            width: view.width; height: view.height
            Text { text: "Commands"; font.bold: true; }
        }
    }

    ListView {
        id: view
        anchors { fill: parent; bottomMargin: 30 }
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 2000
        cacheBuffer: 200
    }

    Rectangle {
        width: root.width; height: 30
        anchors { top: view.bottom; bottom: parent.bottom }
        color: "gray"

        Row {
            anchors.centerIn: parent
            spacing: 20

            Repeater {
                model: itemModel.count

                Rectangle {
                    width: 10; height: 10
                    radius: 3
                    color: view.currentIndex == index ? "blue" : "white"

                    MouseArea {
                        width: 20; height: 20
                        anchors.centerIn: parent
                        onClicked: view.currentIndex = index
                    }
                }
            }
        }
    }
}

