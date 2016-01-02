import QtQuick 2.0

Item{
    Rectangle {
        id: rectangle1
        width: 89
        height: 52
        Text { text: "Hosts"; anchors.fill: parent; font.bold: true; }
    }

    ListModel {
        id: appModel
        ListElement { name: "host 1"; }
        ListElement { name: "host 2"; }
    }

    Rectangle {
        anchors.top: rectangle1.bottom
        width: parent.width
        height: parent.height

        ListView {
            anchors.fill: parent
            model: appModel
            spacing: 10

            delegate: Rectangle {
                width: parent.width
                height: 50

                border.color: "black"

                Text {
                    text: name
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: parent.ListView.view.currentIndex = index
                }
            }
        }
    }
}
