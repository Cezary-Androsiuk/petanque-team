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

const QList<PlayerPtrList> &GroupMatch::getGroupsOfPlayers() const
{
    return m_groupsOfPlayers;
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
