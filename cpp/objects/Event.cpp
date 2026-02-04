#include "Event.h"

#include "support/Log.h"
#include "storages/Personalization.h"
#include "support/Utilities.h"

Event::Event(QObject *parent)
    : QObject{parent}
    , m_phases(2, PhasePtr())
{TRM; DOLTV(SAPF("%p", parent));

    this->initialize();
}

Event::~Event()
{TRM; DOLT;

    for(auto &teamPtr : m_teams)
        teamPtr.clear();
    m_teams.clear();

    for(auto &phasePtr : m_phases)
        phasePtr.clear();
    m_phases.clear();
}

void Event::initialize()
{TRM;
    m_currentPhase = PhaseEnum::First;
    m_currentStage = StageEnum::None;
}

QJsonObject Event::serialize() const
{TRM;
    QJsonObject jEvent;

    /// serialize event details
    QJsonObject jEventDetails;
    jEventDetails[ SERL_EVENT_NAME_KEY ] = m_name;
    jEventDetails[ SERL_EVENT_FIRST_PHASE_DATE_KEY ] = m_firstPhaseDate;
    jEventDetails[ SERL_EVENT_SECOND_PHASE_DATE_KEY ] = m_secondPhaseDate;
    jEventDetails[ SERL_EVENT_COMPETITION_ORGANIZER_KEY ] = m_competitionOrganizer;
    jEventDetails[ SERL_EVENT_FIRST_PHASE_PLACE_KEY ] = m_firstPhasePlace;
    jEventDetails[ SERL_EVENT_SECOND_PHASE_PLACE_KEY ] = m_secondPhasePlace;
    jEventDetails[ SERL_EVENT_JUDGES_KEY ] = QJsonArray::fromStringList(m_judges);
    jEventDetails[ SERL_EVENT_UNION_DELEGATE_KEY ] = m_unionDelegate;

    jEvent[ SERL_EVENT_DETAILS_KEY ] = jEventDetails;

    int currentPhaseInt = static_cast<int>(m_currentPhase);
    jEvent[ SERL_CURRENT_PHASE_KEY ] = currentPhaseInt;
    int currentStageInt = static_cast<int>(m_currentStage);
    jEvent[ SERL_CURRENT_STAGE_KEY ] = currentStageInt;

    if(m_phases[PhaseEnum::First].isNull())
    {
        I("skipping first phase serialization because, phase not started yet");
        jEvent[ SERL_PHASE_FIRST_KEY ] = QJsonObject();
    }
    else jEvent[ SERL_PHASE_FIRST_KEY ] = m_phases[PhaseEnum::First]->serialize();

    if(m_phases[PhaseEnum::Second].isNull())
    {
        I("skipping second phase serialization because, phase not started yet");
        jEvent[ SERL_PHASE_SECOND_KEY ] = QJsonObject();
    }
    else jEvent[ SERL_PHASE_SECOND_KEY ] = m_phases[PhaseEnum::Second]->serialize();


    QJsonArray jTeams;
    for(const auto &teamPtr : m_teams)
    {
        if(teamPtr.isNull())
            W("cannot serialize not exiting team");
        else
            jTeams.append( teamPtr->serialize() );
    }
    jEvent[ SERL_TEAMS_KEY ] = jTeams;

    return jEvent;
}

