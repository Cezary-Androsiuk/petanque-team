import QtQuick

import "Popups"

Item {
    readonly property alias failedEventCreationInfo: failedEventCreationInfoPopup
    readonly property alias failedTeamCreationInfo: failedTeamCreationInfoPopup
    readonly property alias failedPlayerCreationInfo: failedPlayerCreationInfoPopup
    readonly property alias confirmNextRoundStage: confirmNextRoundStagePopup
    readonly property alias askDeleteTeam: askDeleteTeamPopup
    readonly property alias askDeletePlayer: askDeletePlayerPopup

    InfoPopup{
        id: failedEventCreationInfoPopup
        // used in Event.qml
    }
    InfoPopup{
        id: failedTeamCreationInfoPopup
        // used in TeamDelegate.qml
    }
    InfoPopup{
        id: failedPlayerCreationInfoPopup
        // used in PlayerDelegate.qml
    }



    ConfirmNextPopup{
        id: confirmNextRoundStagePopup
        // used in Event.qml
    }



    AskPopup{
        id: askDeleteTeamPopup
        // used in TeamDelegate.qml
    }
    AskPopup{
        id: askDeletePlayerPopup
        // used in PlayerDelegate.qml
    }
}
