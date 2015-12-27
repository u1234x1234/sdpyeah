import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            onClicked: ac.func(12)
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
