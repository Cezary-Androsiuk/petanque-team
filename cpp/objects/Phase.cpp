#include "Phase.h"

Phase::Phase(PhaseEnum phase, QObject *parent)
    : QObject{parent}
    , m_phase{phase}
{
    DOLT(this)
    this->initSubPhases();
}

Phase::~Phase()
{
    DOLT(this)
}

void Phase::initSubPhases()
{
    Personalization *const p = Personalization::getInstance();
    const QJsonObject &roundsMatches = p->getRoundsMatches();
    if(m_phase == PhaseEnum::First)
    {
        QJsonArray arrangement = roundsMatches["phase 1"].toArray();

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[0]->setName("1");
        m_subPhases[0]->initRounds(arrangement);
    }
    else // m_phase == PhaseEnum::Second
    {
        QJsonArray arrangement = roundsMatches["phase 2"].toArray();

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[0]->setName("2a");
        m_subPhases[0]->initRounds(arrangement);

        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
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
    for(auto &subPhasePtr : m_subPhases)
    {
        subPhasePtr->goToNext();
    }
}

void Phase::assignExampleData()
{
    for(auto &subPhasePtr : m_subPhases)
        subPhasePtr->assignExampleData();
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
