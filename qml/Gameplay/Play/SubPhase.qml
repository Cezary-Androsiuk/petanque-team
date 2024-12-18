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

        Loader{
            anchors.fill: parent
            sourceComponent: {
                var crs = roundVar.currentRoundStage;
                if(crs === 6) summaryExample; else
                {
                    if(crs % 2 === 0)
                        selectionExample;
                    else
                        matchExample;

                }
            }

            Component{
                id: summaryExample
                Item{
                    anchors.fill: parent
                    Label{
                        id: headerLabel
                        anchors.centerIn: parent

                        text: "summary example"
                        font.pixelSize: 24
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            Component{
                id: matchExample
                Item{
                    anchors.fill: parent
                    Label{
                        id: headerLabel
                        anchors.centerIn: parent

                        text: "match example"
                        font.pixelSize: 24
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            Component{
                id: selectionExample
                Item{
                    anchors.fill: parent
                    Label{
                        id: headerLabel
                        anchors.centerIn: parent

                        text: "selection example"
                        font.pixelSize: 24
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

    }

}
