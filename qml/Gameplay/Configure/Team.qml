import QtQuick 2.15
import QtQuick.Controls.Material

import "../../Popups"

Item {
    id: configureTeam

    required property var parentStackView
    required property var team
    property bool edit: false

    property var event: Backend.event
    property int headerHeight: 70
    property int footerHeight: 70
    property int delegateHeight: 50

    Component.onCompleted: {
        log.w("now while editing existing team his name can be changed to the invalid one", "Team.qml -> onCompleted")
    }

    function randomNumber(topRange){
        // [0, topRange) - topRange value is not included
        return Math.floor(Math.random() * topRange);
    }

    function generateRandomTeamName(prefix, length) {
        /// Claude AI stuff
        // const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:,.<>?';
        const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';

        let result = '';

        for (let i = 0; i < length; i++) {
            const randomIndex = randomNumber(characters.length);
            result += characters[randomIndex];
        }

        return prefix + result;
    }

    function setExampleTeamDataIfNeeded(){
        if(team.name === "")
            team.name = generateRandomTeamName("Team Nr=", 7) // 3521614606208 options
            // I am 250,000 times more likely to win the Lotto than to have the license number repeated here.
    }

    function addNewPlayer(){
        configureTeam.team.createDetachedPlayer();
        const args = {
            parentStackView: configureTeam.parentStackView,
            team: configureTeam.team,
            player: configureTeam.team.detachedPlayer
        }
        parentStackView.push("Player.qml", args)
    }

    function goBack(){
        parentStackView.pop();
    }

    function cancelAddingTeam(){
        parentStackView.pop();
        event.deleteDetachedTeam();
    }

    function saveAddedTeamAuto(){
        setExampleTeamDataIfNeeded();

        event.validateDetachedTeam();
    }

    function saveAddedTeam(){
        event.validateDetachedTeam();
    }

    Connections{
        target: event
        function onDetachedTeamIsValid(){
            parentStackView.pop();
            event.addDetachedTeam();
        }

        function onDetachedTeamValidationFailed(message){
            log.i(message, "Team.qml->onDetachedTeamValidationFailed")
        }
    }

    InfoPopup{
        id: failedTeamCreationInfoPopup
    }

    Rectangle{ // required because of stack view animation
        anchors.fill: parent
        color: "#1c1b1f" // dark theme color
    }

    Item{
        id: playersListField
        anchors{
            top: header.bottom
            left: parent.left
            bottom: footer.top
        }
        width: parent.width * 0.5

        Item{
            anchors{
                fill: parent
                leftMargin: 30
                rightMargin: 15
            }
            clip: true

            Rectangle{
                id: scrollViewBorder
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.5)
                border.width: 1
            }

            ListView{
                id: listView
                anchors.fill: parent

                model: (!configureTeam.team)?0: configureTeam.team.players.length
                boundsBehavior: Flickable.StopAtBounds
                clip: true
                cacheBuffer: 10000

                ScrollBar.vertical: ScrollBar{
                    policy: ScrollBar.AsNeeded
                }

                delegate: Item{
                    width: listView.width - 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: configureTeam.delegateHeight

                    PlayerDelegate{
                        anchors.fill: parent

                        team: configureTeam.team
                        player: configureTeam.team.players[index]
                        parentStackView: configureTeam.parentStackView
                    }
                }

                footer: Item{
                    width: listView.width - 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: configureTeam.delegateHeight

                    Button{
                        anchors.fill: parent
                        text: qsTr("Add new player")
                        onClicked: {
                            configureTeam.addNewPlayer()
                        }
                    }
                }
            }
        }

    }

    Item{
        id: teamInfoField
        anchors{
            top: header.bottom
            right: parent.right
            bottom: footer.top
        }
        width: parent.width * 0.5

        Item{
            anchors{
                fill: parent
                leftMargin: 15
                rightMargin: 30
            }
            clip: true

            Rectangle{
                id: infoFieldFlickableBorder
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.5)
                border.width: 1
            }

            TextField{
                id: nameTextField
                anchors{
                    top: parent.top
                    topMargin: 10
                }
                height: 60
                width: 230

                placeholderText: qsTr("Team Name")
                text: (!configureTeam.team)?text: configureTeam.team.name
                onTextEdited: {
                    if(configureTeam.team)
                    {
                        configureTeam.team.name = text
                    }
                }
            }
        }
    }





    Item{
        id: header
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: configureTeam.headerHeight

        Button{
            anchors{
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }

            text: "back"

            visible: configureTeam.edit
            onClicked: {
                configureTeam.goBack();
            }
        }
    }

    Item{
        id: footer
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: configureTeam.footerHeight

        Item{
            id: footerButtons
            anchors.fill: parent
            visible: !configureTeam.edit

            Button{
                anchors{
                    right: centerPoint.left
                    verticalCenter: parent.verticalCenter
                }
                text: "cancel"
                onClicked: {
                    configureTeam.cancelAddingTeam();
                }
            }

            Item{
                id: centerPoint
                anchors.centerIn: parent
                width: 20
            }

            Button{
                id: saveTeamButton
                anchors{
                    left: centerPoint.right
                    verticalCenter: parent.verticalCenter
                }
                text: "save team"
                onClicked: {
                    configureTeam.saveAddedTeam();
                }
            }
            Button{
                anchors{
                    left: saveTeamButton.right
                    leftMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                text: "save team auto"
                visible: Backend.isDebugMode
                onClicked: {
                    configureTeam.saveAddedTeamAuto();
                }
            }
        }
    }
}
