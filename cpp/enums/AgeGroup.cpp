#include "AgeGroup.h"

QString EnumConvert::AgeGroupToQString(AgeGroup ageGroup)
{
    switch (ageGroup) {
    case AgeGroup::Junior:  return "junior";
    case AgeGroup::Youth:   return "youth";
    case AgeGroup::Senior:  return "senior";
    case AgeGroup::Veteran: return "veteran";
    default:
        W("unknown age group, returning veteran string");
        return "veteran";
    }
}

AgeGroup EnumConvert::QStringToAgeGroup(const QString &ageGroup)
{
    if(ageGroup == "junior")  return AgeGroup::Junior;
    if(ageGroup == "youth")   return AgeGroup::Youth;
    if(ageGroup == "senior")  return AgeGroup::Senior;
    if(ageGroup == "veteran") return AgeGroup::Veteran;

    W("unknown age group string: " "\"" + ageGroup + "\"" ", returning veteran enum");
    return AgeGroup::Veteran;
}
