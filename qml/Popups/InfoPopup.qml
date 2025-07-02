import QtQuick 2.15
import QtQuick.Controls.Material

import "../Trace.js" as Trace

Popup {
    id: infoPopup
    parent: rootWindowCenterPopupAnchor
    width: parent.width
    height: parent.height

    property bool openedByFOpen: false

    onAboutToShow: { Trace.t();
        if(!openedByFOpen)
            log.e("popup opened by open(), not fOpen()!", "InfoPopup.qml")
        rootWindowPopupDimmer.show();
    }

    onAboutToHide: { Trace.t();
        rootWindowPopupDimmer.hide();
    }

    readonly property string splitedMessage: {
        // message.replace(/:/g, "\n");
        //   / sign starts regex
        //   /g combination tells to look for all instances of :
        if(splitText)
            message.split(":").join(":\n") // simpler
                .split("\n ").join("\n"); // removes spaces in new lines
        else
            "";

    }

    function fOpen(){ Trace.t();
        openedByFOpen = true;
        if(!Backend.enabledPopups)
        {
            return;
        }

        infoPopup.open();
    }

    function fClose(){ Trace.t();
        openedByFOpen = false;
        infoPopup.close();
    }

    property string title
    property string message
    property bool splitText: true
    property bool autoClose: true

    focus: true
    closePolicy: infoPopup.autoClose ?
                     Popup.CloseOnEscape | Popup.CloseOnPressOutside :
                     Popup.NoAutoClose

    background: Item {
        MouseArea{ /// better than default, because handle clicks
            id: backgroudMouseArea
            anchors.fill: parent
            onClicked: {
                if(infoPopup.autoClose)
                    infoPopup.close();
            }
        }

        Rectangle{
            id: popupBody
            anchors.centerIn: parent
            width: 520
            height: 350
            color: "#3f3e40"
            radius: 6

            MouseArea { // to lose textArea focus
                anchors.fill: parent
                onClicked: forceActiveFocus()
            }

            property int titleItemHeight: 50

            Item{
                id: titleItemHeader
                anchors{
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                height: popupBody.titleItemHeight
                clip: true

                Label{
                    id: titleLabel
                    anchors{
                        fill: parent
                        margins: 10
                    }

                    text: infoPopup.title
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    wrapMode: Text.WordWrap
                }
            }

            Item{
                id: content
                anchors{
                    top: titleItemHeader.bottom
                    left: parent.left
                    right: parent.right
                    bottom: buttonsItemFooter.top
                }

                Item{
                    anchors{
                        fill: parent
                        margins: 10
                    }

                    ScrollView{
                        anchors.fill: parent
                        TextArea{
                            id: textArea
                            text: {
                                if(infoPopup.splitText)
                                    infoPopup.splitedMessage
                                else
                                    infoPopup.message
                            }
                            font.family: "Courier New"
                            font.pixelSize: 14
                            readOnly: true
                        }
                    }
                }

            }

            property int buttonsAreaHeight: 70
            property int buttonWidth: 90


            Item{
                id: buttonsItemFooter
                anchors{
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                height: popupBody.buttonsAreaHeight

                Button{
                    id: cancelButton
                    anchors.centerIn: parent
                    text: "Ok"
                    width: popupBody.buttonWidth
                    onClicked:{ Trace.t();
                        infoPopup.fClose();
                    }
                }

            }
        }

    }


}




