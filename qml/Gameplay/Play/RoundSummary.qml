import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

import "../../Trace.js" as Trace

import "RoundSummary"

Item {
    id: roundSummary

    property var roundVar
    property int headerHeight
    property int footerHeight


    Column{
        anchors.fill: parent
        spacing: 0

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
                        visible: stackLayout.currentIndex === 0
                    }

                    TabButton{
                        anchors.fill: parent
                        text: qsTr("Summary")
                        font.pixelSize: 22
                        checkable: false
                        onClicked: { Trace.t();
                            stackLayout.currentIndex = 0
                        }
                    }
                }


                Item{
                    height: tabBar.height
                    width: tabBar.width / 2

                    Rectangle{
                        anchors.fill: parent
                        color: Qt.rgba(1,1,1, 0.03)
                        visible: stackLayout.currentIndex === 1
                    }

                    TabButton{
                        anchors.fill: parent
                        text: qsTr("Ranking")
                        font.pixelSize: 22
                        checkable: false
                        onClicked: { Trace.t();
                            stackLayout.currentIndex = 1
                        }
                    }
                }
            }
        }

        StackLayout{
            id: stackLayout
            width: parent.width
            height: parent.height-tabBar.height

            Item{ Summary{} }
            Item{ Ranking{} }
        }
    }
}
