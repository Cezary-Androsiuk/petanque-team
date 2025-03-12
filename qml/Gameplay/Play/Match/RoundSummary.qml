import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    id: roundSummary
    anchors.fill: parent

    required property var matchVar

    Item{
        id: tabBar
        width: parent.width
        height: 60
        Row{
            Item{
                height: tabBar.height
                width: tabBar.width / 2

                Rectangle{
                    anchors.fill: parent
                    color: Qt.rgba(1,1,1, 0.03)
                    visible: stackLayout.currentIndex === index
                }

                TabButton{
                    anchors.fill: parent
                    text: qsTr("Phase ") + modelData.name
                    font.pixelSize: 22
                    checkable: false
                    onClicked: {
                        stackLayout.currentIndex = index
                    }
                }
            }

            Item{
                height: tabBar.height
                width: tabBar.width / 2

                Rectangle{
                    anchors.fill: parent
                    color: Qt.rgba(1,1,1, 0.03)
                    visible: stackLayout.currentIndex === index
                }

                TabButton{
                    anchors.fill: parent
                    text: qsTr("Phase ") + modelData.name
                    font.pixelSize: 22
                    checkable: false
                    onClicked: {
                        stackLayout.currentIndex = index
                    }
                }
            }
        }
    }

    StackLayout{
        id: stackLayout
        width: parent.width
        height: parent.height-tabBar.height

        Item{ // current round data
            anchors.fill: parent

            Label{
                anchors.centerIn: parent
                text: "Round Summary 1"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Item{ // ranking
            anchors.fill: parent

            Label{
                anchors.centerIn: parent
                text: "Round Summary 2"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

    }


}
