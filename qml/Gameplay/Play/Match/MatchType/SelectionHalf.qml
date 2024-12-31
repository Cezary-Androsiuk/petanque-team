import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selectionHalf

    required property var selectionVar
    property bool isLeft: true; // default is left

    readonly property int playersCount: selectionVar.team.players.length
    readonly property int delegateHeight: 60

    height: (delegateHeight + /*add margins*/(10*2)) * playersCount +
            (selectionHalfContent.anchors.margins * 2) +
            playersListView.spacing * (playersCount > 0 ? playersCount-1 : 0)

    Item{
        id: selectionHalfContent
        anchors{
            fill: parent
            margins: 10
        }

        ListView{
            id: playersListView
            anchors.fill: parent

            model: selectionHalf.playersCount
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            interactive: false
            spacing: 10
            cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

            delegate: Item{
                id: groupDelegate
                width: playersListView.width
                height: selectionHalf.delegateHeight + 20 //+ playersListViewContainer.anchors.margins*2

                Item{
                    id: comboBoxField
                    anchors{
                        top: parent.top
                        bottom: parent.bottom
                        right: selectionHalf.isLeft ? parent.right : undefined
                        rightMargin: selectionHalf.isLeft ? 10 : 0
                        left: selectionHalf.isLeft ? undefined : parent.left
                        leftMargin: selectionHalf.isLeft ? 0 : 10
                    }
                    width: comboBox.width

                    Rectangle{
                        anchors.fill: comboBox
                        color: Qt.rgba(0.8,0,0, 0.6)
                        visible: comboBox.value > 13
                        radius: 5
                    }

                    ComboBox{
                        id: comboBox
                        anchors{
                            verticalCenter: parent.verticalCenter
                            // top: parent.top
                            // topMargin: 10
                            // bottom: parent.bottom
                            // bottomMargin: 10
                            right: selectionHalf.isLeft ? parent.right : undefined
                            left: selectionHalf.isLeft ? undefined : parent.left
                        }

                        editable: true
                        // flat: isLeft
                        // to: 13

                        // value: selectionHalf.matchVar.matchPoints[index]
                        // onValueChanged: {
                        //     selectionHalf.setGroupPoints(index, value);
                        //     focus = false; // prevents keeping spinbox constantly selected
                        // }
                    }
                }

                /*
                Item{
                    id: spinBoxField
                    anchors{
                        top: parent.top
                        bottom: parent.bottom
                        right: matchHalf.isLeft ? parent.right : undefined
                        rightMargin: matchHalf.isLeft ? 10 : 0
                        left: matchHalf.isLeft ? undefined : parent.left
                        leftMargin: matchHalf.isLeft ? 0 : 10
                    }
                    width: spinBox.width

                    Rectangle{
                        anchors.fill: spinBox
                        color: Qt.rgba(0.8,0,0, 0.6)
                        visible: spinBox.value > 13
                        radius: 5
                    }

                    SpinBox{
                        id: spinBox
                        anchors{
                            verticalCenter: parent.verticalCenter
                            // top: parent.top
                            // topMargin: 10
                            // bottom: parent.bottom
                            // bottomMargin: 10
                            right: matchHalf.isLeft ? parent.right : undefined
                            left: matchHalf.isLeft ? undefined : parent.left
                        }

                        editable: true
                        to: 13

                        value: matchHalf.matchVar.matchPoints[index]
                        onValueChanged: {
                            matchHalf.setGroupPoints(index, value);
                            focus = false; // prevents keeping spinbox constantly selected
                        }
                    }
                }

                readonly property int groupIndex: index
                readonly property var playersInGroup: matchHalf.matchVar.groupsOfPlayers[groupIndex]
                readonly property int playersCountInGroup: playersInGroup.length
                // computing playerDelegateHeight here allows to fit 3 players in 2 fields or 4 players in 3 fields
                readonly property int dynamicPlayerDelegateHeight: {
                    let expectedDelegatesHeightSum = defaultPlayerDelegateHeight * defaultPlayersCountInGroup
                    let newDelegateHeight = expectedDelegatesHeightSum / playersCountInGroup
                    newDelegateHeight
                }

                Item{
                    id: playersListViewContainer
                    anchors{
                        top: parent.top
                        bottom: parent.bottom
                        right: matchHalf.isLeft ? spinBoxField.left : parent.right
                        left: matchHalf.isLeft ? parent.left : spinBoxField.right
                        margins: 10
                    }

                    ListView{
                        id: playersListView
                        anchors.fill: parent

                        model: groupDelegate.playersCountInGroup
                        boundsBehavior: Flickable.StopAtBounds
                        interactive: false
                        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

                        delegate: Item{
                            width: playersListViewContainer.width
                            height: groupDelegate.dynamicPlayerDelegateHeight

                            Item{
                                anchors{
                                    fill: parent
                                    // topMargin: 5
                                    // bottomMargin: 5
                                }
                                clip: true

                                Label{
                                    anchors{
                                        fill: parent
                                        leftMargin: 10
                                    }
                                    horizontalAlignment: Text.AlignLeft
                                    verticalAlignment: Text.AlignVCenter
                                    text: {
                                        let player = groupDelegate.playersInGroup[index]
                                        player.firstName + " " + player.lastName
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
                */

                // Item{
                //     anchors{
                //         fill: parent
                //         margins: 10
                //     }
                // }

                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.4)
                    border.width: 1
                }

            }

        }
    }

    // height: rowDelegateHeight * selectionsCount

    // ListView{
    //     id: rowListView
    //     anchors.fill: parent
    //     model: selectionHalf.selectionsCount
    //     clip: true
    //     interactive: false
    //     cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

    //     header: Item{
    //         // columns headers
    //     }

    //     delegate: Item{
    //         id: rowDelegate
    //         width: rowListView.width
    //         height: selectionHalf.rowDelegateHeight

    //         readonly property int rowIndex: index

    //         ListView{
    //             id: columnListView
    //             anchors.fill: parent
    //             model: selectionHalf.selectionVar.groupsCount
    //             clip: true
    //             interactive: false
    //             cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling
    //             orientation: ListView.Horizontal

    //             header: Item{
    //                 // player names headers
    //             }

    //             delegate: Item{
    //                 id: columnDelegate
    //                 width: selectionHalf.columnDelegateWidth
    //                 height: columnListView.height

    //                 readonly property int colIndex: index

    //                 Rectangle{
    //                     anchors.fill: parent
    //                     color: "blue"
    //                     border.color: "white"
    //                     opacity: 0.5
    //                     border.width: 1
    //                 }

    //                 RadioButton{
    //                     anchors.fill: parent

    //                     // // uncheck mechanic // not works fully
    //                     // property bool wasCheckedWhilePressing: false
    //                     // onPressed: {
    //                     //     wasCheckedWhilePressing = checked
    //                     // }
    //                     // onClicked: {
    //                     //     if(wasCheckedWhilePressing)
    //                     //     {
    //                     //         checked = false
    //                     //         // selectionHalf.selectionVar.setPlayerGroup(rowDelegate.rowIndex, -1)
    //                     //     }
    //                     // }

    //                     checked: selectionHalf.selectionVar.playerSelections[rowDelegate.rowIndex] === columnDelegate.colIndex
    //                     onCheckedChanged: {
    //                         if(checked)
    //                             selectionHalf.selectionVar.setPlayerGroup(rowDelegate.rowIndex, columnDelegate.colIndex)
    //                         // groupSelection.setSC(rowDelegate.rowIndex, radioButton.colIndex, checked)
    //                     }
    //                 }

    //             }
    //         }

    //         Rectangle{
    //             anchors.fill: parent
    //             color: "green"
    //             border.color: "white"
    //             opacity: 0.5
    //             border.width: 1
    //         }
    //     }
    // }

}
