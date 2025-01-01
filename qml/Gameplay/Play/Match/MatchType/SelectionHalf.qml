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
                        // defaultSelectionValue
                        editable: false

                        currentIndex: selectionHalf.selectionVar.playerSelections[index]+1
                        model: selectionHalf.selectionVar.comboBoxModel

                        onCurrentIndexChanged: {
                            selectionHalf.selectionVar.setPlayerGroup(index, currentIndex-1)
                        }
                    }
                }

                Item{
                    id: playersListViewContainer
                    anchors{
                        top: parent.top
                        bottom: parent.bottom
                        right: selectionHalf.isLeft ? comboBoxField.left : parent.right
                        left: selectionHalf.isLeft ? parent.left : comboBoxField.right
                        margins: 10
                    }
                    clip: true

                    Label{
                        anchors{
                            fill: parent
                            leftMargin: 10
                            rightMargin: 10
                        }

                        elide: Text.ElideRight
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        text: {
                            let player = selectionHalf.selectionVar.team.players[index];
                            if(!player)
                            {
                                log.w("unknown player - players list is shorter than playerSelections",
                                      "SelectionHalf -> Label -> text");
                                "unknown";
                            }
                            else
                            {
                                player.firstName + " " + player.lastName;
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
