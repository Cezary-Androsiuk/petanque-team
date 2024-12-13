#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
    , m_teams{globalTeams}
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
    QJsonObject jEvent;
    jEvent[ SERL_EVENT_NAME_KEY ] = m_name;
    int currentPhaseInt = static_cast<int>(m_currentPhase);
    jEvent[ SERL_CURRENT_PHASE_KEY ] = currentPhaseInt;
    int currentStageInt = static_cast<int>(m_currentStage);
    jEvent[ SERL_CURRENT_STAGE_KEY ] = currentStageInt;
    jEvent[ SERL_PHASE_FIRST_KEY ] = m_phases[PhaseEnum::First]->serialize();
    jEvent[ SERL_PHASE_SECOND_KEY ] = m_phases[PhaseEnum::Second]->serialize();


    QJsonArray jTeams;
    for(const auto &teamPtr : m_teams)
    {
        jTeams.append( teamPtr->serialize() );
    }
    jEvent[ SERL_TEAMS_KEY ] = jTeams;

    return jEvent;
}

void Event::deserialize(const QJsonObject &jEvent)
{
    this->clear(false);
    // D("cleared to deserialize");

    m_name = jEvent[ SERL_EVENT_NAME_KEY ].toString();
    emit this->nameChanged();

    int currentPhaseInt = jEvent[ SERL_CURRENT_PHASE_KEY ].toInt();
    m_currentPhase = static_cast<PhaseEnum>(currentPhaseInt);
    emit this->currentPhaseChanged();

    int currentStageInt = jEvent[ SERL_CURRENT_STAGE_KEY ].toInt();
    m_currentStage = static_cast<StageEnum>(currentStageInt);
    emit this->currentStageChanged();

    QJsonObject firstPhaseObject = jEvent[ SERL_PHASE_FIRST_KEY ].toObject();
    QJsonObject secondPhaseObject = jEvent[ SERL_PHASE_SECOND_KEY ].toObject();
    m_phases[PhaseEnum::First]->deserialize( firstPhaseObject );
    m_phases[PhaseEnum::Second]->deserialize( secondPhaseObject );
    emit this->phasesChanged();

    QJsonArray jTeams = jEvent[ SERL_TEAMS_KEY ].toArray();
    for(const auto &jTeam : jTeams)
    {
        TeamPtr teamPtr = TeamPtr::create();
        teamPtr->deserialize( jTeam.toObject() );
        m_teams.append(teamPtr);
    }

    emit this->teamsChanged();

    D("deserialized event")
}

void Event::clear(bool emitting)
{
    m_name.clear();
    if(emitting) { emit this->nameChanged(); }

    m_currentPhase = PhaseEnum::First;
    if(emitting) { emit this->currentPhaseChanged(); }

    m_currentStage = StageEnum::None;
    if(emitting) { emit this->currentStageChanged(); }

    m_phases[PhaseEnum::First]->clear();
    m_phases[PhaseEnum::Second]->clear();
    if(emitting) { emit this->phasesChanged(); }
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

void Event::initFirstPhase()
{

}

void Event::initSecondPhase()
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
    // emit this->detachedTeamChanged();
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
    Personalization *p = Personalization::getInstance();

    /// check if required amount of teams was registered
    if(m_teams.size() != p->getRequiredTeamsCount())
    {
        QString message = tr("Event requires %1 teams").arg(p->getRequiredTeamsCount());
        I(message);
        emit this->eventValidationFailed(message);
        return;
    }

    /// check data for teams:
    for(const auto &teamPtr : m_teams)
    {
        const QString &teamName = teamPtr->getName();
        const PlayerPtrList &players = teamPtr->getPlayers();

        /// check if team has at least 6 players
        if(players.size() < p->getMinimumPlayersInTeam())
        {
            /// team has least than 6 players
            QString message = tr("Team %1 has less than %2 players")
                                  .arg(teamName)
                                  .arg(p->getMinimumPlayersInTeam());
            I(message);
            emit this->eventValidationFailed(message);
            return;
        }

        /// check if team has both genders
        bool foundMale = false;
        bool foundFemale = false;
        for(const auto &playerPtr : players)
        {
            if(playerPtr->getGender() == GenderEnum::Male)
                foundMale = true;

            if(playerPtr->getGender() == GenderEnum::Female)
                foundFemale = true;
        }
        if(!foundMale || !foundFemale)
        {
            /// one gender is missing in team
            QString message = tr("Team %1 doesn't contain players of either gender")
                                  .arg(teamName);
            I(message);
            emit this->eventValidationFailed(message);
            return;
        }

        /// check if team has a junior
        if(p->getRequiresJuniors())
        {
            bool foundJunior = false;
            for(const auto &playerPtr : players)
            {
                if(playerPtr->getAgeGroup() == AgeGroupEnum::Junior)
                {
                    foundJunior = true;
                    break;
                }
            }

            if(!foundJunior)
            {
                /// junior player is missing in team
                QString message = tr("Team %1 doesn't contain any junior player")
                                      .arg(teamName);
                I(message);
                emit this->eventValidationFailed(message);
                return;
            }
        }

        /// check if team has one leader
        int foundLeaders = 0;
        for(const auto &playerPtr : players)
        {
            if(playerPtr->getIsTeamLeader())
                ++ foundLeaders;
        }

        if(foundLeaders == 0)
        {
            /// team has no leader
            QString message = tr("In team %1, no leader was selected (each team requires leader)")
                                  .arg(teamName);
            I(message);
            emit this->eventValidationFailed(message);
            return;
        }
        else if(foundLeaders > 1)
        {
            /// team contains few leaders
            QString message = tr("Team %1 has %2 leaders, but should be only one")
                                  .arg(teamName)
                                  .arg(foundLeaders);
            I(message);
            emit this->eventValidationFailed(message);
            return;
        }
    }

    emit this->eventValid();
}

void Event::assignExampleData()
{
    QJsonObject jEvent = Personalization::getInstance()->getExampleData();

    this->setName(jEvent["name"].toString());
    /// judges
    /// place
    /// etc.

    QJsonArray jTeams = jEvent["teams"].toArray();
    m_teams.clear();
    for(int i=0; i<jTeams.size(); i++)
    {
        QJsonObject jTeam = jTeams[i].toObject();

        TeamPtr team = TeamPtr::create();
        team->assignExampleData(jTeam);

        m_teams.append(team);
    }

    emit this->teamsChanged();
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
