import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    id: phase
    anchors.fill: parent

    required property int phaseIndex;
    readonly property var phaseVar: Backend.event.phases[phaseIndex];

    readonly property int headerHeight: 30
    readonly property int footerHeight: 70


    Item{
        id: content
        anchors{
            top: header.bottom
            left: parent.left
            leftMargin: 30
            right: parent.right
            rightMargin: 30
            bottom: footer.top
        }

        Column{
            anchors.fill: parent
            spacing: 0

            // TabBar{
            //     id: tabBar
            //     width: parent.width

            //     Repeater{
            //         model: 2//phaseVar.subPhases
            //         TabButton{
            //             text: qsTr("Phase ") + index//modelData.name

            //         }
            //     }
            // }

            Item{
                id: myTabBar
                width: parent.width
                height: 60

                Row{
                    Repeater{
                        model: phaseVar.subPhases
                        Item{
                            height: myTabBar.height
                            width: myTabBar.width / phaseVar.subPhasesCount

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
            }

            StackLayout{
                id: stackLayout
                width: parent.width

                // tabBar
                // height: parent.height-tabBar.height
                // currentIndex: tabBar.currentIndex

                // myTabBar
                height: parent.height-myTabBar.height

                Repeater{
                    model: phaseVar.subPhases
                    Item{
                        Component.onCompleted: {
                            console.log("item "+index+" created")
                        }

                        SubPhase{
                            subPhaseVar: modelData
                        }

                    }
                }



            }
        }

        Rectangle{
            id: contentBorder
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }
    }


    Item{
        id: header
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: phase.headerHeight

        // Label{
        //     id: titleLabel
        //     anchors{
        //         horizontalCenter: parent.horizontalCenter
        //         top: parent.top
        //         topMargin: 5
        //     }
        //     horizontalAlignment: Text.AlignHCenter
        //     verticalAlignment: Text.AlignVCenter

        //     text: qsTr("Team Selection")
        //     font.pixelSize: 30
        // }

        Rectangle{
            id: headerBorder
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }
    }

    Item{
        id: footer
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: phase.footerHeight


        Item{
            id: centerItem
            anchors{
                centerIn: parent
            }
        }

        // Button{
        //     id: backButton
        //     anchors{
        //         right: centerItem.left
        //         rightMargin: 5
        //         verticalCenter: parent.verticalCenter
        //     }
        //     enabled: Backend.event.hasPrevRoundStage;

        //     text: "Back"
        //     onClicked: {
        //         Backend.event.goToPrevRoundStage();
        //     }
        // }

        Button{
            id: nextButton
            anchors{
                left: centerItem.right
                leftMargin: 5
                verticalCenter: parent.verticalCenter
            }
            text: "Next"
            onClicked: {
                phase.phaseVar.gonext();
                // phase.phaseVar.verifyCurrentRoundStage();
            }
        }

        Button{
            id: exampleDataButton
            anchors{
                left: nextButton.right
                leftMargin: 30
                verticalCenter: parent.verticalCenter
            }
            text: "Set Example Data"
            onClicked:{
                continueLoader.item.setExampleData()
            }
        }

        Button{
            id: exampleDataAndNextButton
            anchors{
                left: exampleDataButton.right
                leftMargin: 30
                verticalCenter: parent.verticalCenter
            }
            text: "Set Example Data And Go Next"
            onClicked:{
                exampleDataButton.clicked();
                nextButton.clicked();
            }
        }

        Rectangle{
            id: footerBorder
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }
    }


}
