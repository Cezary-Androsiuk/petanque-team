#include "Match.h"
#include "cpp/objects/MatchSingiels.h"
#include "cpp/objects/MatchDublets.h"
#include "cpp/objects/MatchTriplets.h"

Match::Match(QObject *parent)
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

Match::~Match()
{
    DOLT(this)
}

QJsonObject Match::serialize() const
{

}

void Match::deserialize(const QJsonObject &jTeam)
{

}

void Match::clear(bool emitting)
{

}

bool Match::verify(QString &message) const
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

bool Match::hasNext() const
{
    // should be called before goToNextRoundStage
    return (m_currentRoundStage != RoundStageEnum::RoundSummary);
}

void Match::goToNext()
{
    // should be called only if hasNextRoundStage return true
    m_currentRoundStage = static_cast<RoundStageEnum>(m_currentRoundStage+1);
    emit this->currentRoundStageChanged();
    D("going to         roundStage: " + QString::number(m_currentRoundStage));
}

RoundStageEnum Match::getCurrentRoundStage() const
{
    return m_currentRoundStage;
}

void Match::setTeamLeft(const TeamPtr &team)
{
    m_teamLeft = team.toWeakRef();
}

void Match::setTeamRight(const TeamPtr &team)
{
    m_teamRight = team.toWeakRef();
}
