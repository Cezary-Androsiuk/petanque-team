#include "GroupMatch.h"

GroupMatch::GroupMatch(QObject *parent)
    : QObject{parent}
{
    DOLT(this)

}

    GroupMatch::~GroupMatch()
{
    DOLT(this)
}

QJsonObject GroupMatch::serialize() const
{

}

void GroupMatch::deserialize(const QJsonObject &jTeam)
{

}

void GroupMatch::clear(bool emitting)
{

}
