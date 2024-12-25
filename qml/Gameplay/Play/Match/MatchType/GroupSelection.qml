import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    anchors.fill: parent

    required property var matchVar
    readonly property var matchType: matchVar.currentMatchType

    Component.onCompleted: {
        matchType.initSelection()
    }

    function setExampleData(){

    }

    Label{
        anchors.centerIn: parent
        text: "Selection"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Column{
        anchors.fill: parent
        Repeater{
            model: 5
            Row{
                height: 50
                Repeater{
                    model: 5
                    Item{
                        height: parent.height
                        width: 40

                        Rectangle{
                            anchors.fill: parent
                            color: "transparent"
                            border.color: "white"
                            border.width: 1
                        }
                    }
                }
            }
        }
    }
}
