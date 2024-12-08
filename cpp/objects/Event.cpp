#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
{}

QJsonObject Event::serialize() const
{

}

void Event::deserialize(const QJsonObject &data)
{

}
