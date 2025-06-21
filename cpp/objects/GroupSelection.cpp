#include "GroupSelection.h"

#include "support/Log.h"

GroupSelection::GroupSelection(int groupsCount, int minPlayersInGroup, int maxPlayersInGroup, QObject *parent)
    : QObject{parent}
    , m_groupsCount{groupsCount}
    , m_minPlayersInGroup{minPlayersInGroup}
    , m_maxPlayersInGroup{maxPlayersInGroup}
{TRM; DOLTV(SAPF("%d, %d, %d, %p", groupsCount, minPlayersInGroup, maxPlayersInGroup, parent));
    // QObject::connect(this, &GroupSelection::playerSelectionsChanged, [&](){D("changed player selections")});
}

GroupSelection::~GroupSelection()
{TRM; DOLT;

}

void GroupSelection::onStart()
{TRM;
    DA(Log::Action::SaveSession, "before groupSelection start: %p", this);
}

void GroupSelection::onEnd()
{TRM;
    DA(Log::Action::SaveSession, "after groupSelection end: %p", this);
}

QJsonObject GroupSelection::serialize() const
{TRM;
    QJsonObject jGroupSelection;

    jGroupSelection[SERL_GROUP_SELECTION_GROUPS_COUNT_KEY] = m_groupsCount;
    jGroupSelection[SERL_GROUP_SELECTION_MIN_PLAYERS_IN_GROUP_KEY] = m_minPlayersInGroup;
    jGroupSelection[SERL_GROUP_SELECTION_MAX_PLAYERS_IN_GROUP_KEY] = m_maxPlayersInGroup;

    /// Serialize player selections
    QJsonArray jPlayerSelections;
    for(int playerSelection : m_playerSelections)
        jPlayerSelections.append(playerSelection);
    jGroupSelection[SERL_GROUP_SELECTION_PLAYER_SELECTIONS_KEY] = jPlayerSelections;

    /// Serialize team name
    if(m_team.isNull())
    {
        W("cannot read team because is null");
        jGroupSelection[SERL_GROUP_SELECTION_TEAM_NAME_KEY] = "";
    }
    else
    {
        QString teamName = m_team->getName();
        jGroupSelection[SERL_GROUP_SELECTION_TEAM_NAME_KEY] = teamName;
    }

    return jGroupSelection;
}

void GroupSelection::deserialize(const QJsonObject &jGroupSelection)
{TRM;
    /// groups count don't need to be deserialized
    /// min players in group don't need to be deserialized
    /// max players in group don't need to be deserialized

    m_playerSelections.clear();
    QJsonArray jPlayerSelections( jGroupSelection[SERL_GROUP_SELECTION_PLAYER_SELECTIONS_KEY].toArray() );

    for(int i=0; i<jPlayerSelections.size(); i++)
        m_playerSelections.append( jPlayerSelections[i].toInt() );
    emit this->playerSelectionsChanged();

    /// team don't need to be deserialized
}

bool GroupSelection::verify(QString &message)
{TRM;
    /// check for each group if it contains enough declared players
    for(int i=0; i<m_groupsCount; i++)
    {
        int foundPlayersInGroup = 0;

        for(int j=0; j<m_playerSelections.size(); j++)
        {
            if(m_playerSelections[j] == i)
                ++ foundPlayersInGroup;
        }

        if(m_minPlayersInGroup <= foundPlayersInGroup && foundPlayersInGroup <= m_maxPlayersInGroup)
            continue;

        QString difference = (m_minPlayersInGroup == m_maxPlayersInGroup) ?
                                 SAPF("%d", m_minPlayersInGroup) :
                                 SAPF("%d or %d", m_minPlayersInGroup, m_maxPlayersInGroup);

        message = SAPF("in group %d, %d players were selected, but %s were expected",
                       i+1, foundPlayersInGroup, difference.toStdString().c_str());

        return false;
    }

    return true;
}

