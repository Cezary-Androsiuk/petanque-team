#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
{
    this->initialize();
}

QJsonObject Event::serialize() const
{
    QJsonObject eventJson;
    eventJson[ SERL_EVENT_NAME_KEY ] = m_name;
    eventJson[ SERL_CURRENT_PHASE_KEY ] = m_currentPhase;
    QJsonArray phasesJson;
    for(const auto &phase : m_phases)
    {
        phasesJson.append( phase->serialize() );
    }
    eventJson[ SERL_PHASES_KEY ] = phasesJson;

    return eventJson;
}

void Event::deserialize(const QJsonObject &eventJson)
{
    this->clear(false);

    m_name = eventJson[ SERL_EVENT_NAME_KEY ].toString();
    emit this->nameChanged();

    m_currentPhase = eventJson[ SERL_CURRENT_PHASE_KEY ].toInt();
    emit this->currentPhaseChanged();

    QJsonArray phasesJson = eventJson[ SERL_PHASES_KEY ].toArray();
    for(const auto &phaseJson : phasesJson)
    {
        PhasePtr phasePtr = PhasePtr::create(0);
        phasePtr->deserialize( phaseJson.toObject() );
        m_phases.append( phasePtr );
    }
    emit this->phasesChanged();
}

void Event::clear(bool emitting)
{
    m_name.clear();
    if(emitting) emit this->nameChanged();

    m_currentPhase = 0;
    if(emitting) emit this->currentPhaseChanged();

    m_phases.clear();
    if(emitting) emit this->phasesChanged();
}

void Event::initialize()
{
    this->createPhases();
    m_currentPhase = 0;
}

void Event::createPhases()
{
    int subPhasesCount;
    subPhasesCount = 1;
    m_phases.append( PhasePtr::create(subPhasesCount) );

    subPhasesCount = 2;
    m_phases.append( PhasePtr::create(subPhasesCount) );

    /// creating objects before possible deserialization
    emit this->phasesChanged();
}

QString Event::getName() const
{
    return m_name;
}

PhasePtrVector Event::getPhases() const
{
    return m_phases;
}

void Event::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}
