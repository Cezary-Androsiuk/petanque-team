#include "MatchTypeBase.h"

#include "support/Log.h"
#include "storages/Personalization.h"

MatchTypeBase::MatchTypeBase(TeamPtr teamL, TeamPtr teamR, int groupsCount, int minPlayersInGroup, int maxPlayersInGroup, QObject *parent)
    : QObject{parent}
    , m_teamLeft{teamL}
    , m_teamRight{teamR}
    , m_groupsCount{groupsCount}
    , m_minPlayersInGroup{minPlayersInGroup}
    , m_maxPlayersInGroup{maxPlayersInGroup}
    , m_selectionInitialized{false}
    , m_matchInitialized{false}
{TRM; DOLTV(SAPF("%p, %p, %d, %d, %d, %p", teamL.data(), teamR.data(), groupsCount, minPlayersInGroup, maxPlayersInGroup, parent));

}

MatchTypeBase::~MatchTypeBase()
{TRM; DOLT;

}

void MatchTypeBase::onSelectionStart()
{TRM;
    DA(Log::Action::SaveSession, "before matchTypeBase selection start: %p", this);

    this->initSelection();

    if(m_groupSelectionLeft.isNull())
    {
        W("groupSelectionLeft is null");
        return;
    }

    if(m_groupSelectionRight.isNull())
    {
        W("groupSelectionRight is null");
        return;
    }

    m_groupSelectionLeft->onStart();
    m_groupSelectionRight->onStart();
}

void MatchTypeBase::onSelectionEnd()
{TRM;
    DA(Log::Action::SaveSession, "after matchTypeBase selection end: %p", this);

    if(m_groupSelectionLeft.isNull())
    {
        W("groupSelectionLeft is null");
        return;
    }

    if(m_groupSelectionRight.isNull())
    {
        W("groupSelectionRight is null");
        return;
    }

    m_groupSelectionLeft->onEnd();
    m_groupSelectionRight->onEnd();
}

void MatchTypeBase::onMatchStart()
{TRM;
    DA(Log::Action::SaveSession, "before matchTypeBase match start: %p", this);

    this->initMatch();

    if(m_groupMatchLeft.isNull())
    {
        W("groupMatchLeft is null");
        return;
    }

    if(m_groupMatchRight.isNull())
    {
        W("groupMatchRight is null");
        return;
    }

    m_groupMatchLeft->onStart();
    m_groupMatchRight->onStart();
}

void MatchTypeBase::onMatchEnd()
{TRM;
    DA(Log::Action::SaveSession, "after matchTypeBase match end: %p", this);

    if(m_groupMatchLeft.isNull())
    {
        W("groupMatchLeft is null");
        return;
    }

    if(m_groupMatchRight.isNull())
    {
        W("groupMatchRight is null");
        return;
    }

    m_groupMatchLeft->onEnd();
    m_groupMatchRight->onEnd();

    this->addPoints();
}

void MatchTypeBase::initSelection()
{TRM;
    DA(Log::Action::SaveSession, "init selection: %p", this);

    if(m_selectionInitialized)
    {
        IA(Log::Action::SaveSession, "prevented double initialization");
        return;
    }

    m_groupSelectionLeft = GroupSelectionPtr::create(
        m_groupsCount, m_minPlayersInGroup, m_maxPlayersInGroup);
    if(m_groupSelectionLeft.isNull())
    {
        E("can't init left selection, due to not exising left selection pointer");
    }
    else
    {
        auto playersSize = m_teamLeft->getPlayers().size();
        m_groupSelectionLeft->setSelectionSize(playersSize);
        m_groupSelectionLeft->setTeam(m_teamLeft);
    }


    m_groupSelectionRight = GroupSelectionPtr::create(
        m_groupsCount, m_minPlayersInGroup, m_maxPlayersInGroup);
    if(m_groupSelectionRight.isNull())
    {
        E("can't init right selection, due to not exising right selection pointer");
    }
    else
    {
        auto playersSize = m_teamRight->getPlayers().size();
        m_groupSelectionRight->setSelectionSize(playersSize);
        m_groupSelectionRight->setTeam(m_teamRight);
    }

    m_selectionInitialized = true;

    emit this->selectionChanged();
}

