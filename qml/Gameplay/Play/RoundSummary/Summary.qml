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
            contentWidth: teamScoresListContainer.width
            contentHeight: teamScoresListContainer.height
            boundsBehavior: Flickable.StopAtBounds

            clip: true

            Item{
                id: teamScoresListContainer
                width: teamScoresListViewRows.width
                height: teamScoresListViewRows.height

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
                        teamScoresListContainer.widestTeamNameLabel =
                                teamScoresListContainer.findWidestTeamNameLabel() + 5
                    }
                }

                ListView{
                    id: teamScoresListViewRows
                    width: dynamicWidth
                    height: headerRowDelegateHeight + elementRowDelegateHeight * summary.teamScoresList.length

                    model: summary.teamScoresList
                    interactive: false
                    clip: true


                    readonly property int headerRowDelegateHeight: 50
                    readonly property int elementRowDelegateHeight: 40
                    readonly property int cellWidth: 50
                    readonly property int teamNameSideMargin: 10

                    TeamScoresLabelsModel{
                        id: teamScoresLabelsModel
                    }

                    readonly property double dynamicWidth:
                        teamScoresListFlickable.width > minWidth ? teamScoresListFlickable.width : minWidth

                    readonly property double minWidth:
                        cellWidth + teamNameSideMargin*2 + teamScoresListContainer.widestTeamNameLabel +
                        teamScoresLabelsModel.model.count * cellWidth

                    header: Item{
                        id: headerItem
                        width: teamScoresListContainer.width
                        height: teamScoresListViewRows.headerRowDelegateHeight

                        Row{
                            Label{
                                id: rowIDLabel
                                height: headerItem.height
                                width: teamScoresListViewRows.cellWidth
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "ID"
                            }
                            Item{
                                id: rowTeamNameLabelContainer
                                width: teamScoresListContainer.widestTeamNameLabel +
                                       teamScoresListViewRows.teamNameSideMargin * 2
                                height: headerItem.height

                                Label{
                                    id: rowTeamNameLabel
                                    anchors{
                                        fill: parent
                                        leftMargin: teamScoresListViewRows.teamNameSideMargin
                                        rightMargin: teamScoresListViewRows.teamNameSideMargin
                                    }
                                    verticalAlignment: Text.AlignVCenter
                                    text: "Team Name"
                                }
                            }
                        }

                        ListView{
                            id: teamScoresListViewLabelsColumns
                            anchors.right: parent.right
                            width: teamScoresLabelsModel.model.count * teamScoresListViewRows.cellWidth
                            height: headerItem.height

                            model: teamScoresLabelsModel.model

                            interactive: false
                            clip: true
                            orientation: ListView.Horizontal

                            readonly property int valueDelegateWidth: 40

                            delegate: Label{
                                height: headerItem.height
                                width: teamScoresListViewRows.cellWidth
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: shortName

                                ToolTip.text: longName
                            }
                        }

                    }

                    delegate: Item {
                        id: delegateItem
                        width: teamScoresListContainer.width
                        height: teamScoresListViewRows.headerRowDelegateHeight

                        Row{
                            Label{
                                id: rowID
                                height: delegateItem.height
                                width: teamScoresListViewRows.cellWidth
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: index
                            }

                            Item{
                                id: rowTeamNameContainer
                                width: teamScoresListContainer.widestTeamNameLabel +
                                       teamScoresListViewRows.teamNameSideMargin * 2
                                height: delegateItem.height

                                Label{
                                    id: rowTeamName
                                    anchors{
                                        fill: parent
                                        leftMargin: teamScoresListViewRows.teamNameSideMargin
                                        rightMargin: teamScoresListViewRows.teamNameSideMargin
                                    }
                                    verticalAlignment: Text.AlignVCenter

                                    text: modelData.teamName
                                }
                            }

                        }


                        ListView{
                            id: teamScoresListViewColumns
                            anchors.right: parent.right
                            width: modelData.allParametersList.length * teamScoresListViewRows.cellWidth
                            height: delegateItem.height

                            model: modelData.allParametersList;

                            interactive: false
                            clip: true
                            orientation: ListView.Horizontal

                            readonly property int valueDelegateWidth: 40

                            delegate: Item{
                                height: delegateItem.height
                                width: teamScoresListViewRows.cellWidth

                                clip: true
                                Label{
                                    anchors.fill: parent
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter

                                    text: modelData
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle{
            anchors.fill: parent
            color: "orange"
            opacity: 0.2
        }
    }


    // Flickable{
    //     id: teamScoresListFlickable
    //     anchors.fill: parent
    //     contentWidth: teamScoresListContainer.width
    //     contentHeight: teamScoresListContainer.height
    //     boundsBehavior: Flickable.StopAtBounds
    //     clip: true


    //     function updateVerticalScrollBar(){
    //         // keep visible, as long as content is larger than flickable area
    //         // console.log("CH: " + teamScoresListFlickable.contentHeight + ", H:" + teamScoresListFlickable.height)
    //         let isContentGreater = teamScoresListFlickable.contentHeight > teamScoresListFlickable.height;
    //         ScrollBar.vertical.policy = isContentGreater ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
    //     }
    //     function updateHorizontalScrollBar(){
    //         // console.log("CW: " + teamScoresListFlickable.contentWidth + ", W:" + teamScoresListFlickable.width)
    //         let isContentGreater = teamScoresListFlickable.contentWidth > teamScoresListFlickable.width;
    //         ScrollBar.horizontal.policy = isContentGreater ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
    //     }

    //     Component.onCompleted: {
    //         updateVerticalScrollBar();
    //         updateHorizontalScrollBar();
    //     }

    //     onHeightChanged: {
    //         updateVerticalScrollBar();
    //     }
    //     onWidthChanged: {
    //         updateHorizontalScrollBar();

    //         /// move element to the center
    //         teamScoresListContainer.x = (width > teamScoresListContainer.width) ? (width - teamScoresListContainer.width)/2 : 0
    //     }

    //     property double previousContentHeight: 0
    //     onContentHeightChanged: {
    //         updateVerticalScrollBar();

    //         // check if it is first time called and init with value,
    //         // to avoid scrolling at the end, right after content was loaded
    //         if(previousContentHeight === 0)
    //             previousContentHeight = contentHeight

    //         /// check if new content height is larger than previous one
    //         let contentIsGrowing = previousContentHeight < contentHeight
    //         previousContentHeight = contentHeight


    //         // react on inner list extension
    //         if(teamScoresListContainer.elementCompleted && contentIsGrowing && contentHeight > height)
    //             contentY = contentHeight - height
    //     }

    //     onContentWidthChanged: {
    //         updateHorizontalScrollBar();
    //     }

    //     ScrollBar.vertical: ScrollBar{
    //         policy: ScrollBar.AsNeeded
    //     }
    //     ScrollBar.horizontal: ScrollBar{
    //         policy: ScrollBar.AsNeeded
    //     }

    //     Item{
    //         id: teamScoresListContainer
    //         width: 800
    //         height: 400

    //         readonly property int headerDelegateHeight: 50
    //         readonly property int elementDelegateHeight: 40
    //         readonly property int verticalSeparatorLength: headerDelegateHeight +
    //                                                        summary.teamScoresList.length * elementDelegateHeight

    //         function getTextLabelWidth(textValue){
    //             const qmlString = `
    //                 import QtQuick 2.15
    //                 import QtQuick.Controls.Material

    //                 Label {
    //                     visible: false;
    //                 }
    //             `;

    //             let tempLabel = null;
    //             try {
    //                 tempLabel = Qt.createQmlObject(qmlString, summary);
    //                 if (tempLabel === null) {
    //                     return -1;
    //                 }

    //                 // set label properties
    //                 // tempLabel.font.pointSize = fontPointSize;
    //                 tempLabel.text = textValue;

    //                 return tempLabel.implicitWidth;
    //             } catch (error){
    //                 console.log("error:", error)
    //                 return -1
    //             } finally {
    //                 if (tempLabel) {
    //                     tempLabel.destroy();
    //                 }
    //             }
    //         }

    //         function findWidestTeamNameLabel(){

    //             let list = teamScoresList;
    //             let largestTeamLabelWidth = 0;

    //             let i = 1;
    //             for(const element of list){
    //                 const labelWidth = getTextLabelWidth(element.teamName)
    //                 console.log(`labelWidth ${i++}: ${labelWidth}`)
    //                 if(labelWidth === -1){
    //                     continue;
    //                 }
    //                 if(largestTeamLabelWidth < labelWidth){
    //                     largestTeamLabelWidth = labelWidth
    //                 }
    //             }
    //             return largestTeamLabelWidth;
    //         }

    //         property double widestTeamNameLabel
    //         Connections{
    //             target: roundSummarySC
    //             function onTeamScoresSummaryChanged(){
    //                 teamScoresListContainer.widestTeamNameLabel =
    //                         teamScoresListContainer.findWidestTeamNameLabel() + 5
    //             }
    //         }

    //         Item{
    //             anchors{
    //                 fill: parent
    //                 margins: 10
    //             }

    //             ListView{
    //                 id: teamScoresListView
    //                 anchors.fill: parent

    //                 model: summary.teamScoresList
    //                 boundsBehavior: Flickable.StopAtBounds
    //                 clip: true

    //                 header: Item{
    //                     id: headerDelegate
    //                     height: teamScoresListContainer.headerDelegateHeight
    //                     width: childrensWider ? childrensWidth : teamScoresListContainer.width

    //                     /// properties to ensure that item won't be shorter than minimum size
    //                     readonly property double childrensWidth:
    //                         teamIndexesLabelsContainer.width + teamParametersLabelsContainer.width;
    //                     readonly property bool childrensWider: childrensWidth > teamScoresListContainer.width;

    //                     Row{
    //                         id: teamIndexesLabelsContainer
    //                         anchors{
    //                             top: parent.top
    //                             left: parent.left
    //                             bottom: parent.bottom
    //                         }

    //                         spacing: 5
    //                         Label{
    //                             id: teamIndexLabel
    //                             width: 20

    //                             // verticalAlignment: Text.AlignVCenter
    //                             // text:
    //                         }

    //                         Rectangle{
    //                             id: separator1
    //                             width: 1
    //                             color: Qt.rgba(1,1,1, 0.4)
    //                             height: teamScoresListContainer.verticalSeparatorLength
    //                         }

    //                         Label{
    //                             id: teamNameLabel
    //                             anchors.verticalCenter: parent.verticalCenter
    //                             width: teamScoresListContainer.widestTeamNameLabel
    //                             verticalAlignment: Text.AlignVCenter
    //                             text: "Team Name"

    //                         }


    //                     }

    //                     Item{
    //                         id: teamParametersLabelsContainer
    //                         anchors{
    //                             top: parent.top
    //                             right: parent.right
    //                             bottom: parent.bottom
    //                         }
    //                         width: childrenRect.width

    //                         ListView{
    //                             id: teamParametersLabels
    //                             height: parent.height
    //                             width: 15 * 50 /// here add model of labels and in element delegate use 15
    //                             model: 15
    //                             boundsBehavior: Flickable.StopAtBounds
    //                             interactive: false
    //                             orientation: ListView.Horizontal

    //                             delegate: Item{
    //                                 width: 50
    //                                 height: headerDelegate.height

    //                                 Label{
    //                                     anchors.fill: parent
    //                                     horizontalAlignment: Text.AlignHCenter
    //                                     verticalAlignment: Text.AlignVCenter
    //                                     text: "LV " + index
    //                                 }

    //                                 Rectangle{
    //                                     id: separator3
    //                                     width: 1
    //                                     color: Qt.rgba(1,1,1, 0.4)
    //                                     height: teamScoresListContainer.verticalSeparatorLength
    //                                 }
    //                             }

    //                         }
    //                     }




    //                     Rectangle{
    //                         anchors.fill: parent
    //                         color: "transparent"
    //                         border.color: Qt.rgba(1,1,1, 0.4)
    //                         border.width: 1
    //                     }
    //                 }

    //                 delegate: Item{
    //                     height: teamScoresListContainer.elementDelegateHeight
    //                     width: teamScoresListContainer.width

    //                     Label{
    //                         id: teamIndex
    //                         anchors{
    //                             top: parent.top
    //                             left: parent.left
    //                             leftMargin: 10
    //                             bottom: parent.bottom
    //                         }
    //                         width: 20

    //                         verticalAlignment: Text.AlignVCenter
    //                         text: index
    //                     }

    //                     Label{
    //                         id: teamName
    //                         anchors{
    //                             top: parent.top
    //                             left: teamIndex.right
    //                             bottom: parent.bottom
    //                         }
    //                         verticalAlignment: Text.AlignVCenter
    //                         text: modelData.teamName
    //                     }


    //                     Rectangle{
    //                         anchors.fill: parent
    //                         color: "transparent"
    //                         border.color: Qt.rgba(1,1,1, 0.4)
    //                         border.width: 1
    //                     }


    //                 }
    //             }

    //         }
    //     }
    // }



}
