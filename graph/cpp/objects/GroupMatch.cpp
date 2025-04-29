#include "GroupMatch.h"

const int GroupMatch::maxPointsInMatch = Personalization::getInstance()->getMaxPointsInMatch();

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

void GroupMatch::onStart()
{
    D(QAPF("before groupMatch start: %p", this), Log::Action::SaveSession)
}

void GroupMatch::onEnd()
{
    D(QAPF("after groupMatch end: %p", this), Log::Action::SaveSession)
}

QJsonObject GroupMatch::serialize() const
{
    QJsonObject jGroupMatch;

    jGroupMatch[SERL_GROUP_MATCH_GROUPS_COUNT_KEY] = m_groupsCount;
    jGroupMatch[SERL_GROUP_MATCH_DPLCIG_KEY] = m_defaultPlayersCountInGroup;

    jGroupMatch[SERL_GROUP_MATCH_GROUPS_OF_PLAYERS_KEY] = this->serializeGroupsOfPlayers();


    QJsonArray jMatchPoints;
    for(int matchPoint : m_matchPoints)
        jMatchPoints.append(matchPoint);
    jGroupMatch[SERL_GROUP_MATCH_MATCH_POINTS_KEY] = jMatchPoints;

    if(m_team.isNull())
    {
        W("cannot read team because is null")
        jGroupMatch[SERL_GROUP_MATCH_TEAM_NAME_KEY] = "";
    }
    else
    {
        QString teamName = m_team->getName();
        jGroupMatch[SERL_GROUP_MATCH_TEAM_NAME_KEY] = teamName;
    }

    return jGroupMatch;
}

void GroupMatch::deserialize(const QJsonObject &jGroupMatch)
{
    /// groups count don't need to be deserialized
    /// default players count in group don't need to be deserialized
    /// groups of players don't need to be deserialized

    m_matchPoints.clear();
    QJsonArray jMatchPoints( jGroupMatch[SERL_GROUP_MATCH_MATCH_POINTS_KEY].toArray() );
    for(const auto &jMatchPoint : jMatchPoints)
        m_matchPoints.append( jMatchPoint.toInt() );
    emit this->matchPointsChanged();

    /// team don't need to be deserialized
}

QJsonArray GroupMatch::serializeGroupsOfPlayers() const
{
    QJsonArray jGroupsOfPlayers;

    for(int i=0; i<m_groupsOfPlayers.size(); i++)
    {
        QJsonArray jGroupOfPlayers;
        for(int j=0; j<m_groupsOfPlayers[i].size(); j++)
        {
            PlayerPtr player = m_groupsOfPlayers[i][j];

            jGroupOfPlayers.append(player->getLicense());
        }
        jGroupsOfPlayers.append(jGroupOfPlayers);
    }

    return jGroupsOfPlayers;
}

void GroupMatch::setGroupPoints(int group, int points)
{
    if(group >= m_matchPoints.size() || group < 0)
    {
        W("trying to assign points to a non-existing group")
        return;
    }

    if(m_matchPoints[group] == points)
        return;

    m_matchPoints[group] = points;
    emit this->matchPointsChanged();
}

// bool GroupMatch::verify(QString &message)
// {
//     return true;
// }

void GroupMatch::assignExampleData(const IntList &data)
{
    if(m_matchPoints.empty())
    {
        for(int value : data)
            m_matchPoints.append(value);
        emit this->matchPointsChanged();
    }
    else if(m_matchPoints.size() != data.size())
    {
        W(QAPF("cannot assign example data: m_matchPoints.size(%lld) != data.size(%lld)",
               m_matchPoints.size(), data.size()));
    }
    else
    {
        for(int i=0; i<m_matchPoints.size(); i++)
            m_matchPoints[i] = data[i];
        emit this->matchPointsChanged();
    }
}

int GroupMatch::getGroupsCount() const
{
    return m_groupsCount;
}

int GroupMatch::getDefaultPlayersCountInGroup() const
{
    return m_defaultPlayersCountInGroup;
}

const QList<PlayerPtrList> &GroupMatch::getGroupsOfPlayers() const
{
    return m_groupsOfPlayers;
}

QmlVecOfPlayersVec GroupMatch::getGroupsOfPlayersQml() const
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
    return m_team.data();
}

int GroupMatch::getMaxPointsInMatch() const
{
    return GroupMatch::maxPointsInMatch;
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
