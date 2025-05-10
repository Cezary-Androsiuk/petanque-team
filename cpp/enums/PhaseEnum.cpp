#include "PhaseEnum.h"

#include "support/Log.h"

QString EnumConvert::PhaseToQString(PhaseEnum phase)
{
    switch (phase) {
    case PhaseEnum::First:  return "Phase First";
    case PhaseEnum::Second: return "Phase Second";
    default:
        W("unknown phase, returning Phase First string");
        return "Phase First";
    }
}

PhaseEnum EnumConvert::QStringToPhase(const QString &phase)
{

    if(phase == "Phase First")  return PhaseEnum::First;
    if(phase == "Phase Second") return PhaseEnum::Second;

    W("unknown phase string: " "\"" + phase + "\"" ", returning Phase First enum");
    return PhaseEnum::First;
}
