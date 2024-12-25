#include "GroupSelection.h"

GroupSelection::GroupSelection(int groupsCount, int minPlayersInGroup, int maxPlayersInGroup, QObject *parent)
    : QObject{parent}
    , m_groupsCount{groupsCount}
    , m_minPlayersInGroup{minPlayersInGroup}
    , m_maxPlayersInGroup{maxPlayersInGroup}
{
    DOLT(this);
    QObject::connect(this, &GroupSelection::playerSelectionsChanged, [&](){D("changed player selections")});
}

GroupSelection::~GroupSelection()
{
    DOLT(this);
}

QJsonObject GroupSelection::serialize() const
{
    return QJsonObject();
}

void GroupSelection::deserialize(const QJsonObject &jGroupSelection)
{
    this->clear(false);
}

void GroupSelection::clear(bool emitting)
{

}

bool GroupSelection::verify(QString &message)
{
    /// check for each group if it contains enough declared players
    for(int i=0; i<m_groupsCount; i++)
    {
        int foundPlayersInGroup = 0;
        for(int playerGroup : m_playerSelections)
        {
            if(playerGroup == i)
                ++ foundPlayersInGroup;
        }

        if(m_minPlayersInGroup <= foundPlayersInGroup && foundPlayersInGroup <= m_maxPlayersInGroup)
            continue;

        QString difference = (m_minPlayersInGroup == m_maxPlayersInGroup) ?
                                 QAPF("%d", m_minPlayersInGroup) :
                                 QAPF("%d or %d", m_minPlayersInGroup, m_maxPlayersInGroup);

        message = QAPF("in group %d, %d players were selected, but %s were expected",
                       i, foundPlayersInGroup, difference.toStdString().c_str());

        return false;
    }

    return true;
}

void GroupSelection::setSelectionSize(qsizetype size)
{
    if(!m_playerSelections.isEmpty() && size > m_playerSelections.size())
    {
        I("resizing selection size")
        m_playerSelections.resize(size, GroupSelection::defaultSelectionValue);
        return;
    }

    if(!m_playerSelections.isEmpty())
    {
        W("trying to shrink selection size!")
        return;
    }

    /// first init
    m_playerSelections.assign(size, GroupSelection::defaultSelectionValue);
}

void GroupSelection::setExampleData()
{
    /// uncheck all
    for(int &group : m_playerSelections)
        group = GroupSelection::defaultSelectionValue;

    for(int i=0; i<m_playerSelections.size(); i++)
    {
        int groupIndex = i/m_minPlayersInGroup; // gives 1->{0,1,2,3,4,5} or 2->{0,0,1,1,2,2} or 3->{0,0,0,1,1,1}
        m_playerSelections[i] = groupIndex;
    }
}

void GroupSelection::setPlayerGroup(int playerIndex, int groupIndex)
{
    /// input value protection (always use protection)
    if(playerIndex >= m_playerSelections.size())
    {
        W(QAPF("trying to access %d playerIndex, while list contains %lld players",
               playerIndex, m_playerSelections.size()))
        return;
    }

    if(groupIndex >= m_groupsCount)
    {
        W(QAPF(
            "trying to assign %d group for %d playerIndex, while groupsCount is %d",
            groupIndex, playerIndex, m_groupsCount ));
        return;
    }

    /// Binding loop protection
    if(m_playerSelections[playerIndex] == groupIndex)
        return;

    /// Uncheck (set to defaultSelectionValue) if other values in list if contains this group

    m_playerSelections[playerIndex] = groupIndex;
    emit this->playerSelectionsChanged();
}

const QList<int> &GroupSelection::getPlayerSelections() const
{
    return m_playerSelections;
}

int GroupSelection::getGroupsCount() const
{
    return m_groupsCount;
}
