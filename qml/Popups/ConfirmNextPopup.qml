import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: confirmNextPopup

    z: 9999 // allways on top

    property var rw: rootWindow
    width: rw.width
    height: rw.height

    property string title: "Are you sure to move on to\nthe next stage?"
    property string fromMessage
    property string toMessage

    property color backgroudColor: Qt.rgba(28/255, 27/255, 31/255)
    property double dimmerShowOpacity: 0.8
    property double dimmerHideOpacity: 0.0
    property bool autoClose: true

    function open(){
        if(!Backend.enabledPopups)
        {
            confirmed();
            return;
        }

        popup.open();
    }

    function close(){
        popup.close();
    }
    signal confirmed()

    Rectangle{
        id: dimmer
        anchors.fill: parent
        color: confirmNextPopup.backgroudColor
        opacity: confirmNextPopup.dimmerHideOpacity
        visible: opacity > 0

        function show(){
            dimmer.opacity = confirmNextPopup.dimmerShowOpacity
        }

        function hide(){
            dimmer.opacity = confirmNextPopup.dimmerHideOpacity
        }

        Behavior on opacity {
            NumberAnimation {
                duration: 100 // slow down changing opacity
            }
        }
    }

    Popup {
        id: popup
        anchors.centerIn: parent

        width: 340
        height: 200

        // dim: true
        // modal: true

        focus: true
        closePolicy: confirmNextPopup.autoClose ?
                         Popup.CloseOnEscape | Popup.CloseOnPressOutside :
                         Popup.NoAutoClose

        onAboutToShow: {
            dimmer.show()
        }

        onAboutToHide: {
            dimmer.hide();
        }

        property int buttonsAreaHeight: 70
        property int buttonWidth: 90

        property double spaceBeetweenButtons:
            (buttonsItem.width - cancelButton.width - nextButton.width)/3


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
                    topMargin: 10
                }
                text: confirmNextPopup.title
                font.pixelSize: 20
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
                    topMargin: 15
                }

                readonly property bool fromFieldIsSet: confirmNextPopup.fromMessage != "";
                readonly property bool toFieldIsSet: confirmNextPopup.toMessage != "";
                readonly property bool bothFieldsAreSet: fromFieldIsSet && toFieldIsSet;

                text: {
                    if(bothFieldsAreSet)
                        confirmNextPopup.fromMessage + "  ➤  " + confirmNextPopup.toMessage;
                    else if(fromFieldIsSet)
                        confirmNextPopup.fromMessage;
                    else if(toFieldIsSet)
                        confirmNextPopup.toMessage;
                    else
                        "";
                }
                opacity: 0.8
                font.pixelSize: 13
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
                visible: bothFieldsAreSet
            }
        }

        Item{
            id: buttonsItem
            anchors{
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            height: popup.buttonsAreaHeight

            Button{
                id: cancelButton
                text: "Cancel"
                anchors.verticalCenter: parent.verticalCenter
                x: popup.spaceBeetweenButtons
                width: popup.buttonWidth
                onClicked:{
                    confirmNextPopup.close();
                }
            }

            Button{
                id: nextButton
                text: "Next"
                anchors.verticalCenter: parent.verticalCenter
                x: popup.spaceBeetweenButtons *2 + popup.buttonWidth
                width: popup.buttonWidth
                onClicked:{
                    confirmNextPopup.confirmed();
                    confirmNextPopup.close();
                }
            }
        }
    }

}


