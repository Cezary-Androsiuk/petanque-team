#include "Phase.h"

Phase::Phase(PhaseEnum phase, QObject *parent)
    : QObject{parent}
    , m_phase{phase}
{
    DOLT(this)
}

Phase::~Phase()
{
    DOLT(this)
}

void Phase::onStart()
{
    D(QAPF("before phase start: %p", this), Log::Action::SaveSession)
    this->subPhaseStart();
}

void Phase::onEnd()
{
    D(QAPF("after phase end: %p", this), Log::Action::SaveSession)
    this->subPhaseEnd();
}

void Phase::initSubPhases(const TeamPtrLists &listsOfTeams)
{
    Personalization *const p = Personalization::getInstance();
    const QJsonObject &roundsMatches = p->getRoundsMatches();

    if(m_phase == PhaseEnum::First)
    {
        QJsonArray arrangement = roundsMatches["phase 1"].toArray();

        if(listsOfTeams.size() != 1)
        {
            E(QAPF("invalid listOfTeams size, required 1, but got %lld", listsOfTeams.size()));
            return;
        }

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[0]->setTeams(listsOfTeams[0]);
        m_subPhases[0]->setName("1");
        m_subPhases[0]->initRounds(arrangement);
    }
    else // m_phase == PhaseEnum::Second
    {
        QJsonArray arrangement = roundsMatches["phase 2"].toArray();

        if(listsOfTeams.size() != 2)
        {
            E(QAPF("invalid listOfTeams size, required 2, but got %lld", listsOfTeams.size()));
            return;
        }

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[0]->setTeams(listsOfTeams[0]);
        m_subPhases[0]->setName("2a");
        m_subPhases[0]->initRounds(arrangement);

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[1]->setTeams(listsOfTeams[1]);
        m_subPhases[1]->setName("2b");
        m_subPhases[1]->initRounds(arrangement);
    }
}

QJsonObject Phase::serialize() const
{
    QJsonObject jPhase;

    /// m_phase - don't need to be serialized

    QJsonArray jSubPhases;
    for(const auto &subPhasePtr : m_subPhases)
    {
        if(subPhasePtr.isNull())
        {
            W("cannot serialize not existing sub phase")
            jSubPhases.append( QJsonObject() );
        }
        else jSubPhases.append( subPhasePtr->serialize() );
    }
    jPhase[ SERL_SUB_PHASES_KEY ] = jSubPhases;

    return jPhase;
}

void Phase::deserialize(const QJsonObject &jPhase)
{
    this->clear(false);

    /// m_phase - don't need to be deserialized

    this->deserializeSubPhases(jPhase);
}

void Phase::deserializeSubPhases(const QJsonObject &jPhase)
{
    if(!jPhase.contains( SERL_SUB_PHASES_KEY ))
    {
        E("cannot deserialize subphases due to missing key in json: " SERL_SUB_PHASES_KEY)
        return;
    }

    QJsonArray jSubPhases = jPhase[ SERL_SUB_PHASES_KEY ].toArray();

    if(m_subPhases.size() != jSubPhases.size())
    {
        E(QAPF("cannot deserialize subphases due to inconsistent size: "
               "m_subPhases(%lld) list and jSubPhases(%lld) list",
               m_subPhases.size(), jSubPhases.size() ))
        return;
    }

    for(int i=0; i<m_subPhases.size(); i++)
    {
        if(m_subPhases[i].isNull())
            E("cannot deserialize, due to not existing subPhase")
        else
            m_subPhases[i]->deserialize( jSubPhases[i].toObject() );
    }
}

void Phase::clear(bool emitting)
{

}

void Phase::verify()
{
    for(const auto &subPhasePtr : m_subPhases)
    {
        QString message;
        if(!subPhasePtr->verify(message))
        {
            QString prefix( "In "+ subPhasePtr->getName() +" phase: " );
            emit this->verificationFailed(prefix + message);
            return;
        }
    }
    emit this->verified();
}

bool Phase::hasNext()
{
    bool hasNextRound = true;
    for(const auto &subPhasePtr : m_subPhases)
    {
        if(!subPhasePtr->hasNext())
        {
            hasNextRound = false;
            break;
        }
    }
    return hasNextRound;
}

void Phase::goToNext()
{
    if(!this->hasNext())
    {
        W("trying to go next, where is no next")
        return;
    }

    for(auto &subPhasePtr : m_subPhases)
    {
        subPhasePtr->goToNext();
    }
}

void Phase::assignExampleData()
{
    /// for all subPhases
    for(auto &subPhasePtr : m_subPhases)
        subPhasePtr->assignExampleData();
}

void Phase::subPhaseStart()
{
    for(auto &subPhase : m_subPhases)
        subPhase->onStart();
}

void Phase::subPhaseEnd()
{
    for(auto &subPhase : m_subPhases)
        subPhase->onEnd();
}

int Phase::getSubPhasesCount() const
{
    return m_subPhases.size();
}

const SubPhasePtrVector &Phase::getSubPhases() const
{
    return m_subPhases;
}

QmlSubPhasePtrVector Phase::getSubPhasesQml() const
{
    QmlSubPhasePtrVector retVec;
    retVec.reserve( m_subPhases.size() );
    for(const auto &subPhasePtr : m_subPhases)
        retVec.append(subPhasePtr.data());
    return retVec;
}
