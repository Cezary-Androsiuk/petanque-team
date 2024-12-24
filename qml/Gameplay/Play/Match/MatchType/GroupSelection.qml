import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    anchors.fill: parent

    required property var matchVar

    Label{
        anchors.centerIn: parent
        text: "Selection"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

}
