import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selectionHalf
    height: 800

    required property var selectionVar

    readonly property int rowDelegateHeight: 50
    readonly property int columnDelegateWidth: 70

    ListView{
        id: rowListView
        anchors.fill: parent
        model: selectionHalf.selectionVar.playerSelections.length
        clip: true
        interactive: false
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

        header: Item{
            // columns headers
        }

        delegate: Item{
            id: rowDelegate
            width: rowListView.width
            height: selectionHalf.rowDelegateHeight

            readonly property int rowIndex: index

            ListView{
                id: columnListView
                anchors.fill: parent
                model: selectionHalf.selectionVar.groupsCount
                clip: true
                interactive: false
                cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling
                orientation: ListView.Horizontal

                header: Item{
                    // player names headers
                }

                delegate: Item{
                    id: columnDelegate
                    width: selectionHalf.columnDelegateWidth
                    height: columnListView.height

                    readonly property int colIndex: index

                    Rectangle{
                        anchors.fill: parent
                        color: "blue"
                        border.color: "white"
                        opacity: 0.5
                        border.width: 1
                    }

                    RadioButton{
                        anchors.fill: parent

                        // uncheck mechanic
                        // property bool wasCheckedWhilePressing: false
                        // onPressed: {
                        //     wasCheckedWhilePressing = checked
                        // }
                        // onClicked: {
                        //     if(wasCheckedWhilePressing)
                        //         checked = false
                        // }

                        checked: selectionHalf.selectionVar.playerSelections[rowDelegate.rowIndex] === columnDelegate.colIndex
                        onCheckedChanged: {
                            if(checked)
                                selectionHalf.selectionVar.setPlayerGroup(rowDelegate.rowIndex, columnDelegate.colIndex)
                            // groupSelection.setSC(rowDelegate.rowIndex, radioButton.colIndex, checked)
                        }
                    }

                }
            }

            Rectangle{
                anchors.fill: parent
                color: "green"
                border.color: "white"
                opacity: 0.5
                border.width: 1
            }
        }
    }

}
