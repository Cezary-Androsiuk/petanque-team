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
    if(m_phase == PhaseEnum::First)
    {
        m_subPhases.append(SubPhasePtr::create(8));
        m_subPhases[0]->setName("1");
    }
    else // m_phase == PhaseEnum::Second
    {
        m_subPhases.append(SubPhasePtr::create(4));
        m_subPhases.append(SubPhasePtr::create(4));
        m_subPhases[0]->setName("2a");
        m_subPhases[1]->setName("2b");
    }
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
        if(!subPhasePtr->hasNextRound())
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
        subPhasePtr->goToNextRound();
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
