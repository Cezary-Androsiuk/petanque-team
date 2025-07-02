import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

import "../Trace.js" as Trace

import "Play"

Item {
    id: play
    anchors.fill: parent

    Component.onCompleted: { Trace.t();
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
