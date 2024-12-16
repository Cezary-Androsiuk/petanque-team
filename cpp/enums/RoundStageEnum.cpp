#include "RoundStageEnum.h"

QString EnumConvert::RoundStageToQString(RoundStageEnum roundStage)
{
    switch (roundStage) {
    case RoundStageEnum::SingielsSelection: return "Singiels Selection";
    case RoundStageEnum::SingielsMatch:     return "Singiels Match";
    case RoundStageEnum::DubletsSelection:  return "Dublets Selection";
    case RoundStageEnum::DubletsMatch:      return "Dublets Match";
    case RoundStageEnum::TripletsSelection: return "Triplets Selection";
    case RoundStageEnum::TripletsMatch:     return "Triplets Match";
    case RoundStageEnum::RoundSummary:      return "Round Summary";
    default:
        W("unknown round stage, returning singiels selection string");
        return "Singiels Selection";
    }
}

RoundStageEnum EnumConvert::QStringToRoundStage(const QString &roundStage)
{
    if(roundStage == "Singiels Selection")  return RoundStageEnum::SingielsSelection;
    if(roundStage == "Singiels Match")      return RoundStageEnum::SingielsMatch;
    if(roundStage == "Dublets Selection")   return RoundStageEnum::DubletsSelection;
    if(roundStage == "Dublets Match")       return RoundStageEnum::DubletsMatch;
    if(roundStage == "Triplets Selection")  return RoundStageEnum::TripletsSelection;
    if(roundStage == "Triplets Match")      return RoundStageEnum::TripletsMatch;
    if(roundStage == "Round Summary")       return RoundStageEnum::RoundSummary;

    W("unknown round stage string: " "\"" + roundStage + "\"" ", returning singlets selection enum");
    return RoundStageEnum::SingielsSelection;
}
