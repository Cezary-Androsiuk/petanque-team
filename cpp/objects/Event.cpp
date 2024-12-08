#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
    , m_phases(2, PhasePtr())
{
    I(QAPF("Creating Event: %p", this));
    this->initialize();
}

Event::~Event()
{
    I(QAPF("Destroying Event: %p", this));
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
    if(phasesJson.size() >= m_phases.size())
    {
        for(int i=0; i<m_phases.size(); i++)
        {
            PhasePtr phasePtr = PhasePtr::create(0);
            phasePtr->deserialize( phasesJson[i].toObject() );
            m_phases[i] = phasePtr ;
        }
        emit this->phasesChanged();
    }
    else
    {
        E("phasesJson has less phases than expected - skipping step")
    }

}

void Event::clear(bool emitting)
{
    m_name.clear();
    if(emitting) emit this->nameChanged();

    m_currentPhase = 0;
    if(emitting) emit this->currentPhaseChanged();

    m_phases[0].clear();
    m_phases[1].clear();
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
    m_phases[0] = PhasePtr::create(subPhasesCount) ;

    subPhasesCount = 2;
    m_phases[1] = PhasePtr::create(subPhasesCount);

    emit this->phasesChanged();
}

QString Event::getName() const
{
    return m_name;
}

PhasePtr Event::getCurrentPhasePtr() const
{
    if(m_phases.size() > m_currentPhase)
        return m_phases[m_currentPhase];

    W("cannot return phase that is out of range: " + QString::number(m_currentPhase));
    return nullptr;
}

// PhasePtrVector Event::getPhases() const
// {
//     return m_phases;
// }

void Event::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}
