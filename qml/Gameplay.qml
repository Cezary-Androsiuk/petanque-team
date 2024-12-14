import QtQuick
import QtQuick.Controls.Material

Item {
    id: play
    anchors.fill: parent

    property string loaderSource: {
        if(Backend.event.currentStage === 0) // None
        {
            log.e("none stage was reached");
            "";
        }
        else
        if(Backend.event.currentStage === 1) // Configure
        {
            "Gameplay/Configure.qml";
        }
        else
        if(Backend.event.currentStage === 2) // Play
        {
            "Gameplay/Play.qml";
        }
        else
        if(Backend.event.currentStage === 3) // Finish
        {
            "Gameplay/Finish.qml";
        }
    }

    Component.onDestruction: {
        Memory.save();
    }

    Loader{
        id: playLoader
        anchors.fill: parent
        source: loaderSource
    }

}
