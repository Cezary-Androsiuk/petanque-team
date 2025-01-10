import QtQuick

import "Popups"

Item {
    readonly property alias info: infoPopup
    readonly property alias confirmNext: confirmNextPopup
    readonly property alias ask: askPopup

    InfoPopup{
        id: infoPopup
    }

    ConfirmNextPopup{
        id: confirmNextPopup
        // used in Event.qml
    }

    AskPopup{
        id: askPopup
        // used in TeamDelegate.qml
        // used in PlayerDelegate.qml
    }
}
