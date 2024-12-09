#include "GenderEnum.h"

QString EnumConvert::GenderToQString(GenderEnum gender)
{
    switch (gender) {
    case GenderEnum::Male:      return "male";
    case GenderEnum::Female:    return "female";
    default:
        W("unknown gender enum, returning male string");
        return "male";
    }
}

GenderEnum EnumConvert::QStringToGender(const QString &gender)
{
    if(gender == "male")    return GenderEnum::Male;
    if(gender == "female")  return GenderEnum::Female;

    W("unknown gender string: " "\"" + gender + "\"" ", returning male enum");
    return GenderEnum::Male;

}
