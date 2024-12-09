#include "SubPhase.h"

SubPhase::SubPhase(QObject *parent)
    : QObject{parent}
{
    I(QAPF("Creating SubPhase: %p", this));
}

SubPhase::~SubPhase()
{
    I(QAPF("Destroying SubPhase: %p", this));
}

QJsonObject SubPhase::serialize() const
{
    return QJsonObject();
}

void SubPhase::deserialize(const QJsonObject &data)
{

}

void SubPhase::clear()
{

}
