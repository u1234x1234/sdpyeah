import QtQuick 2.0
import QtQuick.Controls 1.4

Item{
    objectName: "hostsPage"

    function openPopup() {
        hosts.opacity = 0.5
        hosts.enabled = false
        popup.opacity = 1
        popup.visible = true
    }

    function closePopup(id) {
        hosts.opacity = 1
        hosts.enabled = true
        id.opacity = 0
        id.visible = false
    }

    function connectionError() {
        hosts.opacity = 0.5
        hosts.enabled = false
        popup2.opacity = 1
        popup2.visible = true
    }

    property int selected: 0

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
            color: "#FFFF00"
            Text {
                text: "Hosts";
                anchors.centerIn: parent
                font.bold: true;
            }
        }

        Rectangle {
            id: viewRect
            anchors.top: header.bottom
            anchors.bottom: addHosts.top
            width: parent.width
            z: 1
            color: "black"

            ListView {
                id: listView
                anchors.fill: parent
                model: appModel
                spacing: parent.height * 0.02

                delegate: Rectangle {
                    width: parent.width
                    height: hosts.height * 0.2
                    border.color: "black"
                    color: "yellow"
                    MouseArea {
                        anchors.fill: parent
                        onPressAndHold: {
                            parent.ListView.view.currentIndex = index
                            openPopup()
                        }
                    }
                    Rectangle {
                        y: parent.height * 0.075
                        width: parent.width * 0.7
                        height: parent.height * 0.4
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width * 0.03
                        border.color: "red"
                        radius: 5

                        TextInput {
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width
                            text: model.host
                            anchors.verticalCenter: parent.verticalCenter
                            onTextChanged: appModel.setHost(index, text)
                        }
                    }
                    Rectangle {
                        y: parent.height * 0.5
                        width: parent.width * 0.7
                        height: parent.height * 0.4
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width * 0.03
                        border.color: "red"
                        radius: 5

                        TextInput {
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            text: model.password
                            echoMode: TextInput.Password
                            onTextChanged: appModel.setPassword(index, text)
                        }
                    }

                    Rectangle {
                        id: connectHost
                        width: parent.height * 0.6
                        height: parent.height * 0.4
                        radius: parent.width * 0.1
                        color: "#DD0000"
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.rightMargin: parent.width * 0.05
                        Text {
                            anchors.centerIn: parent
                            text: "connect"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: ac.connectToHost(index)
                        }
                    }
                }
            }
        }
        Rectangle {
            id: addHosts
            width: parent.width
            height: parent.height * 0.1
            color: "yellow"
            anchors.bottom: parent.bottom
            z: 2

            Text {
                anchors.centerIn: parent
                text: "Add new host"
                font.family: "Decorative"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ac.addConnection()
                }
            }
        }
    }

    Rectangle
    {
        id: popup
        color: "darkgreen"
        width: parent.width * 0.7
        height: parent.height * 0.4
        opacity: 0
        visible: false
        z: 5
        Behavior on opacity { NumberAnimation { duration: 500 } }

        anchors
        {
            centerIn:parent
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * 0.4
            width: parent.width * 0.8
            height: parent.height * 0.2
            text: "Delete host"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ac.removeConnection(listView.currentIndex)
                    closePopup(popup)
                }
            }
        }
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * 0.7
            width: parent.width * 0.8
            height: parent.height * 0.2
            text: "Back"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    closePopup(popup)
                }
            }
        }
    }

    Rectangle
    {
        id: popup2
        color: "darkred"
        width: parent.width * 0.7
        height: parent.height * 0.4
        opacity: 0
        visible: false
        z: 5
        Behavior on opacity { NumberAnimation { duration: 500 } }

        anchors.centerIn: parent
        Text {
            anchors.centerIn: parent
            text: "Could not connect to host"
            font.pixelSize: parent.width * 0.07
        }
        MouseArea{
            anchors.fill: parent
            onClicked: closePopup(popup2)
        }
    }
}
