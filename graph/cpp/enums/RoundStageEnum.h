#ifndef ROUNDSTAGEENUM_H
#define ROUNDSTAGEENUM_H

#include <QString>

#include "cpp/support/Log.h"

enum RoundStageEnum{
    SingielsSelection = 0,
    SingielsMatch,
    DubletsSelection,
    DubletsMatch,
    TripletsSelection,
    TripletsMatch,
    RoundSummary,
};

namespace EnumConvert{
QString RoundStageToQString(RoundStageEnum roundStage);
RoundStageEnum QStringToRoundStage(const QString &roundStage);
}


#endif // ROUNDSTAGEENUM_H