void GroupSelection::setSelectionSize(qsizetype size)
{TRM;
    if(!m_playerSelections.isEmpty() && size > m_playerSelections.size())
    {
        I("resizing selection size");
        m_playerSelections.resize(size, GroupSelection::defaultSelectionValue);
        return;
    }

    if(!m_playerSelections.isEmpty())
    {
        W("trying to shrink selection size!");
        return;
    }

    /// first init
    m_playerSelections.assign(size, GroupSelection::defaultSelectionValue);
}

void GroupSelection::assignExampleData()
{TRM;
    /// uncheck all
    for(int &group : m_playerSelections)
        group = GroupSelection::defaultSelectionValue;

    QRandomGenerator* random = QRandomGenerator::global();

    /// m_groupsCount = 6, m_minPlayersInGroup = 1
    /// m_groupsCount = 3, m_minPlayersInGroup = 2
    /// m_groupsCount = 2, m_minPlayersInGroup = 3
    /// lSize >= 6

    int lSize = m_playerSelections.size();
    int additionalPlayers = lSize - (m_groupsCount*m_minPlayersInGroup);

    /// set required players
    for(int i=0; i<lSize - additionalPlayers; i++)
    {
        int groupIndex = i/m_minPlayersInGroup; // gives 1->{0,1,2,3,4,5} or 2->{0,0,1,1,2,2} or 3->{0,0,0,1,1,1}
        m_playerSelections[i] = groupIndex;
    }

    /// set optional players - not finished
    // int diffPlayersInGroup = m_maxPlayersInGroup - m_minPlayersInGroup;
    // int optionalPlayersToSet = diffPlayersInGroup * m_groupsCount;
    // for(int i=0; i<additionalPlayers; i++)
    // {
    //     int offset = lSize-1;
    //     int groupIndex = i/m_minPlayersInGroup;
    //     m_playerSelections[offset + i] = groupIndex;
    // }

    /// shuffle list
    for (int i = lSize - 1; i > 0; --i) {
        int j = random->bounded(i + 1);                         // Losowy indeks od 0 do i
        qSwap(m_playerSelections[i], m_playerSelections[j]);    // Zamiana elementów
    }

    emit this->playerSelectionsChanged();
}

void GroupSelection::setPlayerGroup(int playerIndex, int groupIndex)
{TRM;
    /// input value protection (always use protection)
    if(playerIndex >= m_playerSelections.size())
    {
        W("trying to access %d playerIndex, while list contains %lld players",
          playerIndex, m_playerSelections.size());
        return;
    }

    if(groupIndex >= m_groupsCount)
    {
        W("trying to assign %d group for %d playerIndex, while groupsCount is %d",
          groupIndex, playerIndex, m_groupsCount );
        return;
    }

    /// Binding loop protection
    if(m_playerSelections[playerIndex] == groupIndex)
        return;

    /// Uncheck (set to defaultSelectionValue) if other values in list if contains this group

    m_playerSelections[playerIndex] = groupIndex;
    emit this->playerSelectionsChanged();
}

int GroupSelection::getGroupsCount() const
{TRM;
    return m_groupsCount;
}

const IntList &GroupSelection::getPlayerSelections() const
{TRM;
    return m_playerSelections;
}

const Team *GroupSelection::getTeamQml() const
{TRM;
    return m_team.data();
}

QStringList GroupSelection::getComboBoxModel() const
{TRM;
    if(m_groupsCount < 0)
    {
        W("cannot create comboBoxModel");
        return QStringList();
    }

    QStringList model(m_groupsCount +1);

    // model[0] = "None";
    model[0] = "---";
    for(int i=1; i<model.size(); i++)
        model[i] = "Group " + QString::number(i-1);

    return model;
}

void GroupSelection::setTeam(TeamPtr team)
{TRM;
    m_team = team.toWeakRef();
    emit this->teamChanged();
}
