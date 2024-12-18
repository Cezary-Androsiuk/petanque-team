import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: subPhase

    required property var subPhaseVar
    readonly property var roundVar: subPhaseVar.rounds[subPhaseVar.currentRoundIndex]

    readonly property int headerHeight: 30
    readonly property int footerHeight: 70

    Item{
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: subPhase.headerHeight

        Label{
            id: headerLabel
            anchors.centerIn: parent
            text: "Round " + (subPhaseVar.currentRoundIndex+1);
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }


}
