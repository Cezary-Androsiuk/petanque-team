import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selectionHalf
    height: 800

    property color c

    Rectangle{
        anchors.fill: parent
        color: c
        opacity: 0.3
    }


    ListView{
        id: rowListView
        anchors.fill: parent
        model: 6
        clip: true
        interactive: false
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

        header: Item{
            // columns headers
        }

        delegate: Item{
            width: rowListView.width
            height: selection.rowDelegateHeight

            ListView{
                id: columnListView
                anchors.fill: parent
                model: 3
                clip: true
                interactive: false
                cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling
                orientation: ListView.Horizontal

                header: Item{
                    // player names headers
                }

                delegate: Item{
                    width: selection.columnDelegateWidth
                    height: columnListView.height
                    Rectangle{
                        anchors.fill: parent
                        color: "blue"
                        border.color: "white"
                        opacity: 0.5
                        border.width: 1
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
