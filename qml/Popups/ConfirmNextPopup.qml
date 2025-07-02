import QtQuick 2.15
import QtQuick.Controls.Material

import "../Trace.js" as Trace

Popup {
    id: confirmNextPopup
    parent: rootWindowCenterPopupAnchor
    width: parent.width
    height: parent.height

    property bool openedByFOpen: false

    onAboutToShow: { Trace.t();
        if(!openedByFOpen)
            log.e("popup opened by open(), not fOpen()!", "ConfirmNextPopup.qml")
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

        confirmNextPopup.open();
    }

    function fClose(){ Trace.t();
        openedByFOpen = false;
        confirmNextPopup.close();
    }

    property string title: "Are you sure to move on to\nthe next stage?"
    property string fromMessage
    property string toMessage

    signal confirmed();

    property bool autoClose: true

    focus: true
    closePolicy: confirmNextPopup.autoClose ?
                     Popup.CloseOnEscape | Popup.CloseOnPressOutside :
                     Popup.NoAutoClose

    background: Item {
        MouseArea{ /// better than default, because handle clicks
            id: backgroudMouseArea
            anchors.fill: parent
            onClicked: {
                if(confirmNextPopup.autoClose)
                    confirmNextPopup.fClose();
            }
        }

        Rectangle{
            id: popupBody
            anchors.centerIn: parent
            width: 340
            height: 180
            color: "#3f3e40"
            radius: 6

            MouseArea{ // prevents backgroundMouseArea trigger
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
                        left: parent.left
                        leftMargin: 10
                        right: parent.right
                        rightMargin: 10
                        top: parent.top
                        topMargin: 24
                    }
                    text: confirmNextPopup.title
                    font.pixelSize: 22
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    wrapMode: Text.WordWrap
                }

                Label{
                    id: messageLabel
                    anchors{
                        left: parent.left
                        leftMargin: 10
                        right: parent.right
                        rightMargin: 10
                        top: titleLabel.bottom
                        topMargin: 22
                    }

                    readonly property bool fromFieldIsSet: confirmNextPopup.fromMessage != "";
                    readonly property bool toFieldIsSet: confirmNextPopup.toMessage != "";
                    readonly property bool bothFieldsAreSet: fromFieldIsSet && toFieldIsSet;

                    text: {
                        if(bothFieldsAreSet)
                            confirmNextPopup.fromMessage + "  ➤  " + confirmNextPopup.toMessage;
                        else if(fromFieldIsSet)
                            "from " + confirmNextPopup.fromMessage;
                        else if(toFieldIsSet)
                            "to " + confirmNextPopup.toMessage;
                        else
                            "";
                    }
                    opacity: 0.8
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    visible: fromFieldIsSet || toFieldIsSet
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
                    text: "Cancel"
                    anchors.verticalCenter: parent.verticalCenter
                    x: popupBody.spaceBeetweenButtons
                    width: popupBody.buttonWidth
                    onClicked:{ Trace.t();
                        confirmNextPopup.fClose();
                    }
                }

                Button{
                    id: nextButton
                    text: "Next"
                    anchors.verticalCenter: parent.verticalCenter
                    x: popupBody.spaceBeetweenButtons *2 + popupBody.buttonWidth
                    width: popupBody.buttonWidth
                    onClicked:{ Trace.t();
                        confirmNextPopup.fClose();
                        confirmNextPopup.confirmed();
                    }
                }
            }
        }

    }


}





