#include "Phase.h"

Phase::Phase(PhaseEnum phase, int subPhasesCount, QObject *parent)
    : QObject{parent}
    , m_phase{phase}
    , m_subPhasesCount{subPhasesCount}
    , m_subPhases(subPhasesCount, SubPhasePtr::create())
{
    I(QAPF("Creating Phase: %p", this));
    this->initSubPhases();
}

Phase::~Phase()
{
    I(QAPF("Destroying Phase: %p", this));
}

void Phase::initSubPhases()
{
    if(m_phase == PhaseEnum::First)
    {
        if(m_subPhases.size() != 1)
        {
            E("");
            return;
        }
        m_subPhases[0]->setName("1");
    }
    else // m_phase == PhaseEnum::Second
    {
        if(m_subPhases.size() != 2)
        {
            E("");
            return;
        }
        m_subPhases[0]->setName("2a");
        m_subPhases[1]->setName("2b");
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
    return m_subPhasesCount;
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
