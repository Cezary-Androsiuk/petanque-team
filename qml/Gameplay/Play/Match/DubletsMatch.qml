import QtQuick 2.15

import "MatchType"

Item {
    id: dubletsMatch
    width: parent.width
    height: groupMatch.height

    required property var matchVar

    function setExampleData(){
        groupMatch.setExampleData();
    }

    GroupMatch{
        id: groupMatch
        matchVar: dubletsMatch.matchVar

    }
}