void MatchTypeBase::initMatch()
{TRM;
    DA(Log::Action::SaveSession, "init match: %p", this);

    if(m_matchInitialized)
    {
        IA(Log::Action::SaveSession, "prevented double initialization");
        return;
    }

    m_groupMatchLeft = GroupMatchPtr::create();
    if(m_groupSelectionLeft.isNull())
    {
        E("can't init left match, due to not exising left selection pointer");
    }
    else if(m_groupMatchLeft.isNull())
    {
        E("can't init left match, due to not exising left match pointer");
    }
    else
    {
        auto gop = this->makeGroupsOfPlayersList(m_teamLeft->getPlayers(), m_groupSelectionLeft->getPlayerSelections());
        m_groupMatchLeft->setGroupsCount(m_groupsCount);
        m_groupMatchLeft->setMatchPointsSize(m_groupsCount);
        m_groupMatchLeft->setDefaultPlayersCountInGroup(m_minPlayersInGroup);
        m_groupMatchLeft->setGroupsOfPlayers(gop);
        m_groupMatchLeft->setTeam(m_teamLeft);
    }


    m_groupMatchRight = GroupMatchPtr::create();
    if(m_groupSelectionRight.isNull())
    {
        E("can't init right match, due to not exising right selection pointer");
    }
    else if(m_groupMatchRight.isNull())
    {
        E("can't init right match, due to not exising right match pointer");
    }
    else
    {
        auto gop = this->makeGroupsOfPlayersList(m_teamRight->getPlayers(), m_groupSelectionRight->getPlayerSelections());
        m_groupMatchRight->setGroupsCount(m_groupsCount);
        m_groupMatchRight->setMatchPointsSize(m_groupsCount);
        m_groupMatchRight->setDefaultPlayersCountInGroup(m_minPlayersInGroup);
        m_groupMatchRight->setGroupsOfPlayers(gop);
        m_groupMatchRight->setTeam(m_teamRight);
    }

    m_matchInitialized = true;

    emit this->matchChanged();
}

void MatchTypeBase::addPoints()
{TRM;
    DA(Log::Action::SaveSession, "adding points after match");

    this->addPointsForTeams();

    this->addPointsForPlayers();
}

void MatchTypeBase::addPointsForTeams()
{TRM;
    int size;
    IntList leftPoints = m_groupMatchLeft->getMatchPoints();
    IntList rightPoints = m_groupMatchRight->getMatchPoints();
    size = leftPoints.size();

    if(size != rightPoints.size())
    {
        W("left and right matches has different sizes of points lists");
        return;
    }

    if(m_teamLeft.isNull() || m_teamRight.isNull())
    {
        W("one of the teams is null");
        return;
    }

    for(int i=0; i<size; i++)
    {
        if(leftPoints[i] > rightPoints[i])
        {
            // add large point to team left team
            m_teamLeft->addLargePoints(1);
        }
        else
        {
            // add large point to team left team
            m_teamRight->addLargePoints(1);
        }

        // add small points;
        m_teamLeft->addSmallPoints( leftPoints[i] );
        m_teamRight->addSmallPoints( rightPoints[i] );
    }
}

