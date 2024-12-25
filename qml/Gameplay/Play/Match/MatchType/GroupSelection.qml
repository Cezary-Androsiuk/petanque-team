import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    anchors.fill: parent

    required property var matchVar
    readonly property var matchType: matchVar.currentMatchType

    Component.onCompleted: {
        matchType.initSelection()
    }

    Label{
        anchors.centerIn: parent
        text: "Selection"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

}
