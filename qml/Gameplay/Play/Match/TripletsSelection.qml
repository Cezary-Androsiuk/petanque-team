import QtQuick 2.15

import "MatchType"

Item {
    id: tripletsSelection
    width: parent.width
    height: selection.height

    required property var matchVar

    Selection{
        id: selection
        matchVar: tripletsSelection.matchVar

    }
}
