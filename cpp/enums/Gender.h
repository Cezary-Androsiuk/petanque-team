#ifndef GENDER_H
#define GENDER_H

#include <QString>

#include "cpp/support/Log.h"

enum Gender{
    Male = 0,
    Female,
};

namespace EnumConvert{
QString GenderToQString(Gender gender);
Gender QStringToGender(const QString &gender);
}


#endif // GENDER_H
