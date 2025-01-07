import QtQuick 2.15
import QtQuick.Controls.Material

Item{
    id: infoPopup

    z: 9999 // allways on top

    property var rw: rootWindow
    width: rw.width
    height: rw.height

    property string title
    property string message
    property bool splitText: true
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

    property color backgroudColor: Qt.rgba(28/255, 27/255, 31/255)
    property double dimmerShowOpacity: 0.8
    property double dimmerHideOpacity: 0.0
    property bool autoClose: true

    function open(){
        popup.open();
    }

    function close(){
        popup.close();
    }

    signal confirmed()

    Rectangle{
        id: dimmer
        anchors.fill: parent
        color: infoPopup.backgroudColor
        opacity: infoPopup.dimmerHideOpacity
        visible: opacity > 0

        function show(){
            dimmer.opacity = infoPopup.dimmerShowOpacity
        }

        function hide(){
            dimmer.opacity = infoPopup.dimmerHideOpacity
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

        width: 520
        height: 350

        // dim: true
        // modal: true

        focus: true
        closePolicy: infoPopup.autoClose ?
                         Popup.CloseOnEscape | Popup.CloseOnPressOutside :
                         Popup.NoAutoClose

        onAboutToShow: {
            dimmer.show()
        }

        onAboutToHide: {
            dimmer.hide();
        }

        property int buttonsAreaHeight: 70
        property int titleItemHeight: 50
        property int buttonWidth: 90

        MouseArea {
            anchors.fill: parent
            onClicked: forceActiveFocus()
        }

        Item{
            id: titleItemHeader
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: popup.titleItemHeight
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
                            if(splitText)
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


        Item{
            id: buttonsItemFooter
            anchors{
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            height: popup.buttonsAreaHeight

            Button{
                id: cancelButton
                anchors.centerIn: parent
                text: "Ok"
                width: popup.buttonWidth
                onClicked:{
                    infoPopup.close();
                }
            }

        }
    }

}


