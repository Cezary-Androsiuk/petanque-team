import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

import "../../Trace.js" as Trace

import "../../Popups"

Item {
    id: phase

    required property int phaseIndex;
    readonly property var phaseVar: Backend.event.phases[phaseIndex];

    readonly property int headerHeight: 50
    readonly property int footerHeight: 70

    InfoPopup{
        id: infoPopup
    }

    ConfirmNextPopup{
        id: confirmNextPopup
        fromMessage: "?"
        toMessage: "?"
        onConfirmed: { Trace.t();
            if(phaseVar.hasNext())
            {
                phaseVar.goToNext();
            }
            else
            {
                if(event.hasNextPhase())
                    event.startSecondPhase();
                else
                    event.startFinishStage();
            }
        }
    }

    Connections{
        target: phaseVar
        function onVerified(){ Trace.t();
            confirmNextPopup.title = "Are you sure to move on?"
            confirmNextPopup.fromMessage = Backend.event.getConfirmNextPopupTextFrom();
            confirmNextPopup.toMessage = Backend.event.getConfirmNextPopupTextTo();
            confirmNextPopup.fOpen();
        }

        function onVerificationFailed(message){ Trace.t(message);
            infoPopup.title = "Phase data are not valid!";
            infoPopup.splitText = true;
            infoPopup.message = message;
            infoPopup.fOpen();
        }
    }

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

            Item{
                id: tabBar
                width: parent.width
                height: 60

                Row{
                    Repeater{
                        model: !(phaseVar)?0: phaseVar.subPhases
                        Item{
                            height: tabBar.height
                            width: tabBar.width / phaseVar.subPhasesCount

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
                                onClicked: { Trace.t();
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
                height: parent.height-tabBar.height

                Repeater{
                    model: !(phaseVar)?0: phaseVar.subPhases
                    Item{
                        SubPhase{
                            id: subPhase
                            anchors.fill: parent
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

        Button{
            anchors{
                top: parent.top
                right: parent.right
                rightMargin: 60
                bottom: parent.bottom
            }
            // width: 2*height
            text: "Settings"
            onClicked: { Trace.t();
                playStackView.push(settingsComponent.createObject(playStackView));
            }
        }

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

        Button{
            id: nextButton
            anchors{
                left: centerItem.right
                leftMargin: 5
                verticalCenter: parent.verticalCenter
            }
            text: "Next"
            onClicked: { Trace.t();
                log.i("next pressed",
                      "Phase.qml -> nextButton -> onClicked",
                      log.toAction("save session"))
                phase.phaseVar.verify();
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
            visible: Backend.isDebugMode
            onClicked:{ Trace.t();
                phase.phaseVar.assignExampleData();
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
            visible: Backend.isDebugMode
            onClicked:{ Trace.t();
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
