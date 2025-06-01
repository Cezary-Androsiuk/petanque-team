#ifndef ROUNDSTAGEENUM_H
#define ROUNDSTAGEENUM_H

#include <QString>

enum RoundStageEnum{
    SinglesSelection = 0,
    SinglesMatch,
    DoublesSelection,
    DoublesMatch,
    TriplesSelection,
    TriplesMatch,
    RoundSummary,
};

namespace EnumConvert{
QString RoundStageToQString(RoundStageEnum roundStage);
RoundStageEnum QStringToRoundStage(const QString &roundStage);
}


#endif // ROUNDSTAGEENUM_H
