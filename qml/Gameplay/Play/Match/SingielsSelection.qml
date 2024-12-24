import QtQuick 2.15

import "MatchType"

Item {
    id: singielsSelection
    anchors.fill: parent

    required property var matchVar

    function setExampleData(){
        groupSelection.setExampleData();
    }

    GroupSelection{
        id: groupSelection

    }
}
