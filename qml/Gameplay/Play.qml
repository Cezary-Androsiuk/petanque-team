import QtQuick 2.15

import "Play"

Item {
    id: play
    anchors.fill: parent

    readonly property var event: Backend.event

    Phase{
        phaseIndex: 1
    }
}
