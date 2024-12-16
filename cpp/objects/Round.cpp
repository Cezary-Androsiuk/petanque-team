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
    , m_currentRoundStage{RoundStage::SingielsSelection}
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
    if(m_currentRoundStage == RoundStage::RoundSummary)
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

bool Round::hasNextRoundStage() const
{
    // should be called before goToNextRoundStage
    return (m_currentRoundStage != RoundStage::RoundSummary);
}

void Round::goToNextRoundStage()
{
    // should be called only if hasNextRoundStage return true
    m_currentRoundStage = static_cast<RoundStage>(m_currentRoundStage+1);
    D("going to         roundStage: " + QString::number(m_currentRoundStage));
}
