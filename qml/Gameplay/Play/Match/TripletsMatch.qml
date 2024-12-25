import QtQuick 2.15

import "MatchType"

Item {
    id: tripletsMatch
    width: parent.width
    height: match.height

    required property var matchVar

    Match{
        id: match
        matchVar: tripletsMatch.matchVar

    }
}
