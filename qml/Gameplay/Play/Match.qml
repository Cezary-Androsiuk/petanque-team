import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: match
    width: parent.width
    height: 300

    Rectangle{
        anchors.fill: parent
        color: "red"
        opacity: 0.2
        border.color: "white"
        border.width: 1
    }

    required property var matchVar
    required property int currentRoundStage
    property string currentMatchTypeFile: {
        if(currentRoundStage === 0) "Match/SingielsSelection.qml";    else
        if(currentRoundStage === 1) "Match/SingielsMatch.qml";        else
        if(currentRoundStage === 2) "Match/DubletsSelection.qml";     else
        if(currentRoundStage === 3) "Match/DubletsMatch.qml";         else
        if(currentRoundStage === 4) "Match/TripletsSelection.qml";    else
        if(currentRoundStage === 5) "Match/TripletsMatch.qml";        else
        if(currentRoundStage === 6) "Match/RoundSummary.qml";         else
        {
            log.w("unknown currentRoundStage: " + currentRoundStage, "Match.qml -> currentMatchTypeFile");
            "";
        }
    }
    onCurrentMatchTypeFileChanged: {
        matchTypeLoader.setSource(currentMatchTypeFile, { matchVar: match.matchVar })
    }

    Loader{
        id: matchTypeLoader
        anchors.fill: parent
        // source: ""//currentMatchTypeFile
        onLoaded: {
            // item.width = match.width
            // console.log(item)
            // console.log(item.height)
            // console.log(match.height)
            // console.log(matchTypeLoader.width)
            // match.height = item.height
            // console.log(match.height)
            // console.log(matchTypeLoader.width)
            // console.log()
        }

    }
}
