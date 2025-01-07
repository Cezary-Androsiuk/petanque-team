import QtQuick 2.15
import QtQuick.Controls.Material

Popup {
    id: confirmNextPopup

    property var rw: rootWindow

    required property string text
    // required property string description

    // readonly property bool containsDescription: description != ""

    signal confirmed()

    property double widthRatio: 0.1
    property double heightRatio: 0.1

    width: rw.width * 0.1
    height: rw.height * 0.1
    x: rw.width/2 - width/2
    y: (rw.height * 0.65) - height/2


}