void MatchTypeBase::addPointsForPlayers()
{TRM;
    int size;
    QList<PlayerPtrList> leftGroupsOfPlayers = m_groupMatchLeft->getGroupsOfPlayers();
    IntList leftPoints = m_groupMatchLeft->getMatchPoints();
    size = leftPoints.size();
    if(size != leftGroupsOfPlayers.size())
    {
        W("in left match groups of players and points have different sizes");
        return;
    }

    QList<PlayerPtrList> rightGroupsOfPlayers = m_groupMatchRight->getGroupsOfPlayers();
    IntList rightPoints = m_groupMatchRight->getMatchPoints();
    if(rightPoints.size() != rightGroupsOfPlayers.size())
    {
        W("in right match groups of players and points have different sizes");
        return;
    }

    if(size != rightPoints.size())
    {
        W("left and right matches has different sizes of points lists");
        return;
    }

    for(int i=0; i<size; i++)
    {
        int lp = leftPoints[i];
        int rp = rightPoints[i];

        /// following for loops can't be marged into one, because there can be different
        /// counts of players in each group

        /// add points for left match players
        for(auto &leftPlayer : leftGroupsOfPlayers[i])
        {
            if(lp > rp)
            {
                // add large point to player of left team
                leftPlayer->addLargePoints(1);
            }

            leftPlayer->addSmallPoints(lp);
        }

        /// add points for right match players
        for(auto &rightPlayer : rightGroupsOfPlayers[i])
        {
            if(lp < rp)
            {
                // add large point to player of right team
                rightPlayer->addLargePoints(1);
            }

            rightPlayer->addSmallPoints(rp);
        }
    }
}

QJsonObject MatchTypeBase::serialize() const
{TRM;
    QJsonObject jMatchTypeBase;

    jMatchTypeBase[SERL_MATCH_TYPE_TEAM_LEFT_NAME_KEY] = this->serializeTeam(m_teamLeft);
    jMatchTypeBase[SERL_MATCH_TYPE_TEAM_RIGHT_NAME_KEY] = this->serializeTeam(m_teamRight);
    jMatchTypeBase[SERL_GROUPS_COUNT_KEY] = m_groupsCount;
    jMatchTypeBase[SERL_MIN_PLAYERS_IN_GROUP_KEY] = m_minPlayersInGroup;
    jMatchTypeBase[SERL_MAX_PLAYERS_IN_GROUP_KEY] = m_maxPlayersInGroup;

    if(m_groupSelectionLeft.isNull() != m_groupSelectionRight.isNull())
    {
        /// one selection is null but other don't
        W("one of the group selections are not exit, both won't be serialized");
    }
    else if(m_groupSelectionLeft.isNull())
    {
        /// both selection are null
        // I("group selection not created, then not be serialized");
    }
    else
    {
        /// both selection are pointers
        jMatchTypeBase[SERL_GROUP_SELECTION_LEFT_KEY] =
            this->m_groupSelectionLeft->serialize();
        jMatchTypeBase[SERL_GROUP_SELECTION_RIGHT_KEY] =
            this->m_groupSelectionRight->serialize();
    }

    if(m_groupMatchLeft.isNull() != m_groupMatchRight.isNull())
    {
        /// one selection is null but other don't
        W("one of the group match are not exit, both won't be serialized");
    }
    else if(m_groupMatchLeft.isNull())
    {
        /// both selection are null
        // I("group match not created, then not be serialized");
    }
    else
    {
        // I("======================================================================");
        /// both selection are pointers
        jMatchTypeBase[SERL_GROUP_MATCH_LEFT_KEY] =
            this->m_groupMatchLeft->serialize();
        jMatchTypeBase[SERL_GROUP_MATCH_RIGHT_KEY] =
            this->m_groupMatchRight->serialize();
    }

    return jMatchTypeBase;
}

