#include "RoundStageEnum.h"

#include "support/Log.h"

QString EnumConvert::RoundStageToQString(RoundStageEnum roundStage)
{
    switch (roundStage) {
    case RoundStageEnum::SinglesSelection:  return "Singles Selection";
    case RoundStageEnum::SinglesMatch:      return "Singles Match";
    case RoundStageEnum::DoublesSelection:  return "Doubles Selection";
    case RoundStageEnum::DoublesMatch:      return "Doubles Match";
    case RoundStageEnum::TriplesSelection:  return "Triples Selection";
    case RoundStageEnum::TriplesMatch:      return "Triples Match";
    case RoundStageEnum::RoundSummary:      return "Round Summary";
    default:
        W("unknown round stage, returning Singles Selection string");
        return "Singles Selection";
    }
}

RoundStageEnum EnumConvert::QStringToRoundStage(const QString &roundStage)
{
    if(roundStage == "Singles Selection")   return RoundStageEnum::SinglesSelection;
    if(roundStage == "Singles Match")       return RoundStageEnum::SinglesMatch;
    if(roundStage == "Doubles Selection")   return RoundStageEnum::DoublesSelection;
    if(roundStage == "Doubles Match")       return RoundStageEnum::DoublesMatch;
    if(roundStage == "Triples Selection")   return RoundStageEnum::TriplesSelection;
    if(roundStage == "Triples Match")       return RoundStageEnum::TriplesMatch;
    if(roundStage == "Round Summary")       return RoundStageEnum::RoundSummary;

    W("unknown round stage string: " "\"" + roundStage + "\"" ", returning Singlets Selection enum");
    return RoundStageEnum::SinglesSelection;
}
