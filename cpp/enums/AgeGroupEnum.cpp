#include "AgeGroupEnum.h"

#include "support/Log.h"

QString EnumConvert::AgeGroupToQString(AgeGroupEnum ageGroup)
{
    switch (ageGroup) {
    case AgeGroupEnum::Junior:  return "junior";
    case AgeGroupEnum::Youth:   return "youth";
    case AgeGroupEnum::Senior:  return "senior";
    case AgeGroupEnum::Veteran: return "veteran";
    default:
        W("unknown age group, returning Veteran string");
        return "veteran";
    }
}

AgeGroupEnum EnumConvert::QStringToAgeGroup(const QString &ageGroup)
{
    if(ageGroup == "junior")  return AgeGroupEnum::Junior;
    if(ageGroup == "youth")   return AgeGroupEnum::Youth;
    if(ageGroup == "senior")  return AgeGroupEnum::Senior;
    if(ageGroup == "veteran") return AgeGroupEnum::Veteran;

    W("unknown age group string: " "\"" + ageGroup + "\"" ", returning Veteran enum");
    return AgeGroupEnum::Veteran;
}
