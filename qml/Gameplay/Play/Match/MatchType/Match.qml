import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: match

    required property var matchVar

    width: parent.width
    height: (leftHalf.height > rightHalf.height) ? leftHalf.height : rightHalf.height

    Component.onCompleted: {
        matchVar.currentMatchType.initMatch()
    }

    Item{
        id: matchContent
        anchors.fill: parent

        MatchHalf{
            id: leftHalf
            anchors{
                top: parent.top
                left: parent.left
            }
            width: parent.width/2

            matchVar: match.matchVar.currentMatchType.matchLeft
            team: match.matchVar.teamLeft
        }

        MatchHalf{
            id: rightHalf
            anchors{
                top: parent.top
                right: parent.right
            }
            width: parent.width/2

            matchVar: match.matchVar.currentMatchType.matchRight
            team: match.matchVar.teamRight
        }
    }
}
