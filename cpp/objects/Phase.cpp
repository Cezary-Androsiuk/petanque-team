#include "Phase.h"

Phase::Phase(int subPhasesCount, QObject *parent)
    : QObject{parent}
{
    I(QAPF("Creating Phase: %p", this));
}

Phase::~Phase()
{
    I(QAPF("Destroying Phase: %p", this));
}

QJsonObject Phase::serialize() const
{

}

void Phase::deserialize(const QJsonObject &data)
{

}

void Phase::clear()
{

}
