import QtQuick 2.15

import "MatchType"

Item {
    id: singielsSelection
    width: parent.width
    height: 300

    required property var matchVar

    function setExampleData(){
        groupSelection.setExampleData();
    }

    GroupSelection{
        id: groupSelection
        matchVar: singielsSelection.matchVar

    }
}
