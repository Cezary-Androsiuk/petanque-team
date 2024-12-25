import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selection

    required property var matchVar
    readonly property var matchTypeVar: matchVar.currentMatchType
    readonly property var selectionLeftVar: matchTypeVar.selectionLeft
    readonly property var selectionRightVar: matchTypeVar.selectionRight

    readonly property int rowDelegateHeight: 50
    readonly property int columnDelegateWidth: 70

    width: parent.width
    // height: 800 // compute by model, but for now 800+
    height: (leftHalf.height > rightHalf.height) ? leftHalf.height : rightHalf.height

    Component.onCompleted: {
        matchTypeVar.initSelection()
    }

    function setExampleData(){

    }

    Item{
        id: selectionContent
        anchors.fill: parent

        SelectionHalf{
            id: leftHalf
            anchors{
                top: parent.top
                left: parent.left
            }
            width: parent.width/2
            c: "red"
        }

        SelectionHalf{
            id: rightHalf
            anchors{
                top: parent.top
                right: parent.right
            }
            width: parent.width/2
            c: "green"
        }
    }

}
