#include "MatchTypeBase.h"

MatchTypeBase::MatchTypeBase(QObject *parent)
    : QObject{parent}
{
    DOLT(this)

}

MatchTypeBase::~MatchTypeBase()
{
    DOLT(this)

}

QJsonObject MatchTypeBase::serialize() const
{
    return QJsonObject();
}

void MatchTypeBase::deserialize(const QJsonObject &jTeam)
{

}

void MatchTypeBase::clear(bool emitting)
{

}

bool MatchTypeBase::verifySelection(QString &message)
{
    return true;
}

bool MatchTypeBase::verifyMatch(QString &message)
{
    return true;
}
