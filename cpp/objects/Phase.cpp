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
        m_subPhases.append(SubPhasePtr::create(arrangement.size()));
        m_subPhases[0]->setName("2a");
        m_subPhases[0]->initRounds(arrangement);
        m_subPhases[1]->setName("2b");
        m_subPhases[1]->initRounds(arrangement);
    }
}

QJsonObject Phase::serialize() const
{
    return QJsonObject();
}

void Phase::deserialize(const QJsonObject &phaseJson)
{

}

void Phase::clear()
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
