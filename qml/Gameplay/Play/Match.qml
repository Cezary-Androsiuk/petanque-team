import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: match
    width: parent.width
    height: matchTypeLoader.item ? matchTypeLoader.item.height : 0

    required property var matchVar
    required property int currentRoundStage

    property string currentMatchTypeFile: {
        if(currentRoundStage === 6)
            "Match/RoundSummary.qml";
        else
        {
            if(currentRoundStage % 2 === 0)
                "Match/SelectionTemplate.qml";
            else
                "Match/MatchTemplate.qml";
        }
    }
    onCurrentMatchTypeFileChanged: {
        var param = {
            matchVar: match.matchVar
        }
        matchTypeLoader.setSource(currentMatchTypeFile, param)
    }

    Loader{
        id: matchTypeLoader
        anchors.fill: parent
    }
}
