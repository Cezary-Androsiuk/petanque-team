import QtQuick 2.15
import QtQuick.Controls.Material

import ".."

Item {
    id: teamsList

    required property var parentStackView
    readonly property int delegateHeight: 50

    function addNewTeam(){
        Backend.event.createDetachedTeam()
        const args = {
            parentStackView: teamsList.parentStackView,
            team: Backend.event.detachedTeam
        }
        teamsList.parentStackView.push("../Team.qml", args)
    }

    ListView{
        id: listView
        anchors.fill: parent

        model: Backend.event.teams.length
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        cacheBuffer: 10000

        ScrollBar.vertical: ScrollBar{
            policy: ScrollBar.AsNeeded
        }

        delegate: Item{
            width: listView.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            height: teamDelegate.height

            TeamDelegate{
                id: teamDelegate
                width: parent.width

                defaultHeight: teamsList.delegateHeight
                team: Backend.event.teams[index]

                parentStackView: teamsList.parentStackView
            }
        }

        footer: Item{
            width: listView.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            height: teamsList.delegateHeight

            Button{
                anchors.fill: parent
                text: qsTr("Add new team")
                onClicked: {
                    teamsList.addNewTeam();
                }
            }
        }
    }


}
