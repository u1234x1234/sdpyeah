import QtQuick 2.0

Item{
    Item {
        id: hosts
        opacity: 1
        layer.enabled: true
        anchors.fill: parent

        Behavior on opacity { NumberAnimation { duration: 500 } }

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
            ListElement { name: "host 1"; host: "hostname@192.168.1.192"; }
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

                    MouseArea {
                        anchors.fill: parent
                        onClicked: parent.ListView.view.currentIndex = index
                        onPressAndHold: {
                            hosts.opacity = 0.5
                            hosts.enabled = false
                            popup.opacity = 1
                            popup.visible = true

                        }
                    }
                    Rectangle {
                        width: parent.width * 0.7
                        height: parent.height * 0.4
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width * 0.03

                        border.color: "red"
                        radius: 5

                        TextInput {
                            anchors.fill: parent
                            text: host
                        }
                    }

                    Rectangle {
                        id: removeHost
                        width: parent.height * 0.4
                        height: parent.height * 0.4
                        color: "green"

                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.rightMargin: parent.width * 0.05
                        MouseArea {
                            anchors.fill: parent
                            onClicked: print(appModel.remove(index))
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
                    print(commands.asd)
                }
            }
        }
    }

    Rectangle
    {
        id: popup
        color: "darkgreen"
        width: 200
        height: 100
        opacity: 0
        visible: false
        z: 5

        Behavior on opacity { NumberAnimation { duration: 500 } }

        anchors
        {
            centerIn:parent
        }

        Text
        {
            anchors
            {
                centerIn:parent
            }
            font.family: "Segoe UI Light"
            font.pixelSize: 20
            text : "POPUP"
            color: "darkgrey"
        }

        MouseArea
        {
            anchors.fill: parent

            onClicked:
            {
                hosts.opacity = 1
                hosts.enabled = true
                popup.opacity = 0
                popup.visible = false
            }
        }
    }
}
