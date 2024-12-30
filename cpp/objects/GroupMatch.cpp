#include "GroupMatch.h"

GroupMatch::GroupMatch(QObject *parent)
    : QObject{parent}
    , m_groupsCount{0}
    , m_defaultPlayersCountInGroup{0}
{
    DOLT(this)
}

GroupMatch::~GroupMatch()
{
    DOLT(this)
}

QJsonObject GroupMatch::serialize() const
{
    return QJsonObject();
}

void GroupMatch::deserialize(const QJsonObject &jGroupMatch)
{
    this->clear(false);
}

void GroupMatch::clear(bool emitting)
{

}

void GroupMatch::setGroupPoints(int group, int points)
{
    if(group >= m_matchPoints.size() || group < 0)
    {
        W("trying to assign points to a non-existing group")
        return;
    }

    m_matchPoints[group] = points;
    emit this->matchPointsChanged();
}

bool GroupMatch::verify(QString &message)
{
    return true;
}

void GroupMatch::assignExampleData()
{

}

int GroupMatch::getGroupsCount() const
{
    return m_groupsCount;
}

int GroupMatch::getDefaultPlayersCountInGroup() const
{
    return m_defaultPlayersCountInGroup;
}

QmlVecOfPlayersVec GroupMatch::getGroupsOfPlayers() const
{
    QmlVecOfPlayersVec ret;
    ret.resize(m_groupsOfPlayers.size());
    for(int i=0; i<ret.size(); i++)
    {
        ret[i].resize(m_groupsOfPlayers[i].size());
        for(int j=0; j<ret[i].size(); j++)
            ret[i][j] = m_groupsOfPlayers[i][j].data();
    }
    return ret;
}

const IntList &GroupMatch::getMatchPoints() const
{
    return m_matchPoints;
}

const Team *GroupMatch::getTeamQml() const
{
    if(m_team.isNull())
    {
        W("returning null as a team");
        return nullptr;
    }

    return m_team.toStrongRef().data();
}

void GroupMatch::setGroupsCount(int groupsCount)
{
    if(m_groupsCount == groupsCount)
        return;

    m_groupsCount = groupsCount;
    emit this->groupsCountChanged();
}

void GroupMatch::setDefaultPlayersCountInGroup(int defaultPlayersCountInGroup)
{
    if(m_defaultPlayersCountInGroup == defaultPlayersCountInGroup)
        return;

    m_defaultPlayersCountInGroup = defaultPlayersCountInGroup;
    emit this->defaultPlayersCountInGroupChanged();
}

void GroupMatch::setGroupsOfPlayers(const QList<PlayerPtrList> &groupsOfPlayers)
{
    m_groupsOfPlayers = groupsOfPlayers;
    emit this->groupsOfPlayersChanged();
}

void GroupMatch::setMatchPointsSize(int matchPointsSize)
{
    if(!m_matchPoints.empty())
    {
        I("resizing matchPoints list")
        if(m_matchPoints.size() > matchPointsSize)
        {
            W("trying to shrink matchPoints list")
            return;
        }
    }

    m_matchPoints.resize(matchPointsSize, 0);
    emit this->matchPointsChanged();
}

void GroupMatch::setTeam(TeamPtr team)
{
    m_team = team.toWeakRef();
    emit this->teamChanged();
}
