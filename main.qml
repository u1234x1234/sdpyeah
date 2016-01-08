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
        Text {
            text: "Commands";
            font.bold: true;
        }
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
                onClicked: swapPages()
            }
        }
        Row {
            Button{
                text: "top"
                onClicked: ac.executeCommand("top -b -n 1")
            }
            Button{
                text: "nvidia-smi"
                onClicked: ac.executeCommand("nvidia-smi")
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
                text: "qe"
                font.pixelSize: parent.width * 0.02
                font.family: "Monospace"
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

