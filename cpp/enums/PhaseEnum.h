#ifndef PHASEENUM_H
#define PHASEENUM_H

#include <QString>

enum PhaseEnum{
    First,
    Second,
};


namespace EnumConvert{
QString PhaseToQString(PhaseEnum phase);
PhaseEnum QStringToPhase(const QString &phase);
}


#endif // PHASEENUM_H
