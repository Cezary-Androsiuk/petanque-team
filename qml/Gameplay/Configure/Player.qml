import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: configurePlayer

    required property var parentStackView
    required property var team
    required property var player
    property bool edit: false

    property int headerHeight: 70
    property int footerHeight: 70
    property int delegateHeight: 50

    function goBack(){
        parentStackView.pop();
    }

    function cancelAddingPlayer(){
        parentStackView.pop();
        team.deleteDetachedPlayer();
    }

    function saveAddedPlayer(){
        parentStackView.pop();
        team.addPlayerUsingDetachedPlayer();
    }

    Rectangle{ // required because of stack view animation
        anchors.fill: parent
        color: "#1c1b1f" // dark theme color
    }

    Item{
        id: playerInfoField
        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: footer.top
            leftMargin: 30
            rightMargin: 30
        }

        Rectangle{
            id: scrollViewBorder
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }

        TextField{
            id: fnameTextField
            anchors{
                top: parent.top
                topMargin: 10
            }
            height: 60
            width: 230

            placeholderText: qsTr("First Name")
            text: (!configurePlayer.player)?text: configurePlayer.player.fname
            onTextEdited: {
                if(configurePlayer.player)
                    configurePlayer.player.fname = text
            }
        }

        TextField{
            id: lnameTextField
            anchors{
                top: fnameTextField.bottom
                topMargin: 10
            }
            height: 60
            width: 230

            placeholderText: qsTr("Last Name")
            text: (!configurePlayer.player)?text: configurePlayer.player.lname
            onTextEdited: {
                if(configurePlayer.player)
                    configurePlayer.player.lname = text
            }
        }

        TextField{
            id: licenseTextField
            anchors{
                top: lnameTextField.bottom
                topMargin: 10
            }
            height: 60
            width: 230

            placeholderText: qsTr("License")
            text: (!configurePlayer.player)?text: configurePlayer.player.license
            onTextEdited: {
                if(configurePlayer.player)
                    configurePlayer.player.license = text
            }
        }

        ComboBox{
            id: ageGroupComboBox
            anchors{
                top: licenseTextField.bottom
                topMargin: 10
            }
            model: ["Junior", "Youth", "Senior", "Veteran"]
            currentIndex: (!configurePlayer.player)?currentIndex: configurePlayer.player.ageGroup

            onCurrentIndexChanged: {
                if(configurePlayer.player)
                    configurePlayer.player.ageGroup = currentIndex
            }
        }

        ComboBox{
            id: genderComboBox
            anchors{
                top: ageGroupComboBox.bottom
                topMargin: 10
            }
            model: ["Male", "Female"]
            currentIndex: (!configurePlayer.player)?currentIndex: configurePlayer.player.gender

            onCurrentIndexChanged: {
                if(configurePlayer.player)
                    configurePlayer.player.gender = currentIndex
            }
        }

        CheckBox{
            id: isTeamLeaderCheckBox
            anchors{
                top: genderComboBox.bottom
                topMargin: 10
            }
            checked: (!configurePlayer.player)?checked: configurePlayer.player.isTeamLeader
            onCheckedChanged: {
                if(configurePlayer.player)
                {
                    if(checked === configurePlayer.player.isTeamLeader)
                         return;

                    configurePlayer.team.uncheckAllLeaders();

                    if(checked)
                        configurePlayer.player.isTeamLeader = true
                }

            }
            text: "Is Team Leader"
        }


    }






    Item{
        id: header
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: configurePlayer.headerHeight

        Button{
            anchors{
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }
            text: "back"
            visible: configurePlayer.edit
            onClicked: {
                configurePlayer.goBack();
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
        height: configurePlayer.footerHeight

        Item{
            id: footerButtons
            anchors.fill: parent
            visible: !configurePlayer.edit

            Button{
                anchors{
                    right: centerPoint.left
                    verticalCenter: parent.verticalCenter
                }
                text: "cancel"
                onClicked: {
                    configurePlayer.cancelAddingPlayer();
                }
            }

            Item{
                id: centerPoint
                anchors.centerIn: parent
                width: 20
            }

            Button{
                anchors{
                    left: centerPoint.right
                    verticalCenter: parent.verticalCenter
                }
                text: "save player"
                onClicked: {
                    configurePlayer.saveAddedPlayer();
                }
            }
        }

    }
}
