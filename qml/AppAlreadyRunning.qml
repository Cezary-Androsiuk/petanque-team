import QtQuick
import QtQuick.Controls.Material

import "Trace.js" as Trace

Item {
    id: applicationIsAlreadyRunning
    anchors.fill: parent

    Component.onCompleted: { Trace.t();
        rootWindow.minimumWidth = label.width + 50;
        rootWindow.minimumHeight = label.height + 50;
    }

    Label{
        id: label
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 26
        text: qsTr("Aplikacja jest już uruchomiona!");
        color: Qt.rgba(0.8, 0.3, 0.3)
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
