import QtQuick 2.15

import "MatchType"

Item {
    id: tripletsMatch
    width: parent.width
    height: groupMatch.height

    required property var matchVar

    function setExampleData(){
        groupMatch.setExampleData();
    }

    GroupMatch{
        id: groupMatch
        matchVar: tripletsMatch.matchVar

    }
}
