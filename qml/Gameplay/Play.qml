import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

import "Play"

Item {
    id: play
    anchors.fill: parent

    Component.onCompleted: {
        rootWindow.minimumWidth = 700;
        rootWindow.minimumHeight = 550;
    }

    Component{
        id: settingsComponent
        Settings{

        }
    }

    StackView {
        id: playStackView
        anchors.fill: parent
        initialItem: Phase{
            phaseIndex: Backend.event.currentPhase
        }

    }



}
