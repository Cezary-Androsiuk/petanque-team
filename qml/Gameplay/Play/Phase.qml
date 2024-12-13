import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: phase
    anchors.fill: parent

    required property int phaseIndex;
    readonly property var phaseVar: Backend.event.phases[phaseIndex];

    // Rectangle{
    //     anchors{
    //         top: parent.top
    //         left: parent.left
    //         right: parent.right
    //     }
    //     height: parent.height/2

    //     color: Qt.rgba(0.2, 0.8, 0.2, 0.4)
    // }

    Item{
        id: header
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: parent.height *0.5

        Rectangle{
            anchors.fill: parent
            height: parent.height/2

            color: Qt.rgba(0.2, 0.8, 0.2, 0.4)
        }

        // TabBar{
        //     anchors.fill: parent

        //     Repeater{
        //         model: phaseVar.subPhases
        //         TabButton{
        //             text: modelData.name

        //         }
        //     }
        // }
    }
}
