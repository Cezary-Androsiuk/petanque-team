import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: match

    required property var matchVar
    readonly property var curMatchType: matchVar.currentMatchType

    width: parent.width
    height: (leftHalf.height > rightHalf.height) ? leftHalf.height : rightHalf.height

    Component.onCompleted: {
        curMatchType.initMatch()
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

            matchVar: match.curMatchType.matchLeft
            isLeft: true
        }

        MatchHalf{
            id: rightHalf
            anchors{
                top: parent.top
                right: parent.right
            }
            width: parent.width/2

            matchVar: match.curMatchType.matchRight
            isLeft: false
        }
    }
}
