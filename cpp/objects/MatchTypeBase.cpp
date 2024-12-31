#include "MatchTypeBase.h"

MatchTypeBase::MatchTypeBase(cTeamWPtr teamL, cTeamWPtr teamR, int groupsCount, int minPlayersInGroup, int maxPlayersInGroup, QObject *parent)
    : QObject{parent}
    , m_teamLeft{teamL}
    , m_teamRight{teamR}
    , m_groupsCount{groupsCount}
    , m_minPlayersInGroup{minPlayersInGroup}
    , m_maxPlayersInGroup{maxPlayersInGroup}
{
    DOLT(this)

}

MatchTypeBase::~MatchTypeBase()
{
    DOLT(this)

}

void MatchTypeBase::initSelection()
{
    m_groupSelectionLeft = GroupSelectionPtr::create(
        m_groupsCount, m_minPlayersInGroup, m_maxPlayersInGroup);
    if(m_teamLeft.isNull())
    {
        E("can't init left selection, due to not exising m_teamLeft pointer")
    }
    else if(m_groupSelectionLeft.isNull())
    {
        E("can't init left selection, due to not exising left selection pointer")
    }
    else
    {
        auto playersSize = m_teamLeft.toStrongRef()->getPlayers().size();
        m_groupSelectionLeft->setSelectionSize(playersSize);
        m_groupSelectionLeft->setTeam(m_teamLeft.toStrongRef());
    }


    m_groupSelectionRight = GroupSelectionPtr::create(
        m_groupsCount, m_minPlayersInGroup, m_maxPlayersInGroup);
    if(m_teamRight.isNull())
    {
        E("can't init right selection, due to not exising m_teamRight pointer")
    }
    else if(m_groupSelectionRight.isNull())
    {
        E("can't init right selection, due to not exising right selection pointer")
    }
    else
    {
        auto playersSize = m_teamRight.toStrongRef()->getPlayers().size();
        m_groupSelectionRight->setSelectionSize(playersSize);
        m_groupSelectionRight->setTeam(m_teamRight.toStrongRef());
    }

    emit this->selectionChanged();
}

void MatchTypeBase::initMatch()
{
    m_groupMatchLeft = GroupMatchPtr::create();
    if(m_teamLeft.isNull())
    {
        E("can't init left match, due to not exising m_teamLeft pointer")
    }
    else if(m_groupMatchLeft.isNull())
    {
        E("can't init left match, due to not exising left match pointer")
    }
    else
    {
        auto gop = this->makeGroupsOfPlayersList(m_teamLeft, m_groupSelectionLeft);
        m_groupMatchLeft->setGroupsCount(m_groupsCount);
        m_groupMatchLeft->setMatchPointsSize(m_groupsCount);
        m_groupMatchLeft->setDefaultPlayersCountInGroup(m_minPlayersInGroup);
        m_groupMatchLeft->setGroupsOfPlayers(gop);
        m_groupMatchLeft->setTeam(m_teamLeft.toStrongRef());
    }


    m_groupMatchRight = GroupMatchPtr::create();
    if(m_teamRight.isNull())
    {
        E("can't init right match, due to not exising m_teamRight pointer")
    }
    else if(m_groupMatchRight.isNull())
    {
        E("can't init right match, due to not exising right match pointer")
    }
    else
    {
        auto gop = this->makeGroupsOfPlayersList(m_teamRight, m_groupSelectionRight);
        m_groupMatchRight->setGroupsCount(m_groupsCount);
        m_groupMatchRight->setMatchPointsSize(m_groupsCount);
        m_groupMatchRight->setDefaultPlayersCountInGroup(m_minPlayersInGroup);
        m_groupMatchRight->setGroupsOfPlayers(gop);
        m_groupMatchRight->setTeam(m_teamRight.toStrongRef());
    }

    emit this->matchChanged();
}

