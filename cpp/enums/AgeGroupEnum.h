#ifndef AGEGROUPENUM_H
#define AGEGROUPENUM_H

#include <QString>

enum AgeGroupEnum{
    Junior = 0,
    Youth,
    Senior,
    Veteran,
};

namespace EnumConvert{
QString AgeGroupToQString(AgeGroupEnum ageGroup);
AgeGroupEnum QStringToAgeGroup(const QString &ageGroup);
}

#endif // AGEGROUPENUM_H
