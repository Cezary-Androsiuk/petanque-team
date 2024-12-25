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
        W("cannot set selection size for m_groupSelectionLeft due to teamLeft is null")
    }
    else
    {
        m_groupSelectionLeft->setSelectionSize(
            m_teamLeft.toStrongRef()->getPlayers().size());
    }

    m_groupSelectionRight = GroupSelectionPtr::create(
        m_groupsCount, m_minPlayersInGroup, m_maxPlayersInGroup);
    if(m_teamRight.isNull())
    {
        W("cannot set selection size for m_groupSelectionRight due to teamRight is null")
    }
    else
    {
        m_groupSelectionRight->setSelectionSize(
            m_teamRight.toStrongRef()->getPlayers().size());
    }

    emit this->selectionChanged();
}

void MatchTypeBase::initMatch()
{
    qDebug() <<"about to create left match"<< m_groupMatchLeft << "for:"<<this;
    m_groupMatchLeft = GroupMatchPtr::create();
    qDebug() <<"created left match"<< m_groupMatchLeft;

    m_groupMatchRight = GroupMatchPtr::create();

    emit this->matchChanged();
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
    qDebug() << "trying to access left match" << m_groupMatchLeft << "for:"<<this;

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
