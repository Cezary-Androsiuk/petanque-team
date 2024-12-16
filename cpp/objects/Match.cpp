#include "Match.h"

Match::Match(QObject *parent)
    : QObject{parent}
{
    DOLT(this)

}

Match::~Match()
{
    DOLT(this)
}

QJsonObject Match::serialize() const
{

}

void Match::deserialize(const QJsonObject &jTeam)
{

}

void Match::clear(bool emitting)
{

}
