#include "SecondPhase.h"

SecondPhase::SecondPhase(QObject *parent)
    : Phase{parent}
{}

QJsonObject SecondPhase::serialize() const
{
    return QJsonObject();
}

void SecondPhase::deserialize(const QJsonObject &data)
{

}

void SecondPhase::clear()
{

}
