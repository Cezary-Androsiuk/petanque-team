import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: finish
    anchors.fill: parent

    readonly property int headerHeight: 70
    readonly property int footerHeight: 70

    Item{
        id: header
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: finish.headerHeight

        Label{
            id: titleLabel
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 5
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: qsTr("Event Summary")
            font.pixelSize: 30
        }
    }

    Item{
        id: footer
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: finish.footerHeight

        Button{
            anchors.centerIn: parent

            text: "end event"
            onClicked: {
                rootLoader.source = "";
                Backend.restartEvent();
            }
        }
    }
}