void MatchTypeBase::deserialize(const QJsonObject &jMatchTypeBase)
{TRM;
    this->clear(false);

    /// team left don't need to be deserialized
    /// team right don't need to be deserialized
    /// groupsCount don't need to be deserialized
    /// minPlayersInGroup don't need to be deserialized
    /// maxPlayersInGroup don't need to be deserialized

    bool csl, csr, cml, cmr; // contains [selection/match] [left/right]
    csl = jMatchTypeBase.contains(SERL_GROUP_SELECTION_LEFT_KEY);
    csr = jMatchTypeBase.contains(SERL_GROUP_SELECTION_RIGHT_KEY);
    cml = jMatchTypeBase.contains(SERL_GROUP_MATCH_LEFT_KEY);
    cmr = jMatchTypeBase.contains(SERL_GROUP_MATCH_RIGHT_KEY);

    if(csl != csr)
    {
        /// one selection is null but other don't
        W("one of the group selections are not exit in json, both won't be deserialized");
    }
    else if(!csl)
    {
        /// both selection are null
        // I("group selection not created, then not be deserialized", Log::Action::Save);
    }
    else
    {
        this->initSelection();
        m_groupSelectionLeft->deserialize(
            jMatchTypeBase[SERL_GROUP_SELECTION_LEFT_KEY].toObject());
        m_groupSelectionRight->deserialize(
            jMatchTypeBase[SERL_GROUP_SELECTION_RIGHT_KEY].toObject());
    }

    if(cml != cmr)
    {
        /// one selection is null but other don't
        W("one of the group match are not exit in json, both won't be deserialized");
    }
    else if(!cml)
    {
        /// both selection are null
        // IA(Log::Action::Save, "group match not created, then not be deserialized");
        // I("group match not created, then not be deserialized");
    }
    else
    {
        this->initMatch();
        m_groupMatchLeft->deserialize(
            jMatchTypeBase[SERL_GROUP_MATCH_LEFT_KEY].toObject());
        m_groupMatchRight->deserialize(
            jMatchTypeBase[SERL_GROUP_MATCH_RIGHT_KEY].toObject());
    }
}

void MatchTypeBase::clear(bool emitting)
{TRM;

}

QString MatchTypeBase::serializeTeam(cTeamWPtr wteam) const
{TRM;
    if(wteam.isNull())
    {
        W("team is null");
        return "";
    }
    return wteam.toStrongRef()->getName();
}

bool MatchTypeBase::verifySelection(QString &message)
{TRM;
    if(m_groupSelectionLeft.isNull())
    {
        E("cannot verify, due to not exising left selection pointer");
        return false;
    }

    if(m_groupSelectionRight.isNull())
    {
        E("cannot verify, due to not exising right selection pointer");
        return false;
    }

    if(!m_groupSelectionLeft->verify(message))
    {
        message = "w lewym: " + message;
        return false;
    }

    if(!m_groupSelectionRight->verify(message))
    {
        message = "w prawym: " + message;
        return false;
    }

    return true;
}

bool MatchTypeBase::verifyMatch(QString &message)
{TRM;
    if(m_groupMatchLeft.isNull())
    {
        E("cannot verify, due to not exising left match pointer");
        return false;
    }

    if(m_groupMatchRight.isNull())
    {
        E("cannot verify, due to not exising right match pointer");
        return false;
    }

    const IntList &leftMatchesPoints = m_groupMatchLeft->getMatchPoints();
    const IntList &rightMatchesPoints = m_groupMatchRight->getMatchPoints();

    if(leftMatchesPoints.size() != rightMatchesPoints.size())
    {
        W("matchPoints have different sizes: left(%lld) right(%lld)",
          leftMatchesPoints.size(), rightMatchesPoints.size());
        return false;
    }

    int maxPointsInMatch = Personalization::getInstance()->getMaxPointsInMatch();
    for(int i=0; i<leftMatchesPoints.size(); i++)
    {
        int lValue = leftMatchesPoints[i];
        int rValue = rightMatchesPoints[i];

        if(lValue > maxPointsInMatch)
        {
            message = SAPF("w grupie %d, punkty po lewej wynoszą %d, ale nie mogą być większe niż %d",
                           i+1, lValue, maxPointsInMatch);
            return false;
        }

        if(rValue > maxPointsInMatch)
        {
            message = SAPF("w grupie %d, punkty po prawej wynoszą %d, ale nie mogą być większe niż %d",
                           i+1, rValue, maxPointsInMatch);
            return false;
        }

        if(lValue == rValue)
        {
            message = SAPF("w grupie %d, punkty po lewej i prawej są takie same (wynoszą: %d), ale nie powinny być",
                           i+1, lValue);
            return false;
        }
    }

    return true;
}

