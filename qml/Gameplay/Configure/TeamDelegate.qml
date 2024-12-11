import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: teamDelegate

    required property double defaultHeight
    required property var team
    required property var parentStackView

    property bool extended: false
    readonly property double extendedHeight: defaultHeight * 1.5 + playersInfo.height
    height: extended ? extendedHeight : defaultHeight

    clip: true

    function editTeam(){
        const args = {
            edit: true,
            parentStackView: teamDelegate.parentStackView,
            team: teamDelegate.team
        }
        parentStackView.push("Team.qml", args)
    }

    function deleteTeam(){
        Backend.event.deleteTeam(team);
    }

    function extendTeam(){
        extended = !extended
    }

    Item{
        anchors.fill: parent
        Rectangle{
            id: contentBorder
            anchors{
                fill: parent
            }
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        Item{
            id: teamInfo
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: defaultHeight

            Rectangle{
                id: teamInfoBorder
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.5)
                border.width: 1
            }

            Label{
                anchors{
                    left: parent.left
                    top: parent.top
                    leftMargin: 10
                }
                height: defaultHeight
                text: (!teamDelegate.team)?"": teamDelegate.team.teamName

                verticalAlignment: Text.AlignVCenter
            }

            Button{
                id: deleteTeamButton
                anchors{
                    right: editTeamButton.left
                    top: parent.top
                }
                height: defaultHeight
                width: height * 2

                text: "delete"

                onClicked:{
                    teamDelegate.deleteTeam()
                }
            }

            Button{
                id: editTeamButton
                anchors{
                    top: parent.top
                    right: extendButton.left
                }
                height: defaultHeight
                width: height * 2

                text: "edit"

                onClicked: {
                    teamDelegate.editTeam()
                }
            }

            Button{
                id: extendButton
                anchors{
                    top: parent.top
                    right: parent.right
                }
                height: defaultHeight
                width: height * 2

                text: teamDelegate.extended ? "^" : "v"

                onClicked: {
                    teamDelegate.extendTeam()
                }
            }
        }

        Item{
            id: playersInfo
            anchors{
                top: teamInfo.bottom
                left: parent.left
                right: parent.right
                leftMargin: parent.width * 0.1
            }
            height: playersCount * defaultHeight

            readonly property int playersCount: (!teamDelegate.team)?0: teamDelegate.team.players.length

            ListView{
                anchors.fill: parent

                boundsBehavior: Flickable.StopAtBounds
                interactive: false
                clip: true
                model: playersInfo.playersCount

                // SOMETHING LIKE THIS CAUSED AN ERROR XD
                // delegate: PlayerDelegate{
                //     width: playersInfo.width
                //     height: teamDelegate.defaultHeight

                //     player: teamDelegate.team.players[index]
                //     parentStackView: teamDelegate.parentStackView
                //     team: teamDelegate.team
                // }

                // BUT THIS IS TOTALLY FINE XDD
                delegate: Item{
                    width: playersInfo.width
                    height: teamDelegate.defaultHeight
                    PlayerDelegate{
                        anchors.fill: parent

                        player: teamDelegate.team.players[index]
                        parentStackView: teamDelegate.parentStackView
                        team: teamDelegate.team
                    }
                }
            }
        }
    }


}
