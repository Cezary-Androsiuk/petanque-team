import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: phase

    required property int phaseIndex;
    readonly property var phaseVar: Backend.event.phases[phaseIndex];

    Item{
        id: header
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: parent.height *0.5


        TabBar{
            anchors.fill: parent

            Repeater{
                model: phaseVar.subPhases
                TabButton{
                    text: modelData.name

                }
            }
        }
    }
}
