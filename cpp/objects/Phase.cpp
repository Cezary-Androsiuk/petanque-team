#include "Phase.h"

Phase::Phase(int subPhasesCount, QObject *parent)
    : QObject{parent}
    , m_subPhases(subPhasesCount)
{
    I(QAPF("Creating Phase: %p", this));
}

Phase::~Phase()
{
    I(QAPF("Destroying Phase: %p", this));
}

QJsonObject Phase::serialize() const
{
    return QJsonObject();
}

void Phase::deserialize(const QJsonObject &phaseJson)
{

}

void Phase::clear()
{

}
