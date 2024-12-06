import QtQuick
import QtQuick.Controls.Material

Item {
    id: play
    anchors.fill: parent

    property string loaderSource: {
        if(Backend.event.stage === 0) // None
        {
            log.e("none stage was reached");
            "";
        }
        else
        if(Backend.event.stage === 1) // Configure
        {
            "event/Configure.qml";
        }
        else
        if(Backend.event.stage === 2) // Continue
        {
            "event/Continue.qml";
        }
        else
        if(Backend.event.stage === 3) // Finish
        {
            "event/Finish.qml";
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
