import QtQuick 2.15
import QtQuick.Controls.Material

import "../../Trace.js" as Trace

Item {
    id: infoField
    width: column.implicitWidth + 35 // 35 is a right margin
    height: column.implicitHeight + 30 // 30 is a bootom margin

    // MouseArea{
    //     id: looseFocus
    //     anchors.fill: parent
    //     onClicked:{
    //         infoField.focus = true
    //     }
    // }

    readonly property var event: Backend.event
    property bool elementCompleted: false
    Component.onCompleted: {
        infoField.elementCompleted = true;
    }

    Item{
        anchors{
            fill: parent
            margins: 16
        }

        Column{
            id: column
            // width: parent.width
            width: childrenRect.width
            spacing: 5

            TextField{
                id: eventNameTextField
                height: 60
                width: 400

                placeholderText: qsTr("Event name")
                text: (!event)?null: event.name
                onTextEdited: { Trace.t();
                    event.name = text
                }
            }


            Row{
                id: firstPhaseDateItem
                height: childrenRect.height
                width: childrenRect.width
                spacing: 10

                TextField{
                    id: firstPhaseDateTextField
                    height: 60
                    width: 230

                    placeholderText: qsTr("First phase date")
                    text: (!event)?null: event.firstPhaseDate
                    onTextEdited: {
                        event.firstPhaseDate = text
                    }
                }

                Button{
                    // id: setTodaysDateButton
                    anchors.verticalCenter: firstPhaseDateTextField.verticalCenter

                    text: qsTr("Todays Date")
                    onClicked: {
                        var now = new Date();
                        var todaysDate = now.toISOString().slice(0, 10); // Gemini

                        firstPhaseDateTextField.focus = true
                        firstPhaseDateTextField.text = todaysDate;
                        firstPhaseDateTextField.textEdited();
                    }
                }

                Label{
                    anchors.verticalCenter: firstPhaseDateTextField.verticalCenter
                    text: "Format: YYYY-MM-DD"
                    opacity: 0.4
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }


            Row{
                id: secondPhaseDateItem
                height: childrenRect.height
                width: childrenRect.width
                spacing: 10

                TextField{
                    id: secondPhaseDateTextField
                    height: 60
                    width: 230

                    placeholderText: qsTr("Second phase date")
                    text: (!event)?null: event.secondPhaseDate
                    onTextEdited: {
                        event.secondPhaseDate = text
                    }
                }

                Button{
                    // id: setTodayDateButton
                    anchors.verticalCenter: secondPhaseDateTextField.verticalCenter

                    text: qsTr("Todays Date")
                    onClicked: {
                        var now = new Date();
                        var todaysDate = now.toISOString().slice(0, 10); // Gemini

                        secondPhaseDateTextField.focus = true
                        secondPhaseDateTextField.text = todaysDate;
                        secondPhaseDateTextField.textEdited();
                    }
                }

                Label{
                    anchors.verticalCenter: secondPhaseDateTextField.verticalCenter
                    text: "Format: YYYY-MM-DD"
                    opacity: 0.4
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }


            TextField{
                id: competitionOrganizerTextField
                height: 60
                width: 400

                placeholderText: qsTr("Competition Organizer")
                text: (!event)?null: event.competitionOrganizer
                onTextEdited: { Trace.t();
                    event.competitionOrganizer = text
                }
            }


            TextField{
                id: firstPhasePlaceTextField
                height: 60
                width: 500

                placeholderText: qsTr("First phase place")
                text: (!event)?null: event.firstPhasePlace
                onTextEdited: { Trace.t();
                    event.firstPhasePlace = text
                }
            }


            TextField{
                id: secondPhasePlaceTextField
                height: 60
                width: 500

                placeholderText: qsTr("Second phase place")
                text: (!event)?null: event.secondPhasePlace
                onTextEdited: { Trace.t();
                    event.secondPhasePlace = text
                }
            }


            TextField{
                id: unionDelegateTextField
                height: 60
                width: 400

                placeholderText: qsTr("Union delegate")
                text: (!event)?null: event.unionDelegate
                onTextEdited: { Trace.t();
                    event.unionDelegate = text
                }
            }


            Item{
                id: judgesItem
                height: {
                    let count = (!event) ? 1 : event.judges.length+1;
                    return count * judgesItem.judgeHeight
                }
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter

                readonly property int judgeHeight: 80

                Rectangle{
                    anchors.fill: parent

                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.4)
                    border.width: 1
                }

                ListView{
                    id: judgesListView
                    anchors.fill: parent
                    boundsBehavior: Flickable.StopAtBounds
                    model: (!event)?null: event.judges

                    footer: Item{
                        width: judgesListView.width
                        height: judgesItem.judgeHeight
                        Button{
                            id: addJudgeButton
                            anchors.centerIn: parent

                            text: qsTr("Add judge")
                            onClicked: {
                                event.addJudge();
                            }
                        }
                    }

                    delegate: Item{
                        width: judgesListView.width
                        height: judgesItem.judgeHeight
                        TextField{
                            id: judgeTextField
                            anchors{
                                left: parent.left
                                verticalCenter: parent.verticalCenter
                                margins: 5
                            }
                            width: 300
                            height: 60
                            placeholderText: qsTr("Judge")
                            text: modelData
                            onTextEdited: {
                                event.setJudge(index, text);
                            }
                        }

                        Button{
                            id: deleteJudgeButton
                            anchors{
                                top: parent.top
                                right: parent.right
                                bottom: parent.bottom
                                margins: 15
                            }
                            width: height
                            text: "X"
                            onClicked: {
                                event.deleteJudge(index);
                            }
                        }
                    }
                }


            }
        }
    }


}
