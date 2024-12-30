import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: matchHalf

    required property var matchVar
    property bool isLeft: true; // default is left

    readonly property int groupsCount: matchVar.groupsCount
    readonly property int defaultPlayersCountInGroup: matchVar.defaultPlayersCountInGroup
    readonly property int defaultPlayerDelegateHeight: 60; // overwrited by players count in group to fit additional player
    readonly property int groupHeaderHeight: 60
    readonly property int groupDelegateHeight: defaultPlayerDelegateHeight * defaultPlayersCountInGroup;

    // height: groupHeaderHeight + ( (groupDelegateHeight + /*add margins*/(10*2)) * groupsCount )
    height: 800

    Item{
        id: matchHalfContent
        anchors{
            fill: parent
            margins: 10
        }

        ListView{
            id: groupsListView
            anchors.fill: parent

            model: matchHalf.groupsCount
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            interactive: false
            cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

            header: Item{
                width: groupsListView.width
                height: matchHalf.groupHeaderHeight

                Label{
                    id: leftTeamName
                    anchors.centerIn: parent
                    height: 50
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    text: matchHalf.matchVar.team.name
                }
            }

            delegate: Item{
                id: groupDelegate
                width: groupsListView.width
                height: matchHalf.groupDelegateHeight + playersListViewContainer.anchors.margins*2

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
                            right: matchHalf.isLeft ? parent.right : undefined
                            left: matchHalf.isLeft ? undefined : parent.left
                        }

                        editable: true
                        to: 999

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

                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.4)
                    border.width: 1
                }

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
