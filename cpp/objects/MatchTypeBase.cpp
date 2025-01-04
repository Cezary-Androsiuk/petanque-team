#include "MatchTypeBase.h"

MatchTypeBase::MatchTypeBase(TeamPtr teamL, TeamPtr teamR, int groupsCount, int minPlayersInGroup, int maxPlayersInGroup, QObject *parent)
    : QObject{parent}
    , m_teamLeft{teamL}
    , m_teamRight{teamR}
    , m_groupsCount{groupsCount}
    , m_minPlayersInGroup{minPlayersInGroup}
    , m_maxPlayersInGroup{maxPlayersInGroup}
    , m_selectionInitialized{false}
    , m_matchInitialized{false}
{
    DOLT(this)

}

MatchTypeBase::~MatchTypeBase()
{
    DOLT(this)

}

void MatchTypeBase::onStart()
{
    D(QAPF("before matchTypeBase start: %p", this), Log::Action::SaveSession)

    if(m_groupSelectionLeft.isNull())
    {
        W("groupSelectionLeft is null")
        return;
    }

    if(m_groupSelectionRight.isNull())
    {
        W("groupSelectionRight is null")
        return;
    }

    if(m_groupMatchLeft.isNull())
    {
        W("groupMatchLeft is null")
        return;
    }

    if(m_groupMatchRight.isNull())
    {
        W("groupMatchRight is null")
        return;
    }

    m_groupMatchLeft->onStart();
    m_groupMatchRight->onStart();

    m_groupSelectionLeft->onStart();
    m_groupSelectionRight->onStart();
}

void MatchTypeBase::onEnd()
{
    D(QAPF("after matchTypeBase end: %p", this), Log::Action::SaveSession)

    if(m_groupSelectionLeft.isNull())
    {
        W("groupSelectionLeft is null")
        return;
    }

    if(m_groupSelectionRight.isNull())
    {
        W("groupSelectionRight is null")
        return;
    }

    if(m_groupMatchLeft.isNull())
    {
        W("groupMatchLeft is null")
        return;
    }

    if(m_groupMatchRight.isNull())
    {
        W("groupMatchRight is null")
        return;
    }

    m_groupMatchLeft->onStart();
    m_groupMatchRight->onStart();

    m_groupSelectionLeft->onStart();
    m_groupSelectionRight->onStart();
}

