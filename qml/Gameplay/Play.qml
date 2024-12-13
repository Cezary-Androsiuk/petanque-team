import QtQuick 2.15

import "Play"

Item {
    id: play
    anchors.fill: parent

    Phase{
        phaseIndex: Backend.event.currentPhase
    }
}
