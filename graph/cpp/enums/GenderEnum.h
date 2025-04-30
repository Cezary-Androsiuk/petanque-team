#ifndef GENDERENUM_H
#define GENDERENUM_H

#include <QString>

#include "cpp/support/Log.h"

enum GenderEnum{
    Male = 0,
    Female,
};

namespace EnumConvert{
QString GenderToQString(GenderEnum gender);
GenderEnum QStringToGender(const QString &gender);
}


#endif // GENDERENUM_H
