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
        property int asd: 123
        visible: false
        enabled: false
        width: parent.width; height: parent.height
        Text {
            text: "Commands";
            font.bold: true;
        }
        Rectangle {
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
    }

    function swapPages(){
        print ("swap")
        commands.visible = hosts.visible
        commands.enabled = hosts.enabled
        hosts.visible = !commands.visible
        hosts.enabled = !commands.enabled
    }

}

