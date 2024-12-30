import QtQuick 2.15

import "MatchType"

Item {
    id: groupSelection

    required property var matchVar

    width: parent.width
    height: (leftHalf.height > rightHalf.height) ? leftHalf.height : rightHalf.height

    Component.onCompleted: {
        matchVar.currentMatchType.initSelection()
    }

    Item{
        id: selectionContent
        anchors.fill: parent

        Item{
            id: leftHalfContainer
            anchors{
                top: parent.top
                left: parent.left
                bottom: parent.bottom
            }
            width: parent.width/2 - 10 /*margin*/

            SelectionHalf{
                id: leftHalf
                anchors{
                    top: parent.top
                    right: parent.right
                    left: parent.left
                }

                selectionVar: groupSelection.matchVar.currentMatchType.selectionLeft
                team: groupSelection.matchVar.teamLeft
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.4)
                border.width: 1
            }
        }


        Item{
            id: rightHalfContainer
            anchors{
                top: parent.top
                right: parent.right
                bottom: parent.bottom
            }
            width: parent.width/2 - 10 /*margin*/

            SelectionHalf{
                id: rightHalf
                anchors{
                    top: parent.top
                    right: parent.right
                    left: parent.left
                }

                selectionVar: groupSelection.matchVar.currentMatchType.selectionRight
                team: groupSelection.matchVar.teamRight
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.4)
                border.width: 1
            }
        }

    }
}
