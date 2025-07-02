import QtQuick 2.15
import QtQuick.Controls.Material

import "../../Trace.js" as Trace

Item {
    anchors.fill: parent

    property var roundVar
    property int headerHeight
    property int footerHeight

    ListView{
        id: matchListView
        anchors.fill: parent

        model: roundVar.matches
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

        ScrollBar.vertical: ScrollBar{
            policy: ScrollBar.AsNeeded
        }

        footer: Item{
            width: matchListView.width
            height: 50
        }

        delegate: Item{
            width: matchListView.width
            height: content.delegateHeaderHeight +
                    match.height +
                    content.delegateFooterHeight +
                    (delegateContent.anchors.margins * 2) +
                    (matchContent.anchors.margins * 2)

            Item{
                id: delegateContent
                anchors{
                    fill: parent
                    margins: 10
                }

                Rectangle{
                    id: delegateContentBackground
                    anchors.fill: parent
                    opacity: 0.2
                    color: {
                        if(roundVar.currentRoundStage === 6)
                            "#1c1b1f";
                        else
                            roundVar.currentRoundStage % 2 === 0 ?
                                        "#545467" :
                                        "#864E2E";
                    }
                }

                Item{
                    id: delegateHeader
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }
                    height: content.delegateHeaderHeight

                    Item{
                        id: leftTeamNameHeader
                        anchors{
                            top: parent.top
                            topMargin: 10
                            left: parent.left
                            leftMargin: 10
                            bottom: parent.bottom
                        }
                        width: parent.width/2 - anchors.leftMargin*2

                        Label{
                            id: leftTeamName
                            anchors.centerIn: parent
                            height: 50
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter

                            text: modelData.teamLeft.name
                        }

                        Rectangle{
                            anchors.fill: parent
                            color: "transparent"
                            border.color: Qt.rgba(1,1,1, 0.4)
                            border.width: 1
                        }
                    }

                    Item{
                        id: rightTeamNameHeader
                        anchors{
                            top: parent.top
                            topMargin: 10
                            right: parent.right
                            rightMargin: 10
                            bottom: parent.bottom
                        }
                        width: parent.width/2 - anchors.rightMargin*2

                        Label{
                            id: rightTeamName
                            anchors.centerIn: parent
                            height: 50
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter

                            text: modelData.teamRight.name
                        }

                        Rectangle{
                            anchors.fill: parent
                            color: "transparent"
                            border.color: Qt.rgba(1,1,1, 0.4)
                            border.width: 1
                        }
                    }
                }

                Item{
                    id: matchContent
                    anchors{
                        top: delegateHeader.bottom
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                        margins: 10
                    }

                    Match{
                        id: match
                        anchors{
                            top: parent.top
                            left: parent.left
                            right: parent.right
                        }

                        matchVar: modelData
                        currentRoundStage: roundVar.currentRoundStage
                    }
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
}
