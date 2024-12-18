import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: subPhase

    required property var subPhaseVar
    readonly property var roundVar: subPhaseVar.rounds[subPhaseVar.currentRoundIndex]

    Column{
        anchors.centerIn: parent
        Label{
            text: subPhaseVar.name
        }
        Label{
            text: subPhaseVar.currentRoundIndex
        }
        Label{
            // text: roundVar.currentRoundStage
        }

    }


}
