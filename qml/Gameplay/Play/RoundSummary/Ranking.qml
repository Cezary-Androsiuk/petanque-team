import QtQuick 2.15
import QtQuick.Controls.Material

import "../../../Trace.js" as Trace

import com.petanque.roundsummaryscorecounter 1.0

Item {
    id: ranking
    anchors.fill: parent

    required property RoundSummarySC roundSummarySC;

    Label{
        anchors.centerIn: parent
        text: "ranking"
    }
}
