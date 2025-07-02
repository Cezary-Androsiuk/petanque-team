import QtQuick 2.15
import QtQuick.Controls.Material

import "../../Trace.js" as Trace

Item {
    id: subPhase

    required property var subPhaseVar
    readonly property var roundVar: subPhaseVar.rounds[subPhaseVar.currentRoundIndex]

    readonly property int headerHeight: 60
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
                topMargin: 2
                horizontalCenter: parent.horizontalCenter
            }

            text: "Round " + (subPhaseVar.currentRoundIndex+1);
            font.pixelSize: 26
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Label{
            id: headerRoundStageLabel
            anchors{
                bottom: parent.bottom
                bottomMargin: 5
                horizontalCenter: parent.horizontalCenter
            }

            text: {
                var crs = roundVar.currentRoundStage;
                if(crs === 0 || crs === 1) "Singles"; else
                if(crs === 2 || crs === 3) "Doubles";  else
                if(crs === 4 || crs === 5) "Triples"; else
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


        Loader{
            id: matchesOrRoundSummeryLoader
            anchors.fill: parent
            sourceComponent: {
                var crs = roundVar.currentRoundStage;
                if(crs >= 0 && crs <= 5) matchesComponent;
                else if(crs === 6) roundSummeryComponent;
                else
                {
                    log.e("unknown round stage("+crs+")", "SubPage.qml -> matchesOrRoundSummaryLoader")
                    return null;
                }
            }
        }

        Component{
            id: matchesComponent
            Item{
                Matches{
                    anchors.fill: parent
                    roundVar: subPhase.roundVar
                    headerHeight: subPhase.headerHeight
                    footerHeight: subPhase.footerHeight
                }
            }
        }

        Component{
            id: roundSummeryComponent
            Item{
                RoundSummary{
                    anchors.fill: parent
                    roundVar: subPhase.roundVar
                    headerHeight: subPhase.headerHeight
                    footerHeight: subPhase.footerHeight
                }

            }
        }

    }

}
