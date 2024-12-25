import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: match
    anchors.fill: parent

    required property var matchVar
    readonly property var matchType: matchVar.currentMatchType

    Component.onCompleted: {
        console.log("on completed matchVar: " + matchVar)
        console.log("on completed matchType: " + matchType)
        matchType.initMatch()
    }

    Label{
        anchors.centerIn: parent
        text: "Match"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