void Event::deserialize(const QJsonObject &jEvent)
{TRM;
    this->clear(false);
    // D("cleared to deserialize");

    /// deserialize event details
    const QJsonObject jEventDetails = jEvent[ SERL_EVENT_DETAILS_KEY ].toObject();
    this->setName( jEventDetails[ SERL_EVENT_NAME_KEY ].toString() );
    this->setFirstPhaseDate( jEventDetails[ SERL_EVENT_FIRST_PHASE_DATE_KEY ].toString() );
    this->setSecondPhaseDate( jEventDetails[ SERL_EVENT_SECOND_PHASE_DATE_KEY ].toString() );
    this->setCompetitionOrganizer( jEventDetails[ SERL_EVENT_COMPETITION_ORGANIZER_KEY ].toString() );
    this->setFirstPhasePlace( jEventDetails[ SERL_EVENT_FIRST_PHASE_PLACE_KEY ].toString() );
    this->setSecondPhasePlace( jEventDetails[ SERL_EVENT_SECOND_PHASE_PLACE_KEY ].toString() );
    this->setUnionDelegate( jEventDetails[ SERL_EVENT_UNION_DELEGATE_KEY ].toString() );
    const QJsonArray jsonJudges = jEventDetails[ SERL_EVENT_JUDGES_KEY ].toArray();
    m_judges.clear();
    m_judges.reserve(jsonJudges.size());
    for(int i=0; i<jsonJudges.size(); i++)
    {
        m_judges.append(jsonJudges[i].toString());
    }
    emit this->judgesChanged();

    int currentPhaseInt = jEvent[ SERL_CURRENT_PHASE_KEY ].toInt();
    m_currentPhase = static_cast<PhaseEnum>(currentPhaseInt);
    emit this->currentPhaseChanged();

    int currentStageInt = jEvent[ SERL_CURRENT_STAGE_KEY ].toInt();
    m_currentStage = static_cast<StageEnum>(currentStageInt);
    emit this->currentStageChanged();

    QJsonArray jTeams = jEvent[ SERL_TEAMS_KEY ].toArray();

    for(int i=0; i<jTeams.size(); i++)
    {
        TeamPtr teamPtr = TeamPtr::create();
        teamPtr->deserialize( jTeams[i].toObject() );
        m_teams.append(teamPtr);
    }

    emit this->teamsChanged();

    if(!jEvent.contains(SERL_PHASE_FIRST_KEY))
    {
        E("cannot deserialize first phase due to missing key in json: " SERL_PHASE_FIRST_KEY);
    }
    else
    {
        QJsonObject jPhase = jEvent[ SERL_PHASE_FIRST_KEY ].toObject();

        /// if is empty => hasn't been initialized => first phase was not started yet
        if(!jPhase.isEmpty())
        {
            this->startFirstPhase();

            if(m_phases[PhaseEnum::First].isNull())
                W("cannot deserialize not existing first phase");
            else
                m_phases[PhaseEnum::First]->deserialize( jPhase );
        }
        else
        {
            I("skipped initialization of first phase, because it hasn't started yet");
        }
    }

    if(!jEvent.contains(SERL_PHASE_SECOND_KEY))
    {
        E("cannot deserialize second phase due to missing key in json: " SERL_PHASE_SECOND_KEY);
    }
    else
    {
        QJsonObject jPhase = jEvent[ SERL_PHASE_SECOND_KEY ].toObject();

        /// if is empty => hasn't been initialized => second phase was not started yet
        if(!jPhase.isEmpty())
        {
            this->startSecondPhase();

            if(m_phases[PhaseEnum::Second].isNull())
                W("cannot deserialize not existing second phase");
            else
                m_phases[PhaseEnum::Second]->deserialize( jPhase );
        }
        else
        {
            I("skipped initialization of second phase, because it hasn't started yet");
        }
    }
    emit this->phasesChanged();

    D("deserialized event");
}

void Event::clear(bool emitting)
{TRM;
    m_name.clear();
    if(emitting) { emit this->nameChanged(); }

    m_currentPhase = PhaseEnum::First;
    if(emitting) { emit this->currentPhaseChanged(); }

    m_currentStage = StageEnum::None;
    if(emitting) { emit this->currentStageChanged(); }
}

void Event::goToNextStage()
{TRM;
    if(m_currentStage >= lastStageEnum)
    {
        W("trying to exceed the highest stage!");
        return;
    }

    if(m_currentStage == StageEnum::Play)
    {
        this->secondPhaseEnd();
    }

    m_currentStage = static_cast<StageEnum>(m_currentStage +1);
    emit this->currentStageChanged();

    if(m_currentStage == StageEnum::Play)
    {
        this->firstPhaseStart();
    }
}

void Event::goToPrevStage()
{TRM;
    if(m_currentStage <= firstStageEnum)
    {
        W("trying to exceed the lowest stage!");
        return;
    }
    m_currentStage =  static_cast<StageEnum>(m_currentStage -1);
    emit this->currentStageChanged();
}

void Event::startFinishStage()
{TRM;
    D("start finish stage");
    this->goToNextStage();
}

bool Event::hasNextPhase() const
{TRM;
    return m_currentPhase == PhaseEnum::First;
}

