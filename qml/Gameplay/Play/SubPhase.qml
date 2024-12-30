import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: subPhase

    required property var subPhaseVar
    readonly property var roundVar: subPhaseVar.rounds[subPhaseVar.currentRoundIndex]

    readonly property int headerHeight: 45
    readonly property int footerHeight: 70

    Item{
        id: header
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: subPhase.headerHeight

        Label{
            id: headerLabel
            anchors{
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }

            text: "Round " + (subPhaseVar.currentRoundIndex+1);
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Label{
            id: headerRoundStageLabel
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }

            text: {
                var crs = roundVar.currentRoundStage;
                if(crs === 0 || crs === 1) "Singiels"; else
                if(crs === 2 || crs === 3) "Dublets";  else
                if(crs === 4 || crs === 5) "Triplets"; else
                if(crs === 6) "Round Summary";  else
                {
                    log.e("unknown round stage("+crs+")", "SubPage.qml -> headerRoundStageLabel")
                    return "?";
                }
            }

            font.pixelSize: 15
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        Rectangle{
            id: contentBorder
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }
    }


    Item{
        id: content
        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        readonly property int delegateHeaderHeight: 60
        readonly property int delegateFooterHeight: 0//50

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

}
