#include "Gender.h"

QString EnumConvert::GenderToQString(Gender gender)
{
    switch (gender) {
    case Gender::Male:      return "male";
    case Gender::Female:    return "female";
    default:
        W("unknown gender enum, returning male string");
        return "male";
    }
}

Gender EnumConvert::QStringToGender(const QString &gender)
{
    if(gender == "male")    return Gender::Male;
    if(gender == "female")  return Gender::Female;

    W("unknown gender string: " "\"" + gender + "\"" ", returning male enum");
    return Gender::Male;

}
