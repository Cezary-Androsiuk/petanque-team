#include "StageEnum.h"

QString EnumConvert::StageToQString(StageEnum stage)
{
    switch (stage) {
    case StageEnum::None:       return "None";
    case StageEnum::Configure:  return "Configure";
    case StageEnum::Play:       return "Play";
    case StageEnum::Finish:     return "Finish";
    default:
        W("unknown stage, returning None string");
        return "None";
    }
}

StageEnum EnumConvert::QStringToStage(const QString stage)
{
    if(stage == "None")         return StageEnum::None;
    if(stage == "Configure")    return StageEnum::Configure;
    if(stage == "Play")         return StageEnum::Play;
    if(stage == "Finish")       return StageEnum::Finish;

    W("unknown stage string: " "\"" + stage + "\"" ", returning None enum");
    return StageEnum::None;
}
