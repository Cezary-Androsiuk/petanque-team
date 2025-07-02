import QtQuick 2.15
import QtQuick.Controls.Material

import "../../Trace.js" as Trace

import "../../Popups"

Item{
    id: teamDelegate

    required property double defaultHeight
    required property var team
    required property var parentStackView

    property bool extended: false
    readonly property double extendedHeight: defaultHeight * 1.5 + playersInfo.height
    height: extended ? extendedHeight : defaultHeight

    clip: true

    function editTeam(){ Trace.t();
        const args = {
            edit: true,
            parentStackView: teamDelegate.parentStackView,
            team: teamDelegate.team
        }
        parentStackView.push("Team.qml", args)
    }

    function addNewPlayer(){ Trace.t();
        teamDelegate.team.createDetachedPlayer();
        const args = {
            parentStackView: teamDelegate.parentStackView,
            team: teamDelegate.team,
            player: teamDelegate.team.detachedPlayer
        }
        parentStackView.push("Player.qml", args)
    }

    function deleteTeam(){ Trace.t();
        Backend.event.deleteTeam(team);
    }

    function extendTeam(){ Trace.t();
        extended = !extended
    }

    AskPopup{
        id: askDeleteTeamPopup
        onConfirmed: { Trace.t();
            teamDelegate.deleteTeam()
        }
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
                text: (!teamDelegate.team)?"": teamDelegate.team.name

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

                onClicked:{ Trace.t();
                    askDeleteTeamPopup.title = "Are you sure to delete Team?"
                    askDeleteTeamPopup.fOpen()
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

                onClicked: { Trace.t();
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

                onClicked: { Trace.t();
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
            height: (playersCount +1/*footer*/) * defaultHeight
            visible: teamDelegate.extended

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

                footer: Item{
                    width: playersInfo.width
                    height: teamDelegate.defaultHeight

                    Button{
                        anchors.fill: parent
                        text: qsTr("Add new player")
                        onClicked: { Trace.t();
                            teamDelegate.addNewPlayer()
                        }
                    }
                }
            }
        }
    }


}