void Event::startFirstPhase()
{TRM;
    D("start first phase");

    TeamPtrList teams1;
    this->createListForFirstPhase(teams1);

    m_phases[PhaseEnum::First] = PhasePtr::create(PhaseEnum::First);
    m_phases[PhaseEnum::First]->initSubPhases({m_teams});

    emit this->phasesChanged();

    m_currentPhase = PhaseEnum::First;
    emit this->currentPhaseChanged();
}

void Event::startSecondPhase()
{TRM;
    m_phases[PhaseEnum::First]->onEnd();

    D("start second phase");

    TeamPtrList teams2a, teams2b;
    this->createListForSecondPhase(teams2a, teams2b);

    m_phases[PhaseEnum::Second] = PhasePtr::create(PhaseEnum::Second);
    m_phases[PhaseEnum::Second]->initSubPhases({teams2a,teams2b});

    emit this->phasesChanged();

    m_currentPhase = PhaseEnum::Second;
    emit this->currentPhaseChanged();

    m_phases[PhaseEnum::Second]->onStart();
    /// onEnd called in goToNextStage
}

void Event::createDetachedTeam()
{TRM;
    // I("Creating detached Team")
    if(!m_detachedTeam.isNull())
    {
        W("Creating new detached Team, while old wasn't deleted");
    }

    m_detachedTeam = TeamPtr::create();
    emit this->detachedTeamChanged();
}

void Event::deleteDetachedTeam()
{TRM;
    // I("Deleting detached Team")
    if(m_detachedTeam.isNull())
    {
        E("trying to delete aleady deleted detached Team");
        return;
    }

    m_detachedTeam.clear();
    // emit this->detachedTeamChanged();
}

void Event::validateDetachedTeam()
{TRM;
    if(m_detachedTeam.isNull())
    {
        E("Detached Team not exist");
        emit this->detachedTeamValidationFailed("Tymczasowa drużyna nie istnieje");
        return;
    }

    /// Check if the fields are empty
    if(m_detachedTeam->getName().isEmpty())
    {
        emit this->detachedTeamValidationFailed("Nazwa drużyny jest wymagana");
        return;
    }

    /// Check unique parameter
    for(int i=0; i<m_teams.size(); i++)
    {
        if(m_detachedTeam->getName() == m_teams[i]->getName())
        {
            emit this->detachedTeamValidationFailed("Nazwa drużyny musi być unikalna!");
            return;
        }
    }

    emit this->detachedTeamIsValid();
}

void Event::addDetachedTeam()
{TRM;
    // I("Adding detached Team to Event")
    if(m_detachedTeam.isNull())
    {
        E("cannot add not existing detached team to list");
        return;
    }

    m_teams.append(m_detachedTeam);
    emit this->teamsChanged();

    m_detachedTeam.clear();
    emit this->detachedTeamChanged();
}

void Event::deleteTeam(int index)
{TRM;
    if(m_teams.size() <= index)
    {
        QString sSize = QString::number(m_teams.size());
        QString sIndex = QString::number(index);
        E("Próba usunięcia nie istniejącej drużyny (indeks: "+sIndex+") z listy (rozmiar: "+sSize+")");
        return;
    }

    m_teams.remove(index);
    emit this->teamsChanged();
}

void Event::validateEvent()
{TRM;
    Personalization *p = Personalization::getInstance();

    /// check event details
    if(!this->validateEventDetails())
    {
        /// signals emited in method
        return;
    }

    /// check if required amount of teams was registered
    if(m_teams.size() != p->getRequiredTeamsCount())
    {
        QString message = tr("Wydarzenie wymaga %1 drużyn").arg(p->getRequiredTeamsCount());
        I(message);
        emit this->eventValidationFailed(message);
        return;
    }

    /// check data for teams:
    for(int i=0; i<m_teams.size(); i++)
    {
        const QString &teamName = m_teams[i]->getName();
        const PlayerPtrList &players = m_teams[i]->getPlayers();

        /// check if team has at least 6 players
        if(players.size() < p->getMinimumPlayersInTeam())
        {
            /// team has least than 6 players
            QString message = tr("Drużyna %1 ma mniej niż %2 graczy")
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
            QString message = tr("Drużyna %1 nie posiada graczy obu płci")
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
                QString message = tr("Drużyna %1 nie posiada gracza typu junior")
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
            QString message = tr("W drużynie %1 nie wybrano lidera")
                                  .arg(teamName);
            I(message);
            emit this->eventValidationFailed(message);
            return;
        }
        else if(foundLeaders > 1)
        {
            /// team contains few leaders
            QString message = tr("Drużyna %1 posiada %2 liderów, a powinien być tylko jeden")
                                  .arg(teamName)
                                  .arg(foundLeaders);
            I(message);
            emit this->eventValidationFailed(message);
            return;
        }
    }

    emit this->eventValid();
}

