#include "GroupSelection.h"

GroupSelection::GroupSelection(uint groupsCount, uint minPlayersInGroup, uint maxPlayersInGroup, QObject *parent)
    : QObject{parent}
    , m_groupsCount{groupsCount}
    , m_minPlayersInGroup{minPlayersInGroup}
    , m_maxPlayersInGroup{maxPlayersInGroup}
{
    DOLT(this);
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
