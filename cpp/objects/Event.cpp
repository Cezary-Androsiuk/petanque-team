#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
{
    this->initialize();
}

QJsonObject Event::serialize() const
{

}

void Event::deserialize(const QJsonObject &data)
{

}

void Event::initialize()
{
    this->createPhases();
    m_currentPhase = 0;
}

void Event::createPhases()
{
    int subPhases;
    subPhases = 1;
    m_phases.append( QSharedPointer<Phase>::create(subPhases) );

    subPhases = 2;
    m_phases.append( QSharedPointer<Phase>::create(subPhases) );
}