QJsonObject MatchTypeBase::serialize() const
{
    QJsonObject jMatchTypeBase;

    jMatchTypeBase[SERL_MATCH_TYPE_TEAM_LEFT_NAME_KEY] = this->serializeTeam(m_teamLeft);
    jMatchTypeBase[SERL_MATCH_TYPE_TEAM_RIGHT_NAME_KEY] = this->serializeTeam(m_teamRight);
    jMatchTypeBase[SERL_GROUPS_COUNT_KEY] = m_groupsCount;
    jMatchTypeBase[SERL_MIN_PLAYERS_IN_GROUP_KEY] = m_minPlayersInGroup;
    jMatchTypeBase[SERL_MAX_PLAYERS_IN_GROUP_KEY] = m_maxPlayersInGroup;

    if(m_groupSelectionLeft.isNull() != m_groupSelectionRight.isNull())
    {
        /// one selection is null but other don't
        W("one of the group selections are not exit, both won't be serialized")
    }
    else if(m_groupSelectionLeft.isNull())
    {
        /// both selection are null
        // I("group selection not created, then not be serialized")
    }
    else
    {
        /// both selection are pointers
        jMatchTypeBase[SERL_GROUP_SELECTION_LEFT_KEY] = this->m_groupSelectionLeft->serialize();
        jMatchTypeBase[SERL_GROUP_SELECTION_RIGHT_KEY] = this->m_groupSelectionRight->serialize();
    }

    if(m_groupMatchLeft.isNull() != m_groupMatchRight.isNull())
    {
        /// one selection is null but other don't
        W("one of the group match are not exit, both won't be serialized")
    }
    else if(m_groupMatchLeft.isNull())
    {
        /// both selection are null
        // I("group match not created, then not be serialized")
    }
    else
    {
        /// both selection are pointers
        jMatchTypeBase[SERL_GROUP_MATCH_LEFT_KEY] = this->m_groupMatchLeft->serialize();
        jMatchTypeBase[SERL_GROUP_MATCH_RIGHT_KEY] = this->m_groupMatchRight->serialize();
    }

    return jMatchTypeBase;
}

void MatchTypeBase::deserialize(const QJsonObject &jMatchTypeBase)
{
    I("Deserialize")
    qDebug() << this;
    this->clear(false);

    /// team left don't need to be deserialized
    /// team right don't need to be deserialized
    /// groupsCount don't need to be deserialized
    /// minPlayersInGroup don't need to be deserialized
    /// maxPlayersInGroup don't need to be deserialized

    QJsonObject obj;
    bool csl, csr, cml, cmr; // contains [selection/match] [left/right]
    csl = jMatchTypeBase.contains(SERL_GROUP_SELECTION_LEFT_KEY);
    csr = jMatchTypeBase.contains(SERL_GROUP_SELECTION_RIGHT_KEY);
    cml = jMatchTypeBase.contains(SERL_GROUP_MATCH_LEFT_KEY);
    cmr = jMatchTypeBase.contains(SERL_GROUP_MATCH_RIGHT_KEY);

    if(csl != csr)
    {
        /// one selection is null but other don't
        W("one of the group selections are not exit in json, both won't be deserialized")
    }
    else if(csl)
    {
        /// both selection are null
        // I("group selection not created, then not be deserialized")

    }
    else
    {
        this->initSelection();
        obj = jMatchTypeBase[SERL_GROUP_SELECTION_LEFT_KEY].toObject();
        m_groupSelectionLeft->deserialize( obj );
        obj = jMatchTypeBase[SERL_GROUP_SELECTION_RIGHT_KEY].toObject();
        m_groupSelectionRight->deserialize( obj );
    }

    if(cml != cmr)
    {
        /// one selection is null but other don't
        W("one of the group match are not exit in json, both won't be deserialized")
    }
    else if(cml)
    {
        /// both selection are null
        // I("group match not created, then not be deserialized")
    }
    else
    {
        this->initMatch();
        obj = jMatchTypeBase[SERL_GROUP_MATCH_LEFT_KEY].toObject();
        m_groupMatchLeft->deserialize( obj );
        obj = jMatchTypeBase[SERL_GROUP_MATCH_RIGHT_KEY].toObject();
        m_groupMatchRight->deserialize( obj );
    }
}

