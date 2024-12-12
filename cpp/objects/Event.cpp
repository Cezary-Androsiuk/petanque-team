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

void Event::goToFirstPhase()
{

}

void Event::goToSecondPhase()
{

}

void Event::createDetachedTeam()
{
    // I("Creating detached Team")
    if(!m_detachedTeam.isNull())
    {
        W("Creating new detached Team, while old wasn't deleted")
    }

    m_detachedTeam = TeamPtr::create();
    emit this->detachedTeamChanged();
}

void Event::deleteDetachedTeam()
{
    // I("Deleting detached Team")
    if(m_detachedTeam.isNull())
    {
        E("trying to delete aleady deleted detached Team")
        return;
    }

    m_detachedTeam.clear();
}

void Event::validateDetachedTeam()
{
    if(m_detachedTeam.isNull())
    {
        const char *message = "Detached Team not exist";
        E(message);
        emit this->detachedTeamValidationFailed(message);
        return;
    }

    /// Check if the fields are empty
    if(m_detachedTeam->getName().isEmpty())
    {
        emit this->detachedTeamValidationFailed("Team required name");
        return;
    }

    /// Check unique parameter
    for(const auto &teamPtr : m_teams)
    {
        if(m_detachedTeam->getName() == teamPtr->getName())
        {
            emit this->detachedTeamValidationFailed("Team name is not unique in this event!");
            return;
        }
    }

    emit this->detachedTeamIsValid();
}

void Event::addDetachedTeam()
{
    // I("Adding detached Team to Event")
    if(m_detachedTeam.isNull())
    {
        E("cannot add not existing detached team to list")
        return;
    }

    m_teams.append(m_detachedTeam);
    emit this->teamsChanged();

    m_detachedTeam.clear();
    emit this->detachedTeamChanged();
}

void Event::deleteTeam(int index)
{
    if(m_teams.size() <= index)
    {
        QString sSize = QString::number(m_teams.size());
        QString sIndex = QString::number(index);
        E("trying to delete not existing team("+sIndex+") from list("+sSize+")");
        return;
    }

    m_teams.remove(index);
    emit this->teamsChanged();
}

void Event::validateEvent()
{
    E("NOT FINISHED");
    emit this->eventValidationFailed();
}

void Event::createExampleTeams()
{
    E("NOT FINISHED");
    /// call Team::createExamplePlayers()
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

Team *Event::getDetachedTeamQml() const
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
