import QtQuick 2.15
import QtQuick.Controls.Material

import "../../../Trace.js" as Trace

import com.petanque.roundsummaryscorecounter 1.0

Item {
    id: summary
    anchors.fill: parent

    required property RoundSummarySC roundSummarySC;
    readonly property var teamScoresList: roundSummarySC.teamScoresSummary


    Item{
        id: flickableContainer
        anchors{
            fill: parent
            margins: 10
        }

        Flickable{
            id: teamScoresListFlickable
            anchors.fill: parent
            contentWidth: lvContainer.width
            contentHeight: lvContainer.height
            boundsBehavior: Flickable.StopAtBounds

            clip: true

            function updateVerticalScrollBar(){
                // keep visible, as long as content is larger than flickable area
                let isContentGreater = teamScoresListFlickable.contentHeight > teamScoresListFlickable.height;
                ScrollBar.vertical.policy = isContentGreater ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            }
            function updateHorizontalScrollBar(){
                let isContentGreater = teamScoresListFlickable.contentWidth > teamScoresListFlickable.width;
                ScrollBar.horizontal.policy = isContentGreater ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            }

            Component.onCompleted: {
                updateVerticalScrollBar();
                updateHorizontalScrollBar();
            }
            onHeightChanged:        updateVerticalScrollBar();
            onWidthChanged:         updateHorizontalScrollBar();
            onContentHeightChanged: updateVerticalScrollBar();
            onContentWidthChanged:  updateHorizontalScrollBar();
            ScrollBar.vertical: ScrollBar{ policy: ScrollBar.AsNeeded }
            ScrollBar.horizontal: ScrollBar{ policy: ScrollBar.AsNeeded }

            Item{
                id: lvContainer
                width: dynamicWidth
                height: lvContainer.headerRowDelegateHeight +
                        lvContainer.elementRowDelegateHeight * summary.teamScoresList.length

                readonly property int fontSize: 22

                function getTextLabelWidth(textValue){
                    const qmlString = `
                        import QtQuick 2.15
                        import QtQuick.Controls.Material

                        Label {
                            visible: false;
                        }
                    `;

                    let tempLabel = null;
                    try {
                        tempLabel = Qt.createQmlObject(qmlString, summary);
                        if (tempLabel === null) {
                            return -1;
                        }

                        // set label properties
                        // tempLabel.font.pointSize = fontPointSize;
                        tempLabel.font.pixelSize = lvContainer.fontSize
                        tempLabel.text = textValue;

                        return tempLabel.implicitWidth;
                    } catch (error){
                        console.warn("error:", error)
                        return -1
                    } finally {
                        if (tempLabel) {
                            tempLabel.destroy();
                        }
                    }
                }
                function findWidestTeamNameLabel(){

                    let list = teamScoresList;
                    let largestTeamLabelWidth = 0;

                    let i = 1;
                    for(const element of list){
                        const labelWidth = getTextLabelWidth(element.teamName)
                        // console.log(`labelWidth ${i++}: ${labelWidth}`)
                        if(labelWidth === -1){
                            continue;
                        }
                        if(largestTeamLabelWidth < labelWidth){
                            largestTeamLabelWidth = labelWidth
                        }
                    }
                    return largestTeamLabelWidth;
                }
                property double widestTeamNameLabel
                Connections{
                    target: roundSummarySC
                    function onTeamScoresSummaryChanged(){
                        lvContainer.widestTeamNameLabel =
                                lvContainer.findWidestTeamNameLabel() + 5
                    }
                }

                readonly property int headerRowDelegateHeight: 70
                readonly property int elementRowDelegateHeight: 60

                readonly property int cellWidth: 75 // cell is a single element like
                    // row ID or TeamScore parameter (but not a TeamName)
                readonly property int teamNameSideMargin: 10 // margin around TeamName field

                TeamScoresLabelsModel{
                    id: teamScoresLabelsModel
                }

                readonly property double minWidth:
                    cellWidth + teamNameSideMargin*2 + widestTeamNameLabel +
                    teamScoresLabelsModel.model.count * cellWidth

                readonly property double dynamicWidth:
                    teamScoresListFlickable.width > minWidth ? teamScoresListFlickable.width : minWidth

                ListView{
                    id: teamScoresListViewRows
                    anchors.fill: parent

                    model: summary.teamScoresList
                    interactive: false
                    clip: true

                    header: Item{
                        id: headerItem
                        width: lvContainer.width
                        height: lvContainer.headerRowDelegateHeight

                        Rectangle{
                            anchors.fill: parent
                            color: "white"
                            opacity: 0.08
                        }

                        Row{
                            Label{
                                id: rowIDLabel
                                height: headerItem.height
                                width: lvContainer.cellWidth
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "ID"
                                font.pixelSize: lvContainer.fontSize

                                Rectangle{ // white column separator
                                    anchors.right: parent.right
                                    width: 1
                                    height: lvContainer.height
                                    color: "white"
                                    opacity: 0.5
                                }
                            }
                            Item{
                                id: rowTeamNameLabelContainer
                                width: lvContainer.widestTeamNameLabel +
                                       lvContainer.teamNameSideMargin * 2
                                height: headerItem.height

                                Label{
                                    id: rowTeamNameLabel
                                    anchors{
                                        fill: parent
                                        leftMargin: lvContainer.teamNameSideMargin
                                        rightMargin: lvContainer.teamNameSideMargin
                                    }
                                    verticalAlignment: Text.AlignVCenter
                                    text: "Team Name"
                                    font.pixelSize: lvContainer.fontSize
                                }
                            }
                        }

                        ListView{
                            id: teamScoresListViewLabelsColumns
                            anchors.right: parent.right
                            width: teamScoresLabelsModel.model.count * lvContainer.cellWidth
                            height: headerItem.height

                            model: teamScoresLabelsModel.model

                            interactive: false
                            orientation: ListView.Horizontal

                            readonly property int valueDelegateWidth: 40

                            delegate: Item{
                                height: headerItem.height
                                width: lvContainer.cellWidth

                                Rectangle{ /// white column separator
                                    anchors.left: parent.left
                                    width: 1
                                    height: lvContainer.height
                                    color: "white"
                                    opacity: 0.5
                                }
                                // Rectangle{ /// green color background (column)
                                //     width: parent.width
                                //     height: lvContainer.height
                                //     color: "green"
                                //     opacity: 0.1
                                //     visible: index%2 === 0
                                // }

                                Label{
                                    anchors.fill: parent
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    text: shortName
                                    font.pixelSize: lvContainer.fontSize

                                    ToolTip{
                                        text: longName
                                        delay: 1000
                                        visible: mouseArea.containsMouse || mouseArea.containsPress
                                    }

                                    MouseArea{
                                        id: mouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                    }
                                }
                            }
                        }

                    }

                    delegate: Item {
                        id: delegateItem
                        width: lvContainer.width
                        height: lvContainer.elementRowDelegateHeight

                        Rectangle{ // white color background (row)
                            anchors.fill: parent
                            color: "white"
                            opacity: 0.05
                            visible: index % 2 === 1
                        }

                        Row{
                            Label{
                                id: rowID
                                height: delegateItem.height
                                width: lvContainer.cellWidth
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: (index+1)
                                font.pixelSize: lvContainer.fontSize
                            }

                            Item{
                                id: rowTeamNameContainer
                                width: lvContainer.widestTeamNameLabel +
                                       lvContainer.teamNameSideMargin * 2
                                height: delegateItem.height

                                Label{
                                    id: rowTeamName
                                    anchors{
                                        fill: parent
                                        leftMargin: lvContainer.teamNameSideMargin
                                        rightMargin: lvContainer.teamNameSideMargin
                                    }
                                    verticalAlignment: Text.AlignVCenter

                                    text: modelData.teamName
                                    font.pixelSize: lvContainer.fontSize
                                }
                            }

                        }


                        ListView{
                            id: teamScoresListViewColumns
                            anchors.right: parent.right
                            width: modelData.allParametersList.length * lvContainer.cellWidth
                            height: delegateItem.height

                            model: modelData.allParametersList;

                            interactive: false
                            clip: true
                            orientation: ListView.Horizontal

                            readonly property int valueDelegateWidth: 40

                            delegate: Item{
                                height: delegateItem.height
                                width: lvContainer.cellWidth

                                clip: true
                                Label{
                                    anchors.fill: parent
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter

                                    text: modelData
                                    font.pixelSize: lvContainer.fontSize
                                }
                            }
                        }
                    }
                }
            }
        }

        // Rectangle{
        //     anchors.fill: parent
        //     color: "orange"
        //     opacity: 0.2
        // }
    }


}