bool Event::validateEventDetails()
{
    if(m_name.isEmpty())
    {
        I("Event name can't be empty");
        emit this->eventValidationFailed("Wydarzenie musi posiadać nazwę");
        return false;
    }
    if(!Utilities::isDateValid(m_firstPhaseDate, "yyyy-MM-dd"))
    {
        I("First phase date is invalid! Correct format is 'YYYY-MM-DD'");
        emit this->eventValidationFailed("Data pierwszej fazy jest niepoprawa! Poprawny format to 'YYYY-MM-DD'");
        return false;
    }
    if(!Utilities::isDateValid(m_secondPhaseDate, "yyyy-MM-dd"))
    {
        I("Second phase date is invalid! Correct format is 'YYYY-MM-DD'");
        emit this->eventValidationFailed("Data drugiej fazy jest niepoprawna! Poprawny format to 'YYYY-MM-DD'");
        return false;
    }


    /// WHAT IS NECCESSARY AND WHAT MIGHT BE NOT


    return true;
}

void Event::assignExampleData()
{TRM;
    QJsonObject jEvent = Personalization::getInstance()->getExampleData();

    QJsonObject jEventDetails = jEvent["event details"].toObject();
    this->setName(jEventDetails["event name"].toString());
    this->setFirstPhaseDate( jEventDetails[ "event first phase date" ].toString() );
    this->setSecondPhaseDate( jEventDetails[ "event second phase date" ].toString() );
    this->setCompetitionOrganizer( jEventDetails[ "event competition organizer" ].toString() );
    this->setFirstPhasePlace( jEventDetails[ "event first phase place" ].toString() );
    this->setSecondPhasePlace( jEventDetails[ "event second phase place" ].toString() );
    this->setUnionDelegate( jEventDetails[ "event union delegate" ].toString() );
    const QJsonArray jsonJudges = jEventDetails[ "event judges" ].toArray();
    m_judges.clear();
    m_judges.reserve(jsonJudges.size());
    for(int i=0; i<jsonJudges.size(); i++)
    {
        m_judges.append(jsonJudges[i].toString());
    }
    emit this->judgesChanged();

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

void Event::firstPhaseStart()
{TRM;
    m_phases[PhaseEnum::First]->onStart();
}

void Event::secondPhaseEnd()
{TRM;
    m_phases[PhaseEnum::Second]->onEnd();
}

void Event::createListForFirstPhase(TeamPtrList &teams1) const
{TRM;
    teams1.clear();
    for(const auto &team : m_teams)
        teams1.append(team);
}

void Event::createListForSecondPhase(TeamPtrList &teams2a, TeamPtrList &teams2b) const
{TRM;
    teams2a.clear();
    teams2b.clear();

    E("Lists for the second subphase are not devided properly yet");

    /// take first and last 4 for now
    /// later sort then by points or something

    if(m_teams.size() == 8)
    {
        for(int i=0; i<4; i++)
            teams2a.append(m_teams[i]);

        for(int i=0; i<4; i++)
            teams2b.append(m_teams[4+i]);
    }
    else
        W("teams size != 8");

}

QString Event::getName() const
{TRM;
    return m_name;
}

QString Event::getFirstPhaseDate() const
{TRM;
    return m_firstPhaseDate;
}

QString Event::getSecondPhaseDate() const
{TRM;
    return m_secondPhaseDate;
}

QString Event::getCompetitionOrganizer() const
{TRM;
    return m_competitionOrganizer;
}

QString Event::getFirstPhasePlace() const
{TRM;
    return m_firstPhasePlace;
}

QString Event::getSecondPhasePlace() const
{TRM;
    return m_secondPhasePlace;
}

QString Event::getUnionDelegate() const
{TRM;
    return m_unionDelegate;
}

QStringList Event::getJudges() const
{TRM;
    return m_judges;
}

PhaseEnum Event::getCurrentPhase() const
{TRM;
    return m_currentPhase;
}

StageEnum Event::getCurrentStage() const
{TRM;
    return m_currentStage;
}

const PhasePtrVector &Event::getPhases() const
{TRM;
    return m_phases;
}

const TeamPtr &Event::getDetachedTeam() const
{TRM;
    return m_detachedTeam;
}

const TeamPtrList &Event::getTeams() const
{TRM;
    return m_teams;
}

QString Event::getConfirmNextPopupTextFrom() const
{TRM;
    /// returned right before changing Round or RoundStage
    if(m_phases[m_currentPhase]->hasNext())
    {
        return m_phases[m_currentPhase]->getCurrentName();
    }

    /// returned right before changing the phase
    if(this->hasNextPhase())
    {
        return EnumConvert::PhaseToQString(m_currentPhase);
    }

    /// returned right before changing stage
    return EnumConvert::StageToQString(m_currentStage);
}

QString Event::getConfirmNextPopupTextTo() const
{TRM;
    /// returned right before changing Round or RoundStage
    if(m_phases[m_currentPhase]->hasNext())
    {
        return m_phases[m_currentPhase]->getNextName();
    }

    /// returned right before changing the phase
    if(this->hasNextPhase())
    {
        return EnumConvert::PhaseToQString(PhaseEnum::Second);
    }

    /// returned right before changing stage
    return EnumConvert::StageToQString(
        static_cast<StageEnum>(m_currentStage+1));
}

QmlPhasePtrVector Event::getPhasesQml() const
{TRM;
    QmlPhasePtrVector retVec;
    retVec.reserve( m_phases.size() );
    for(const auto &phasePtr : m_phases)
        retVec.append(phasePtr.data());
    return retVec;
}

Team *Event::getDetachedTeamQml() const
{TRM;
    return m_detachedTeam.data();
}

QmlTeamPtrVector Event::getTeamsQml() const
{TRM;
    QmlTeamPtrVector retVec;
    retVec.reserve( m_teams.size() );
    for(const auto &teamPtr : m_teams)
        retVec.append(teamPtr.data());
    return retVec;
}

void Event::setName(QString name)
{TRM;
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}

void Event::setFirstPhaseDate(QString firstPhaseDate)
{TRM;
    if (m_firstPhaseDate == firstPhaseDate)
        return;
    m_firstPhaseDate = firstPhaseDate;
    emit firstPhaseDateChanged();
}

void Event::setSecondPhaseDate(QString secondPhaseDate)
{TRM;
    if (m_secondPhaseDate == secondPhaseDate)
        return;
    m_secondPhaseDate = secondPhaseDate;
    emit secondPhaseDateChanged();
}

void Event::setCompetitionOrganizer(QString competitionOrganizer)
{TRM;
    if (m_competitionOrganizer == competitionOrganizer)
        return;
    m_competitionOrganizer = competitionOrganizer;
    emit competitionOrganizerChanged();
}

void Event::setFirstPhasePlace(QString firstPhasePlace)
{TRM;
    if (m_firstPhasePlace == firstPhasePlace)
        return;
    m_firstPhasePlace = firstPhasePlace;
    emit firstPhasePlaceChanged();
}

void Event::setSecondPhasePlace(QString secondPhasePlace)
{TRM;
    if (m_secondPhasePlace == secondPhasePlace)
        return;
    m_secondPhasePlace = secondPhasePlace;
    emit secondPhasePlaceChanged();
}

void Event::setUnionDelegate(QString unionDelegate)
{TRM;
    if (m_unionDelegate == unionDelegate)
        return;
    m_unionDelegate = unionDelegate;
    emit unionDelegateChanged();
}

void Event::setJudges(QStringList judges)
{TRM;
    if (m_judges == judges)
        return;
    m_judges = judges;
    emit judgesChanged();
}

void Event::addJudge()
{TRM;
    m_judges.append("");
    emit this->judgesChanged();
}

void Event::deleteJudge(int index)
{TRM;
    if(index >= m_judges.size())
    {
        W("trying to delete not existing judge");
        return;
    }

    m_judges.remove(index);
    emit this->judgesChanged();
}

void Event::setJudge(int index, QString judge)
{TRM;
    if(index >= m_judges.size())
    {
        W("trying to acces not existing judge");
        return;
    }

    m_judges[index] = judge;
    /// do not emit here, it cause entire list to reload
    /// and user lose focus
    // emit this->judgesChanged();
}
