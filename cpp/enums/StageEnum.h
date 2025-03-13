#ifndef STAGEENUM_H
#define STAGEENUM_H

#include <QString>

#include "cpp/support/Log.h"

enum StageEnum{
    None = 0,
    Configure,
    Play,
    Finish,
};

constexpr StageEnum firstStageEnum = StageEnum::Configure;
constexpr StageEnum lastStageEnum = StageEnum::Finish;

namespace EnumConvert{
QString StageToQString(StageEnum stage);
StageEnum QStringToStage(const QString stage);
}

#endif // STAGEENUM_H
