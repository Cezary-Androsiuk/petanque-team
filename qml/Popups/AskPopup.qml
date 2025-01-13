import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: askPopup

    z: 9999 // allways on top

    property var rw: rootWindow
    width: rw.width
    height: rw.height

    property string title
    property string lButtonText: "Cancel"
    property string rButtonText: "Yes"
    property var arg1;

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
    // signal confirmed()
    signal confirmed(var a1);

    Rectangle{
        id: dimmer
        anchors.fill: parent
        color: askPopup.backgroudColor
        opacity: askPopup.dimmerHideOpacity
        visible: opacity > 0

        function show(){
            dimmer.opacity = askPopup.dimmerShowOpacity
        }

        function hide(){
            dimmer.opacity = askPopup.dimmerHideOpacity
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
        height: 180

        // dim: true
        // modal: true

        focus: true
        closePolicy: askPopup.autoClose ?
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
                text: askPopup.lButtonText
                anchors.verticalCenter: parent.verticalCenter
                x: popup.spaceBeetweenButtons
                width: popup.buttonWidth
                onClicked:{
                    askPopup.close();
                }
            }

            Button{
                id: nextButton
                text: askPopup.rButtonText
                anchors.verticalCenter: parent.verticalCenter
                x: popup.spaceBeetweenButtons *2 + popup.buttonWidth
                width: popup.buttonWidth
                onClicked:{
                    // askPopup.confirmed();
                    console.log(arg1)
                    askPopup.confirmed(arg1);
                    askPopup.close();
                }
            }
        }
    }

}


