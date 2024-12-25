import QtQuick 2.15

import "MatchType"

Item {
    id: dubletsMatch
    width: parent.width
    height: match.height

    required property var matchVar

    Match{
        id: match
        matchVar: dubletsMatch.matchVar

    }
}
