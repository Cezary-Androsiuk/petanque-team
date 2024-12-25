import QtQuick 2.15

import "MatchType"

Item {
    id: dubletsSelection
    width: parent.width
    height: selection.height

    required property var matchVar

    Selection{
        id: selection
        matchVar: dubletsSelection.matchVar

    }
}
