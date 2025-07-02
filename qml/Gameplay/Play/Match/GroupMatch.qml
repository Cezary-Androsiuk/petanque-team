import QtQuick 2.15

import "../../../Trace.js" as Trace

import "MatchType"

Item {
    id: groupMatch

    required property var matchVar
    readonly property var curMatchType: matchVar.currentMatchType

    width: parent.width
    height: (leftHalf.height > rightHalf.height) ? leftHalf.height : rightHalf.height

    Component.onCompleted: { Trace.t();
        curMatchType.initMatch()
    }

    Item{
        id: matchContent
        anchors.fill: parent

        Item{
            id: leftHalfContainer
            anchors{
                top: parent.top
                left: parent.left
                bottom: parent.bottom
            }
            width: parent.width/2 - 10 /*margin*/

            MatchHalf{
                id: leftHalf
                anchors{
                    top: parent.top
                    right: parent.right
                    left: parent.left
                }

                matchVar: groupMatch.curMatchType.matchLeft
                isLeft: true
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

            MatchHalf{
                id: rightHalf
                anchors{
                    top: parent.top
                    right: parent.right
                    left: parent.left
                }

                matchVar: groupMatch.curMatchType.matchRight
                isLeft: false
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
