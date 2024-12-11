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

void Event::initialize()
{
    this->createPhases();
    m_currentPhase = PhaseEnum::First;
    m_currentStage = StageEnum::None;
}

void Event::createPhases()
{
    m_phases[0] = PhasePtr::create(1);
    m_phases[1] = PhasePtr::create(2);

    emit this->phasesChanged();
}

QJsonObject Event::serialize() const
{
    QJsonObject eventJson;
    eventJson[ SERL_EVENT_NAME_KEY ] = m_name;
    int currentPhaseInt = static_cast<int>(m_currentPhase);
    eventJson[ SERL_CURRENT_PHASE_KEY ] = currentPhaseInt;
    int currentStageInt = static_cast<int>(m_currentStage);
    eventJson[ SERL_CURRENT_STAGE_KEY ] = currentStageInt;
    eventJson[ SERL_PHASE_FIRST_KEY ] = m_phases[PhaseEnum::First]->serialize();
    eventJson[ SERL_PHASE_SECOND_KEY ] = m_phases[PhaseEnum::Second]->serialize();

    return eventJson;
}

void Event::deserialize(const QJsonObject &eventJson)
{
    this->clear(false);
    D("cleared to deserialize");

    m_name = eventJson[ SERL_EVENT_NAME_KEY ].toString();
    emit this->nameChanged();

    int currentPhaseInt = eventJson[ SERL_CURRENT_PHASE_KEY ].toInt();
    m_currentPhase = static_cast<PhaseEnum>(currentPhaseInt);
    emit this->currentPhaseChanged();

    int currentStageInt = eventJson[ SERL_CURRENT_STAGE_KEY ].toInt();
    m_currentStage = static_cast<StageEnum>(currentStageInt);
    emit this->currentStageChanged();

    QJsonObject firstPhaseObject = eventJson[ SERL_PHASE_FIRST_KEY ].toObject();
    QJsonObject secondPhaseObject = eventJson[ SERL_PHASE_SECOND_KEY ].toObject();
    m_phases[PhaseEnum::First]->deserialize( firstPhaseObject );
    m_phases[PhaseEnum::Second]->deserialize( secondPhaseObject );
    emit this->phasesChanged();

    D("deserialized event")
}

void Event::clear(bool emitting)
{
    m_name.clear();
    if(emitting) emit this->nameChanged();

    m_currentPhase = PhaseEnum::First;
    if(emitting) emit this->currentPhaseChanged();

    m_currentStage = StageEnum::None;
    if(emitting) emit this->currentStageChanged();

    m_phases[PhaseEnum::First]->clear();
    m_phases[PhaseEnum::Second]->clear();
    if(emitting) emit this->phasesChanged();
}

void Event::goToNextStage()
{
    if(m_currentStage >= lastStageEnum)
    {
        W("trying to exceed the highest stage!");
        return;
    }
    m_currentStage = static_cast<StageEnum>(m_currentStage +1);
    emit this->currentStageChanged();
}

void Event::goToPrevStage()
{
    if(m_currentStage <= firstStageEnum)
    {
        W("trying to exceed the lowest stage!");
        return;
    }
    m_currentStage =  static_cast<StageEnum>(m_currentStage -1);
    emit this->currentStageChanged();
}

void Event::createDetachedTeam()
{

}

void Event::deleteDetachedTeam()
{

}

void Event::addDetachedTeam()
{

}

void Event::deleteTeam(int index)
{

}

void Event::validateTeams()
{
    emit this->teamsDataValid();
}

void Event::createExampleTeams()
{

}

const QString &Event::getName() const
{
    return m_name;
}

PhaseEnum Event::getCurrentPhase() const
{
    return m_currentPhase;
}

StageEnum Event::getCurrentStage() const
{
    return m_currentStage;
}

const PhasePtrVector &Event::getPhases() const
{
    return m_phases;
}

const TeamPtr &Event::getDetachedTeam() const
{
    return m_detachedTeam;
}

const TeamPtrList &Event::getTeams() const
{
    return m_teams;
}

QmlPhasePtrVector Event::getPhasesQml() const
{
    QmlPhasePtrVector retVec;
    retVec.reserve( m_phases.size() );
    for(const auto &phasePtr : m_phases)
        retVec.append(phasePtr.data());
    return retVec;
}

const Team *Event::getDetachedTeamQml() const
{
    return m_detachedTeam.data();
}

QmlTeamPtrVector Event::getTeamsQml() const
{
    QmlTeamPtrVector retVec;
    retVec.reserve( m_teams.size() );
    for(const auto &teamPtr : m_teams)
        retVec.append(teamPtr.data());
    return retVec;
}

void Event::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}
