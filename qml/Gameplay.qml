import QtQuick
import QtQuick.Controls.Material

import "Trace.js" as Trace

Item {
    id: gameplay
    anchors.fill: parent

    property var event: Backend.event
    property int currentStage: event ? event.currentStage : 0

    property string loaderSource: {
        if(currentStage === 0) // None
        {
            log.e("none stage was reached", "Gameplay.qml");
            "";
        }
        else
        if(currentStage === 1) // Configure
        {
            "Gameplay/Configure.qml";
        }
        else
        if(currentStage === 2) // Play
        {
            "Gameplay/Play.qml";
        }
        else
        if(currentStage === 3) // Finish
        {
            "Gameplay/Finish.qml";
        }
    }

    Component.onDestruction: { Trace.t();
        Backend.memory.save();
    }

    Loader{
        id: playLoader
        anchors.fill: parent
        source: loaderSource
    }

}
