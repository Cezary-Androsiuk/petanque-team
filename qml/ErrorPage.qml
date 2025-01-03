import QtQuick
import QtQuick.Controls.Material

Item {
    id: errorPage
    anchors.fill: parent

    required property string pageTitle;
    required property string pageMessage;

    Component.onCompleted: {
        rootWindow.minimumWidth = titleLabel.width + 50;
        rootWindow.minimumHeight = 400;
    }

    Item{
        id: content
        anchors{
            fill: parent
            topMargin: 20
            leftMargin: 40
            rightMargin: 40
            bottomMargin: 60
        }

        Label{
            id: titleLabel
            anchors{
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }

            font.pixelSize: 30
            text: pageTitle

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Label{
            id: messageLabel
            anchors{
                top: titleLabel.bottom
                left: parent.left
                right: parent.right
            }

            wrapMode: Text.WordWrap
            font.pixelSize: 16
            text: pageMessage
            opacity: 0.7

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        ScrollView{
            anchors{
                top: messageLabel.bottom
                topMargin: 10
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            TextArea{
                id: textArea

                text: log.currentSession
                font.family: "Courier New"
                // wrapMode: Text.WordWrap
                font.pixelSize: 14
                readOnly: true
            }

        }

    }
    Button{
        anchors{
            top: content.bottom
            horizontalCenter: parent.horizontalCenter
        }
        text: "Refresh"

        onClicked:{
            textArea.text = "";
            textArea.text = log.sessionLogs;
        }
    }

}
