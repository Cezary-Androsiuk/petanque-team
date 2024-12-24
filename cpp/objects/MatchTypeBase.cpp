#include "MatchTypeBase.h"

MatchTypeBase::MatchTypeBase(const TeamWPtr &tl, const TeamWPtr &tr, QObject *parent)
    : QObject{parent}
    , m_groupSelectionLeft{GroupSelectionPtr::create(tl)}
    , m_groupSelectionRight{GroupSelectionPtr::create(tr)}
    , m_groupMatchLeft{GroupMatchPtr::create(tl)}
    , m_groupMatchRight{GroupMatchPtr::create(tr)}
{
    DOLT(this)

}

MatchTypeBase::~MatchTypeBase()
{
    DOLT(this)

}

void MatchTypeBase::initSelection()
{

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
