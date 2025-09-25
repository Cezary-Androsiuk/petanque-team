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
        E("subPhasePtr is null!: %p", m_subPhasePtr);
        I("Can't build rankings!");
        return;
    }

    Q_ASSERT(m_teamScores.size() == 0);

    TeamScore *ts = new TeamScore(this);
    ts->setTeamName("example testing value");
    m_teamScores.append(ts);
    emit this->teamScoresChanged();

    // QString data = SAPF("rounds: %lld", m_subPhasePtr->getRoundsQml().size());
}

void RoundSummaryScoreCounter::classBegin()
{TRM;

}

SubPhase *RoundSummaryScoreCounter::getSubPhasePtr() const
{TRM;
    return m_subPhasePtr;
}

TeamPtrScores RoundSummaryScoreCounter::getTeamScores() const
{TRM;
    return m_teamScores;
}

void RoundSummaryScoreCounter::setSubPhasePtr(SubPhase *subPhasePtr)
{TRM;
    m_subPhasePtr = subPhasePtr;
}
