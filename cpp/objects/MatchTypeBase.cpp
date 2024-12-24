#include "MatchTypeBase.h"

MatchTypeBase::MatchTypeBase(cTeamWPtr teamL, cTeamWPtr teamR, QObject *parent)
    : QObject{parent}
    , m_groupSelectionLeft{GroupSelectionPtr::create()}
    , m_groupSelectionRight{GroupSelectionPtr::create()}
    , m_groupMatchLeft{GroupMatchPtr::create()}
    , m_groupMatchRight{GroupMatchPtr::create()}
    , m_teamLeft{teamL}
    , m_teamRight{teamR}
{
    DOLT(this)

}

MatchTypeBase::~MatchTypeBase()
{
    DOLT(this)

}

void MatchTypeBase::initSelection()
{
    m_groupSelectionLeft->setGroupsCount(0);
    m_groupSelectionLeft->setMinPlayersInGroup(0);
    m_groupSelectionLeft->setMaxPlayersInGroup(0);
    if(m_teamLeft.isNull())
    {
        W("cannot set selection size for m_groupSelectionLeft due to teamLeft is null")
    }
    else
    {
        m_groupSelectionLeft->setSelectionSize(
            m_teamLeft.toStrongRef()->getPlayers().size());
    }

    m_groupSelectionRight->setGroupsCount(0);
    m_groupSelectionRight->setMinPlayersInGroup(0);
    m_groupSelectionRight->setMaxPlayersInGroup(0);
    if(m_teamRight.isNull())
    {
        W("cannot set selection size for m_groupSelectionRight due to teamRight is null")
    }
    else
    {
        m_groupSelectionRight->setSelectionSize(
            m_teamRight.toStrongRef()->getPlayers().size());
    }
}

void MatchTypeBase::initMatch()
{

}

QJsonObject MatchTypeBase::serialize() const
{
    return QJsonObject();
}

void MatchTypeBase::deserialize(const QJsonObject &jTeam)
{
    this->clear(false);

}

void MatchTypeBase::clear(bool emitting)
{

}

bool MatchTypeBase::verifySelection(QString &message)
{
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
