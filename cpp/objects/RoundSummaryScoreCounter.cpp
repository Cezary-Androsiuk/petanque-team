#include "RoundSummaryScoreCounter.h"

#include "support/Log.h"

RoundSummaryScoreCounter::RoundSummaryScoreCounter(QObject *parent)
    : QObject{parent}
    , m_subPhasePtr{nullptr}
{
    D("round summary SC created");
}

RoundSummaryScoreCounter::~RoundSummaryScoreCounter()
{
    D("round summary destroyed");
}

SubPhase *RoundSummaryScoreCounter::getSubPhasePtr() const
{
    return m_subPhasePtr;
}

void RoundSummaryScoreCounter::setSubPhasePtr(SubPhase *subPhasePtr)
{
    D("sub phase set");
    m_subPhasePtr = subPhasePtr;
}

QString RoundSummaryScoreCounter::getData() const
{
    D("data get: " + m_data);
    return m_data;
}

void RoundSummaryScoreCounter::setData(const QString &newData)
{
    D("data set");
    if (m_data == newData)
        return;
    m_data = newData;
    emit dataChanged();
}

void RoundSummaryScoreCounter::buildRankings()
{
    D("init");
    if(!m_subPhasePtr)
    {
        E("subPhasePtr is null!: %p", m_subPhasePtr);
        return;
    }

    QString data = SAPF("rounds: %lld", m_subPhasePtr->getRoundsQml().size());
    this->setData(data);
}
