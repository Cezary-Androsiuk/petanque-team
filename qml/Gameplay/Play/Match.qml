import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: match
    width: parent.width
    height: 40

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
            // if (item && (typeof item.setParameters === "function")) {
            //     item.setParameters({ matchVar: match.matchVar });
            // }
        }

        // sourceComponent: {
        //     var crs = currentRoundStage;
        //     if(crs === 6) summaryExample; else
        //     {
        //         if(crs % 2 === 0)
        //             selectionExample;
        //         else
        //             matchExample;
        //     }
        // }

        // Component{
        //     id: summaryExample
        //     Item{
        //         anchors.fill: parent
        //         Label{
        //             id: headerLabel
        //             anchors.centerIn: parent

        //             text: "summary example"
        //             font.pixelSize: 24
        //             horizontalAlignment: Text.AlignHCenter
        //             verticalAlignment: Text.AlignVCenter
        //         }
        //     }
        // }

        // Component{
        //     id: matchExample
        //     Item{
        //         anchors.fill: parent
        //         Label{
        //             id: headerLabel
        //             anchors.centerIn: parent

        //             text: "match example"
        //             font.pixelSize: 24
        //             horizontalAlignment: Text.AlignHCenter
        //             verticalAlignment: Text.AlignVCenter
        //         }
        //     }
        // }

        // Component{
        //     id: selectionExample
        //     Item{
        //         anchors.fill: parent
        //         Label{
        //             id: headerLabel
        //             anchors.centerIn: parent

        //             text: "selection example"
        //             font.pixelSize: 24
        //             horizontalAlignment: Text.AlignHCenter
        //             verticalAlignment: Text.AlignVCenter
        //         }
        //     }
        // }
    }
}
