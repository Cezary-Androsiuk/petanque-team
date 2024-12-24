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

    Component.onCompleted: {
        log.i("completed: " + matchVar, "Match->onCompleted")
    }

    Loader{
        anchors.fill: parent
        sourceComponent: {
            var crs = matchVar.currentRoundStage;
            if(crs === 6) summaryExample; else
            {
                if(crs % 2 === 0)
                    selectionExample;
                else
                    matchExample;

            }
        }

        Component{
            id: summaryExample
            Item{
                anchors.fill: parent
                Label{
                    id: headerLabel
                    anchors.centerIn: parent

                    text: "summary example"
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        Component{
            id: matchExample
            Item{
                anchors.fill: parent
                Label{
                    id: headerLabel
                    anchors.centerIn: parent

                    text: "match example"
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        Component{
            id: selectionExample
            Item{
                anchors.fill: parent
                Label{
                    id: headerLabel
                    anchors.centerIn: parent

                    text: "selection example"
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}
