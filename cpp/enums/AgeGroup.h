#ifndef AGEGROUP_H
#define AGEGROUP_H

#include <QString>

#include "cpp/support/Log.h"

enum AgeGroup{
    Junior = 0,
    Youth,
    Senior,
    Veteran,
};

namespace EnumConvert{
QString AgeGroupToQString(AgeGroup ageGroup);
AgeGroup QStringToAgeGroup(const QString &ageGroup);
}

#endif // AGEGROUP_H