void MatchTypeBase::initSelection()
{
    if(m_selectionInitialized)
    {
        I("prevented double initialization", Log::Action::SaveSession)
        return;
    }

    m_groupSelectionLeft = GroupSelectionPtr::create(
        m_groupsCount, m_minPlayersInGroup, m_maxPlayersInGroup);
    if(m_groupSelectionLeft.isNull())
    {
        E("can't init left selection, due to not exising left selection pointer")
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
        E("can't init right selection, due to not exising right selection pointer")
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
{
    if(m_matchInitialized)
    {
        I("prevented double initialization")
        return;
    }

    m_groupMatchLeft = GroupMatchPtr::create();
    if(m_groupSelectionLeft.isNull())
    {
        E("can't init left match, due to not exising left selection pointer")
    }
    else if(m_groupMatchLeft.isNull())
    {
        E("can't init left match, due to not exising left match pointer")
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
        E("can't init right match, due to not exising right selection pointer")
    }
    else if(m_groupMatchRight.isNull())
    {
        E("can't init right match, due to not exising right match pointer")
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
    else if(!csl)
    {
        /// both selection are null
        I("group selection not created, then not be deserialized", Log::Action::Save);
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
    else if(!cml)
    {
        /// both selection are null
        I("group match not created, then not be deserialized", Log::Action::Save);
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
        message = "in left: " + message;
        return false;
    }

    if(!m_groupSelectionRight->verify(message))
    {
        message = "in right: " + message;
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

    const IntList &leftMatchPoints = m_groupMatchLeft->getMatchPoints();
    const IntList &rightMatchPoints = m_groupMatchRight->getMatchPoints();

    if(leftMatchPoints.size() != rightMatchPoints.size())
    {
        W(QAPF("matchPoints have different sizes: left(%lld) right(%lld)",
               leftMatchPoints.size(), rightMatchPoints.size()));
        return false;
    }

    int maxPointsInMatch = Personalization::getInstance()->getMaxPointsInMatch();
    for(int i=0; i<leftMatchPoints.size(); i++)
    {
        int lValue = leftMatchPoints[i];
        int rValue = rightMatchPoints[i];

        if(lValue + rValue > maxPointsInMatch)
        {
            message = QAPF("in group %d, the sum of left and right points is %d, but cannot be larger than %d",
                           i+1, lValue+rValue, maxPointsInMatch);
            return false;
        }

        if(lValue == rValue)
        {
            message = QAPF("in group %d, the left and right points are equal (value: %d), but they should not be",
                           i+1, lValue);
            return false;
        }
    }

    return true;
}

QList<PlayerPtrList> MatchTypeBase::makeGroupsOfPlayersList(const PlayerPtrList &players, const IntList &selection) const
{
    QList<PlayerPtrList> groupsOfPlayers(m_groupsCount);

    if(players.size() != selection.size())
    {
        E("players count received from team agument is different than set selections size")
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
                selectionsStr.append( QAPF("%d ", playerGroupIndex) );
            W("player selection contains to hight groupID value: [ " + selectionsStr + "]");
            continue;
        }

        auto player = players[i]; /// safe []
        groupsOfPlayers[playerGroupID].append(player); /// safe []
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
    if(m_groupMatchLeft.isNull())
    {
        E("cannot assign example data, due to not exising left match pointer")
        return;
    }

    if(m_groupMatchRight.isNull())
    {
        E("cannot assign example data, due to not exising right match pointer")
        return;
    }

    qsizetype leftMatchPointsSize = m_groupMatchLeft->getMatchPoints().size();
    IntList leftMatchPoints( leftMatchPointsSize );

    qsizetype rightMatchPointsSize = m_groupMatchRight->getMatchPoints().size();
    IntList rightMatchPoints( rightMatchPointsSize );

    if(leftMatchPointsSize != rightMatchPointsSize)
    {
        W(QAPF("cannot assign example data, matchPoints have different sizes: "
               "left(%lld) right(%lld)", leftMatchPointsSize, rightMatchPointsSize));
        return;
    }

    /// CONDITIONS
    /// left and right sum, need to be smaller or equal to <<maxPointsInMatch>>
    /// left cannot equal to right

    int maxPointsInMatch = m_groupMatchLeft->getMaxPointsInMatch();
    for(int i=0; i<leftMatchPointsSize; i++)
    {
        MatchTypeBase::generateTwoRandomValues3(
            leftMatchPoints[i], rightMatchPoints[i], maxPointsInMatch);
    }

    m_groupMatchLeft->assignExampleData(leftMatchPoints);
    m_groupMatchRight->assignExampleData(rightMatchPoints);
}

void MatchTypeBase::generateTwoRandomValues1(int &v1, int &v2, int max)
{
    /// Algorithm is not that good and surprisingly not always gives valid result
    auto rnd = QRandomGenerator::global();
    int mod1 = max + 1;
    int randomPoints1 = rnd->bounded(0, mod1); // r1 = [0, 13]
    int mod2 = max - randomPoints1 +1;
    int randomPoints2 = rnd->bounded(0, mod2); // r2 = [0, 13-r1]

    if(randomPoints1 == randomPoints2)
    {
        randomPoints1 += (randomPoints1 == 0) ? 1 : (randomPoints1-1);
    }

    if((randomPoints1 + randomPoints2) > max)
    {
        I(QAPF("%d + %d > %d, generated values sum is larger than max points",
               randomPoints1, randomPoints2, max), Log::Action::Save);
        /// I CANNOT FIND OUT WHY SOMETIMES THEY DON'T ADD UP
        /// for example 13 - 9 + 1 gives 9 or something

        /// if that happend assign my own random data xd
        randomPoints1 = 6;
        randomPoints2 = 3;
    }

    if(rnd->generate()%2)
    {
        v1 = randomPoints1;
        v2 = randomPoints2;
    }
    else
    {
        v2 = randomPoints1;
        v1 = randomPoints2;
    }

    /// secure
    if(v1 < 0) v1 *= -1;
    if(v2 < 0) v2 *= -1;
}

void MatchTypeBase::generateTwoRandomValues2(int &v1, int &v2, int max)
{
    auto rnd = QRandomGenerator::global();

    int randomPoints1 = 3;
    int randomPoints2 = 6;

    if(rnd->generate()%2)
    {
        v1 = randomPoints1;
        v2 = randomPoints2;
    }
    else
    {
        v2 = randomPoints1;
        v1 = randomPoints2;
    }
}

void MatchTypeBase::generateTwoRandomValues3(int &v1, int &v2, int max)
{
    auto rnd = QRandomGenerator::global();
    uint rndVal = rnd->generate();
    rndVal = rndVal % 12;

    int _v1, _v2;
    switch (rndVal) {
    case 0:  _v1 =  4; _v2 =  8; break;
    case 1:  _v1 =  6; _v2 =  2; break;
    case 2:  _v1 =  3; _v2 =  6; break;
    case 3:  _v1 =  1; _v2 = 10; break;
    case 4:  _v1 =  2; _v2 = 11; break;
    case 5:  _v1 =  5; _v2 =  3; break;
    case 6:  _v1 =  0; _v2 =  7; break;
    case 7:  _v1 =  3; _v2 =  8; break;
    case 8:  _v1 = 13; _v2 =  0; break;
    case 9:  _v1 =  4; _v2 =  9; break;
    case 10: _v1 =  3; _v2 =  6; break;
    case 11: _v1 =  2; _v2 = 11; break;
    default: _v1 =  0; _v2 =  1; break;
    }

    rndVal = rnd->generate();
    if(rndVal % 2)
    { v1 = _v1; v2 = _v2; }
    else
    { v1 = _v2; v2 = _v1; }
}

Team *MatchTypeBase::getTeamLeftQml() const
{
    return m_teamLeft.data();
}

Team *MatchTypeBase::getTeamRightQml() const
{
    return m_teamRight.data();
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
