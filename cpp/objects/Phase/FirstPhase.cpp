#include "FirstPhase.h"

FirstPhase::FirstPhase(QObject *parent)
    : Phase{parent}
{}

QJsonObject FirstPhase::serialize() const
{
    return QJsonObject();
}

void FirstPhase::deserialize(const QJsonObject &data)
{

}

void FirstPhase::clear()
{

}
