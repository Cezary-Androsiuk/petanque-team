import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selection

    required property var matchVar

    width: parent.width
    height: (leftHalf.height > rightHalf.height) ? leftHalf.height : rightHalf.height

    Component.onCompleted: {
        matchVar.currentMatchType.initSelection()
    }

    Item{
        id: selectionContent
        anchors.fill: parent

        SelectionHalf{
            id: leftHalf
            anchors{
                top: parent.top
                left: parent.left
            }
            width: parent.width/2

            selectionVar: matchVar.currentMatchType.selectionLeft
            team: matchVar.teamLeft
        }

        SelectionHalf{
            id: rightHalf
            anchors{
                top: parent.top
                right: parent.right
            }
            width: parent.width/2

            selectionVar: matchVar.currentMatchType.selectionRight
            team: matchVar.teamRight
        }
    }

}
