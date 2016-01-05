import QtQuick 2.0

Item{
    id: hosts

    Rectangle {
        id: header
        anchors.top: parent.top
        z: 2
        width: parent.width
        height: parent.height * 0.1
        color: "yellow"
        Text { text: "Hosts"; anchors.fill: parent; font.bold: true; }
    }

    ListModel {
        id: appModel
        ListElement { name: "host 1"; }
        ListElement { name: "host 2"; }
    }

    Rectangle {
        id: viewRect
        anchors.top: header.bottom
        anchors.bottom: addHosts.top
        width: parent.width
        z: 1

        ListView {
            anchors.fill: parent
            model: appModel
            spacing: 10

            delegate: Rectangle {
                width: parent.width
                height: hosts.height * 0.2

                border.color: "black"

                Text {
                    text: name
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: parent.ListView.view.currentIndex = index
                }
                Rectangle {
                    width: parent.height * 0.4
                    height: parent.height * 0.4
                    color: "green"

                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: parent.width * 0.05
                    MouseArea {
                        anchors.fill: parent
                        onClicked: print(index)
                    }
                }
            }
        }
    }

    Rectangle {
        id: addHosts
        width: parent.width
        height: parent.height * 0.1
        color: "red"
        anchors.bottom: parent.bottom
        z: 2

        Text {
            anchors.fill: parent
            text: "add new host"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                appModel.append({"name":  "host 3"})
                print(1)
            }
        }
    }
}
