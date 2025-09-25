import QtQuick 2.15
import QtQuick.Controls.Material

import "../../../Trace.js" as Trace

import com.petanque.roundsummaryscorecounter 1.0

Item {
    id: summary
    anchors.fill: parent

    required property RoundSummarySC roundSummarySC;

    Item{
        id: teamScoresListContainer
        anchors{
            fill: parent
            margins: 5
        }

        readonly property int headerDelegateHeight: 50
        readonly property int elementDelegateHeight: 40
        readonly property int verticalSeparatorLength: headerDelegateHeight +
                                                       roundSummarySC.teamScoresSummary.length * elementDelegateHeight

        function findWidestTeamNameLabel(){ // kod z czata tworzący element i sprawdzający jego szerokość, następnie trzeba ustawić każdy Label z TeamName na taką szerokość
            // Definicja obiektu, który chcemy utworzyć.
            // Ważne: dołączamy importy i ustawiamy 'visible: false'.
            const qmlString = `
                import QtQuick.Controls;
                Label {
                    visible: false;
                    padding: 10 // Uwzględnij padding, jeśli jest ważny
                }
            `;

            // Utworzenie obiektu. 'root' jest rodzicem.
            let tempLabel = null;
            try {
                tempLabel = Qt.createQmlObject(qmlString, root);

                if (tempLabel === null) {
                    console.log("Error creating temporary Label.");
                    return 0;
                }

                // Ustawiamy właściwości, które wpływają na szerokość
                tempLabel.font.pointSize = fontPointSize;
                tempLabel.text = textToMeasure;

                // Odczytujemy naturalną, obliczoną szerokość
                const measuredWidth = tempLabel.implicitWidth;

                console.log(`Measured implicitWidth for "${textToMeasure}" is: ${measuredWidth}`);
                return measuredWidth;

            } finally {
                // ⚠️ KRYTYCZNIE WAŻNE: Zawsze niszczymy obiekt po użyciu!
                if (tempLabel) {
                    tempLabel.destroy();
                    console.log("Temporary Label has been destroyed.");
                }
            }
        }

        ListView{
            id: teamScoresList
            anchors.fill: parent

            model: roundSummarySC.teamScoresSummary
            boundsBehavior: Flickable.StopAtBounds
            clip: true

            header: Item{
                id: headerDelegate
                height: teamScoresListContainer.headerDelegateHeight
                width: childrensWider ? childrensWidth : teamScoresListContainer.width

                /// properties to ensure that item won't be shorter than minimum size
                readonly property double childrensWidth:
                    teamIndexesLabelsContainer.width +teamParametersLabelsContainer.width;
                readonly property bool childrensWider: childrensWidth > teamScoresListContainer.width;

                Row{
                    id: teamIndexesLabelsContainer
                    anchors{
                        top: parent.top
                        left: parent.left
                        bottom: parent.bottom
                    }

                    spacing: 5
                    Label{
                        id: teamIndexLabel
                        width: 20

                        // verticalAlignment: Text.AlignVCenter
                        // text:
                    }

                    Rectangle{
                        id: separator1
                        width: 1
                        color: Qt.rgba(1,1,1, 0.4)
                        height: teamScoresListContainer.verticalSeparatorLength
                    }

                    Label{
                        id: teamNameLabel
                        anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Team Name"

                    }


                }

                Item{
                    id: teamParametersLabelsContainer
                    anchors{
                        top: parent.top
                        right: parent.right
                        bottom: parent.bottom
                    }
                    width: childrenRect.width

                    ListView{
                        id: teamParametersLabels
                        height: parent.height
                        width: 15 * 50 /// here add model of labels and in element delegate use 15
                        model: 15
                        boundsBehavior: Flickable.StopAtBounds
                        interactive: false
                        orientation: ListView.Horizontal

                        delegate: Item{
                            width: 50
                            height: headerDelegate.height

                            Label{
                                anchors.fill: parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "LV " + index
                            }

                            Rectangle{
                                id: separator3
                                width: 1
                                color: Qt.rgba(1,1,1, 0.4)
                                height: teamScoresListContainer.verticalSeparatorLength
                            }
                        }

                    }
                }




                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.4)
                    border.width: 1
                }
            }

            delegate: Item{
                height: teamScoresListContainer.elementDelegateHeight
                width: teamScoresListContainer.width

                Label{
                    id: teamIndex
                    anchors{
                        top: parent.top
                        left: parent.left
                        leftMargin: 10
                        bottom: parent.bottom
                    }
                    width: 20

                    verticalAlignment: Text.AlignVCenter
                    text: index
                }

                Label{
                    id: teamName
                    anchors{
                        top: parent.top
                        left: teamIndex.right
                        bottom: parent.bottom
                    }
                    verticalAlignment: Text.AlignVCenter
                    text: modelData.teamName
                }


                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.4)
                    border.width: 1
                }


            }
        }
    }


}