void MatchTypeBase::clear(bool emitting)
{

}

QString MatchTypeBase::serializeTeam(cTeamWPtr wteam) const
{
    if(wteam.isNull())
    {
        W("team is null")
        return "";
    }
    return wteam.toStrongRef()->getName();
}

bool MatchTypeBase::verifySelection(QString &message)
{
    if(m_groupSelectionLeft.isNull())
    {
        E("cannot verify, due to not exising left selection pointer")
        return false;
    }

    if(m_groupSelectionRight.isNull())
    {
        E("cannot verify, due to not exising right selection pointer")
        return false;
    }

    if(!m_groupSelectionLeft->verify(message))
    {
        message = "" + message;
        return false;
    }

    if(!m_groupSelectionRight->verify(message))
    {
        message = "" + message;
        return false;
    }

    return true;
}

bool MatchTypeBase::verifyMatch(QString &message)
{
    if(m_groupMatchLeft.isNull())
    {
        E("cannot verify, due to not exising left match pointer")
        return false;
    }

    if(m_groupMatchRight.isNull())
    {
        E("cannot verify, due to not exising right match pointer")
        return false;
    }

    if(!m_groupMatchLeft->verify(message))
    {
        message = "" + message;
        return false;
    }

    if(!m_groupMatchRight->verify(message))
    {
        message = "" + message;
        return false;
    }

    return true;
}

QList<PlayerPtrList> MatchTypeBase::makeGroupsOfPlayersList(cTeamWPtr wteam, const GroupSelectionPtr &gs) const
{
    QList<PlayerPtrList> groupsOfPlayers(m_groupsCount);

    if(wteam.isNull())
    {
        W("wteam is null")
        return QList<PlayerPtrList>();
    }

    if(gs.isNull())
    {
        W("groupSelection is null")
        qDebug() << this;
        return QList<PlayerPtrList>();
    }

    const TeamPtr team = wteam.toStrongRef();
    const QList<int> &selection = gs->getPlayerSelections();

    if(team->getPlayers().size() != selection.size())
    {
        E("players count received from team agument is different than set selections size")
        return groupsOfPlayers;
    }

    for(int i=0; i<selection.size(); i++)
    {
        int playerGroupID = selection[i];
        if(playerGroupID < 0)
        {
            W("player selection contains negative groupID value:");
            for(const auto &pgi : selection)
                qDebug() << pgi;
            exit(1);
            continue;
        }
        else if(playerGroupID >= m_groupsCount)
        {
            W("player selection contains to hight groupID value:");
            for(const auto &pgi : selection)
                qDebug() << pgi;
            continue;
        }

        auto player = team->getPlayers()[i];
        groupsOfPlayers[playerGroupID].append(player);
    }

    return groupsOfPlayers;
}

void MatchTypeBase::assignSelectionExampleData()
{
    m_groupSelectionLeft->assignExampleData();
    m_groupSelectionRight->assignExampleData();
}

void MatchTypeBase::assignMatchExampleData()
{
    m_groupMatchLeft->assignExampleData();
    m_groupMatchRight->assignExampleData();
}

Team *MatchTypeBase::getTeamLeftQml() const
{
    if(m_teamLeft.isNull())
    {
        W("Team left is null, but it shouldn't be")
        return nullptr;
    }
    return m_teamLeft.toStrongRef().data();
}

Team *MatchTypeBase::getTeamRightQml() const
{
    if(m_teamRight.isNull())
    {
        W("Team right is null, but it shouldn't be")
        return nullptr;
    }
    return m_teamRight.toStrongRef().data();
}

GroupSelection *MatchTypeBase::getSelectionLeft() const
{
    return m_groupSelectionLeft.data();
}

GroupSelection *MatchTypeBase::getSelectionRight() const
{
    return m_groupSelectionRight.data();
}

GroupMatch *MatchTypeBase::getMatchLeft() const
{
    return m_groupMatchLeft.data();
}

GroupMatch *MatchTypeBase::getMatchRight() const
{
    return m_groupMatchRight.data();
}
