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
    return QJsonObject();
}

void GroupMatch::deserialize(const QJsonObject &jGroupMatch)
{
    this->clear(false);
}

void GroupMatch::clear(bool emitting)
{

}

bool GroupMatch::verify(QString &message)
{
    return true;
}
