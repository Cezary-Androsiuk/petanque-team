import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: groupSelection

    required property var matchVar
    readonly property var matchTypeVar: matchVar.currentMatchType
    readonly property var selectionLeftVar: matchTypeVar.selectionLeft
    readonly property var selectionRightVar: matchTypeVar.selectionRight

    readonly property int rowDelegateHeight: 50
    readonly property int columnDelegateWidth: 70

    width: parent.width
    height: 800 // compute by model, but for now 800+

    Component.onCompleted: {
        console.log(selectionLeftVar)
        matchTypeVar.initSelection()
        console.log(selectionLeftVar)
    }

    function setExampleData(){

    }

    Label{
        anchors.centerIn: parent
        text: "Selection"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    ListView{
        id: rowListView
        anchors.fill: parent
        model: 10
        clip: true
        interactive: false
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

        header: Item{
            // columns headers
        }

        delegate: Item{
            width: rowListView.width
            height: groupSelection.rowDelegateHeight

            ListView{
                id: columnListView
                anchors.fill: parent
                model: 10
                clip: true
                interactive: false
                cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling
                orientation: ListView.Horizontal

                header: Item{
                    // player names headers
                }

                delegate: Item{
                    width: groupSelection.columnDelegateWidth
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
