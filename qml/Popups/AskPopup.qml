import QtQuick 2.15
import QtQuick.Controls.Material

import "../Trace.js" as Trace

Popup {
    id: askPopup
    parent: rootWindowCenterPopupAnchor
    width: parent.width
    height: parent.height

    property bool openedByFOpen: false

    onAboutToShow: { Trace.t();
        if(!openedByFOpen)
            log.e("popup opened by open(), not fOpen()!", "AskPopup.qml")
        rootWindowPopupDimmer.show();
    }

    onAboutToHide: { Trace.t();
        rootWindowPopupDimmer.hide();
    }

    function fOpen(){ Trace.t();
        openedByFOpen = true;
        if(!Backend.enabledPopups)
        {
            confirmed();
            return;
        }

        askPopup.open();
    }

    function fClose(){ Trace.t();
        openedByFOpen = false;
        askPopup.close();
    }

    property string title
    property string lButtonText: "Cancel"
    property string rButtonText: "Yes"

    signal confirmed();

    property bool autoClose: true

    focus: true
    closePolicy: askPopup.autoClose ?
                     Popup.CloseOnEscape | Popup.CloseOnPressOutside :
                     Popup.NoAutoClose

    background: Item {
        MouseArea{ /// better than default, because handle clicks
            id: backgroudMouseArea
            anchors.fill: parent
            onClicked: {
                if(askPopup.autoClose)
                    askPopup.fClose();
            }
        }

        Rectangle{
            id: popupBody
            anchors.centerIn: parent
            width: 340
            height: 180
            color: "#3f3e40"
            radius: 6

            MouseArea{
                id: bodyMouseArea
                anchors.fill: parent
                onClicked: {}
            }

            Item{
                id: content
                anchors{
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    bottom: buttonsItem.top
                }

                Label{
                    id: titleLabel
                    anchors{
                        fill: parent
                        margins: 10
                    }
                    text: askPopup.title
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                }

            }

            property int buttonsAreaHeight: 70
            property int buttonWidth: 90

            property double spaceBeetweenButtons:
                (buttonsItem.width - cancelButton.width - nextButton.width)/3


            Item{
                id: buttonsItem
                anchors{
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                height: popupBody.buttonsAreaHeight

                Button{
                    id: cancelButton
                    text: askPopup.lButtonText
                    anchors.verticalCenter: parent.verticalCenter
                    x: popupBody.spaceBeetweenButtons
                    width: popupBody.buttonWidth
                    onClicked:{ Trace.t();
                        askPopup.fClose();
                    }
                }

                Button{
                    id: nextButton
                    text: askPopup.rButtonText
                    anchors.verticalCenter: parent.verticalCenter
                    x: popupBody.spaceBeetweenButtons *2 + popupBody.buttonWidth
                    width: popupBody.buttonWidth
                    onClicked:{ Trace.t();
                        askPopup.fClose();
                        askPopup.confirmed();
                    }
                }
            }
        }

    }


}
