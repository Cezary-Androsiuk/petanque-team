#include "Round.h"
#include "cpp/objects/MatchSingiels.h"
#include "cpp/objects/MatchDublets.h"
#include "cpp/objects/MatchTriplets.h"

Round::Round(QObject *parent)
    : QObject{parent}
    , m_matchTypes({
                    MatchSingielsPtr::create(),
                    MatchDubletsPtr::create(),
                    MatchTypeBasePtr::create()
      })
    , m_currentRoundStage{RoundStageEnum::SingielsSelection}
{
    DOLT(this)

}

Round::~Round()
{
    DOLT(this)

}

QJsonObject Round::serialize() const
{

}

void Round::deserialize(const QJsonObject &jTeam)
{

}

void Round::clear(bool emitting)
{

}

bool Round::verify(QString &message) const
{
    if(m_currentRoundStage == RoundStageEnum::RoundSummary)
        return true;

    MatchTypeBasePtr currentMatchType = m_matchTypes[m_currentRoundStage/2];
    bool isSelectionStage = m_currentRoundStage%2 == 0;

    if(isSelectionStage)
    {
        if(!currentMatchType->verifySelection(message))
        {
            message = "in roundStage " +QString::number(m_currentRoundStage)+": " + message;
            return false;
        }
    }
    else
    {
        if(!currentMatchType->verifyMatch(message))
        {
            message = "in roundStage " +QString::number(m_currentRoundStage)+": " + message;
            return false;
        }
    }

    return true;
}

bool Round::hasNext() const
{
    // should be called before goToNextRoundStage
    return (m_currentRoundStage != RoundStageEnum::RoundSummary);
}

void Round::goToNext()
{
    // should be called only if hasNextRoundStage return true
    m_currentRoundStage = static_cast<RoundStageEnum>(m_currentRoundStage+1);
    emit this->currentRoundStageChanged();
    D("going to         roundStage: " + QString::number(m_currentRoundStage));
}

RoundStageEnum Round::getCurrentRoundStage() const
{
    return m_currentRoundStage;
}

void Round::setArrangement(const IntPairs &arrangement)
{
    m_arrangement = arrangement;
    D(QAPF("set arrangement for %p Round:", this))
    for(const auto &pair : m_arrangement)
    {
        D(QAPF("%d %d", pair.first, pair.second))
    }
}
