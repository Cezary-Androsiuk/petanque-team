#include "TeamScore.h"

TeamScore::TeamScore(QObject *parent)
    : QObject{parent}
    , m_allParametersList{
        &m_wins,
        &m_gainedMatchPoints,
        &m_competitionsWon,
        &m_wonTriples,
        &m_wonDoubles,
        &m_wonSingles,
        &m_smallPointsTriples.gained,
        &m_smallPointsTriples.lost,
        &m_smallPointsTriples.diff,
        &m_smallPointsDoubles.gained,
        &m_smallPointsDoubles.lost,
        &m_smallPointsDoubles.diff,
        &m_smallPointsSingles.gained,
        &m_smallPointsSingles.lost,
        &m_smallPointsSingles.diff
    }
{}

QString TeamScore::getTeamName() const
{
    return m_teamName;
}

int TeamScore::getWins() const
{
    return m_wins;
}

int TeamScore::getGainedMatchPoints() const
{
    return m_gainedMatchPoints;
}

int TeamScore::getCompetitionsWon() const
{
    return m_competitionsWon;
}

int TeamScore::getWonTriples() const
{
    return m_wonTriples;
}

int TeamScore::getWonDoubles() const
{
    return m_wonDoubles;
}

int TeamScore::getWonSingles() const
{
    return m_wonSingles;
}

int TeamScore::getGainedSmallPointsInTriples() const
{
    return m_smallPointsTriples.gained;
}

int TeamScore::getLostSmallPointsInTriples() const
{
    return m_smallPointsTriples.lost;
}

int TeamScore::getDiffSmallPointsInTriples() const
{
    return m_smallPointsTriples.diff;
}

int TeamScore::getGainedSmallPointsInDoubles() const
{
    return m_smallPointsDoubles.gained;
}

int TeamScore::getLostSmallPointsInDoubles() const
{
    return m_smallPointsDoubles.lost;
}

int TeamScore::getDiffSmallPointsInDoubles() const
{
    return m_smallPointsDoubles.diff;
}

int TeamScore::getGainedSmallPointsInSingles() const
{
    return m_smallPointsSingles.gained;
}

int TeamScore::getLostSmallPointsInSingles() const
{
    return m_smallPointsSingles.lost;
}

int TeamScore::getDiffSmallPointsInSingles() const
{
    return m_smallPointsSingles.diff;
}

const QList<int *> TeamScore::getAllParametersList() const
{
    return m_allParametersList;
}

void TeamScore::setTeamName(const QString &teamName)
{
    if (m_teamName == teamName)
        return;
    m_teamName = teamName;
    emit teamNameChanged();
}

void TeamScore::setWins(int wins)
{
    if (m_wins == wins)
        return;
    m_wins = wins;
    emit winsChanged();
}

void TeamScore::setGainedMatchPoints(int gainedMatchPoints)
{
    if (m_gainedMatchPoints == gainedMatchPoints)
        return;
    m_gainedMatchPoints = gainedMatchPoints;
    emit gainedMatchPointsChanged();
}

void TeamScore::setCompetitionsWon(int competitionsWon)
{
    if (m_competitionsWon == competitionsWon)
        return;
    m_competitionsWon = competitionsWon;
    emit competitionsWonChanged();
}

void TeamScore::setWonTriples(int wonTriples)
{
    if (m_wonTriples == wonTriples)
        return;
    m_wonTriples = wonTriples;
    emit wonTriplesChanged();
}

void TeamScore::setWonDoubles(int wonDoubles)
{
    if (m_wonDoubles == wonDoubles)
        return;
    m_wonDoubles = wonDoubles;
    emit wonDoublesChanged();
}

void TeamScore::setWonSingles(int wonSingles)
{
    if (m_wonSingles == wonSingles)
        return;
    m_wonSingles = wonSingles;
    emit wonSinglesChanged();
}

void TeamScore::setGainedSmallPointsInTriples(int gainedSmallPointsInTriples)
{
    if(m_smallPointsTriples.gained == gainedSmallPointsInTriples)
        return;
    m_smallPointsTriples.gained = gainedSmallPointsInTriples;
    emit gainedSmallPointsInTriplesChanged();
}

void TeamScore::setLostSmallPointsInTriples(int lostSmallPointsInTriples)
{
    if(m_smallPointsTriples.lost == lostSmallPointsInTriples)
        return;
    m_smallPointsTriples.lost = lostSmallPointsInTriples;
    emit lostSmallPointsInTriplesChanged();
}

void TeamScore::setDiffSmallPointsInTriples(int diffSmallPointsInTriples)
{
    if(m_smallPointsTriples.diff == diffSmallPointsInTriples)
        return;
    m_smallPointsTriples.diff = diffSmallPointsInTriples;
    emit diffSmallPointsInTriplesChanged();
}

void TeamScore::setGainedSmallPointsInDoubles(int gainedSmallPointsInDoubles)
{
    if(m_smallPointsDoubles.gained == gainedSmallPointsInDoubles)
        return;
    m_smallPointsDoubles.gained = gainedSmallPointsInDoubles;
    emit gainedSmallPointsInDoublesChanged();
}

void TeamScore::setLostSmallPointsInDoubles(int lostSmallPointsInDoubles)
{
    if(m_smallPointsDoubles.lost == lostSmallPointsInDoubles)
        return;
    m_smallPointsDoubles.lost = lostSmallPointsInDoubles;
    emit lostSmallPointsInDoublesChanged();
}

void TeamScore::setDiffSmallPointsInDoubles(int diffSmallPointsInDoubles)
{
    if(m_smallPointsDoubles.diff == diffSmallPointsInDoubles)
        return;
    m_smallPointsDoubles.diff = diffSmallPointsInDoubles;
    emit diffSmallPointsInDoublesChanged();
}

void TeamScore::setGainedSmallPointsInSingles(int gainedSmallPointsInSingles)
{
    if(m_smallPointsSingles.gained == gainedSmallPointsInSingles)
        return;
    m_smallPointsSingles.gained = gainedSmallPointsInSingles;
    emit gainedSmallPointsInSinglesChanged();
}

void TeamScore::setLostSmallPointsInSingles(int lostSmallPointsInSingles)
{
    if(m_smallPointsSingles.lost == lostSmallPointsInSingles)
        return;
    m_smallPointsSingles.lost = lostSmallPointsInSingles;
    emit lostSmallPointsInSinglesChanged();
}

void TeamScore::setDiffSmallPointsInSingles(int diffSmallPointsInSingles)
{
    if(m_smallPointsSingles.diff == diffSmallPointsInSingles)
        return;
    m_smallPointsSingles.diff = diffSmallPointsInSingles;
    emit diffSmallPointsInSinglesChanged();
}
