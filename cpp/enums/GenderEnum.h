#ifndef GENDERENUM_H
#define GENDERENUM_H

#include <QString>

enum GenderEnum{
    Male = 0,
    Female,
};

namespace EnumConvert{
QString GenderToQString(GenderEnum gender);
GenderEnum QStringToGender(const QString &gender);
}


#endif // GENDERENUM_H
