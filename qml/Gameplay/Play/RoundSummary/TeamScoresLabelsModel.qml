import QtQuick 2.15

Item {
    /// POLISH
    readonly property alias model: teamScoresLabelsModel

    ListModel{
        id: teamScoresLabelsModel
        ListElement{ shortName: "LZ";   longName: "Liczba zwycięstw"  }
        ListElement{ shortName: "LZP";  longName: "Liczba zdobytych puktów w meczach" }
        ListElement{ shortName: "LWK";  longName: "Liczba wygranych konkurencji" }
        ListElement{ shortName: "T";    longName: "liczba wygranych tripletów" }
        ListElement{ shortName: "D";    longName: "liczba wygranych dubletów" }
        ListElement{ shortName: "S";    longName: "liczba wygranych singli" }
        ListElement{ shortName: "PZT";  longName: "małe punkty zdobyte w tripletach" }
        ListElement{ shortName: "PST";  longName: "małe punkty stracone w tripletach" }
        ListElement{ shortName: "RT";   longName: "różnica małych punktów zdobytych w tripletach" }
        ListElement{ shortName: "PZD";  longName: "małe punkty zdobyte w dubletach" }
        ListElement{ shortName: "PSD";  longName: "małe punkty stracone w dubletach" }
        ListElement{ shortName: "RD";   longName: "różnica małych punktów zdobytych w dubletach" }
        ListElement{ shortName: "PZS";  longName: "małe punkty zdobyte w singlach" }
        ListElement{ shortName: "PSS";  longName: "małe punkty stracone w singlach" }
        ListElement{ shortName: "RS";   longName: "różnica małych punktów zdobytych w singlach" }
    }

}
