import QtQuick 2.15

Item {
    readonly property alias model: teamScoresLabelsModel

    /// POLISH
    ListModel{
        id: teamScoresLabelsModel
        ListElement{ shortName: "LZ";   longName: "Liczba zwycięstw"  }
        ListElement{ shortName: "LZP";  longName: "Liczba zdobytych puktów w meczach" }
        ListElement{ shortName: "LWK";  longName: "Liczba wygranych konkurencji" }
        ListElement{ shortName: "T";    longName: "Liczba wygranych tripletów" }
        ListElement{ shortName: "D";    longName: "Liczba wygranych dubletów" }
        ListElement{ shortName: "S";    longName: "Liczba wygranych singli" }
        ListElement{ shortName: "PZT";  longName: "Małe punkty zdobyte w tripletach" }
        ListElement{ shortName: "PST";  longName: "Małe punkty stracone w tripletach" }
        ListElement{ shortName: "RT";   longName: "Różnica małych punktów zdobytych w tripletach" }
        ListElement{ shortName: "PZD";  longName: "Małe punkty zdobyte w dubletach" }
        ListElement{ shortName: "PSD";  longName: "Małe punkty stracone w dubletach" }
        ListElement{ shortName: "RD";   longName: "Różnica małych punktów zdobytych w dubletach" }
        ListElement{ shortName: "PZS";  longName: "Małe punkty zdobyte w singlach" }
        ListElement{ shortName: "PSS";  longName: "Małe punkty stracone w singlach" }
        ListElement{ shortName: "RS";   longName: "Różnica małych punktów zdobytych w singlach" }
    }

}
