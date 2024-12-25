import QtQuick 2.15

import "MatchType"

Item {
    id: singielsMatch
    width: parent.width
    height: match.height

    required property var matchVar

    function setExampleData(){
        match.setExampleData();
    }

    Match{
        id: match
        matchVar: singielsMatch.matchVar

    }
}
