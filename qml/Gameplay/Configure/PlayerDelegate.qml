import QtQuick 2.15
import QtQuick.Controls.Material

import "../../Trace.js" as Trace

import "../../Popups"

Item{
    id: playerDelegate

    required property var player
    required property var team
    required property var parentStackView

    clip: true

    function editPlayer(){ Trace.t();
        const args = {
            edit: true,
            parentStackView: playerDelegate.parentStackView,
            player: playerDelegate.player,
            team: playerDelegate.team
        }
        parentStackView.push("Player.qml", args)
    }

    AskPopup{
        id: askDeletePlayerPopup
        onConfirmed: { Trace.t();
            console.log("onConfirmed", player)
            playerDelegate.team.deletePlayer(playerDelegate.player);
        }
    }

    Item{
        anchors.fill: parent

        Rectangle{
            id: playerInfoBorder
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        Label{
            id: playerInfo
            anchors{
                left: parent.left
                top: parent.top
                leftMargin: 10
                bottom: parent.bottom
            }
            verticalAlignment: Text.AlignVCenter
            text: {
                if(!playerDelegate.player) ""; else
                {
                    let player = playerDelegate.player;

                    let firstName = player.firstName;
                    let lastName = player.lastName;
                    let license = "[" + player.license + "]";
                    let ageGroup = "("+ player.ageGroup +")";
                    let gender = player.gender ? "F" : "M";
                    let isTeamLeader = player.isTeamLeader ? " 👑" : "";

                    firstName + " " + lastName + "    " + license + " " + ageGroup + " " + gender + " " + isTeamLeader;
                }
            }
        }

        Button{
            id: deletePlayerButton
            anchors{
                right: editPlayerButton.left
                top: parent.top
            }
            height: playerDelegate.height
            width: height * 2

            text: "delete"

            onClicked:{ Trace.t();
                console.log("onClicked ",player)
                askDeletePlayerPopup.title = "Are you sure to delete Player?"
                askDeletePlayerPopup.fOpen();
            }
        }

        Button{
            id: editPlayerButton
            anchors{
                top: parent.top
                right: parent.right
            }
            height: playerDelegate.height
            width: height * 2

            text: "edit"

            onClicked: { Trace.t();
                playerDelegate.editPlayer();
            }
        }
    }


}
