import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

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
        visible: false
        enabled: false
        width: parent.width; height: parent.height
        Rectangle {
            id: footer
            height: parent.height * 0.1
            width: parent.width
            anchors.bottom: parent.bottom
            color: "yellow"

            Text {
                text: "back"
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: ac.backToHostsPage()
            }
        }
        Row {
            id: simpleCommands
            Button{
                text: "top"
                onClicked: ac.executeCommand("top -b -n 1")
            }
            Button{
                text: "nvidia-smi"
                onClicked: ac.executeCommand("nvidia-smi")
            }
        }
        Rectangle {
            anchors.top: simpleCommands.bottom
            anchors.topMargin: 20
            width: parent.width * 0.5
            height: parent.height * 0.3
            Button {
                id: printButton
                text: "print file"
                onClicked: ac.executeCommand("cat " + printInput.text)
            }
            Rectangle {
                height: printButton.height
                width: parent.width
                anchors.left: printButton.right
                border.color: "black"
                TextInput {
                    width: parent.width
                    id: printInput
                    objectName: "printInput"
                    text: "~/walmart/log"
                }
            }
        }

        Rectangle{
            color: "black"
            width: parent.width
            height: parent.height * 0.5
            anchors.bottom: footer.top
            TextArea {
                objectName: "textInput"
                anchors.fill: parent
                height: parent.height
                font.pixelSize: parent.width * 0.02
                textColor: "white"
                backgroundVisible: false
            }
        }
    }

    function swapPages(){
        print ("swap")
        commands.visible = hosts.visible
        commands.enabled = hosts.enabled
        hosts.visible = !commands.visible
        hosts.enabled = !commands.enabled
    }

}