QList<PlayerPtrList> MatchTypeBase::makeGroupsOfPlayersList(const PlayerPtrList &players, const IntList &selection) const
{TRM;
    QList<PlayerPtrList> groupsOfPlayers(m_groupsCount);

    if(players.size() != selection.size())
    {
        E("players count received from team agument is different than set selections size");
        return groupsOfPlayers;
    }

    for(int i=0; i<selection.size(); i++)
    {
        int playerGroupID = selection[i]; /// safe []
        if(playerGroupID < 0)
            continue;
        else if(playerGroupID >= m_groupsCount || playerGroupID >= groupsOfPlayers.size())
        {
            QString selectionsStr;
            for(int playerGroupIndex : selection)
                selectionsStr.append( SAPF("%d ", playerGroupIndex) );
            W("player selection contains to hight groupID value: [ " + selectionsStr + "]");
            continue;
        }

        auto player = players[i]; /// safe []
        groupsOfPlayers[playerGroupID].append(player); /// safe []
    }

    return groupsOfPlayers;
}

void MatchTypeBase::assignSelectionExampleData()
{TRM;
    m_groupSelectionLeft->assignExampleData();
    m_groupSelectionRight->assignExampleData();
}

void MatchTypeBase::assignMatchExampleData()
{TRM;
    if(m_groupMatchLeft.isNull())
    {
        E("cannot assign example data, due to not exising left match pointer");
        return;
    }

    if(m_groupMatchRight.isNull())
    {
        E("cannot assign example data, due to not exising right match pointer");
        return;
    }

    qsizetype leftMatchPointsSize = m_groupMatchLeft->getMatchPoints().size();
    IntList leftMatchPoints( leftMatchPointsSize );

    qsizetype rightMatchPointsSize = m_groupMatchRight->getMatchPoints().size();
    IntList rightMatchPoints( rightMatchPointsSize );

    if(leftMatchPointsSize != rightMatchPointsSize)
    {
        W("cannot assign example data, matchPoints have different sizes: "
          "left(%lld) right(%lld)", leftMatchPointsSize, rightMatchPointsSize);
        return;
    }

    /// CONDITIONS
    /// left and right sum, need to be smaller or equal to <<maxPointsInMatch>>
    /// left cannot equal to right

    int maxPointsInMatch = m_groupMatchLeft->getMaxPointsInMatch();
    for(int i=0; i<leftMatchPointsSize; i++)
    {
        MatchTypeBase::generateTwoRandomValues(
            leftMatchPoints[i], rightMatchPoints[i], maxPointsInMatch);
    }

    m_groupMatchLeft->assignExampleData(leftMatchPoints);
    m_groupMatchRight->assignExampleData(rightMatchPoints);
}

void MatchTypeBase::generateTwoRandomValues(int &v1, int &v2, int max)
{TRF;
    auto rnd = QRandomGenerator::global();
    int mod = max + 1;
    int randomPoint1 = rnd->bounded(0, mod); // r1 = [0, 13]
    int randomPoint2 = rnd->bounded(0, mod); // r2 = [0, 13]

    if(randomPoint1 == randomPoint2)
    {
        randomPoint1 += (randomPoint1 == 0) ? 1 : (randomPoint1-1);
    }

    if(randomPoint1 < 0 || randomPoint1 > max || randomPoint2 < 0 || randomPoint2 > max)
    {
        IA(Log::Action::Save,
           "%d, %d not belong to  [0, %d], "
           "generated values are not match required range",
           randomPoint1, randomPoint2, max);

        /// if that happend assign my own random data xd
        randomPoint1 = 6;
        randomPoint2 = 3;
    }

    v1 = randomPoint1;
    v2 = randomPoint2;
}

Team *MatchTypeBase::getTeamLeftQml() const
{TRM;
    return m_teamLeft.data();
}

Team *MatchTypeBase::getTeamRightQml() const
{TRM;
    return m_teamRight.data();
}

GroupSelection *MatchTypeBase::getSelectionLeft() const
{TRM;
    return m_groupSelectionLeft.data();
}

GroupSelection *MatchTypeBase::getSelectionRight() const
{TRM;
    return m_groupSelectionRight.data();
}

GroupMatch *MatchTypeBase::getMatchLeft() const
{TRM;
    return m_groupMatchLeft.data();
}

GroupMatch *MatchTypeBase::getMatchRight() const
{TRM;
    return m_groupMatchRight.data();
}
