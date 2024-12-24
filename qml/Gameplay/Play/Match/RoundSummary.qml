import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: roundSummary
    anchors.fill: parent

    required property var matchVar

    Label{
        anchors.centerIn: parent
        text: "Round Summary"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
