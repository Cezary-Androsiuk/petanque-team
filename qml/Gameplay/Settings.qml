import QtQuick 2.15n
import QtQuick.Controls.Material

import "../Trace.js" as Trace
import "../Popups"

Item {
    id: settings

    readonly property int headerHeight: 70

    AskPopup{
        id: askAboutRestartingEvent
        title: "Restartować wydarzenie? Wszystkie dane tego wydarzenia\n"+"zostaną bezpowrotnie usunięte."
        onConfirmed: {
            rootLoader.source = "";
            Backend.restartEvent();
        }
    }

    Rectangle{
        anchors.fill: parent
        color: Material.backgroundColor
    }

    Item{
        id: header
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: settings.headerHeight

        Button{
            anchors{
                top: parent.top
                left: parent.left
                topMargin: 5
                leftMargin: 5
            }
            text: "Cofnij"
            onClicked: { Trace.t();
                playStackView.pop();
            }
        }
    }


    Button{
        anchors{
            centerIn: parent
        }
        // width: 2*height
        text: "Restartuj wydarzenie"
        onClicked: { Trace.t();

        }
    }
}
