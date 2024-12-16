#include "Round.h"

Round::Round(QObject *parent)
    : QObject{parent}
{
    DOLT(this)

}

Round::~Round()
{
    DOLT(this)

}

void Round::initMatches()
{
    const TeamPtrList &teams = globalTeams;
    const int teamSize = teams.size();

    m_matches.reserve(m_arrangement.size());
    for(int i=0; i<m_arrangement.size(); i++)
    {
        // D("creating "+ QString::number(i) +" match")
        const auto &matchArrangement = m_arrangement[i];
        int t1 = matchArrangement.first;
        int t2 = matchArrangement.second;
        if(t1 >= teamSize || t2 >= teamSize)
        {
            W(QAPF("cannot assing team to match t1(%d), t2(%d), teamSize(%d),"
                   " then match will not be created", t1, t2, teamSize))
            continue;
        }

        MatchPtr match = MatchPtr::create();
        match->setTeamLeft(teams[t1]);
        match->setTeamRight(teams[t2]);
        m_matches.append(match);
    }
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
    for(int i=0; i<m_matches.size(); i++)
    {
        if(!(m_matches[i]->verify(message)))
        {
            message = "in match " + QString::number(i) + ": " + message;
            return false;
        }
    }
    return true;
}

bool Round::hasNext() const
{
#if DEBUG_MODE
    /// find inconsistency in matches "hasNext"

    /// check for what value look for
    bool expectedValue = true;
    for(const auto &matchPtr : m_matches)
    {
        if(!matchPtr->hasNext())
        {
            expectedValue = false;
            break;
        }
    }
    for(const auto &matchPtr : m_matches)
    {
        if(matchPtr->hasNext() != expectedValue)
        {
            W("found inconsistency in matches: ")
            for(int i=0; i<m_matches.size(); i++)
            {
                I(QAPF("match %d %s next", i, m_matches[i]->hasNext()?"has":"doesn't have"))
            }
            break;
        }
    }
#endif

    for(const auto &matchPtr : m_matches)
    {
        if(!matchPtr->hasNext())
        {
            /// matches don't have next one
            return false;
        }
    }

    if(m_matches.isEmpty())
    {
        E("matches are empty")
        return false;
    }

    return true;
}

void Round::goToNext()
{
    for(int i=0; i<m_matches.size(); i++)
        m_matches[i]->goToNext();
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
