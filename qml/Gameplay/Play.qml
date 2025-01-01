import QtQuick 2.15

import "Play"

Item {
    id: play
    anchors.fill: parent

    Component.onCompleted: {
        rootWindow.minimumWidth = 700;
        rootWindow.minimumHeight = 550;
    }

    Phase{
        phaseIndex: Backend.event.currentPhase
    }
}
