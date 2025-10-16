#include "RoundSummaryScoreCounter.h"

#include "support/Log.h"

RoundSummaryScoreCounter::RoundSummaryScoreCounter(QObject *parent)
    : QObject{parent}
    , m_subPhasePtr{nullptr}
{TRM; DOLTV("%p", parent);

}

RoundSummaryScoreCounter::~RoundSummaryScoreCounter()
{TRM; DOLT;

}

void RoundSummaryScoreCounter::componentComplete()
{TRM;
    if(!m_subPhasePtr)
    {
        E("subPhasePtr is a null!: %p", m_subPhasePtr);
        I("Can't build rankings!");
        emit this->initError("subPhasePtr is a null!");
        return;
    }

    const TeamPtrList &teams = m_subPhasePtr->getTeams();



    /// create summary here
    for(int i=0; i<teams.size(); i++)
    {
        const QSharedPointer<Team> &team = teams[i];
        TeamScore *ts = new TeamScore(this);
        ts->setTeamName(team->getName());

        m_teamScoresSummary.append(ts);
    }
    emit this->teamScoresSummaryChanged();



    /// create rankings here
    for(int i=0; i<teams.size(); i++)
    {
        const QSharedPointer<Team> &team = teams[i];
        TeamScore *ts = new TeamScore(this);
        ts->setTeamName(team->getName());

        m_teamScoresRanking.append(ts);
    }
    emit this->teamScoresRankingChanged();



    emit this->initComplete();
}

void RoundSummaryScoreCounter::classBegin(){}

SubPhase *RoundSummaryScoreCounter::getSubPhasePtr() const
{TRM;
    return m_subPhasePtr;
}

TeamPtrScores RoundSummaryScoreCounter::getTeamScoresSummary() const
{TRM;
    return m_teamScoresSummary;
}

TeamPtrScores RoundSummaryScoreCounter::getTeamScoresRanking() const
{TRM;
    return m_teamScoresRanking;
}

void RoundSummaryScoreCounter::setSubPhasePtr(SubPhase *subPhasePtr)
{TRM;
    m_subPhasePtr = subPhasePtr;
}
