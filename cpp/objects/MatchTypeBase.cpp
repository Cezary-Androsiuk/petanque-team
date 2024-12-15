#include "MatchTypeBase.h"

MatchTypeBase::MatchTypeBase(QObject *parent)
    : QObject{parent}
{}

QJsonObject MatchTypeBase::serialize() const
{

}

void MatchTypeBase::deserialize(const QJsonObject &jTeam)
{

}

void MatchTypeBase::clear(bool emitting)
{

}

bool MatchTypeBase::verifySelection(QString &message)
{

}

bool MatchTypeBase::verifyMatch(QString &message)
{

}
