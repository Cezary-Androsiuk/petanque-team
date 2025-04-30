import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: settings

    readonly property int headerHeight: 70

    Rectangle{
        anchors.fill: parent
        color: Material.backgroundColor
    }

    Item{
        id: header
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: settings.headerHeight

        Button{
            anchors{
                top: parent.top
                left: parent.left
                topMargin: 5
                leftMargin: 5
            }
            text: "Back"
            onClicked: {
                playStackView.pop();
            }
        }
    }


    Button{
        anchors{
            centerIn: parent
        }
        // width: 2*height
        text: "Restart event"
        onClicked: {
            rootLoader.source = "";
            Backend.restartEvent();
        }
    }
}
